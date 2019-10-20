#ifndef GEOMETRYAREA_H
#define GEOMETRYAREA_H

#include "geometryview.h"

#include <QWidget>

namespace Core {
class GeometryArea : public QWidget
{
public:
    GeometryArea(QWidget* parent = nullptr);
    ~GeometryArea() override;

private:
    void setCurrentView(GeometryView* view);
    GeometryView* m_currentView;
};
}//namespace Core

#endif // GEOMETRYAREA_H
