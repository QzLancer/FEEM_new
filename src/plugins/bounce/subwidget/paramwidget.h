#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "bouncetab.h"

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>

class ParamWidget : public QWidget
{
    Q_OBJECT
public:
    enum ContactType{
        PLANE_PLANE = 0,
        SPHERE_SPHERE = 1,
        CURVE_PLANE = 2,
        CURVE_CURVE = 3,
    };

    enum CalculateType{
        IMPACT = 0,
        FRACTAL = 1,
    };

    explicit ParamWidget(QWidget *parent = nullptr);

    /**物理属性**/
    QLineEdit *mOpenDistanceEdit;           /**开距**/
    QLineEdit *mStrokeEdit;                 /**行程**/
    QLineEdit *mMovingMassEdit;             /**动触头的质量**/
    QLineEdit *mConcentratedMassEdit;       /**可动部件的质量**/

    /**反力系统**/
    QLineEdit *mContactSpringStiffnessEdit; /**触头弹簧刚度**/
    QLineEdit *mReturnSpringStiffnessEdit;  /**返回弹簧刚度**/
    QLineEdit *mContactSpringPreloadsEdit;  /**触头弹簧预压力**/
    QLineEdit *mReturnSpringPreloadsEdit;   /**返回弹簧预压力**/

    /**碰撞接触**/
    QComboBox *mContactTypeBox;             /**接触类型**/
    QComboBox *mCalculateTypeBox;           /**求解方式**/
    QLineEdit *mContactStiffnessEdit;       /**接触刚度**/
    QLineEdit *mContactPenetrationEdit;     /**接触深度**/
    QLineEdit *mContactDampingEdit;         /**接触阻尼**/
    QLineEdit *mContactCoefficientEdit;     /**接触系数**/

    ContactType mContactType;
    CalculateType mCalculateType;

    QTabWidget *mTabWidget;

signals:

public slots:
    void slotChangeContactType(int index);
    void slotChangeCalculateType(int index);

private:
    void addPhysicsTab();
    void addReactionTab();
    void addCollisionTab();

    QWidget *mImpactWidget;
};

#endif // PARAMETERSWIDGET_H
