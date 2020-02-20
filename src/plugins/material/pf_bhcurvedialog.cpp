#include "pf_bhcurvedialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

PF_BHCurveDialog::PF_BHCurveDialog(CMaterialProp* material,QWidget *parent)
    : QDialog(parent)
    ,mTableView(new QTableView(this))
    ,mItemModel(new QStandardItemModel(1,2))
    ,mOKButton(new QPushButton(tr("Ok"), this))
    ,mCancelButton(new QPushButton(tr("Cancel"), this))
    ,m_material(material)
{
    setWindowTitle(tr("B-H Curve"));
    resize(500, 500);
    /** 如果有数据，则进行显示。 **/
    QStandardItem* item = nullptr;
    for(int i = 0;i < m_material->BHpoints;i++){
        item = new QStandardItem(QString("%1").arg(m_material->BHdata[i].Re()));
        mItemModel->setItem(i,0,item);
        item = new QStandardItem(QString("%1").arg(m_material->BHdata[i].Im()));
        mItemModel->setItem(i,1,item);
    }

    mTableView->setModel(mItemModel);
    mTableView->setColumnWidth(0, 200);
    mTableView->setColumnWidth(1, 200);
//    setHorizontalHeaderLabels(QStringList() << tr("B(Flux density value(T))") << tr("H(Field value(A.m-1))"));
//    mItemModel->setRowCount(1);
//    mItemModel->setColumnCount(2);
    mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QWidget *bottomwidget = new QWidget(this);
    QHBoxLayout *bottomlayout = new QHBoxLayout(bottomwidget);
    bottomlayout->addStretch();
    bottomlayout->addWidget(mOKButton);
    bottomlayout->addWidget(mCancelButton);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(mTableView);
    mainlayout->addWidget(bottomwidget);

    connect(mItemModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
    connect(mCancelButton, &QPushButton::clicked, this, &PF_BHCurveDialog::close);
    connect(mOKButton, &QPushButton::clicked, this, &PF_BHCurveDialog::slotClickOKButton);
}

CComplex *PF_BHCurveDialog::getItemData() const
{
    return mItemData;
}

int PF_BHCurveDialog::getBHPoints() const
{
    return mItemModel->rowCount() - 1;
}

void PF_BHCurveDialog::setHorizontalHeaderLabels(const QStringList strlist)
{
    mItemModel->setHorizontalHeaderLabels(strlist);
}

void PF_BHCurveDialog::slotChangeData(const QModelIndex &topleft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    disconnect(mItemModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));

//    mItemData.resize(mItemModel->rowCount());
//    mItemData[mItemModel->rowCount() - 1].resize(2);
//    if(mItemModel->item(mItemModel->rowCount() - 1, 0)->text() != "" && mItemModel->item(mItemModel->rowCount() - 1, 1)->text() != "")
//    mItemData[topleft.row()][topleft.column()] = topleft.data().toDouble();
    qDebug() << topleft.row() << topleft.column();
    double data = mItemModel->itemFromIndex(topleft)->text().toDouble();
    mItemModel->itemFromIndex(topleft)->setText(QString::number(data));
    if(topleft.column() == 1 && mItemModel->item(topleft.row(), 0) == nullptr){
        QStandardItem *item = new QStandardItem("0");
        mItemModel->setItem(topleft.row(), 0, item);
    }
    else if(topleft.column() == 0 && mItemModel->item(topleft.row(), 1) == nullptr){
        QStandardItem *item = new QStandardItem("0");
        mItemModel->setItem(topleft.row(), 1, item);
    }
    if(topleft.row() == (mItemModel->rowCount() - 1) && !mItemModel->itemFromIndex(topleft)->text().isEmpty()){
        mItemModel->setRowCount(topleft.row() + 2);
    }

    connect(mItemModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
}

void PF_BHCurveDialog::slotClickOKButton()
{
    mItemData = new CComplex[static_cast<unsigned long long>(mItemModel->rowCount() - 1)];
    for(int i = 0; i < mItemModel->rowCount() - 1; ++i){
        mItemData[i] = CComplex(mItemModel->item(i, 0)->text().toDouble(), mItemModel->item(i, 1)->text().toDouble());
    }
    close();
}
