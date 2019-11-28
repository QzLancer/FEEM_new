#ifndef PF_MAGFEMNODE_H
#define PF_MAGFEMNODE_H

#include "pf_mag2dsproject.h"

#include <project/pf_node.h>

namespace MagFEMProjectManagerPlugin {

class PF_MagFEMNode : public ProjectExplorer::ProjectNode
{
public:
    PF_MagFEMNode(PF_Mag2DSProject* pro);
};

}// namespace MagFEMProjectManagerPlugin


#endif // PF_MAGFEMNODE_H
