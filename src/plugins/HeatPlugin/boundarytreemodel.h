#ifndef BOUNDARYTREEMODEL_H
#define BOUNDARYTREEMODEL_H

#include <project/pf_node.h>
#include <utils/treemodel.h>
#include <project/pf_projectmodel.h>

#include "boundaryprop.h"

using namespace ProjectExplorer;

class BoundaryTreeNode : public LeafNode
{
public:
    BoundaryTreeNode(CHBoundaryProp* boundary);

    CHBoundaryProp* m_boundary;
};

class BoundaryTreeModel : public Utils::BaseTreeModel
{
    Q_OBJECT

public:
    BoundaryTreeModel(QObject *parent);
//    ~BoundaryTreeModel();

//    // QAbstractItemModel
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

//    Node *nodeForIndex(const QModelIndex &index) const;
//    WrapperNode *wrapperForNode(const Node *node) const;
//    QModelIndex indexForNode(const Node *node) const;

//    void onExpanded(const QModelIndex &idx);
//    void onCollapsed(const QModelIndex &idx);

//    bool loadBuiltinMaterials();

//    void updateSubtree(FolderNode *node);
//    void rebuildModel();
//    void addFolderNode(WrapperNode *parent, FolderNode *folderNode, QSet<Node *> *seen);

//    void handleProjectAdded(PF_Project *project);
//    void handleProjectRemoved(PF_Project *project);
//    WrapperNode *nodeForProject(const PF_Project *project) const;
//    void addOrRebuildProjectModel(PF_Project *project);

//    QTimer m_timer;
////    QSet<ExpandData> m_toExpand;
//    QColor m_enabledTextColor;
//    QColor m_disabledTextColor;

//    std::vector<std::unique_ptr<FolderNode>> nodes;
};

#endif // BOUNDARYTREEMODEL_H
