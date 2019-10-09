#ifndef PF_NODETREEBUILDER_H
#define PF_NODETREEBUILDER_H

#include <memory>

namespace ProjectExplorer {
class ProjectNode;
class PF_Project;

class PF_NodeTreeBuilder
{
public:
    static std::unique_ptr<ProjectNode> buildTree(PF_Project *project);
};
}//namespace ProjectExplorer
#endif // PF_NODETREEBUILDER_H
