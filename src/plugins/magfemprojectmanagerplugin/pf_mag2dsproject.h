#ifndef PF_MAG2DSPROJECT_H
#define PF_MAG2DSPROJECT_H

#include <project/pf_project.h>

#include <QVector>

namespace MagFEMProjectManagerPlugin {
class PF_MagFEMNode;
class PF_Mag2DSProject : public ProjectExplorer::PF_Project
{
public:
    PF_Mag2DSProject();
    ~PF_Mag2DSProject();

private:

};

class PF_Mag2DSNodeTreeBuilder
{
public:
    static std::unique_ptr<PF_MagFEMNode> buildTree(PF_Mag2DSProject* pro);
};
}// namespace MagFEMProjectManagerPlugin


#endif // PF_MAG2DSPROJECT_H
