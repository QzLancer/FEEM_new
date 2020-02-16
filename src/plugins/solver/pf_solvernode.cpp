#include "pf_solvernode.h"

namespace Solver {

PF_SolverNode::PF_SolverNode(const QString& displayName, QIcon icon)
    :ProjectExplorer::FolderNode(displayName,ProjectExplorer::NodeType::Folder,icon)
{

}

PF_SolverNode::~PF_SolverNode()
{

}


}//namespace Solver
