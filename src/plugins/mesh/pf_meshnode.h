#ifndef PF_MESHNODE_H
#define PF_MESHNODE_H

#include "mesh_global.h"

#include <project/pf_node.h>

namespace Mesh{

/**
 * @brief 分网节点的node
 *
 */
class FEEM_MESH_EXPORT PF_MeshNode : public ProjectExplorer::FolderNode
{
public:
    PF_MeshNode(const QString &displayName, QIcon icon=QIcon());
    ~PF_MeshNode() override;
};

}//namespace Mesh

#endif // PF_MESHNODE_H
