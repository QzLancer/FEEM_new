#ifndef PF_POSTVIEW_H
#define PF_POSTVIEW_H

#include "postoperation_global.h"

#include <QObject>
namespace Postoperation {
/**
 * @brief 这是一个处理云图、等高线等数据的类。
 *
 */
class FEEM_POSTOPERATION_EXPORT PF_PostView : public QObject
{
    Q_OBJECT
public:
    PF_PostView(QObject *parent = nullptr);
    ~PF_PostView();



signals:

public slots:
};
}//namespace Postoperation


#endif // PF_POSTVIEW_H
