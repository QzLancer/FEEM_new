#ifndef PF_PROJECTACCESSOR_H
#define PF_PROJECTACCESSOR_H

#include "utils_global.h"
#include "persistentsettings.h"
#include "fileutils.h"

#include <QHash>
#include <QMessageBox>
#include <QVariantMap>

#include <memory>

namespace Utils {

/**
 * @brief 可以处理project文件，这个类顶层的通用的。针对各个project可能要单独实现。
 *
 */
class FEEM_UTILS_EXPORT PF_ProjectAccessor
{
public:
    PF_ProjectAccessor(const QString &docType, const QString &displayName,
                       const QString &applicationDisplayName);
    virtual ~PF_ProjectAccessor() = default;

    enum ProceedInfo { Continue, DiscardAndContinue };
    using ButtonMap = QHash<QMessageBox::StandardButton, ProceedInfo>;
    class Issue {
    public:
        enum class Type { ERROR, WARNING };
        Issue(const QString &title, const QString &message, const Type type) :
            title{title}, message{message}, type{type}
        { }

        QMessageBox::StandardButtons allButtons() const;

        QString title;
        QString message;
        Type type;
        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
        QMessageBox::StandardButton escapeButton = QMessageBox::Ok;
        QHash<QMessageBox::StandardButton, ProceedInfo> buttons = {{QMessageBox::Ok, ProceedInfo::Continue}};
    };

    class RestoreData {
    public:
        RestoreData() = default;
        RestoreData(const FileName &path, const QVariantMap &data) : path{path}, data{data} { }
//        RestoreData(const QString &title, const QString &message, const Issue::Type type) :
//            RestoreData(Issue(title, message, type))
//        { }
//        RestoreData(const Issue &issue) : issue{issue} { }

        bool hasIssue() const { return false;/*bool(issue);*/ }
        bool hasError() const { return hasIssue() /*&& issue.value().type == Issue::Type::ERROR*/; }
        bool hasWarning() const { return hasIssue() /*&& issue.value().type == Issue::Type::WARNING*/; }

        FileName path;
        QVariantMap data;
//        Issue issue;
    };

    QVariantMap restoreProject(QWidget *parent) const;
    bool saveProject(const QVariantMap &data, QWidget *parent) const;

    const QString docType;
    const QString displayName;
    const QString applicationDisplayName;

    void setBaseFilePath(const FileName &baseFilePath) { m_baseFilePath = baseFilePath; }
    void setReadOnly() { m_readOnly = true; }
    FileName baseFilePath() const { return m_baseFilePath; }

    virtual RestoreData readData(const FileName &path, QWidget *parent) const;
    virtual /*optional<Issue>*/bool writeData(const FileName &path, const QVariantMap &data, QWidget *parent) const;

protected:
    // Report errors:
    QVariantMap restoreProject(const FileName &settingsPath, QWidget *parent) const;
//    ProceedInfo reportIssues(const Issue &issue, const FileName &path, QWidget *parent) const;

    virtual QVariantMap preprocessReadProject(const QVariantMap &data) const;
    virtual QVariantMap prepareToWriteProject(const QVariantMap &data) const;

    virtual RestoreData readFile(const FileName &path) const;
    virtual /*optional<Issue>*/bool writeFile(const FileName &path, const QVariantMap &data) const;

private:
    FileName m_baseFilePath;
    mutable std::unique_ptr<PersistentSettingsWriter> m_writer;
    bool m_readOnly = false;
};
}// Utils
#endif // PF_PROJECTACCESSOR_H
