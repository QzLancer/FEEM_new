#include "paramwidget.h"

#include <QLabel>
#include <QDebug>

ParamWidget::ParamWidget(QWidget *parent)
    : QWidget(parent),
      mContactType(PLANE_PLANE),
      mCalculateType(IMPACT),
      mTabWidget(new QTabWidget(this)),
      mImpactWidget(new QWidget(this))
{
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(mTabWidget);

    addPhysicsTab();
    addReactionTab();
    addCollisionTab();
}

void ParamWidget::addPhysicsTab()
{
    QWidget *physicstab = new QWidget(this);

    QLabel *opendistancelabel = new QLabel(tr("Open Distance(m)"), physicstab);
    mOpenDistanceEdit = new QLineEdit(physicstab);
    QLabel *strokelabel = new QLabel(tr("Stroke(m)"), physicstab);
    mStrokeEdit = new QLineEdit(physicstab);
    QLabel *movingmasslabel = new QLabel(tr("The Mass of Moving Contact(kg)"), physicstab);
    mMovingMassEdit = new QLineEdit(physicstab);
    QLabel *concentratedmasslabel = new QLabel(tr("Concentrated Mass(kg)"));
    mConcentratedMassEdit = new QLineEdit(physicstab);

    QVBoxLayout *vlayout = new QVBoxLayout(physicstab);
    vlayout->addWidget(opendistancelabel);
    vlayout->addWidget(mOpenDistanceEdit);
    vlayout->addWidget(strokelabel);
    vlayout->addWidget(mStrokeEdit);
    vlayout->addWidget(movingmasslabel);
    vlayout->addWidget(mMovingMassEdit);
    vlayout->addWidget(concentratedmasslabel);
    vlayout->addWidget(mConcentratedMassEdit);
    vlayout->addStretch();

    mTabWidget->addTab(physicstab, tr("Physics"));

    /**LineEdit初始值**/
    mOpenDistanceEdit->setText("0.0017");
    mStrokeEdit->setText("0.00268");
    mMovingMassEdit->setText("0.007");
    mConcentratedMassEdit->setText("0.0129");
}

void ParamWidget::addReactionTab()
{
    QWidget *reactiontab = new QWidget(this);

    QLabel *contactspringstiffnesslabel = new QLabel(tr("The Stiffness of the Contact Spring(N/m)"), reactiontab);
    mContactSpringStiffnessEdit = new QLineEdit(this);
    QLabel *returnspringstiffnesslabel = new QLabel(tr("The Stiffness of the Return Spring(N/m)"), reactiontab);
    mReturnSpringStiffnessEdit = new QLineEdit(this);
    QLabel *contactspringpreloadslabel = new QLabel(tr("The Preloads of Contact Spring(N)"), reactiontab);
    mContactSpringPreloadsEdit = new QLineEdit(this);
    QLabel *returnspringpreloadslabel = new QLabel(tr("The Preloads of Return Spring(N)"), reactiontab);
    mReturnSpringPreloadsEdit = new QLineEdit(this);

    QVBoxLayout *vlayout = new QVBoxLayout(reactiontab);
    vlayout->addWidget(contactspringstiffnesslabel);
    vlayout->addWidget(mContactSpringStiffnessEdit);
    vlayout->addWidget(returnspringstiffnesslabel);
    vlayout->addWidget(mReturnSpringStiffnessEdit);
    vlayout->addWidget(contactspringpreloadslabel);
    vlayout->addWidget(mContactSpringPreloadsEdit);
    vlayout->addWidget(returnspringpreloadslabel);
    vlayout->addWidget(mReturnSpringPreloadsEdit);
    vlayout->addStretch();

    mTabWidget->addTab(reactiontab, tr("Reaction System"));

    /**LineEdit初始值**/
    mContactSpringStiffnessEdit->setText("13000");
    mReturnSpringStiffnessEdit->setText("370");
    mContactSpringPreloadsEdit->setText("7");
    mReturnSpringPreloadsEdit->setText("6");
}

void ParamWidget::addCollisionTab()
{
    QWidget *collisiontab = new QWidget(this);

    /**碰撞接触Box**/
    QGroupBox *contacttypegroup = new QGroupBox(tr("Contact Type"), collisiontab);
    mContactTypeBox = new QComboBox(contacttypegroup);
    mContactTypeBox->addItem(tr("Plane-Plane"));
    mContactTypeBox->addItem(tr("Sphere-Sphere"));
    mContactTypeBox->addItem(tr("Curve-Plane"));
    mContactTypeBox->addItem(tr("Curve-Curve"));
    QVBoxLayout *contacttypelayout = new QVBoxLayout(contacttypegroup);
    contacttypelayout->addWidget(mContactTypeBox);

    /**配置ImpactWidget**/
    QLabel *contactstiffnesslabel = new QLabel(tr("Contact Stiffness(N/m)"), mImpactWidget);
    mContactStiffnessEdit = new QLineEdit(mImpactWidget);
    QLabel *contactpenetrationlabel = new QLabel(tr("Contact Penetration(m)"), mImpactWidget);
    mContactPenetrationEdit = new QLineEdit(mImpactWidget);
    QLabel *contactdampinglabel = new QLabel(tr("Contact Damping"), mImpactWidget);
    mContactDampingEdit = new QLineEdit(mImpactWidget);
    QLabel *contactcoefficientlabel = new QLabel(tr("Contact Coefficient"), mImpactWidget);
    mContactCoefficientEdit = new QLineEdit(mImpactWidget);
    QVBoxLayout *impactwidgetlayout = new QVBoxLayout(mImpactWidget);
    impactwidgetlayout->setMargin(0);
    impactwidgetlayout->addWidget(contactstiffnesslabel);
    impactwidgetlayout->addWidget(mContactStiffnessEdit);
    impactwidgetlayout->addWidget(contactpenetrationlabel);
    impactwidgetlayout->addWidget(mContactPenetrationEdit);
    impactwidgetlayout->addWidget(contactdampinglabel);
    impactwidgetlayout->addWidget(mContactDampingEdit);
    impactwidgetlayout->addWidget(contactcoefficientlabel);
    impactwidgetlayout->addWidget(mContactCoefficientEdit);
    impactwidgetlayout->addStretch();

    /**计算方法Box**/
    QGroupBox *calculatetypegroup = new QGroupBox(tr("Calculate Type"), collisiontab);
    mCalculateTypeBox = new QComboBox(calculatetypegroup);
    mCalculateTypeBox->addItem(tr("Impact"));
    mCalculateTypeBox->addItem(tr("Fractal"));
    mCalculateTypeBox->setItemData(1, 0, Qt::UserRole - 1);
    QVBoxLayout *calculatetypelayout = new QVBoxLayout(calculatetypegroup);
    calculatetypelayout->addWidget(mCalculateTypeBox);
    calculatetypelayout->addWidget(mImpactWidget);

    /**主要layout配置**/
    QVBoxLayout *mainlayout = new QVBoxLayout(collisiontab);
    mainlayout->addWidget(contacttypegroup);
    mainlayout->addWidget(calculatetypegroup);
    mainlayout->addStretch();
    mTabWidget->addTab(collisiontab, tr("Collision Contact"));

    connect(mContactTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeContactType(int)));
    connect(mCalculateTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeCalculateType(int)));

    /**LineEdit初始值**/
    mContactStiffnessEdit->setText("5.3e+8");
    mContactPenetrationEdit->setText("0.0001");
    mContactDampingEdit->setText("1000");
    mContactCoefficientEdit->setText("1.5");
}

void ParamWidget::slotChangeContactType(int index)
{
    mContactType = static_cast<ContactType>(index);
}

void ParamWidget::slotChangeCalculateType(int index)
{
    mCalculateType = static_cast<CalculateType>(index);
    switch (mCalculateType) {
    case IMPACT:
        mImpactWidget->show();
        break;
    case FRACTAL:
        mImpactWidget->hide();
        break;
    }
}
