#ifndef PF_POSTFEEM_H
#define PF_POSTFEEM_H

#include "postoperation_global.h"

#include <QObject>

namespace Postoperation {

/**
 * @brief 用来处理project当中得到的一些数据，并进行一些云图，等高线等
 * 的绘制。后处理插件是依赖于project插件的，因此，可以将project当中的
 * 一些信号连接过来。这样就可以实现二者之间的联动。
 *
 */
class FEEM_POSTOPERATION_EXPORT PF_PostFEEM : public QObject
{
    Q_OBJECT
public:
    PF_PostFEEM();
};
}//namespace Postoperation


#endif // PF_POSTFEEM_H
