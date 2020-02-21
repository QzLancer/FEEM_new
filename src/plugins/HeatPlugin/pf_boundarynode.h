#ifndef PF_BOUNDARYNODE_H
#define PF_BOUNDARYNODE_H

#include "heatplugin_global.h"

#include <project/pf_node.h>

class HEATPLUGINSHARED_EXPORT PF_BoundaryNode : public ProjectExplorer::FolderNode
{
public:
    PF_BoundaryNode(const QString &displayName, QIcon icon=QIcon());
    ~PF_BoundaryNode() override;
};

#endif // PF_MATERIALNODE_H
