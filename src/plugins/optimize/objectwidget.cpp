#include "objectwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "readonlydelegate.h"

ObjectWidget::ObjectWidget(QWidget *parent)
    : QWidget(parent),
      mObjectTable(new QTableView((this))),
      mObjectModel(new QStandardItemModel(this)),
      mObjectSelection(new QItemSelectionModel(mObjectModel)),
      mObjectBox(new QComboBox(this)),
      mModeBox(new QComboBox(this)),
      mObjectDeleteButton(new QPushButton(tr("Delete"), this)),
      mObjectAddButton(new QPushButton(tr("Add"), this)),
      mObjectWarningLabel(new QLabel(this))
{
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    mObjectWarningLabel->setPalette(pe);

    /**优化目标**/
    QLabel *objectlabel = new QLabel(tr("Object to be optimized"), this);
    QTableView *objecttable = mObjectTable;
    QLabel *objectlabel1 = new QLabel(tr("Object to be optimized: "), this);
    QComboBox *objectbox = mObjectBox;
    QLabel *modelabel = new QLabel(tr("Optimize mode: "), this);
    QComboBox *modebox = mModeBox;

    mObjectTable->setModel(mObjectModel);
    QStringList inputlist;
    inputlist << tr("Object to be optimized") << tr("Optimize mode");
    mObjectModel->setHorizontalHeaderLabels(inputlist);

    /**委托构造**/
    ItemDelegate *itemdelegate = new ItemDelegate(this);
    mObjectTable->setItemDelegateForColumn(1, itemdelegate);
    ReadOnlyDelegate *readonlydelegate = new ReadOnlyDelegate(this);
    mObjectTable->setItemDelegateForColumn(0, readonlydelegate);


    /**表头设置**/
    mObjectTable->resizeColumnsToContents();
    QStringList modeist;
    modeist << tr("Maximize") << tr("Minimize");
    mModeBox->addItems(modeist);

    /**layout**/
    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(objectlabel, 0, 0);
    glayout->addWidget(objecttable, 1, 0, 1, 2);
    glayout->addWidget(objectlabel1, 2, 0);
    glayout->addWidget(objectbox, 2, 1);
    glayout->addWidget(modelabel, 3, 0);
    glayout->addWidget(modebox, 3, 1);

    QHBoxLayout *buttonlayout = new QHBoxLayout;
    buttonlayout->addStretch();
    buttonlayout->addWidget(mObjectDeleteButton);
    buttonlayout->addWidget(mObjectAddButton);

    QVBoxLayout *objectlayout = new QVBoxLayout(this);
    objectlayout->addLayout(glayout);
    objectlayout->addLayout(buttonlayout);
    objectlayout->addWidget(mObjectWarningLabel);


    /**connect**/
    connect(mObjectAddButton, &QPushButton::clicked, this, &ObjectWidget::slotAddTableItem);
    connect(mObjectDeleteButton, &QPushButton::clicked, this, &ObjectWidget::slotDeleteTableItem);
    connect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
}

QStringList ObjectWidget::getObjectList() const
{
    return mObjectList;
}

QStringList ObjectWidget::getModeList() const
{
    return mModeList;
}

QMap<QString, QString> ObjectWidget::getObjectModeMap() const
{
    return mObjectModeMap;
}

QComboBox* ObjectWidget::getObjectBox() const
{
    return mObjectBox;
}

void ObjectWidget::setObjectList(QStringList objectlist)
{
    mObjectList = objectlist;
    mObjectBox->clear();
    mObjectBox->addItems(mObjectList);
}

void ObjectWidget::slotAddTableItem()
{
    qDebug() << "ObjectWidget::slotAddTableItem";
    disconnect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
    QString object = mObjectBox->currentText();
    QString mode = mModeBox->currentText();
    if(!mObjectModeMap.contains(mObjectBox->currentText())){
        setWarning(tr(""));
        mObjectModeMap.insert(object, mode);
        refreshTable();
    }else{
        setWarning(tr("Error: Current Object Exist!"));
    }
    connect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
}

void ObjectWidget::slotChangeData(const QModelIndex &topleft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    qDebug() << "ObjectWidget::slotChangeData";
    disconnect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
    QString key = mObjectModel->item(topleft.row())->text();
    mObjectModeMap[key] = mObjectModel->itemFromIndex(topleft)->text();
//    qDebug() << mObjectModeMap;
    connect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
}

void ObjectWidget::slotDeleteTableItem()
{
    qDebug() << "ObjectWidget::slotDeleteTableItem";
    disconnect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
    QModelIndex index = mObjectTable->currentIndex();
//    qDebug() << index;
    if(index.row() != -1){
        int row = index.row();
        QString key = mObjectModel->item(row, 0)->text();
//        mObjectModel->removeRow(row);
        mObjectModeMap.remove(key);
        refreshTable();
    }
    connect(mObjectModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotChangeData(QModelIndex,QModelIndex,QVector<int>)));
}

void ObjectWidget::setWarning(QString string)
{
    mObjectWarningLabel->setText(string);
}

void ObjectWidget::appendObjectList(const QString string)
{
    mObjectList.append(string);
    mObjectBox->addItem(string);
}

void ObjectWidget::refreshTable()
{
    mObjectModel->setRowCount(mObjectModeMap.size());
    int count = 0;
    for(auto i = mObjectModeMap.begin(); i != mObjectModeMap.end(); ++i){
        mObjectModel->setItem(count, 0, new QStandardItem(i.key()));
        mObjectModel->setItem(count, 1, new QStandardItem(i.value()));
        ++count;
    }
    mObjectTable->resizeColumnsToContents();
    emit(objectChanged());
}
