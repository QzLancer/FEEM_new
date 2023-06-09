#include "coreplugin.h"
#include "idocument.h"
#include "mainwindow.h"
#include <coreplugin/workpage.h>
#include <coreplugin/pagemanager.h>

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
    delete m_workPage;
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
    qDebug()<<Q_FUNC_INFO;
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

    /** 软件主界面 **/
    m_mainWindow = new MainWindow;
    m_mainWindow->setWindowTitle("FEEM");

    m_workPage = new WorkPage;
    PageManager::activatePage(m_workPage->id());

    ActionManager::instance()->setContext(Context(Constants::C_GLOBAL));

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
    /** 显示Windows，需要在所有的菜单都初始化完成之后，
        但是总是warning 不能设置几何，所以先resize一下。
        不知道什么原因，至少这样是好使的。**/
    m_mainWindow->extensionsInitialized();
    m_mainWindow->resize(900,600);
    m_mainWindow->show();
    m_mainWindow->setFocus();
    m_mainWindow->showMaximized();
}

bool CorePlugin::delayedInitialize()
{
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
