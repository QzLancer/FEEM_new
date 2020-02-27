#ifndef PF_POSTPROCESSORWIDGET_H
#define PF_POSTPROCESSORWIDGET_H

#include "postoperation_global.h"

#include <QWidget>

namespace Postoperation {

/**
 * @brief 一个用来设置后处理的参数和数据，并进行绘图显示的控件。
 *
 */
class FEEM_POSTOPERATION_EXPORT PF_PostprocessorWidget : public QWidget
{
    Q_OBJECT
public:
    PF_PostprocessorWidget();
};

}//namespace Postoperation

#endif // PF_POSTPROCESSORWIDGET_H
