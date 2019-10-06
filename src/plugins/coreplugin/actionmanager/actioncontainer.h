#pragma once

#include "coreplugin/core_global.h"
//#include "coreplugin/icontext.h"

#include <QObject>

#include "coreplugin/id.h"
#include "coreplugin/context.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
class QAction;
QT_END_NAMESPACE
namespace Qtitan {
class RibbonBar;
class RibbonPage;
class RibbonGroup;
}
namespace Core {

class Command;

class CORE_EXPORT ActionContainer : public QObject
{
    Q_OBJECT

public:
    enum OnAllDisabledBehavior {
        Disable,
        Hide,
        Show
    };

    virtual void setOnAllDisabledBehavior(OnAllDisabledBehavior behavior) = 0;
    virtual ActionContainer::OnAllDisabledBehavior onAllDisabledBehavior() const = 0;

    virtual Id id() const = 0;

    virtual QMenu *menu() const = 0;
    virtual QMenuBar *menuBar() const = 0;
    virtual Qtitan::RibbonBar* ribbonBar() const = 0;
    virtual Qtitan::RibbonPage* ribbonPage() const = 0;
    virtual Qtitan::RibbonGroup* ribbonGroup() const = 0;

    virtual QAction *insertLocation(Id group) const = 0;
    virtual void appendGroup(Id group) = 0;
    virtual void insertGroup(Id before, Id group) = 0;
    virtual void addAction(Command *action, Id group = Id()) = 0;
    virtual void addMenu(ActionContainer *menu, Id group = Id()) = 0;
    virtual void addMenu(ActionContainer *before, ActionContainer *menu, Id group = Id()) = 0;
    virtual void addRibbonPage(ActionContainer *page, Id group = Id()) = 0;
    virtual void addRibbonPage(ActionContainer *before, ActionContainer *page, Id group = Id()) = 0;
    virtual void addRibbonGroup(ActionContainer *rgroup, Id group = Id()) = 0;
    virtual void addRibbonGroup(ActionContainer *before, ActionContainer *rgroup, Id group = Id()) = 0;
    Command *addSeparator(Id group = Id());
    virtual Command *addSeparator(const Context &context, Id group = Id(), QAction **outSeparator = nullptr) = 0;

    /** 这会从所有操作和子菜单中清除此菜单和子菜单。
     它不会破坏子菜单和命令，只是将它们从父母身上移除。**/
    virtual void clear() = 0;
};

} // namespace Core
