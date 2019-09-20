#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "context.h"
#include "icore.h"

#include <QMap>
#include <QDockWidget>

#include "ribbonwindow.h"

class PF_ActionHandler;
class PF_WidgetFactory;
class PF_ActionGroupManager;

class MessageManager;
class PF_ProjectExplorerPlugin;

class PF_ModelWidget;
class PF_MaterialLibraryWidget;

class MainWindow : public RibbonWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

    void setupDockWidgets();
    void setupStatusBar();

    void registerDefaultContainers();
    void registerDefaultActions();

    QMap<QString, QAction*> a_map;/**动作列表**/
    PF_ActionGroupManager* ag_manager;

public slots:


private:
    /** 插件  **/
    ICore* m_coreImpl = nullptr;

    QList<IContext *> m_activeContext;

    QMap<QWidget *, IContext *> m_contextWidgets;
};

#endif // MAINWINDOW_H
