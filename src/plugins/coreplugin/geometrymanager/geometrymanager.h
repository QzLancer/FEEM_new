#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

#include "core_global.h"

#include <QWidget>
#include <QList>

namespace Core {
class MainWindow;

class FEEM_CORE_EXPORT GeometryManagerPlaceHolder : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryManagerPlaceHolder(QWidget *parent = nullptr);
    ~GeometryManagerPlaceHolder() final;
protected:
    void showEvent(QShowEvent *event) override;
};

class FEEM_CORE_EXPORT GeometryManager : public QObject
{
    Q_OBJECT
private:
    /** 私有构造函数，只能在MainWindow当中构造，单例模式 **/
    explicit GeometryManager(QObject *parent);
    ~GeometryManager() override;

    friend class Core::MainWindow;
};
}//namespace Core

#endif // GEOMETRYMANAGER_H
