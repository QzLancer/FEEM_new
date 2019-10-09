#ifndef NAVIGATIONTREEVIEW_H
#define NAVIGATIONTREEVIEW_H

#include "utils_global.h"
#include "viewitem.h"

namespace Utils {
class FEEM_UTILS_EXPORT NavigationTreeView : public TreeView
{
    Q_OBJECT
public:
    explicit NavigationTreeView(QWidget *parent = nullptr);
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};
}//namespace Utils
#endif // NAVIGATIONTREEVIEW_H
