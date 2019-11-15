#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "itemdelegate.h"

class ObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectWidget(QWidget *parent = nullptr);

    /**getter**/
    QStringList getObjectList() const;
    QStringList getModeList() const;
    QMap<QString, QString> getObjectModeMap() const;
    QComboBox *getObjectBox() const;

    /**setter**/
    void setObjectList(QStringList objectlist);
    void setWarning(QString string);
    void appendObjectList(const QString string);

    enum OptimizeMode{
        MINIMIZE,
        MAXIMIZE,
    };

signals:
    void objectChanged();

private slots:
    void slotAddTableItem();
    void slotChangeData(const QModelIndex &topleft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void slotDeleteTableItem();

private:
    void refreshTable();
    /**object控件**/
    QTableView *mObjectTable;
    QStandardItemModel *mObjectModel;
    QItemSelectionModel *mObjectSelection;
    QComboBox *mObjectBox;
    QComboBox *mModeBox;
    QPushButton *mObjectDeleteButton;
    QPushButton *mObjectAddButton;
    QLabel *mObjectWarningLabel;

    /**ComboBox中的列表**/
    QStringList mObjectList;
    QStringList mModeList;

    /**Table中被添加的选项**/
    QMap<QString, QString> mObjectModeMap;

};

#endif // TARGETWIDGET_H
