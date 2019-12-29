#include "pf_projectaccessor.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QRegExp>

namespace Utils {

/**
 * @brief
 *
 * @param docType
 * @param displayName
 * @param applicationDisplayName
 */
PF_ProjectAccessor::PF_ProjectAccessor(const QString& docType,
                                       const QString& displayName,
                                       const QString& applicationDisplayName)
    :docType(docType),
     displayName(displayName),
     applicationDisplayName(applicationDisplayName)
{

}

/**
 * @brief 从硬盘当中读取project
 *
 * @param parent 主要用来弹出对话框
 * @return QVariantMap
 */
QVariantMap PF_ProjectAccessor::restoreProject(QWidget* parent) const
{
    if(m_baseFilePath.isEmpty())
        return QVariantMap();
    return restoreProject(m_baseFilePath,parent);
}

/**
 * @brief 将data保存到硬盘，
 *
 * @param data
 * @param parent
 * @return bool
 */
bool PF_ProjectAccessor::saveProject(const QVariantMap& data, QWidget* parent) const
{
    const bool result = writeData(m_baseFilePath, data, parent);

//    const ProceedInfo pi = result ? reportIssues(result.value(), m_baseFilePath, parent) : ProceedInfo::Continue;
    return result/*pi == ProceedInfo::Continue*/;
}
/**
 * @brief 从硬盘当中读取数据
 *
 * @param path
 * @param parent
 */
PF_ProjectAccessor::RestoreData PF_ProjectAccessor::readData(const FileName& path, QWidget* parent) const
{
    Q_UNUSED(parent);
    RestoreData result = readFile(path);
    if (!result.data.isEmpty())
        result.data = preprocessReadProject(result.data);
    return result;
}

/**
 * @brief 将data写入到path中
 *
 * @param path
 * @param data
 * @param parent
 * @return bool
 */
bool PF_ProjectAccessor::writeData(const FileName& path, const QVariantMap& data, QWidget* parent) const
{
    Q_UNUSED(parent);
    return writeFile(path, prepareToWriteProject(data));
}

/**
 * @brief restoreProject的一个重载
 *
 * @param settingsPath
 * @param parent
 * @return QVariantMap
 */
QVariantMap PF_ProjectAccessor::restoreProject(const FileName& settingsPath, QWidget* parent) const
{
    const RestoreData result = readData(settingsPath, parent);

//    const ProceedInfo pi = result.hasIssue() ? reportIssues(result.issue.value(), result.path, parent)
//                                             : ProceedInfo::Continue;
    return /*pi == ProceedInfo::DiscardAndContinue ? QVariantMap() :*/ result.data;
}
/*!
 * This method is called right after reading data from disk and modifies \a data.
 */
QVariantMap PF_ProjectAccessor::preprocessReadProject(const QVariantMap& data) const
{
    return data;
}
/*!
 * This method is called right before writing data to disk and modifies \a data.
 */
QVariantMap PF_ProjectAccessor::prepareToWriteProject(const QVariantMap& data) const
{
    return data;
}

/**
 * @brief 从硬盘当中读取数据，并进行保存。
 *
 * @param path
 * @return PF_ProjectAccessor::RestoreData
 */
PF_ProjectAccessor::RestoreData PF_ProjectAccessor::readFile(const FileName& path) const
{
    PersistentSettingsReader reader;
    /** 文件错误 **/
    if (!reader.load(path.fileName())) {
        qDebug()<<"Error open "<<path.fileName();
        return RestoreData();
    }

    /** 将数据保存到writer中 **/
    const QVariantMap data = reader.restoreValues();
    if (!m_readOnly && path == m_baseFilePath) {
        if (!m_writer)
            m_writer = std::make_unique<PersistentSettingsWriter>(m_baseFilePath, docType);
        m_writer->setContents(data);
    }

    return RestoreData(path, data);
}

/**
 * @brief 将data写入到文件path中
 *
 * @param path
 * @param data
 * @return bool
 */
bool PF_ProjectAccessor::writeFile(const FileName& path, const QVariantMap& data) const
{
    /** 数据为空 **/
    if (data.isEmpty()) {
        return false;
    }

    QString errorMessage;
    if (!m_readOnly && (!m_writer || m_writer->fileName() != path.fileName()))
        m_writer = std::make_unique<PersistentSettingsWriter>(path.fileName(), docType);

    if (!m_writer->save(data, &errorMessage)) {
        return false;
    }
    return true;
}




}// Utils
