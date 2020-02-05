#include "pf_femprojectaccessor.h"

#include "pf_project.h"

#include <app/app_version.h>

using namespace Utils;
using namespace ProjectExplorer;

namespace ProjectExplorer {

PF_FEMProjectAccessor::PF_FEMProjectAccessor(PF_Project* project)
    :PF_ProjectAccessor(project->mimeType(),project->displayName(),Core::Constants::IDE_DISPLAY_NAME),
     m_project(project)
{
    const QString femProject = projectFile();
    setBaseFilePath(Utils::FileName::fromString(femProject));
}

PF_Project*PF_FEMProjectAccessor::project() const
{
    return m_project;
}

/**
 * @brief 每一个project的项目文件名可能不相同。
 *
 * @return QString
 */
QString PF_FEMProjectAccessor::projectFile() const
{
    return m_project->document()->filePath().toString();
}

}// ProjectExplorer
