#ifndef IPAGE_H
#define IPAGE_H

#include "context.h"
#include "id.h"

namespace Core {
class FEEM_CORE_EXPORT IPage : public IContext
{
    Q_OBJECT
public:
    IPage(QObject* parent = nullptr);
    ~IPage() override;

    QString displayName() const {return m_displayName;}
    int priority() const {return m_priority;}
    Id id() const {return m_id;}
    bool isEnabled() const {return m_isEnabled;}

    void setEnabled(bool enabled);
    void setDispalyName(const QString &displayName) {m_displayName = displayName;}
    void setPriority(int priority) {m_priority = priority;}
    void setId(Id id) {m_id = id;}
private:
    QString m_displayName;
    int m_priority = -1;
    Id m_id;
    bool m_isEnabled = true;
};
}//namespace Core

#endif // IPAGE_H
