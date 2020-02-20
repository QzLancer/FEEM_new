#include "pf_resultnode.h"

namespace Postoperation {

PF_ResultNode::PF_ResultNode(const QString& displayName, QIcon icon)
    :ProjectExplorer::FolderNode(displayName,ProjectExplorer::NodeType::Folder,icon)
{

}

PF_ResultNode::~PF_ResultNode()
{

}


}//namespace Postoperation
