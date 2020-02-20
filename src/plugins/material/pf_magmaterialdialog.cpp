#include "pf_magmaterialdialog.h"
#include "pf_material.h"
#include "pf_bhcurvedialog.h"

#include <coreplugin/icore.h>

#include <output/outputpluginplugin.h>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QToolButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QDebug>
#include <QTabWidget>
#include <QPushButton>

PF_MagMaterialDialog::PF_MagMaterialDialog(CMaterialProp *material, QWidget *parent)
    :QDialog (parent)
    ,m_material(material)
{
    initialization();
    resize(650,500);
    updateDialog();
}

PF_MagMaterialDialog::~PF_MagMaterialDialog()
{
//    delete m_material;
//    m_material = nullptr;
}

void PF_MagMaterialDialog::initialization()
{
    QFormLayout* formlayout = new QFormLayout;
    edit_name = new QLineEdit(this);
    QLineEdit* edit_comment = new QLineEdit(this);
    formlayout->addRow(tr("Name"),edit_name);
    formlayout->addRow(tr("Comment"),edit_comment);

    tab_material = new QTabWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addLayout(formlayout);
    vbox->addWidget(tab_material);
    tab_material->addTab(createBasicPage(),QString(tr("Basic Material")));
    tab_material->addTab(createMagneticPage(),QString(tr("Magnetic Material")));
    tab_material->addTab(createHeatPage(),QString(tr("Heat Material")));
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
        this->accept();
    });
    connect(pb_Cancle,&QPushButton::clicked,[this](){
        this->reject();
    });

    setLayout(vbox);

    /** 作用对话框关闭时，自动销毁对话框，但是，这里不能设置
        自动销毁，不然，按下ok之后，对话框销毁，就无法访问
        内部的变量**/
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(windowFlags() | Qt::WindowCloseButtonHint);
}

QWidget *PF_MagMaterialDialog::createBasicPage()
{
    QWidget* w = new QWidget(this);

    return w;
}

QWidget *PF_MagMaterialDialog::createMagneticPage()
{
    QWidget* w = new QWidget(this);

    QVBoxLayout* mainlayout = new QVBoxLayout;

    /** Name & B-H curve **/
    QFormLayout* formlayout = new QFormLayout;
//    QLineEdit* edit_name = new QLineEdit(w);
    combo_bhtype = new QComboBox(w);
    combo_bhtype->addItem(tr("Linear B-H relationship"));
    combo_bhtype->addItem(tr("Nonlinear B-H curve"));

//    formlayout->addRow(tr("Name"),edit_name);
    formlayout->addRow(tr("B-H curve"),combo_bhtype);
    formlayout->setLabelAlignment(Qt::AlignLeft);

    mainlayout->addLayout(formlayout);

    /** Linear Material Properties **/
    QGroupBox* gbox_linear = new QGroupBox(w);
    QHBoxLayout* hbox_linear = new QHBoxLayout;
    edit_ux = new QLineEdit(w);
    edit_uy = new QLineEdit(w);
    edit_hx = new QLineEdit(w);
    edit_hy = new QLineEdit(w);
    QFormLayout* formlayout_linear1 = new QFormLayout;
    formlayout_linear1->addRow(tr("Relative ux:"),edit_ux);
    formlayout_linear1->addRow(tr("Relative hx:"),edit_hx);
    QFormLayout* formlayout_linear2 = new QFormLayout;
    formlayout_linear2->addRow(tr("Relative uy:"),edit_uy);
    formlayout_linear2->addRow(tr("Relative hy:"),edit_hy);
    hbox_linear->addLayout(formlayout_linear1);
    hbox_linear->addLayout(formlayout_linear2);
    gbox_linear->setLayout(hbox_linear);
    gbox_linear->setTitle(tr("Linear Material Properties"));

    mainlayout->addWidget(gbox_linear);

    /**  Nonlinear Material Properties **/
    QGroupBox* gbox_nonl = new QGroupBox(w);
    gbox_nonl->setTitle(tr("Nonlinear Material Properties"));
    hbox_linear = new QHBoxLayout;
    QPushButton* bt_bhcurve = new QPushButton(w);
    bt_bhcurve->setText(tr("B-H Curve"));
    QHBoxLayout* hbox1 = new QHBoxLayout;
    hbox1->addWidget(bt_bhcurve);
    formlayout_linear1 = new QFormLayout;
    edit_hmax = new QLineEdit(w);
    formlayout_linear1->addRow(tr("hmax"),edit_hmax);
    formlayout_linear1->setFormAlignment(Qt::AlignCenter);
//    hbox_linear->addStretch();
    hbox_linear->addLayout(hbox1,1);

//    hbox_linear->addStretch();
    hbox_linear->addLayout(formlayout_linear1,1);
//    hbox_linear->addStretch();
    hbox_linear->setSpacing(0);
    gbox_nonl->setLayout(hbox_linear);

    mainlayout->addWidget(gbox_nonl);

    QGroupBox* gbox_corer = new QGroupBox(w);
    gbox_corer->setTitle(tr("Coercivity"));
    QFormLayout* form_coer = new QFormLayout;
    edit_coer = new QLineEdit(w);
    form_coer->addRow(tr("T"),edit_coer);
    gbox_corer->setLayout(form_coer);

    QGroupBox* gbox_conduct = new QGroupBox(w);
    gbox_conduct->setTitle(tr("Electrical Conductivity"));
    QFormLayout* form_conduct = new QFormLayout;
    edit_conduct = new QLineEdit(w);
    form_conduct->addRow(tr("S/m"),edit_conduct);
    gbox_conduct->setLayout(form_conduct);

    QHBoxLayout* coer_conduct = new QHBoxLayout;
    coer_conduct->addWidget(gbox_corer);
    coer_conduct->addWidget(gbox_conduct);

    mainlayout->addLayout(coer_conduct);

    QGroupBox* gbox_source = new QGroupBox(w);
    gbox_source->setTitle(tr("Source Current Density"));
    QFormLayout* form_current = new QFormLayout;
    edit_current = new QLineEdit(w);
    form_current->addRow(tr("A/(m2)"),edit_current);
    gbox_source->setLayout(form_current);

    mainlayout->addWidget(gbox_source);

    w->setLayout(mainlayout);

    connect(combo_bhtype,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),w,[gbox_linear,gbox_nonl](int index){
        if(index == 0){
            gbox_linear->setEnabled(true);
            gbox_nonl->setEnabled(false);
        }
        if(index == 1){
            gbox_linear->setEnabled(false);
            gbox_nonl->setEnabled(true);
        }
    });
    /** 根据材料的属性设置，有可能材料是非线性的，但是暂时没有设置bh数据 **/
    if(!m_material->m_linear || m_material->BHpoints > 0){
        combo_bhtype->setCurrentIndex(1);
        emit combo_bhtype->currentIndexChanged(1);
    }else{
        combo_bhtype->setCurrentIndex(0);
        emit combo_bhtype->currentIndexChanged(0);
    }

    connect(bt_bhcurve, &QPushButton::clicked, this, &PF_MagMaterialDialog::slotAddBHCurve);
    mainlayout->addStretch();
    return w;
}

QWidget *PF_MagMaterialDialog::createHeatPage()
{
    QWidget* w = new QWidget(this);

    QVBoxLayout* mainlayout = new QVBoxLayout(w);
    /** 选择线性or非线性 **/
    QFormLayout* formlayout = new QFormLayout;
    combo_condtype = new QComboBox(w);
    combo_condtype->addItem(tr("Linear heat conductivity"));
    combo_condtype->addItem(tr("Nonlinear heat conductivity"));

    formlayout->addRow(tr("Heat conductivity Type"),combo_condtype);
    formlayout->setLabelAlignment(Qt::AlignLeft);

    mainlayout->addLayout(formlayout);

    /** 线性热导率设置 **/
    QGroupBox *gbox_linear = new QGroupBox(tr("Linear Material Properties"), w);
    QFormLayout *form_linear = new QFormLayout(gbox_linear);
    edit_lambdax = new QLineEdit(gbox_linear);
    edit_lambday = new QLineEdit(gbox_linear);
    form_linear->addRow(tr("Heat conductivity in x(W/(m*k)): "), edit_lambdax);
    form_linear->addRow(tr("Heat conductivity in y(W/(m*k)): "), edit_lambday);
    gbox_linear->setLayout(form_linear);
    mainlayout->addWidget(gbox_linear);

    /** 非线性热导率设置 **/
    QGroupBox *gbox_nonlinear = new QGroupBox(tr("Nonlinear Material Properties"), w);
    QHBoxLayout *layout_nonlinear = new QHBoxLayout(gbox_nonlinear);
    QPushButton *curvebutton = new QPushButton(tr("Heat conductivity-Temperature Curve"), gbox_nonlinear);

    QFormLayout *form_nonlinear = new QFormLayout(gbox_nonlinear);
    edit_Tmax = new QLineEdit(gbox_nonlinear);
    form_nonlinear->addRow(tr("Tmax(K): "), edit_Tmax);
    layout_nonlinear->addWidget(curvebutton, 1);
    layout_nonlinear->addLayout(form_nonlinear, 1);
    layout_nonlinear->setSpacing(0);
    form_nonlinear->setFormAlignment(Qt::AlignCenter);
    mainlayout->addWidget(gbox_nonlinear);

    /** 选择热源 **/
    QFormLayout *typelayout = new QFormLayout(w);
    sourcetype = new QComboBox(w);
    typelayout->addRow(tr("Heat Source"), sourcetype);
    sourcetype->addItem(tr("Other fixed internal heat source"));
    sourcetype->addItem(tr("Joule heat"));
    mainlayout->addLayout(typelayout);

    /** 内热源设置 **/
    QGroupBox *gbox_source = new QGroupBox(tr("Heat Source Properties"), w);
    QFormLayout *form_source = new QFormLayout(gbox_source);
    edit_heatsource = new QLineEdit(gbox_source);
    form_source->addRow(tr("Heat Source Intensity: "), edit_heatsource);
    mainlayout->addWidget(gbox_source);

    mainlayout->addStretch();

    connect(combo_condtype,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),w,[gbox_linear,gbox_nonlinear](int index){
        if(index == 0){
            gbox_linear->setEnabled(true);
            gbox_nonlinear->setEnabled(false);
        }
        if(index == 1){
            gbox_linear->setEnabled(false);
            gbox_nonlinear->setEnabled(true);
        }
    });

    connect(sourcetype,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),w,[gbox_source](int index){
        if(index == 0){
            gbox_source->setEnabled(true);
        }
        if(index == 1){
            gbox_source->setEnabled(false);
        }
    });

    connect(curvebutton, &QPushButton::clicked, this, &PF_MagMaterialDialog::slotAddCondTempCurve);

    return w;
}

/*!
 \brief 赋值材料属性

 \param material
*/
void PF_MagMaterialDialog::setMaterial(CMaterialProp *material)
{
    m_material = material;
    updateDialog();
}

CMaterialProp *PF_MagMaterialDialog::getMaterial()
{
    if(m_material)
        return m_material;
    else
        return nullptr;
}

/*!
 \brief 根据材料值，更新对话框的显示，TODO：需要更新

*/
void PF_MagMaterialDialog::updateDialog()
{
    edit_name->setText(m_material->BlockName);
    edit_ux->setText(QString::number(m_material->mu_x));
    edit_uy->setText(QString::number(m_material->mu_y));
    edit_hx->setText(QString::number(m_material->Theta_hx));
    edit_hy->setText(QString::number(m_material->Theta_hy));
    edit_conduct->setText(QString::number(m_material->Cduct));
    edit_coer->setText(QString::number(m_material->H_c));
    edit_current->setText(QString::number(m_material->Jsrc.re));
    if(m_material->m_linear){
        combo_bhtype->setCurrentIndex(0);
        emit combo_bhtype->currentIndexChanged(0);
    }else{
        combo_bhtype->setCurrentIndex(1);
        emit combo_bhtype->currentIndexChanged(1);
    }

    /** 温度场材料值更新 **/
    edit_lambdax->setText(QString::number(m_material->h_lambdax));
    edit_lambday->setText(QString::number(m_material->h_lambday));
    edit_heatsource->setText(QString::number(m_material->h_source));
    sourcetype->setCurrentIndex(m_material->h_sourcetype);
    if(m_material->h_condlinear){
        combo_condtype->setCurrentIndex(0);
        emit combo_condtype->currentIndexChanged(0);
    }else{
        combo_condtype->setCurrentIndex(1);
        emit combo_condtype->currentIndexChanged(1);
    }
}

/*!
 \brief 根据对话框填写更新材料变量，TODO：需要更新

*/
void PF_MagMaterialDialog::updateMaterial()
{
    m_material->BlockName = edit_name->text();
    m_material->mu_x = edit_ux->text().toDouble();
    m_material->mu_y = edit_uy->text().toDouble();
    m_material->Theta_hx = edit_hx->text().toDouble();
    m_material->Theta_hy = edit_hy->text().toDouble();
    m_material->Cduct = edit_conduct->text().toDouble();
    m_material->H_c = edit_coer->text().toDouble();
    m_material->Jsrc.re = edit_current->text().toDouble();
    if(combo_bhtype->currentIndex() == 0){
        m_material->m_linear = true;
    }else{
        m_material->m_linear = false;
    }

    /** 更新热场相关参数 **/
    m_material->h_lambdax = edit_lambdax->text().toDouble();
    m_material->h_lambday = edit_lambday->text().toDouble();
    m_material->h_sourcetype = sourcetype->currentIndex();
    if(sourcetype->currentIndex() == 0){
        m_material->h_source = edit_heatsource->text().toDouble();
    }
    if(combo_condtype->currentIndex() == 0){
        m_material->h_condlinear = true;
    }else{
        m_material->h_condlinear = false;
    }
}

/*!
 \brief 用户在完成确认之后，对话框关闭之前更新材料变量。

*/
void PF_MagMaterialDialog::accept()
{
    updateMaterial();
    done(QDialog::Accepted);
}

void PF_MagMaterialDialog::slotAddBHCurve()
{
    PoofeeSay<<tr("Edit B-H data.");
    PF_BHCurveDialog *bhcurve = new PF_BHCurveDialog(m_material,Core::ICore::dialogParent());
    bhcurve->setHorizontalHeaderLabels(QStringList() << tr("B(Flux density value(T))") << tr("H(Field value(A.m-1))"));
    if(!bhcurve->exec()){
        m_material->BHpoints = bhcurve->getBHPoints();
        if(m_material->BHdata != nullptr){
            free(m_material->BHdata);
        }
        m_material->BHdata = bhcurve->getItemData();
        PoofeeSay<<tr("B-H data is modified!");
    };
}

void PF_MagMaterialDialog::slotAddCondTempCurve()
{
    PoofeeSay<<tr("Edit Heat conductivity-Temperature data.");
    PF_BHCurveDialog *curve = new PF_BHCurveDialog(m_material,Core::ICore::dialogParent());
    curve->setHorizontalHeaderLabels(QStringList() << tr("lambda(Heat conductivity(W/(m*K)))") << tr("T(Temperature(K))"));
    if(!curve->exec()){
        m_material->h_nonlpoints = curve->getBHPoints();
        if(m_material->h_nonldata != nullptr){
            free(m_material->h_nonldata);
        }
        m_material->h_nonldata = curve->getItemData();
        PoofeeSay<<tr("Heat conductivity-Temperature data is modified!");
    }
}


