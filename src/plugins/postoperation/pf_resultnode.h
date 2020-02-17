#ifndef PF_RESULTNODE_H
#define PF_RESULTNODE_H

#include "postoperation_global.h"

#include <project/pf_node.h>

namespace Postoperation {

class FEEM_POSTOPERATION_EXPORT PF_ResultNode : public ProjectExplorer::FolderNode
{
public:
    PF_ResultNode(const QString &displayName, QIcon icon=QIcon());
    ~PF_ResultNode() override;
};

}//namespace Postoperation


#endif // PF_RESULTNODE_H
