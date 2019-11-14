#ifndef MESSAGEOUTPUTWINDOW_H
#define MESSAGEOUTPUTWINDOW_H

#include "ioutputpane.h"

namespace OutputPlugin {
class OutputWindow;

class MessageOutputWindow : public IOutputPane
{
    Q_OBJECT
public:
    MessageOutputWindow();
    ~MessageOutputWindow() override;


};
} // namespace OutputPlugin
#endif // MESSAGEOUTPUTWINDOW_H
