#ifndef TYPEPAGE_H
#define TYPEPAGE_H

#include <QWizardPage>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QMap>

class TypePage : public QWizardPage
{
    Q_OBJECT
public:
    explicit TypePage(QWizardPage *parent = nullptr);
    void appendListPicMap(const QString name, const QPixmap pic);

signals:

public slots:
    void slotChangePic(QListWidgetItem *item);
    void resizeEvent(QResizeEvent *event) override;

private:
    QListWidget *mList;
    QLabel *mPicLabel;
    QHBoxLayout *mHLayout;
    QMap<QString, QPixmap> mListPicMap;
};

#endif // TYPEPAGE_H
