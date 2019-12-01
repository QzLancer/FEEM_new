#ifndef IGEOMETRY_H
#define IGEOMETRY_H

#include "../core_global.h"
#include "../context.h"

namespace Core {

/**
 * @brief 一个抽象的几何编辑器
 *
 */
class FEEM_CORE_EXPORT IGeometry : public IContext
{
    Q_OBJECT
public:
    IGeometry(QObject *parent = nullptr);
};
}//namespace Core
#endif // IGEOMETRY_H
