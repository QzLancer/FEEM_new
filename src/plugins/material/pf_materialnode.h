#ifndef PF_MATERIALNODE_H
#define PF_MATERIALNODE_H

#include "material_global.h"

#include <project/pf_node.h>

class FEEM_MATERIAL_EXPORT PF_MaterialNode : public ProjectExplorer::FolderNode
{
public:
    PF_MaterialNode(const QString &displayName, QIcon icon=QIcon());
    ~PF_MaterialNode() override;
};

#endif // PF_MATERIALNODE_H
