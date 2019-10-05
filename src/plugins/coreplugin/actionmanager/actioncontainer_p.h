#pragma once

#include "actionmanager_p.h"

#include "actioncontainer.h"
#include "command.h"

namespace Core {
//namespace Internal {

struct Group
{
    Group(Id id) : id(id) {}
    Id id;
    QList<QObject *> items; // Command * or ActionContainer *
};

/**
 * @brief 作为一个中间类，过渡作用，只是作为一个容器，和控件不挂钩。
 *
 */
class ActionContainerPrivate : public ActionContainer
{
    Q_OBJECT

public:
    ActionContainerPrivate(Id id);
    ~ActionContainerPrivate() override = default;

    void setOnAllDisabledBehavior(OnAllDisabledBehavior behavior) override;
    ActionContainer::OnAllDisabledBehavior onAllDisabledBehavior() const override;

    QAction *insertLocation(Id groupId) const override;
    void appendGroup(Id id) override;
    void insertGroup(Id before, Id groupId) override;
    void addAction(Command *action, Id group = Id()) override;
    void addMenu(ActionContainer *menu, Id groupId = Id()) override;
    void addMenu(ActionContainer *before, ActionContainer *menu, Id groupId = Id()) override;
    void addRibbonPage(ActionContainer *page, Id groupId = Id()) override;
    void addRibbonPage(ActionContainer *before, ActionContainer *page, Id groupId = Id()) override;
    void addRibbonGroup(ActionContainer *group, Id groupId = Id()) override;
    void addRibbonGroup(ActionContainer *before, ActionContainer *group, Id groupId = Id()) override;
    Command *addSeparator(const Context &context, Id group = Id(), QAction **outSeparator = nullptr) override;
    void clear() override;

    Id id() const override;

    QMenu *menu() const override;
    QMenuBar *menuBar() const override;
    Qtitan::RibbonBar* ribbonBar() const override;
    Qtitan::RibbonPage* ribbonPage() const override;
    Qtitan::RibbonGroup* ribbonGroup() const override;

    virtual void insertAction(QAction *before, QAction *action) = 0;
    virtual void insertMenu(QAction *before, QMenu *menu) = 0;
    virtual void insertRibbonPage(int index, Qtitan::RibbonPage* page) = 0;
    virtual void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) = 0;

    virtual void removeAction(QAction *action) = 0;
    virtual void removeMenu(QMenu *menu) = 0;

    virtual bool updateInternal() = 0;

protected:
    bool canAddAction(Command *action) const;
    bool canAddMenu(ActionContainer *menu) const;
    virtual bool canBeAddedToMenu() const = 0;
    virtual bool canBeAddedToRibbonBar() const = 0;
    virtual bool canBeAddedToPage() const = 0;

    // groupId --> list of Command* and ActionContainer*
    QList<Group> m_groups;

private:
    void scheduleUpdate();
    void update();
    void itemDestroyed();

    QList<Group>::const_iterator findGroup(Id groupId) const;
    QAction *insertLocation(QList<Group>::const_iterator group) const;

    OnAllDisabledBehavior m_onAllDisabledBehavior;
    Id m_id;
    bool m_updateRequested;
};

class MenuActionContainer : public ActionContainerPrivate
{
public:
    explicit MenuActionContainer(Id id);
    ~MenuActionContainer() override;

    QMenu *menu() const override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;
    void insertRibbonPage(int index, Qtitan::RibbonPage* page) override;
    void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

protected:
    bool canBeAddedToMenu() const override;
    bool canBeAddedToRibbonBar() const override;
    bool canBeAddedToPage() const override;
    bool updateInternal() override;

private:
    QPointer<QMenu> m_menu;
};

class MenuBarActionContainer : public ActionContainerPrivate
{
public:
    explicit MenuBarActionContainer(Id id);

    void setMenuBar(QMenuBar *menuBar);
    QMenuBar *menuBar() const override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;
    void insertRibbonPage(int index, Qtitan::RibbonPage* page) override;
    void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

protected:
    bool canBeAddedToMenu() const override;
    bool canBeAddedToRibbonBar() const override;
    bool canBeAddedToPage() const override;
    bool updateInternal() override;

private:
    QMenuBar *m_menuBar;
};

/**
 * @brief 要构造出RibbonBar控件，只实现必要的部分。
 *
 */
class RibbonBarActionContainer : public ActionContainerPrivate
{
public:
    explicit RibbonBarActionContainer(Id id);

    void setRibbonBar(Qtitan::RibbonBar *ribbonBar);
    Qtitan::RibbonBar *ribbonBar() const override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;
    void insertRibbonPage(int index, Qtitan::RibbonPage* page) override;
    void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

protected:
    bool canBeAddedToMenu() const override;
    bool canBeAddedToRibbonBar() const override;
    bool canBeAddedToPage() const override;
    bool updateInternal() override;

private:
    Qtitan::RibbonBar *m_ribbonBar;
};

/**
 * @brief 保存RibbonPage的container，通过AM进行创建。
 *
 */
class RibbonPageActionContainer : public ActionContainerPrivate
{
public:
    explicit RibbonPageActionContainer(Id id);
    ~RibbonPageActionContainer() override;

    Qtitan::RibbonPage *ribbonPage() const override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;
    void insertRibbonPage(int index, Qtitan::RibbonPage* page) override;
    void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

protected:
    bool canBeAddedToMenu() const override;
    bool canBeAddedToRibbonBar() const override;
    bool canBeAddedToPage() const override;
    bool updateInternal() override;

private:
    Qtitan::RibbonPage *m_ribbonPage;
};

/**
 * @brief 保存RibbonGroup的container，通过AM进行创建。
 *
 */
class RibbonGroupActionContainer : public ActionContainerPrivate
{
public:
    explicit RibbonGroupActionContainer(Id id);
    ~RibbonGroupActionContainer() override;

    Qtitan::RibbonGroup *ribbonGroup() const override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;
    void insertRibbonPage(int index, Qtitan::RibbonPage* page) override;
    void insertRibbonGroup(int index, Qtitan::RibbonGroup* group) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

protected:
    bool canBeAddedToMenu() const override;
    bool canBeAddedToRibbonBar() const override;
    bool canBeAddedToPage() const override;
    bool updateInternal() override;

private:
    Qtitan::RibbonGroup *m_ribbonGroup;
};
//} // namespace Internal
} // namespace Core
