#ifndef PF_MAGFEMFILE_H
#define PF_MAGFEMFILE_H

#include <QHash>
#include <QStringList>
#include <QMap>
#include <QFutureWatcher>

#include <memory>

namespace MagneticFEM {

class PF_Mag2DSProject;

class PF_MagFEMFile
{
public:
    PF_MagFEMFile(PF_Mag2DSProject* m_project);
    ~PF_MagFEMFile();
private:
    PF_Mag2DSProject* m_project = nullptr;
};

}// namespace MagneticFEM
#endif // PF_MAGFEMFILE_H
