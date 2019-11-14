#ifndef MESSAGEOUTPUTPANE_H
#define MESSAGEOUTPUTPANE_H

#include "ioutputpane.h"

class QToolButton;
class QAction;

namespace OutputPlugin {

class OutputWindow;
/*!
 \brief 一个简单的信息输出控件

*/
class MessageOutputPane : public IOutputPane
{
public:
    MessageOutputPane();
    ~MessageOutputPane();

    QWidget *outputWidget() const override;
    QString displayName() const override;
    void clearContents() override;
    void appendMessage(const QString &out);
private:
    QWidget *m_mainWidget = nullptr;
    OutputWindow* m_outputWindow = nullptr;
    QToolButton *m_clearButton = nullptr;
    QToolButton *m_zoomInButton = nullptr;
    QToolButton *m_zoomOutButton = nullptr;
};

}// namespace OutputPlugin


#endif // MESSAGEOUTPUTPANE_H
