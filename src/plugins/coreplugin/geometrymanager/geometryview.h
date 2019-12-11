#ifndef GEOMETRYVIEW_H
#define GEOMETRYVIEW_H

#include "../core_global.h"

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
class IGeometry;
/**
 * @brief 打开几何文件的时候，可以是空，也可以是二维三维，
 * 需要不同的模块去打开。
 *
 */
class FEEM_CORE_EXPORT GeometryView : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryView(QWidget* parent = nullptr);
    ~GeometryView() override;

//    GeometryView *findNextView();
//    GeometryView *findPreviousView();
    int CADCount() const;
    void addCAD(IGeometry* cad);
    void removeCAD(IGeometry* cad);
    IGeometry* currentCAD() const;
    void setCurrentCAD(IGeometry* cad);

    bool hasCAD(IGeometry* cad) const;

    QList<IGeometry*> CADs() const;
signals:
    void currentCADChanged(IGeometry* cad);
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *e) override;
    void focusInEvent(QFocusEvent *) override;
private:
    QStackedWidget *m_container;/**保存所有的view**/
    QLabel *m_emptyViewLabel;
    QList<IGeometry*> m_CADs;
    /** 每打开一个几何文件，都进行存储，这样可以方便切换 **/
    QMap<QWidget*,IGeometry*> m_widgetCADMap;
};
}//namespace Core

#endif // GEOMETRYVIEW_H
