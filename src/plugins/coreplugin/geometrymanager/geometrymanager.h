#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

#include "core_global.h"

#include <QWidget>

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
    explicit GeometryManager(QObject *parent);
    ~GeometryManager() override;

    friend class Core::MainWindow;
};
}//namespace Core

#endif // GEOMETRYMANAGER_H
