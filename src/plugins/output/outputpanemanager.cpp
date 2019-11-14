#include "outputpanemanager.h"

#include "ioutputpane.h"

namespace OutputPlugin {

OutputPaneManager::OutputPaneManager(QWidget *parent) : QWidget(parent)
{

}

IOutputPane::IOutputPane(QObject *parent)
    : QObject(parent)
{

}

IOutputPane::~IOutputPane()
{

}

} // namespace OutputPlugin
