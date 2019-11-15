#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "context.h"
#include "icore.h"

#include <QMap>
#include <QDockWidget>

#include "ribbonwindow.h"

namespace Core {


class PF_ActionHandler;
class PF_WidgetFactory;
class PF_ActionGroupManager;

class MessageManager;
class PF_ProjectExplorerPlugin;

class PF_ModelWidget;
class PF_MaterialLibraryWidget;

class PageManager;
class PF_PageWidget;

class GeometryManager;

class MainWindow : public RibbonWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    IContext *contextObject(QWidget *widget);
    void addContextObject(IContext *context);
    void removeContextObject(IContext *context);

    void init();

    void extensionsInitialized();

    void registerDefaultContainers();
    void registerDefaultActions();
private:
    void updateContextObject(const QList<IContext *> &context);
    void updateContext();

public slots:


private:
    /** 插件  **/
    ICore* m_coreImpl = nullptr;
    PageManager* m_pageManager = nullptr;
    PF_PageWidget* m_pagesStack = nullptr;
    GeometryManager* m_geometryManager = nullptr;

    QList<IContext *> m_activeContext;

    QMap<QWidget *, IContext *> m_contextWidgets;
};
} //namespace Core
#endif // MAINWINDOW_H
