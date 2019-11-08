#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include "../iwizardfactory.h"

#include <QDialog>
#include <QIcon>
#include <QList>
#include <QVariantMap>

class QAbstractProxyModel;
class QModelIndex;
class QSortFilterProxyModel;
class QPushButton;
class QStandardItem;
class QStandardItemModel;

namespace Core {

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent);
    ~NewDialog() override;

    void setWizardFactories(QList<IWizardFactory*> factories, const QString &defaultLocation, const QVariantMap &extraVariables);

    void showDialog();
//    Id selectedPlatform() const;

    static QWidget *currentDialog();

protected:
    bool event(QEvent *) override;

private:
    void currentCategoryChanged(const QModelIndex &);
    void currentItemChanged(const QModelIndex &);
    void accept() override;
    void reject() override;
    void updateOkButton();
//    void setSelectedPlatform(const QString &platform);

    Core::IWizardFactory *currentWizardFactory() const;
    void addItem(QStandardItem *topLevelCategoryItem, IWizardFactory *factory);
    void saveState();

    static QWidget *m_currentDialog;

    Ui::NewDialog *m_ui;/**ui文件**/
    QStandardItemModel *m_model;
    QSortFilterProxyModel *m_filterProxyModel;
    QPushButton *m_okButton = nullptr;
    QIcon m_dummyIcon;
    QList<QStandardItem*> m_categoryItems;
    QString m_defaultLocation;
    QVariantMap m_extraVariables;
};
}// namespace Core

#endif // NEWDIALOG_H
