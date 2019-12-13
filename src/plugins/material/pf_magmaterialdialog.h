#ifndef PF_MAGMATERIALDIALOG_H
#define PF_MAGMATERIALDIALOG_H
#include "material_global.h"
#include <QDialog>

class QLineEdit;
class QTabWidget;
class CMaterialProp;
class QComboBox;
/*!
 \brief 创建一个电磁材料的材料设置窗口

*/
class FEEM_MATERIAL_EXPORT PF_MagMaterialDialog : public QDialog
{
    Q_OBJECT
public:
    PF_MagMaterialDialog(CMaterialProp* material,QWidget* parent = nullptr);
    ~PF_MagMaterialDialog();

    void initialization();

    QWidget* createBasicPage();
    QWidget* createMagneticPage();
    QWidget* createHeatPage();

    void setMaterial(CMaterialProp* material);
    CMaterialProp* getMaterial();

    void updateDialog();
    void updateMaterial();

    void accept();

public slots:
    void slotAddBHCurve();
private:
    QLineEdit* edit_name;
    QLineEdit* edit_comment;
    QTabWidget* tab_material;
    QLineEdit* edit_ux;
    QLineEdit* edit_uy;
    QLineEdit* edit_hx;
    QLineEdit* edit_hy;
    QLineEdit* edit_conduct;
    QLineEdit* edit_coer;
    QLineEdit* edit_current;
    QLineEdit* edit_hmax;
    QComboBox* combo_bhtype;
    CMaterialProp* m_material;
};

#endif // PF_MAGMATERIALDIALOG_H
