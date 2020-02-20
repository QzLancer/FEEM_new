#ifndef PF_SOLVERNODE_H
#define PF_SOLVERNODE_H

#include "solver_global.h"

#include <project/pf_node.h>
namespace Solver {
class FEEM_SOLVER_EXPORT PF_SolverNode : public ProjectExplorer::FolderNode
{
public:
    PF_SolverNode(const QString &displayName, QIcon icon=QIcon());
    ~PF_SolverNode() override;
};
}//namespace Solver

#endif // PF_SOLVERNODE_H
