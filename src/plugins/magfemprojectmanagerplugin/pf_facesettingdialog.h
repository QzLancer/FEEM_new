#ifndef PF_FACESETTINGDIALOG_H
#define PF_FACESETTINGDIALOG_H

#include "pf_commonfemproject.h"

#include <QDialog>

class QComboBox;

namespace MagFEMProjectManagerPlugin {
/*!
 \brief 材料设置，但是Project那么多，每个都要新建一个吗？？

*/
class PF_FaceSettingDialog : public QDialog
{
public:
    PF_FaceSettingDialog(QWidget *parent = nullptr,PF_CommonFEMProject* pro=nullptr,int index=-1);
    ~PF_FaceSettingDialog();

private:
    PF_CommonFEMProject* m_project;
    int m_faceIndex;
    QComboBox* m_combobox;
};
}//MagFEMProjectManagerPlugin
#endif // PF_FACESETTINGDIALOG_H
