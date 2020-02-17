#ifndef PF_HEATFEMNODE_H
#define PF_HEATFEMNODE_H

#include "pf_heat2dsproject.h"

#include <project/pf_node.h>

namespace HeatFEMProjectManagerPlugin {

class PF_HeatFEMNode : public ProjectExplorer::ProjectNode
{
public:
    PF_HeatFEMNode(PF_Heat2DSProject* pro);
};

}   //namespace HeatFEMProjectManagerPlugin


#endif // PF_HEATFEMNODE_H
