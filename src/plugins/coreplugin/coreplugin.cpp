#include "coreplugin.h"
#include "idocument.h"
#include "mainwindow.h"

#include <coreplugin/actionmanager/actionmanager.h>

#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <utils/algorithm.h>
#include <utils/mimetypes/mimedatabase.h>
#include <utils/stringutils.h>

#include <QtPlugin>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QUuid>

#include <QSplashScreen>

#include <cstdlib>

using namespace Core;
//using namespace Core::Internal;
using namespace Utils;

static CorePlugin *m_instance = nullptr;

CorePlugin::CorePlugin()
{
    qRegisterMetaType<Id>();
    //    qRegisterMetaType<Core::Search::TextPosition>();
    m_instance = this;
}

CorePlugin::~CorePlugin()
{
    delete m_mainWindow;
}

CorePlugin *CorePlugin::instance()
{
    return m_instance;
}

struct CoreArguments {
    QColor overrideColor;
    Id themeId;
    bool presentationMode = false;
};

CoreArguments parseArguments(const QStringList &arguments)
{
    CoreArguments args;
    for (int i = 0; i < arguments.size(); ++i) {
        if (arguments.at(i) == QLatin1String("-color")) {
            const QString colorcode(arguments.at(i + 1));
            args.overrideColor = QColor(colorcode);
            i++; // skip the argument
        }
        if (arguments.at(i) == QLatin1String("-presentationMode"))
            args.presentationMode = true;
        if (arguments.at(i) == QLatin1String("-theme")) {
            args.themeId = Id::fromString(arguments.at(i + 1));
            i++; // skip the argument
        }
    }
    return args;
}

/**
 * @brief initialize()函数会在Qt Creator请求插件初始化时被调用，
 * 常用于初始化插件的内部状态和插件注册actions/objects到QtCreator。
 * 当插件依赖的所有资源都被加载后，initialize()函数才会被调用。
 * 初始化成功返回true，用于告诉QtCreator本插件已经初始化成功。
 * 如果初始化不成功，应该在errMsg中存储可读的错误信息，供QtCreator
 * 在界面上显示出来。
 *
 * @param arguments
 * @param errorMessage
 * @return bool
 */
bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    // register all mime types from all plugins
    for (ExtensionSystem::PluginSpec *plugin : ExtensionSystem::PluginManager::plugins()) {
        if (!plugin->isEffectivelyEnabled())
            continue;
        const QJsonObject metaData = plugin->metaData();
        const QJsonValue mimetypes = metaData.value("Mimetypes");
        QString mimetypeString;
        if (Utils::readMultiLineString(mimetypes, &mimetypeString))
            Utils::addMimeTypes(plugin->name() + ".mimetypes", mimetypeString.trimmed().toUtf8());
    }

    /** 创建action管理器，保存所有的actions **/
    new ActionManager(this);
    /** 欢迎页面 **/
    QSplashScreen* splash = new QSplashScreen;

    QPixmap pixmap(":/main/splash.png");
    splash->setPixmap(pixmap);
    splash->setAttribute(Qt::WA_DeleteOnClose);
    splash->show();
    splash->showMessage(QObject::tr("Loading..."),
                        Qt::AlignRight|Qt::AlignBottom,Qt::black);
//    QDateTime n=QDateTime::currentDateTime();
//    QDateTime now;
//    do{
//        now=QDateTime::currentDateTime();
//    } while (n.secsTo(now)<=0.5);//6 为需要延时的秒数

    /** 软件主界面 **/
    m_mainWindow = new MainWindow;
    m_mainWindow->setWindowTitle("FEEM");

    m_mainWindow->showMaximized();
    m_mainWindow->show();
    m_mainWindow->setFocus();

//    splash->raise();
//    splash->showMessage(QObject::tr("Loading..."),
//                        Qt::AlignRight|Qt::AlignBottom,Qt::black);

//    splash->finish(m_mainWindow);
//    delete splash;

    ActionManager::instance()->setContext(Context(Constants::C_GLOBAL));

//    PF_Project* pro = new PF_Project(this);
//    //    PF_Project* pro1 = new PF_Project(this);
//    PF_SessionManager::instance()->addProject(pro);
//    //    PF_SessionManager::instance()->addProject(pro1);
//    PF_ProjectTree::instance()->expandAll();

    return true;
}

/**
 * @brief extensionsInitialized()函数在插件初始化后被调用
 * （例如initialize()函数调用后）。extensionsInitialized()
 * 函数会由第一个依赖于本插件的其他插件进行调用。
 *
 */
void CorePlugin::extensionsInitialized()
{
//    DesignMode::createModeIfRequired();
//    Find::extensionsInitialized();
//    m_locator->extensionsInitialized();
//    m_mainWindow->extensionsInitialized();
//    if (ExtensionSystem::PluginManager::hasError()) {
//        auto errorOverview = new ExtensionSystem::PluginErrorOverview(m_mainWindow);
//        errorOverview->setAttribute(Qt::WA_DeleteOnClose);
//        errorOverview->setModal(true);
//        errorOverview->show();
//    }
}

bool CorePlugin::delayedInitialize()
{
/*    m_locator->delayedInitialize();
    IWizardFactory::allWizardFactories();*/ // scan for all wizard factories
    return true;
}

QObject *CorePlugin::remoteCommand(const QStringList & /* options */,
                                   const QString &workingDirectory,
                                   const QStringList &args)
{
//    if (!ExtensionSystem::PluginManager::isInitializationDone()) {
//        connect(ExtensionSystem::PluginManager::instance(), &ExtensionSystem::PluginManager::initializationDone,
//                this, [this, workingDirectory, args]() {
//            remoteCommand(QStringList(), workingDirectory, args);
//        });
//        return nullptr;
//    }
//    IDocument *res = m_mainWindow->openFiles(
//                args, ICore::OpenFilesFlags(ICore::SwitchMode | ICore::CanContainLineAndColumnNumbers | ICore::SwitchSplitIfAlreadyVisible),
//                workingDirectory);
//    m_mainWindow->setWindowState(m_mainWindow->windowState() & ~Qt::WindowMinimized);
    m_mainWindow->raise();
    m_mainWindow->activateWindow();
//    return res;
    return nullptr;
}

void CorePlugin::fileOpenRequest(const QString &f)
{
    remoteCommand(QStringList(), QString(), QStringList(f));
}


ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
//    Find::aboutToShutdown();
//    m_mainWindow->aboutToShutdown();
    return SynchronousShutdown;
}
