#ifndef PF_PAGEWIDGET_H
#define PF_PAGEWIDGET_H

#include <QWidget>

class QPainter;
class QStackedLayout;
class QStatusBar;

namespace Core {
class PF_Index : public QObject
{
    Q_OBJECT
public:
    PF_Index(QObject *tabbar)
        : m_pageIndex(tabbar)
    {
    }
    QString text;
    bool enabled = false;
private:
    QObject *m_pageIndex;
};

/*!
 \brief 需要一个东西来保存页面的顺序

*/
class PF_PageIndex : public QObject
{
    Q_OBJECT

public:
    PF_PageIndex(QObject *parent = nullptr);

    bool validIndex(int index) const { return index >= 0 && index < m_inds.count(); }

    void setPageEnabled(int index, bool enable);
    bool isPageEnabled(int index) const;

    void insertPage(int index, const QString &label)
    {
        auto tab = new PF_Index(this);
        tab->text = label;
        m_inds.insert(index, tab);
        if (m_currentIndex >= index)
            ++m_currentIndex;
    }
    void setEnabled(int index, bool enabled);
    void removePage(int index)
    {
        PF_Index *ind = m_inds.takeAt(index);
        delete ind;
    }
    void setCurrentIndex(int index);
    int currentIndex() const { return m_currentIndex; }

    int count() const { return m_inds.count(); }

signals:
    void currentChanged(int index);
    void menuTriggered(int index, QMouseEvent *event);

private:
    int m_currentIndex = -1;
    QList<PF_Index *> m_inds;
};

class PF_PageWidget : public QWidget
{
    Q_OBJECT
public:
    PF_PageWidget(QWidget *parent = nullptr);

    void insertPage(int index, QWidget *page, const QString &label);
    void removePage(int index);

    int currentIndex() const;
    QStatusBar *statusBar() const;

    void setPageEnabled(int index, bool enable);
    bool isPageEnabled(int index) const;

signals:
    void currentAboutToShow(int index);
    void currentChanged(int index);

public slots:
    void setCurrentIndex(int index);

private:
    void showWidget(int index);

    PF_PageIndex* m_pageIndex;
    QStackedLayout *m_pagesStack;
    QStatusBar *m_statusBar;
};
}//namespace Core

#endif // PF_PAGEWIDGET_H
