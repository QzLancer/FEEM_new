#ifndef PF_FEMPROJECTACCESSOR_H
#define PF_FEMPROJECTACCESSOR_H

#include "project_export.h"

#include <utils/fileutils.h>
#include <utils/pf_projectaccessor.h>

#include <QHash>
#include <QVariantMap>
#include <QMessageBox>

namespace ProjectExplorer {
class PF_Project;
/**
 * @brief 用于读取fem project的工具
 *
 */
class FEEM_PROJECT_EXPORT PF_FEMProjectAccessor : public Utils::PF_ProjectAccessor
{
public:
    PF_FEMProjectAccessor(PF_Project* project);

    PF_Project* project() const;

    virtual QString projectFile() const;

private:
    PF_Project* m_project;
};
}// ProjectExplorer


#endif // PF_FEMPROJECTACCESSOR_H
