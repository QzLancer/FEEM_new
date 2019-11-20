#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

class InputWidget : public QWidget
{
    Q_OBJECT
public:
    enum Input{
        FORCE_TIME_CURVE = 0,
    };

    explicit InputWidget(QWidget *parent = nullptr);
    QComboBox *mCurveSelectBox;

signals:

public slots:
    void slotChangeInput(int index);

private:
    QGroupBox *mGroupBox;
    QVBoxLayout *mVLayout1;
    QVBoxLayout *mVLayout2;
    Input mInput;
};

#endif // INPUTWIDGET_H
