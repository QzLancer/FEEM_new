#include "pf_projecttreewidget.h"

#include <utils/navigationtreeview.h>
#include "pf_projectmodel.h"
#include "pf_projecttree.h"
#include "pf_node.h"
#include "pf_project.h"

#include <coreplugin/geometrymanager/geometrymanager.h>

#include <output/outputpluginplugin.h>

#include <QApplication>
#include <QSettings>

#include <QStyledItemDelegate>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QToolButton>
#include <QPainter>
#include <QAction>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>


namespace ProjectExplorer {
class PF_ProjectTreeItemDelegate : public QStyledItemDelegate
{
public:
    PF_ProjectTreeItemDelegate(QTreeView *view)
        : QStyledItemDelegate(view)
        ,m_view(view)
    {
        connect(m_view->model(), &QAbstractItemModel::modelReset,
                this, &PF_ProjectTreeItemDelegate::deleteAllIndicators);

        // Actually this only needs to delete the indicators in the effected rows and *after* it,
        // but just be lazy and nuke all the indicators.
        connect(m_view->model(), &QAbstractItemModel::rowsAboutToBeRemoved,
                this, &PF_ProjectTreeItemDelegate::deleteAllIndicators);
        connect(m_view->model(), &QAbstractItemModel::rowsAboutToBeInserted,
                this, &PF_ProjectTreeItemDelegate::deleteAllIndicators);
    }

    ~PF_ProjectTreeItemDelegate() override
    {
        deleteAllIndicators();
    }

//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
//    {
//        QStyledItemDelegate::paint(painter, option, index);

//        if (index.data(Project::isParsingRole).toBool()) {
//            QStyleOptionViewItem opt = option;
//            initStyleOption(&opt, index);
//            ProgressIndicatorPainter *indicator = findOrCreateIndicatorPainter(index);

//            QStyle *style = option.widget ? option.widget->style() : QApplication::style();
//            const QRect rect = style->subElementRect(QStyle::SE_ItemViewItemDecoration, &opt, opt.widget);

//            indicator->paint(*painter, rect);
//        } else {
//            delete m_indicators.value(index);
//            m_indicators.remove(index);
//        }
//    }

private:
//    ProgressIndicatorPainter *findOrCreateIndicatorPainter(const QModelIndex &index) const
//    {
//        ProgressIndicatorPainter *indicator = m_indicators.value(index);
//        if (!indicator)
//            indicator = createIndicatorPainter(index);
//        return indicator;
//    }

//    ProgressIndicatorPainter *createIndicatorPainter(const QModelIndex &index) const
//    {
//        auto indicator = new ProgressIndicatorPainter(ProgressIndicatorSize::Small);
//        indicator->setUpdateCallback([index, this]() { m_view->update(index); });
//        indicator->startAnimation();
//        m_indicators.insert(index, indicator);
//        return indicator;
//    }

    void deleteAllIndicators()
    {
//        qDeleteAll(m_indicators);
//        m_indicators.clear();
    }

//    mutable QHash<QModelIndex, ProgressIndicatorPainter *> m_indicators;
    QTreeView *m_view;
};


class PF_ProjectTreeView : public Utils::NavigationTreeView
{
public:
    PF_ProjectTreeView()
    {
        setEditTriggers(QAbstractItemView::EditKeyPressed);
        setContextMenuPolicy(Qt::CustomContextMenu);
        setDragEnabled(true);
        setDragDropMode(QAbstractItemView::DragOnly);
        //        m_context = new IContext(this);
        //        m_context->setContext(Context(ProjectExplorer::Constants::C_PROJECT_TREE));
        //        m_context->setWidget(this);

        //        ICore::addContextObject(m_context);

//        connect(this, &PF_ProjectTreeView::expanded,
//                this, &PF_ProjectTreeView::invalidateSize);
//        connect(this, &PF_ProjectTreeView::collapsed,
//                this, &PF_ProjectTreeView::invalidateSize);
    }

    void invalidateSize()
    {
        m_cachedSize = -1;
    }

    void setModel(QAbstractItemModel *newModel) override
    {
        // Note: Don't connect to column signals, as we have only one column
        if (model()) {
            QAbstractItemModel *m = model();
            disconnect(m, &QAbstractItemModel::dataChanged,
                       this, &PF_ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::layoutChanged,
                       this, &PF_ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::modelReset,
                       this, &PF_ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsInserted,
                       this, &PF_ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsMoved,
                       this, &PF_ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsRemoved,
                       this, &PF_ProjectTreeView::invalidateSize);
        }
        if (newModel) {
            connect(newModel, &QAbstractItemModel::dataChanged,
                    this, &PF_ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::layoutChanged,
                    this, &PF_ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::modelReset,
                    this, &PF_ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsInserted,
                    this, &PF_ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsMoved,
                    this, &PF_ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsRemoved,
                    this, &PF_ProjectTreeView::invalidateSize);
        }
        Utils::NavigationTreeView::setModel(newModel);
    }

    ~PF_ProjectTreeView() override
    {
        //        ICore::removeContextObject(m_context);
        //        delete m_context;
    }

    int sizeHintForColumn(int column) const override
    {
        if (m_cachedSize < 0)
            m_cachedSize = NavigationTreeView::sizeHintForColumn(column);

        return m_cachedSize;
    }

private:
    mutable int m_cachedSize = -1;
    //    IContext *m_context;
};
/**
 * @brief 以树的形式保存一个工程
 *
 * @param parent
 */
PF_ProjectTreeWidget::PF_ProjectTreeWidget(QWidget *parent) : QWidget(parent)
{
    m_model = new PF_ProjectModel(this);
//    auto noderoot = new Node(QString("root:untitled.mph"),NodeType::Leaf,QIcon(":/imgs/model_3d.png"));
//    auto nodedef = new Node(QString("Global Definitions"),NodeType::Leaf,QIcon(":/imgs/global_branch.png"));

//    auto nodemat = new Node(QString("Materials:Materials"),NodeType::Leaf,QIcon(":/imgs/material.png"));
//    auto nodecomp = new Node(QString("Component:Component1"),NodeType::Folder,QIcon(":/imgs/model_2d_axi.png"));
//    auto nodedefin = new Node(QString("Definitions"),NodeType::Leaf,QIcon(":/imgs/definitions.png"));
//    auto nodegeo = new Node(QString("Geometry1"),NodeType::Leaf,QIcon(":/imgs/geometry.png"));
//    auto nodemesh = new Node(QString("Mesh1"),NodeType::Leaf,QIcon(":/imgs/mesh.png"));

//    auto comp = new WrapperNode(nodecomp);
//    comp->appendChild(new WrapperNode(nodedefin));
//    comp->appendChild((new WrapperNode(nodegeo)));
//    comp->appendChild((new WrapperNode(nodemesh)));
//    auto def = new WrapperNode(nodedef);
//    def->appendChild(new WrapperNode(nodemat));
//    WrapperNode* root = new WrapperNode(noderoot);
//    root->appendChild(def);
//    root->appendChild(comp);
//    m_model->rootItem()->insertChild(0,root);

    m_view = new PF_ProjectTreeView;
    m_view->setModel(m_model);
    m_view->setItemDelegate(new PF_ProjectTreeItemDelegate(m_view));
    setFocusProxy(m_view);
    m_view->installEventFilter(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_view);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    /** 信号连接 **/
//    connect(m_model, &PF_ProjectModel::renamed,
//            this, &PF_ProjectTreeWidget::renamed);
    connect(m_model, &PF_ProjectModel::requestExpansion,
            m_view, &QTreeView::expand);
    /** 节点被选中的操作 ,如果是activated，需要双击或者回车
        如果是clicked，好像只支持鼠标单击触发**/
    connect(m_view, &QAbstractItemView::clicked,
            this, &PF_ProjectTreeWidget::openItem);
    connect(m_view, &QAbstractItemView::doubleClicked,
            this, &PF_ProjectTreeWidget::doubleopenItem);
//    connect(m_view, &QAbstractItemView::activated,
//            this, &PF_ProjectTreeWidget::openItem);
    connect(m_view->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &PF_ProjectTreeWidget::handleCurrentItemChange);
    /** 处理右键操作 **/
    connect(m_view, &QWidget::customContextMenuRequested,
            this, &PF_ProjectTreeWidget::showContextMenu);
    connect(m_view, &QTreeView::expanded,
            m_model, &PF_ProjectModel::onExpanded);
    connect(m_view, &QTreeView::collapsed,
            m_model, &PF_ProjectModel::onCollapsed);

    /** 将widget连接到projecttree **/
    PF_ProjectTree::registerWidget(this);
}

PF_ProjectTreeWidget::~PF_ProjectTreeWidget()
{
    PF_ProjectTree::unregisterWidget(this);
}

/*!
 \brief 当前节点

 \return Node
*/
Node *PF_ProjectTreeWidget::currentNode()
{
    return m_model->nodeForIndex(m_view->currentIndex());
}

void PF_ProjectTreeWidget::sync(Node* node)
{
    if (m_autoSync)
        setCurrentItem(node);
}

void PF_ProjectTreeWidget::collapseAll()
{
    m_view->collapseAll();
}

void PF_ProjectTreeWidget::expandAll()
{
    m_view->expandAll();
}

/*!
 \brief 处理选中的node的变化。

 \param current
*/
void PF_ProjectTreeWidget::handleCurrentItemChange(const QModelIndex &current)
{

}

/*!
 \brief 根据不同的node，显示不同的右键菜单。

 \param pos
*/
void PF_ProjectTreeWidget::showContextMenu(const QPoint &pos)
{
    qDebug()<<Q_FUNC_INFO;
    QModelIndex index = m_view->indexAt(pos);
    Node *node = m_model->nodeForIndex(index);
    PF_ProjectTree::showContextMenu(this, m_view->mapToGlobal(pos), node);
}

/*!
 \brief node选中激活之后的动作。应该只有LeafNode才能吧？

 \param mainIndex
*/
void PF_ProjectTreeWidget::openItem(const QModelIndex &mainIndex)
{
    Node *node = m_model->nodeForIndex(mainIndex);
    if (!node /*|| node->asLeafNode()*/)
        return;
    /** 不同的节点，跳转到相应的视图 **/
    switch (node->nodeType()) {
        case NodeType::Geometry:
        {
            break;
        }
        default:
        {
            break;
        }
    }
    //    qDebug()<<Q_FUNC_INFO<<node->displayName()<<" Clicked!";
    /** 激活几何视图 **/
    PF_Project* pro = PF_ProjectTree::projectForNode(node);
    if(pro)
        Core::GeometryManager::instance()->openCAD(pro->CAD());
    /** 如果是LeafNode，几何形状的话，设置选中，非几何的话，就是没选中 **/
    if(node->asLeafNode()){
        switch ((dynamic_cast<LeafNode*>(node)->leafType())) {
        case LeafType::Point:
        case LeafType::Line:
        case LeafType::Face:{
            PoofeeSay<<"You select "+node->displayName();
            pro->entitySelected(true,node);
            break;
        }
        case LeafType::CMaterialProp:{
            PoofeeSay<<"You select "+node->displayName();
            break;
        }
        default:{
            break;
        }
        }
    }else{
        pro->entitySelected(false);
    }
}

/*!
 \brief 适用于双击实现动作，这种情况下，节点必须是Leaf类型。

 \param mainIndex
*/
void PF_ProjectTreeWidget::doubleopenItem(const QModelIndex &mainIndex)
{
    Node *node = m_model->nodeForIndex(mainIndex);
    if (!node || node->asFolderNode())
        return;
    PF_Project* pro = PF_ProjectTree::projectForNode(node);
    /** 不同的节点，跳转到相应的视图 **/
    LeafNode* lNode = dynamic_cast<LeafNode*>(node);
    switch (lNode->leafType()) {
        case LeafType::CMaterialProp:
        {
            /** 查看编辑材料 **/
            pro->editMaterial(node);
            break;
        }
        default:
        {
            break;
        }
    }
    qDebug()<<Q_FUNC_INFO<<node->displayName()<<" Clicked!";
}

/*!
 \brief 跳转到node

 \param node
*/
void PF_ProjectTreeWidget::setCurrentItem(Node* node)
{
    const QModelIndex mainIndex = m_model->indexForNode(node);

    if (mainIndex.isValid()) {
        if (mainIndex != m_view->selectionModel()->currentIndex()) {
            // Expand everything between the index and the root index!
            QModelIndex parent = mainIndex.parent();
            while (parent.isValid()) {
                m_view->setExpanded(parent, true);
                parent = parent.parent();
            }
            m_view->setCurrentIndex(mainIndex);
            m_view->scrollTo(mainIndex);
        }
    } else {
        m_view->clearSelection();
    }
}

ProjectTreeWidgetFactory::ProjectTreeWidgetFactory()
{
    setDisplayName(tr("Projects"));
}

Core::NavigationView ProjectTreeWidgetFactory::createWidget()
{
    Core::NavigationView n;
    auto ptw = new PF_ProjectTreeWidget;
    n.widget = ptw;

//    auto filter = new QToolButton;
//    filter->setIcon(Icons::FILTER.icon());
//    filter->setToolTip(tr("Filter Tree"));
//    filter->setPopupMode(QToolButton::InstantPopup);
//    filter->setProperty("noArrow", true);
//    auto filterMenu = new QMenu(filter);
//    filterMenu->addAction(ptw->m_filterProjectsAction);
//    filterMenu->addAction(ptw->m_filterGeneratedFilesAction);
//    filterMenu->addAction(ptw->m_trimEmptyDirectoriesAction);
//    filter->setMenu(filterMenu);

//    n.dockToolBarWidgets << filter << ptw->toggleSync();
    return n;
}
}//namespace ProjectExplorer
