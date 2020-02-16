#include "pf_meshnode.h"

namespace Mesh{

PF_MeshNode::PF_MeshNode(const QString& displayName, QIcon icon)
    :ProjectExplorer::FolderNode(displayName,ProjectExplorer::NodeType::Folder,icon)
{

}

PF_MeshNode::~PF_MeshNode()
{

}

}//namespace Mesh
