#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QPlainTextEdit>

namespace OutputPlugin {

class OutputWindow : public QPlainTextEdit
{
public:
    OutputWindow(QWidget* parent = nullptr);
    ~OutputWindow() override;
};
} // namespace OutputPlugin
#endif // OUTPUTWINDOW_H
