#pragma once

#include "coreplugin/core_global.h"
#include "coreplugin/constants.h"
#include "coreplugin/context.h"
#include "coreplugin/actionmanager/command.h"

#include <QObject>
#include <QList>

QT_BEGIN_NAMESPACE
class QAction;
class QString;
QT_END_NAMESPACE

namespace Core {

class ActionContainer;
class Command;
class Context;

//namespace Internal {
//class CorePlugin;
//class MainWindow;
//} // Internal

class FEEM_CORE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager *instance();

    static ActionContainer *createMenu(Id id);
    static ActionContainer *createMenuBar(Id id);
    static ActionContainer* createRibbonBar(Id id);
    static ActionContainer* createRibbonPage(Id id);
    static ActionContainer* createRibbonGroup(Id id);

    static Command *registerAction(QAction *action, Id id,
                                   const Context &context = Context(Constants::C_GLOBAL),
                                   bool scriptable = false);

    static Command *command(Id id);
    static ActionContainer *actionContainer(Id id);

    static QList<Command *> commands();

    static void unregisterAction(QAction *action, Id id);

    static void setPresentationModeEnabled(bool enabled);
    static bool isPresentationModeEnabled();

    static QString withNumberAccelerator(const QString &text, const int number);

signals:
    void commandListChanged();
    void commandAdded(Id id);

public:
    ActionManager(QObject *parent = nullptr);
    ~ActionManager() override;
    static void saveSettings();
    static void setContext(const Context &context);

    friend class coreApp;
    friend class MainWindow;
};

} // namespace Core
