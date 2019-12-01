#ifndef GEOMETRYMANAGER_P_H
#define GEOMETRYMANAGER_P_H

#include "../id.h"
#include "../core_global.h"

#include <QObject>
#include <QList>

namespace Core {
class GeometryManager;
class GeometryView;
class IGeometry;

class FEEM_CORE_EXPORT GeometryManagerPrivate : public QObject
{
    Q_OBJECT
    friend class Core::GeometryManager;
public:
    static GeometryManagerPrivate* instance();

    static GeometryView* currentGeoView();
    static void setCurrentView(GeometryView* view);
    static void activateView(GeometryView* view);
    static GeometryView* viewForCAD(IGeometry* cad);

    static void setCurrentCAD(IGeometry* cad);
    static IGeometry* openCAD(GeometryView* view,
                              IGeometry* cad,
                              Id cadId = Id());
    static IGeometry* activateCAD(GeometryView* view, IGeometry* cad);

    static void closeCAD(IGeometry* cad);
    static void closeCADs(const QList<IGeometry*>& cads);
private:
    static IGeometry* placeCAD(GeometryView* view, IGeometry*cad);
private:
    explicit GeometryManagerPrivate(QObject* parent);
    ~GeometryManagerPrivate() override;

    void init();

    GeometryView* m_currentView = nullptr;
    IGeometry* m_currentCAD = nullptr;

};
}//namespace Core
#endif // GEOMETRYMANAGER_P_H
