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
    explicit TypePage(QWizard *parent = nullptr);
    void appendListPicMap(const QString name, const QPixmap pic);

    QPixmap getCurrentMap() const;
    QPixmap getCurrentPic() const;

    void setCurrentPic(const QPixmap &currentPic);

signals:

public slots:
    void slotChangePic(QListWidgetItem *item);
    void resizeEvent(QResizeEvent *event) override;

private:
    QListWidget *mList;
    QLabel *mPicLabel;
    QHBoxLayout *mHLayout;
    QMap<QString, QPixmap> mListPicMap;
    QPixmap mCurrentPic;
    QPixmap mScaledPic;
};

#endif // TYPEPAGE_H
