#ifndef BOUNCESTACK_H
#define BOUNCESTACK_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class BounceDialog;

class BounceStack : public QWidget
{
    Q_OBJECT
public:
    explicit BounceStack(BounceDialog *parent = nullptr, QString title = nullptr, QWidget *mainwidget = nullptr);

signals:

public slots:

private:
    QLabel *mTitleLabel;
    QWidget *mMainWidget;
    QVBoxLayout *mMainLayout;
};

#endif // BOUNCESTACK_H
