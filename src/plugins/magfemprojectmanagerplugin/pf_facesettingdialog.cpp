#include "pf_facesettingdialog.h"

#include <QWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

namespace MagFEMProjectManagerPlugin {

PF_FaceSettingDialog::PF_FaceSettingDialog(QWidget *parent, PF_CommonFEMProject *pro, int index)
    :QDialog (parent)
    ,m_project(pro)
    ,m_faceIndex(index)
{
    QVBoxLayout* vbox = new QVBoxLayout;

    QGroupBox* setMaterial = new QGroupBox(this);
    setMaterial->setTitle(tr("Material"));
    QFormLayout* form = new QFormLayout;
    m_combobox = new QComboBox(setMaterial);
    form->addRow(tr("Material"),m_combobox);

    int i=0,in=-1;
    for(auto m : pro->m_materialList){
        m_combobox->addItem(m.BlockName);
        if(m_project->m_domains[m_faceIndex] == m.BlockName){
            in = i;
            qDebug()<<"have material";
            m_combobox->setCurrentIndex(i);
        }
        i++;
    }
    if(in < 0)
        m_combobox->setCurrentIndex(-1);


    setMaterial->setLayout(form);

    vbox->addWidget(setMaterial);

    QHBoxLayout* hbox = new QHBoxLayout;
    QPushButton* pb_OK = new QPushButton();
    pb_OK->setText(tr("OK"));
    QPushButton* pb_Cancle = new QPushButton();
    pb_Cancle->setText(tr("Cancle"));
    hbox->addStretch();
    hbox->addWidget(pb_OK);
    hbox->addWidget(pb_Cancle);
    vbox->addLayout(hbox);

    connect(pb_OK,&QPushButton::clicked,[this](){
        m_project->m_domains[m_faceIndex]=m_combobox->currentText();
        qDebug()<<m_combobox->currentText();
        qDebug()<<m_project->m_domains[m_faceIndex];
        this->accept();
    });
    connect(pb_Cancle,&QPushButton::clicked,[this](){
        this->reject();
    });

    setLayout(vbox);
    resize(350,170);
}

PF_FaceSettingDialog::~PF_FaceSettingDialog()
{

}

}//MagFEMProjectManagerPlugin
