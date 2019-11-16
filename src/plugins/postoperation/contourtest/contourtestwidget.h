#ifndef CONTOURTESTWIDGET_H
#define CONTOURTESTWIDGET_H

#include <QWidget>

class Plot;

class ContourTestWidget : public QWidget
{
    Q_OBJECT
public:
    ContourTestWidget(QWidget* parent = nullptr);
    ~ContourTestWidget();
private:
    Plot* m_Plot;
};

#endif // CONTOURTESTWIDGET_H
