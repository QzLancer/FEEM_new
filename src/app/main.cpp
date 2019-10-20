#include "QtnRibbonStyle.h"

#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

#include <QDir>

#include <QDebug>
#include <QApplication>
#include <QStandardPaths>
#include <QTranslator>
#include <QSplashScreen>
#include <QDateTime>
#include <QPixmap>
#include <QLibraryInfo>

using namespace ExtensionSystem;

typedef QList<PluginSpec *> PluginSpecSet;

const char corePluginNameC[] = "Core";

static inline QStringList getPluginPaths()
{
    QStringList rc(QDir::cleanPath(QApplication::applicationDirPath()
                                   + '/' + RELATIVE_PLUGIN_PATH));
    QString pluginPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);

//    pluginPath += QLatin1Char('/')
//            + QLatin1String(Core::Constants::IDE_SETTINGSVARIANT_STR)
//            + QLatin1Char('/');
//    pluginPath += QLatin1String(Utils::HostOsInfo::isMacHost() ?
//                                    Core::Constants::IDE_DISPLAY_NAME :
//                                    Core::Constants::IDE_ID);
    pluginPath += QLatin1String("/plugins/");
//    pluginPath += QLatin1String(Core::Constants::IDE_VERSION_LONG);
    rc.push_back(pluginPath);
    return rc;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle( new Qtitan::RibbonStyle() );
    app.processEvents();
    /** 欢迎页面 **/
    QSplashScreen* splash = new QSplashScreen;

    QPixmap pixmap(":/app/splash.png");
    splash->setPixmap(pixmap);
    splash->setAttribute(Qt::WA_DeleteOnClose);
    splash->show();
    splash->showMessage(QApplication::tr("Loading..."),
                        Qt::AlignRight|Qt::AlignBottom,Qt::black);
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=1);//6 为需要延时的秒数
//    splash->raise();
//    splash->showMessage(QSplashScreen::tr("Loading..."),
//                        Qt::AlignRight|Qt::AlignBottom,Qt::black);

    /** 初始化插件管理器 **/
    PluginManager pluginManager;
    PluginManager::setPluginIID(QLatin1String("org.hit.feem.feemPlugin"));
    //PluginManager::setGlobalSettings(globalSettings);
    //PluginManager::setSettings(settings);
    /** 翻译文件 **/
    QTranslator translator;
    QTranslator qtTranslator;
    QStringList uiLanguages;
    uiLanguages = QLocale::system().uiLanguages();
//    QString overrideLanguage = settings->value(QLatin1String("General/OverrideLanguage")).toString();
//    if (!overrideLanguage.isEmpty())
//        uiLanguages.prepend(overrideLanguage);
    const QString &feemTrPath = QDir::cleanPath(QApplication::applicationDirPath() + '/' + RELATIVE_DATA_PATH) + "/translations";
    foreach (QString locale, uiLanguages) {
        locale = QLocale(locale).name();
        if (translator.load("feem_" + locale, ":/translations")) {
            const QString &qtTrPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
            const QString &qtTrFile = QLatin1String("qt_") + locale;
            // Binary installer puts Qt tr files into feemTrPath
            if (qtTranslator.load(qtTrFile, qtTrPath) || qtTranslator.load(qtTrFile, feemTrPath)) {
                app.installTranslator(&translator);
                app.installTranslator(&qtTranslator);
                app.setProperty("qtc_locale", locale);
                break;
            }
            translator.load(QString()); // unload()
        } else if (locale == QLatin1String("C") /* overrideLanguage == "English" */) {
            // use built-in
            break;
        } else if (locale.startsWith(QLatin1String("en")) /* "English" is built-in */) {
            // use built-in
            break;
        }
    }
    /** 载入插件 **/
    const QStringList pluginPaths = getPluginPaths();// + options.customPluginPaths;
    PluginManager::setPluginPaths(pluginPaths);
    QMap<QString, QString> foundAppOptions;
//    if (pluginArguments.size() > 1) {
//        QMap<QString, bool> appOptions;
//        appOptions.insert(QLatin1String(HELP_OPTION1), false);
//        appOptions.insert(QLatin1String(HELP_OPTION2), false);
//        appOptions.insert(QLatin1String(HELP_OPTION3), false);
//        appOptions.insert(QLatin1String(HELP_OPTION4), false);
//        appOptions.insert(QLatin1String(VERSION_OPTION), false);
//        appOptions.insert(QLatin1String(CLIENT_OPTION), false);
//        appOptions.insert(QLatin1String(PID_OPTION), true);
//        appOptions.insert(QLatin1String(BLOCK_OPTION), false);
//        QString errorMessage;
//        if (!PluginManager::parseOptions(pluginArguments, appOptions, &foundAppOptions, &errorMessage)) {
//            displayError(errorMessage);
//            printHelp(QFileInfo(app.applicationFilePath()).baseName());
//            return -1;
//        }
//    }


    const PluginSpecSet plugins = PluginManager::plugins();
    PluginSpec *coreplugin = nullptr;
    foreach (PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(corePluginNameC)) {
            coreplugin = spec;
            break;
        }
    }
    /** 判断主插件是否正常载入 **/
//    if (!coreplugin) {
//        QString nativePaths = QDir::toNativeSeparators(pluginPaths.join(QLatin1Char(',')));
//        const QString reason = QCoreApplication::translate("Application", "Could not find Core plugin in %1").arg(nativePaths);
//        displayError(msgCoreLoadFailure(reason));
//        return 1;
//    }
//    if (!coreplugin->isEffectivelyEnabled()) {
//        const QString reason = QCoreApplication::translate("Application", "Core plugin is disabled.");
//        displayError(msgCoreLoadFailure(reason));
//        return 1;
//    }
//    if (coreplugin->hasError()) {
//        displayError(msgCoreLoadFailure(coreplugin->errorString()));
//        return 1;
//    }
//    if (foundAppOptions.contains(QLatin1String(VERSION_OPTION))) {
//        printVersion(coreplugin);
//        return 0;
//    }
//    if (foundAppOptions.contains(QLatin1String(HELP_OPTION1))
//            || foundAppOptions.contains(QLatin1String(HELP_OPTION2))
//            || foundAppOptions.contains(QLatin1String(HELP_OPTION3))
//            || foundAppOptions.contains(QLatin1String(HELP_OPTION4))) {
//        printHelp(QFileInfo(app.applicationFilePath()).baseName());
//        return 0;
//    }

//    qint64 pid = -1;
//    if (foundAppOptions.contains(QLatin1String(PID_OPTION))) {
//        QString pidString = foundAppOptions.value(QLatin1String(PID_OPTION));
//        bool pidOk;
//        qint64 tmpPid = pidString.toInt(&pidOk);
//        if (pidOk)
//            pid = tmpPid;
//    }

//    bool isBlock = foundAppOptions.contains(QLatin1String(BLOCK_OPTION));
//    if (app.isRunning() && (pid != -1 || isBlock
//                            || foundAppOptions.contains(QLatin1String(CLIENT_OPTION)))) {
//        app.setBlock(isBlock);
//        if (app.sendMessage(PluginManager::serializedArguments(), 5000 /*timeout*/, pid))
//            return 0;

//        // Message could not be send, maybe it was in the process of quitting
//        if (app.isRunning(pid)) {
//            // Nah app is still running, ask the user
//            int button = askMsgSendFailed();
//            while (button == QMessageBox::Retry) {
//                if (app.sendMessage(PluginManager::serializedArguments(), 5000 /*timeout*/, pid))
//                    return 0;
//                if (!app.isRunning(pid)) // App quit while we were trying so start a new creator
//                    button = QMessageBox::Yes;
//                else
//                    button = askMsgSendFailed();
//            }
//            if (button == QMessageBox::No)
//                return -1;
//        }
//    }

    PluginManager::loadPlugins();
//    if (coreplugin->hasError()) {
//        displayError(msgCoreLoadFailure(coreplugin->errorString()));
//        return 1;
//    }

    // Set up remote arguments.
//    QObject::connect(&app, &SharedTools::QtSingleApplication::messageReceived,
//                     &pluginManager, &PluginManager::remoteArguments);

//    QObject::connect(&app, SIGNAL(fileOpenRequest(QString)), coreplugin->plugin(),
//                     SLOT(fileOpenRequest(QString)));

    // shutdown plugin manager on the exit
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &pluginManager, &PluginManager::shutdown);

    delete splash;
    return app.exec();
}

