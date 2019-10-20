#ifndef GEOMETRYVIEW_H
#define GEOMETRYVIEW_H

#include <QMap>
#include <QList>
#include <QString>
#include <QPointer>
#include <QVariant>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QFrame;
class QLabel;
class QMenu;
class QSplitter;
class QStackedLayout;
class QStackedWidget;
class QToolButton;
QT_END_NAMESPACE

namespace Core {

/**
 * @brief 打开几何文件的时候，可以是空，也可以是二维三维，
 * 需要不同的模块去打开。
 *
 */
class GeometryView : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryView(QWidget* parent = nullptr);
    ~GeometryView() override;

    GeometryView *findNextView();
    GeometryView *findPreviousView();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *e) override;
    void focusInEvent(QFocusEvent *) override;
private:
    QStackedWidget *m_container;/**保存所有的view**/
    QLabel *m_emptyViewLabel;
};
}//namespace Core

#endif // GEOMETRYVIEW_H
