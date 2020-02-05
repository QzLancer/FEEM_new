#ifndef PERSISTENTSETTINGS_H
#define PERSISTENTSETTINGS_H

#include "utils_global.h"

#include <QVariant>

class FEEM_UTILS_EXPORT PersistentSettingsReader
{
public:
    PersistentSettingsReader();
    QVariant restoreValue(const QString &variable, const QVariant &defaultValue = QVariant()) const;
    QVariantMap restoreValues() const;
    bool load(const QString &fileName);
private:
    QMap<QString, QVariant> m_valueMap;
};

class FEEM_UTILS_EXPORT PersistentSettingsWriter
{
public:
    PersistentSettingsWriter(const QString &fileName, const QString &docType);
    ~PersistentSettingsWriter();

    bool save(const QVariantMap &data, QString *errorString) const;

    QString fileName() const;

    void setContents(const QVariantMap &data);

private:
    bool write(const QVariantMap &data, QString *errorString) const;

    const QString m_fileName;
    const QString m_docType;
    mutable QMap<QString, QVariant> m_savedData;
};

#endif // PERSISTENTSETTINGS_H
