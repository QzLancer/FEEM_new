#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

#include "core_global.h"
#include "id.h"

#include <QWidget>
#include <QList>

namespace Core {
class MainWindow;
class IGeometry;

class FEEM_CORE_EXPORT GeometryManagerPlaceHolder : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryManagerPlaceHolder(QWidget *parent = nullptr);
    ~GeometryManagerPlaceHolder() final;
protected:
    void showEvent(QShowEvent *event) override;
};

/*!
 \brief 管理文件的打开，跟编辑器的显示，等等。项目当中会保存
 一个几何文件，新建项目之后，打开的时候，就会调用打开的动作。
 这样界面当中就有图形显示了。

*/
class FEEM_CORE_EXPORT GeometryManager : public QObject
{
    Q_OBJECT
public:
    static GeometryManager* instance();
    static IGeometry* openCAD(const QString &fileName, Id editorId = Id(),
                              bool* newGeoEditor = nullptr);
    static IGeometry *currentCAD();

    static void activateCAD(IGeometry* cad);
private:
    /** 私有构造函数，只能在MainWindow当中构造，单例模式 **/
    explicit GeometryManager(QObject *parent);
    ~GeometryManager() override;    

    friend class Core::MainWindow;
};
}//namespace Core

#endif // GEOMETRYMANAGER_H
