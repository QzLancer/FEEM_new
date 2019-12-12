#ifndef PF_BHCURVEDIALOG_H
#define PF_BHCURVEDIALOG_H

#include "pf_material.h"

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

class PF_BHCurveDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PF_BHCurveDialog(QWidget *parent = nullptr);
    CComplex *getItemData() const;
    int getBHPoints() const;
signals:

public slots:
    void slotChangeData(const QModelIndex &topleft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void slotClickOKButton();

private:
    CComplex *mItemData;
    QTableView *mTableView;
    QStandardItemModel *mItemModel;
    QPushButton *mOKButton;
    QPushButton *mCancelButton;
};

#endif // PF_BHCURVEDIALOG_H
