#pragma once

#include "project_export.h"

#include <QString>

#include <functional>

namespace Utils {
class FileName;
class MimeType;
} // Utils

namespace ProjectExplorer {

class PF_Project;

class FEEM_PROJECT_EXPORT PF_ProjectManager
{
public:
    static bool canOpenProjectForMimeType(const Utils::MimeType &mt);
    static PF_Project *openProject(const Utils::MimeType &mt, const Utils::FileName &fileName);

    template <typename T>
    static void registerProjectType(const QString &mimeType)
    {
        PF_ProjectManager::registerProjectCreator(mimeType, [](const Utils::FileName &fileName) {
            return new T(fileName);
        });
    }

private:
    static void registerProjectCreator(const QString &mimeType,
                                       const std::function<PF_Project *(const Utils::FileName &)> &);
};

} // namespace ProjectExplorer
