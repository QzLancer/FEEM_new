#include "persistentsettings.h"

#include <QDebug>
#include <QDir>
#include <QStack>
#include <QXmlStreamAttributes>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
#include <QTextStream>
#include <QRegExp>
#include <QRect>
#include <QCoreApplication>

// Read and write rectangle in X11 resource syntax "12x12+4+3"
static QString rectangleToString(const QRect &r)
{
    QString result;
    QTextStream(&result) << r.width() << 'x' << r.height() << forcesign << r.x() << r.y();
    return result;
}

static QRect stringToRectangle(const QString &v)
{
    static QRegExp pattern(QLatin1String("(\\d+)x(\\d+)([-+]\\d+)([-+]\\d+)"));
    Q_ASSERT(pattern.isValid());
    return pattern.exactMatch(v) ?
        QRect(QPoint(pattern.cap(3).toInt(), pattern.cap(4).toInt()),
              QSize(pattern.cap(1).toInt(), pattern.cap(2).toInt())) :
        QRect();
}

/**
 * @brief 定义一些XML当中出现的节点以及属性的名称
 *
 */
struct Context
{
    Context() {}
    const QString rootElement = QString("FEEM");
    const QString dataElement = QString("data");
    const QString variableElement = QString("variable");
    const QString typeAttribute = QString("type");
    const QString valueElement = QString("value");
    const QString valueListElement = QString("valuelist");
    const QString valueMapElement = QString("valuemap");
    const QString keyAttribute = QString("key");
};


/**
 * @brief 保存从文件中读取的条目
 *
 */
struct ParseValueStackEntry
{
    explicit ParseValueStackEntry(QVariant::Type t = QVariant::Invalid, const QString &k = QString()) : type(t), key(k) {}
    explicit ParseValueStackEntry(const QVariant &aSimpleValue, const QString &k);

    QVariant value() const;
    void addChild(const QString &key, const QVariant &v);

    QVariant::Type type;
    QString key;
    QVariant simpleValue;
    QVariantList listValue;
    QVariantMap mapValue;
};

ParseValueStackEntry::ParseValueStackEntry(const QVariant &aSimpleValue, const QString &k)
    : type(aSimpleValue.type())
    , key(k)
    , simpleValue(aSimpleValue)
{
    //    QTC_ASSERT(simpleValue.isValid(), return);
}

QVariant ParseValueStackEntry::value() const
{
    switch (type) {
    case QVariant::Invalid:
        return QVariant();
    case QVariant::Map:
        return QVariant(mapValue);
    case QVariant::List:
        return QVariant(listValue);
    default:
        break;
    }
    return simpleValue;
}

void ParseValueStackEntry::addChild(const QString &key, const QVariant &v)
{
    switch (type) {
    case QVariant::Map:
        mapValue.insert(key, v);
        break;
    case QVariant::List:
        listValue.push_back(v);
        break;
    default:
        qWarning() << "ParseValueStackEntry::Internal error adding " << key << v << " to "
                   << QVariant::typeToName(type) << value();
        break;
    }
}


/**
 * @brief 解析读取的XML文件内容
 *
 */
class ParseContext : public Context
{
public:
    QVariantMap parse(QFile &file);

private:
    enum Element {
        RootElement,
        DataElement,
        VariableElement,
        SimpleValueElement,
        ListValueElement,
        MapValueElement,
        UnknownElement
    };

    Element element(const QStringRef &r) const;
    static inline bool isValueElement(Element e)
    { return e == SimpleValueElement || e == ListValueElement || e == MapValueElement; }
    QVariant readSimpleValue(QXmlStreamReader &r, const QXmlStreamAttributes &attributes) const;

    bool handleStartElement(QXmlStreamReader &r);
    bool handleEndElement(const QStringRef &name);

    static QString formatWarning(const QXmlStreamReader &r, const QString &message);

    QStack<ParseValueStackEntry> m_valueStack;
    QVariantMap m_result;
    QString m_currentVariableName;
};


/**
 * @brief XML解析器，读取的思路是建立一个while循环，
 * 先寻找StartElement，将结果保存在栈当中，然后继续
 * 读到EndElement时，将数据保存，并让数据出栈。需要
 * 想办法，让这个类能够支持更多的节点名称。
 *
 * @param file
 * @return QVariantMap
 */
QVariantMap ParseContext::parse(QFile &file)
{
    QXmlStreamReader r(&file);

    m_result.clear();
    m_currentVariableName.clear();

    while (!r.atEnd()) {
        switch (r.readNext()) {
        case QXmlStreamReader::StartElement:
            if (handleStartElement(r))
                return m_result;
            break;
        case QXmlStreamReader::EndElement:
            if (handleEndElement(r.name()))
                return m_result;
            break;
        case QXmlStreamReader::Invalid:
            qWarning("Error reading %s:%d: %s", qPrintable(file.fileName()),
                     int(r.lineNumber()), qPrintable(r.errorString()));
            return QVariantMap();
        default:
            break;
        } // switch token
    } // while (!r.atEnd())
    return m_result;
}


/**
 * @brief 读取到StartElement后的处理动作，暂时将数据保存。
 *
 * @param r
 * @return bool
 */
bool ParseContext::handleStartElement(QXmlStreamReader &r)
{
    const QStringRef name = r.name();
    const Element e = element(name);
    if (e == VariableElement) {
        m_currentVariableName = r.readElementText();
        return false;
    }
    if (!ParseContext::isValueElement(e))
        return false;

    const QXmlStreamAttributes attributes = r.attributes();
    const QString key = attributes.hasAttribute(keyAttribute) ?
                attributes.value(keyAttribute).toString() : QString();
    switch (e) {
    case SimpleValueElement: {
        // This reads away the end element, so, handle end element right here.
        const QVariant v = readSimpleValue(r, attributes);
        if (!v.isValid()) {
            qWarning() << ParseContext::formatWarning(r, QString::fromLatin1("Failed to read element \"%1\".").arg(name.toString()));
            return false;
        }
        m_valueStack.push_back(ParseValueStackEntry(v, key));
        return handleEndElement(name);
    }
    case ListValueElement:
        m_valueStack.push_back(ParseValueStackEntry(QVariant::List, key));
        break;
    case MapValueElement:
        m_valueStack.push_back(ParseValueStackEntry(QVariant::Map, key));
        break;
    default:
        break;
    }
    return false;
}


/**
 * @brief 读取到EndElement后的处理动作，将数据按顺序保存到结果中。
 *
 * @param name
 * @return bool
 */
bool ParseContext::handleEndElement(const QStringRef &name)
{
    const Element e = element(name);
    if (ParseContext::isValueElement(e)) {
        if(m_valueStack.isEmpty())
            return true;
        const ParseValueStackEntry top = m_valueStack.pop();
        if (m_valueStack.isEmpty()) { // Last element? -> Done with that variable.
            if(m_currentVariableName.isEmpty())
                return true;
            m_result.insert(m_currentVariableName, top.value());
            m_currentVariableName.clear();
            return false;
        }
        m_valueStack.top().addChild(top.key, top.value());
    }
    return e == RootElement;
}

QString ParseContext::formatWarning(const QXmlStreamReader &r, const QString &message)
{
    QString result = QLatin1String("Warning reading ");
    if (const QIODevice *device = r.device())
        if (const auto file = qobject_cast<const QFile *>(device))
            result += QDir::toNativeSeparators(file->fileName()) + QLatin1Char(':');
    result += QString::number(r.lineNumber());
    result += QLatin1String(": ");
    result += message;
    return result;
}

ParseContext::Element ParseContext::element(const QStringRef &r) const
{
    if (r == valueElement)
        return SimpleValueElement;
    if (r == valueListElement)
        return ListValueElement;
    if (r == valueMapElement)
        return MapValueElement;
    if (r == rootElement)
        return RootElement;
    if (r == dataElement)
        return DataElement;
    if (r == variableElement)
        return VariableElement;
    return UnknownElement;
}

QVariant ParseContext::readSimpleValue(QXmlStreamReader &r, const QXmlStreamAttributes &attributes) const
{
    // Simple value
    const QStringRef type = attributes.value(typeAttribute);
    const QString text = r.readElementText();
    if (type == QLatin1String("QChar")) { // Workaround: QTBUG-12345
        if(!(text.size() == 1))
            return QVariant();
        return QVariant(QChar(text.at(0)));
    }
    if (type == QLatin1String("QRect")) {
        const QRect rectangle = stringToRectangle(text);
        return rectangle.isValid() ? QVariant(rectangle) : QVariant();
    }
    QVariant value;
    value.setValue(text);
    value.convert(QMetaType::type(type.toLatin1().data()));
    return value;
}
/**
 * @brief 从XML文件当中读取自定义嵌套数据结构QVariantMap。
 *
 */
PersistentSettingsReader::PersistentSettingsReader() = default;

QVariant PersistentSettingsReader::restoreValue(const QString &variable, const QVariant &defaultValue) const
{
    if (m_valueMap.contains(variable))
        return m_valueMap.value(variable);
    return defaultValue;
}

QVariantMap PersistentSettingsReader::restoreValues() const
{
    return m_valueMap;
}


/**
 * @brief 读入XML文件，并将读取的数据保存。
 *
 * @param fileName
 * @return bool
 */
bool PersistentSettingsReader::load(const QString &fileName)
{
    m_valueMap.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    ParseContext ctx;
    m_valueMap = ctx.parse(file);
    file.close();
    return true;
}

static void writeVariantValue(QXmlStreamWriter &w, const Context &ctx,
                              const QVariant &variant, const QString &key = QString())
{
    switch (static_cast<int>(variant.type())) {
    case static_cast<int>(QVariant::StringList):
    case static_cast<int>(QVariant::List):
        w.writeStartElement(ctx.valueListElement);
        w.writeAttribute(ctx.typeAttribute, QLatin1String(QVariant::typeToName(QVariant::List)));
        if (!key.isEmpty())
            w.writeAttribute(ctx.keyAttribute, key);
        foreach (const QVariant &var, variant.toList())
            writeVariantValue(w, ctx, var);
        w.writeEndElement();
        break;
    case static_cast<int>(QVariant::Map): {
        w.writeStartElement(ctx.valueMapElement);
        w.writeAttribute(ctx.typeAttribute, QLatin1String(QVariant::typeToName(QVariant::Map)));
        if (!key.isEmpty())
            w.writeAttribute(ctx.keyAttribute, key);
        const QVariantMap varMap = variant.toMap();
        const QVariantMap::const_iterator cend = varMap.constEnd();
        for (QVariantMap::const_iterator i = varMap.constBegin(); i != cend; ++i)
            writeVariantValue(w, ctx, i.value(), i.key());
        w.writeEndElement();
    }
        break;
    case static_cast<int>(QMetaType::QObjectStar): // ignore QObjects!
    case static_cast<int>(QMetaType::VoidStar): // ignore void pointers!
        break;
    default:
        w.writeStartElement(ctx.valueElement);
        w.writeAttribute(ctx.typeAttribute, QLatin1String(variant.typeName()));
        if (!key.isEmpty())
            w.writeAttribute(ctx.keyAttribute, key);
        switch (variant.type()) {
        case QVariant::Rect:
            w.writeCharacters(rectangleToString(variant.toRect()));
            break;
        default:
            w.writeCharacters(variant.toString());
            break;
        }
        w.writeEndElement();
        break;
    }
}


/**
 * @brief 将自定义的数据类型写入XML文件
 *
 * @param fileName
 * @param docType
 */
PersistentSettingsWriter::PersistentSettingsWriter(const QString &fileName, const QString &docType)
    : m_fileName(fileName)
    , m_docType(docType)
{

}

PersistentSettingsWriter::~PersistentSettingsWriter()
{
    write(m_savedData, nullptr);
}

bool PersistentSettingsWriter::save(const QVariantMap &data, QString *errorString) const
{
    if (data == m_savedData)
        return true;
    return write(data, errorString);
}

QString PersistentSettingsWriter::fileName() const
{
    return m_fileName;
}

/** * @brief Set contents of file (e.g. from data read from it). */
void PersistentSettingsWriter::setContents(const QVariantMap &data)
{
    m_savedData = data;
}

bool PersistentSettingsWriter::write(const QVariantMap &data, QString *errorString) const
{
    QDir tmp;
    tmp.mkpath(QFileInfo(m_fileName).path());

    QFile *saver = new QFile{m_fileName};
    if (!saver->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString err = QFile::exists(m_fileName) ?
                QObject::tr("Cannot overwrite file %1: %2") : QObject::tr("Cannot create file %1: %2");
        qDebug()<<err.arg(QDir::toNativeSeparators(m_fileName), saver->errorString());;
        return false;
    }else{
        const Context ctx;
        QXmlStreamWriter w(saver);
        w.setAutoFormatting(true);
        w.setAutoFormattingIndent(1); // Historical, used to be QDom.
        w.writeStartDocument();
        w.writeDTD(QLatin1String("<!DOCTYPE ") + m_docType + QLatin1Char('>'));
        w.writeComment(QString::fromLatin1(" Written by %1 %2, %3. ").
                       arg(QCoreApplication::applicationName(),
                           QCoreApplication::applicationVersion(),
                           QDateTime::currentDateTime().toString(Qt::ISODate)));
        w.writeStartElement(ctx.rootElement);
        const QVariantMap::const_iterator cend = data.constEnd();
        for (QVariantMap::const_iterator it =  data.constBegin(); it != cend; ++it) {
            w.writeStartElement(ctx.dataElement);
            w.writeTextElement(ctx.variableElement, it.key());
            writeVariantValue(w, ctx, it.value());
            w.writeEndElement();
        }
        w.writeEndDocument();

//        saver.setResult(&w);
    }
    bool ok = true;
    saver->close();
    if (ok) {
        m_savedData = data;
    } else if (errorString) {
        m_savedData.clear();
        *errorString = saver->errorString();
    }

    return ok;
}
