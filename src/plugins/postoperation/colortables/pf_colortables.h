#ifndef PF_COLORTABLES_H
#define PF_COLORTABLES_H

#include <postoperation_global.h>

#include <qwt/qwt_color_map.h>

/** 自定义一些颜色表，用来绘制云图 **/
namespace Postoperation {

class FEEM_POSTOPERATION_EXPORT PF_ColorMap : public QwtLinearColorMap
{
public:
    enum PF_ColorBarStyle{
        AuroraAustralis,
        AuroraBorealis,
        Cividis,
        Cyclic,
        Disco,
        DiscoLight,
        GrayPrint,
        GrayScale,
        HeatCamera,
        HeatCameraLight,
        JupiterAuroraBorealis,
        Rainbow,
        RainbowLight,
        Spectrum,
        Thermal,
        ThermalEquidistant,
        ThermalLight,
        Traffic,
        TrafficLight,
        Twilight,
        Wave,
        WaveLight
    };
    PF_ColorMap();
    PF_ColorMap(PF_ColorBarStyle style);
    ~PF_ColorMap();
private:
    void setColorData(PF_ColorBarStyle style);
};

}// namespace Postoperation


#endif // PF_COLORTABLES_H
