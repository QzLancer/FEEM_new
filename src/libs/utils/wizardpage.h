#pragma once

#include "utils_global.h"

#include <QSet>
#include <QString>
#include <QWizardPage>

#include <functional>

namespace Utils {

class Wizard;
namespace Internal {

class FEEM_UTILS_EXPORT ObjectToFieldWidgetConverter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY textChanged)

public:
    template <class T, typename... Arguments>
    static ObjectToFieldWidgetConverter *create(T *sender, void (T::*member)(Arguments...), const std::function<QString()> &toTextFunction)
    {
        auto widget = new ObjectToFieldWidgetConverter();
        widget->toTextFunction = toTextFunction;
        connect(sender, &QObject::destroyed, widget, &QObject::deleteLater);
        connect(sender, member, widget, [widget] () {
            emit widget->textChanged(widget->text());
        });
        return widget;
    }

signals:
    void textChanged(const QString&);

private:
    ObjectToFieldWidgetConverter () = default;

    // is used by the property text
    QString text() {return toTextFunction();}
    std::function<QString()> toTextFunction;
};

} // Internal

class FEEM_UTILS_EXPORT WizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WizardPage(QWidget *parent = nullptr);

    virtual void pageWasAdded(); // called when this page was added to a Utils::Wizard

    template<class T, typename... Arguments>
    void registerObjectAsFieldWithName(const QString &name, T *sender, void (T::*changeSignal)(Arguments...),
        const std::function<QString()> &senderToString)
    {
        registerFieldWithName(name, Internal::ObjectToFieldWidgetConverter::create(sender, changeSignal, senderToString), "text", SIGNAL(textChanged(QString)));
    }

    void registerFieldWithName(const QString &name, QWidget *widget,
                               const char *property = nullptr, const char *changedSignal = nullptr);

    virtual bool handleReject();
    virtual bool handleAccept();

signals:
    // Emitted when there is something that the developer using this page should be aware of.
    void reportError(const QString &errorMessage);

private:
    void registerFieldName(const QString &name);

    QSet<QString> m_toRegister;
};

} // namespace Utils
