#include "outputpluginplugin.h"
#include "outputpluginconstants.h"


#include <QtAdvancedDock/DockManager.h>

#include <coreplugin/icore.h>
#include <coreplugin/context.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/constants.h>
#include <coreplugin/workpage.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QDateTime>

using namespace Core;

namespace OutputPlugin {
static MessageOutputPane* m_messagePane = nullptr;

OutputPluginPlugin::OutputPluginPlugin()
{
    // Create your members
}

OutputPluginPlugin::~OutputPluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
    if(m_messagePane)
        delete m_messagePane;
    m_messagePane = nullptr;
}

bool OutputPluginPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    qDebug()<<Q_FUNC_INFO;
    m_messagePane = new MessageOutputPane();

    return true;
}

void OutputPluginPlugin::extensionsInitialized()
{
    qDebug()<<Q_FUNC_INFO;
    ads::CDockWidget* DockWidget1 = new ads::CDockWidget(tr("Message outputpane"));
    DockWidget1->setWidget(m_messagePane->outputWidget());
    Core::WorkPage::DockManager()->addDockWidget(ads::BottomDockWidgetArea, DockWidget1);
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
//    PoofeeSay<<current_date;
    PoofeeSay<<tr("Welcome to FEEM! Copyright 2018-2020 HIT. All rights reserved.");
//    m_messagePane->appendMessage(current_date+QLatin1Char('\n'));
//    m_messagePane->appendMessage(tr("Welcome to FEEM!")+QLatin1Char('\n'));
}

ExtensionSystem::IPlugin::ShutdownFlag OutputPluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

MessageOutputPane* OutputPluginPlugin::MessagePane()
{
    return m_messagePane;
}



} // namespace OutputPlugin
