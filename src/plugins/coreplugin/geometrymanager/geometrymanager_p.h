#ifndef GEOMETRYMANAGER_P_H
#define GEOMETRYMANAGER_P_H

#include <QObject>
#include <QList>

namespace Core {
class GeometryManager;
class GeometryView;

class GeometryManagerPrivate : public QObject
{
    Q_OBJECT
    friend class Core::GeometryManager;
public:
    static GeometryManagerPrivate* instance();

    static GeometryView* currentGeoView();
    static void setCurrentView(GeometryView* view);

private:
    explicit GeometryManagerPrivate(QObject* parent);
    ~GeometryManagerPrivate() override;

    void init();

    GeometryView* m_currentView = nullptr;

};
}//namespace Core
#endif // GEOMETRYMANAGER_P_H
