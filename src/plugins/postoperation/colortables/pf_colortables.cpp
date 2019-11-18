#include "pf_colortables.h"

#include <QColor>
#include <QVector>

namespace Postoperation {

/*!
 \brief 默认会生成Rainbow风格的颜色表

*/
PF_ColorMap::PF_ColorMap()
    :QwtLinearColorMap(QwtColorMap::RGB )
{
    setColorData(PF_ColorBarStyle::Rainbow);
}

PF_ColorMap::PF_ColorMap(PF_ColorMap::PF_ColorBarStyle style)
    :QwtLinearColorMap(QwtColorMap::RGB )
{
    setColorData(style);
}

PF_ColorMap::~PF_ColorMap()
{

}

void PF_ColorMap::setColorData(PF_ColorBarStyle style)
{
    int alpha = 255;
    int n = 0;
    QVector<QColor> cTab;
    switch (style) {
    case AuroraAustralis:
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.796000,0.878000,0.875000);
        cTab[n++].setRgbF(0.592000,0.757000,0.753000);
        cTab[n++].setRgbF(0.384000,0.635000,0.635000);
        cTab[n++].setRgbF(0.106000,0.522000,0.518000);
        cTab[n++].setRgbF(0.475000,0.000000,0.914000);
        cTab[n++].setRgbF(0.000000,0.000000,0.816000);
        cTab[n++].setRgbF(0.000000,0.000000,0.502000);
        break;

    case AuroraBorealis:
        cTab[n++].setRgbF(0.900000,1.000000,0.900000);
        cTab[n++].setRgbF(0.729000,0.961000,0.792000);
        cTab[n++].setRgbF(0.420000,0.788000,0.565000);
        cTab[n++].setRgbF(0.271000,0.529000,0.408000);
        cTab[n++].setRgbF(0.443000,0.443000,0.561000);
        cTab[n++].setRgbF(0.463000,0.204000,0.702000);
        cTab[n++].setRgbF(0.459000,0.004000,0.694000);
        cTab[n++].setRgbF(0.353000,0.000000,0.667000);
        cTab[n++].setRgbF(0.216000,0.000000,0.667000);
        cTab[n++].setRgbF(0.102000,0.000000,0.553000);
        break;

    case Cividis:
        cTab[n++].setRgbF(0.000000,0.126200,0.301500);
        cTab[n++].setRgbF(0.000000,0.168500,0.403100);
        cTab[n++].setRgbF(0.000000,0.207300,0.432900);
        cTab[n++].setRgbF(0.156600,0.249800,0.423600);
        cTab[n++].setRgbF(0.237500,0.292000,0.420000);
        cTab[n++].setRgbF(0.301400,0.334000,0.422400);
        cTab[n++].setRgbF(0.358200,0.376300,0.430200);
        cTab[n++].setRgbF(0.411400,0.418900,0.443000);
        cTab[n++].setRgbF(0.462200,0.462200,0.462000);
        cTab[n++].setRgbF(0.515800,0.506500,0.473600);
        cTab[n++].setRgbF(0.573500,0.552200,0.472000);
        cTab[n++].setRgbF(0.632800,0.599300,0.464100);
        cTab[n++].setRgbF(0.693600,0.647800,0.449900);
        cTab[n++].setRgbF(0.756000,0.697900,0.429000);
        cTab[n++].setRgbF(0.820000,0.749700,0.400700);
        cTab[n++].setRgbF(0.885800,0.803500,0.362700);
        cTab[n++].setRgbF(0.953600,0.859300,0.311600);
        cTab[n++].setRgbF(1.000000,0.916900,0.273100);
        break;

    case Cyclic:
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(0.000000,1.000000,0.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        break;

    case Disco:
        cTab[n++].setRgbF(0.000000,0.000000,0.500000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.000000,0.500000,1.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.500000,0.500000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.500000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        break;

    case DiscoLight:
        cTab[n++].setRgbF(0.000000,0.000000,0.500000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.000000,0.500000,1.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.500000,0.750000,1.000000);
        cTab[n++].setRgbF(1.000000,0.500000,1.000000);
        cTab[n++].setRgbF(1.000000,0.250000,0.500000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        break;

    case GrayPrint:
        cTab[n++].setRgbF(0.050980,0.050980,0.050980);
        cTab[n++].setRgbF(0.949020,0.949020,0.949020);
        break;

    case GrayScale:
        cTab[n++].setRgbF(0.000000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        break;

    case HeatCamera:
        cTab[n++].setRgbF(0.008000,0.000000,0.102000);
        cTab[n++].setRgbF(0.098000,0.000000,0.463000);
        cTab[n++].setRgbF(0.325000,0.000000,0.576000);
        cTab[n++].setRgbF(0.710000,0.016000,0.573000);
        cTab[n++].setRgbF(0.906000,0.235000,0.169000);
        cTab[n++].setRgbF(0.973000,0.525000,0.004000);
        cTab[n++].setRgbF(1.000000,0.808000,0.039000);
        cTab[n++].setRgbF(0.988000,0.961000,0.851000);
        break;

    case HeatCameraLight:
        cTab[n++].setRgbF(0.090000,0.063000,0.271000);
        cTab[n++].setRgbF(0.106000,0.063000,0.376000);
        cTab[n++].setRgbF(0.329000,0.031000,0.588000);
        cTab[n++].setRgbF(0.729000,0.137000,0.541000);
        cTab[n++].setRgbF(0.839000,0.263000,0.365000);
        cTab[n++].setRgbF(0.933000,0.529000,0.067000);
        cTab[n++].setRgbF(0.945000,0.670000,0.040000);
        cTab[n++].setRgbF(0.937000,0.784000,0.145000);
        cTab[n++].setRgbF(0.910000,0.880000,0.500000);
        cTab[n++].setRgbF(0.950000,0.950000,0.950000);
        break;

    case JupiterAuroraBorealis:
        cTab[n++].setRgbF(0.000000,0.000000,0.043000);
        cTab[n++].setRgbF(0.000000,0.471000,0.906000);
        cTab[n++].setRgbF(0.145000,0.663000,1.000000);
        cTab[n++].setRgbF(0.420000,0.773000,1.000000);
        cTab[n++].setRgbF(0.600000,0.843000,1.000000);
        cTab[n++].setRgbF(0.761000,0.906000,1.000000);
        cTab[n++].setRgbF(0.863000,0.949000,1.000000);
        cTab[n++].setRgbF(0.996000,1.000000,1.000000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        break;

    case Rainbow:
        cTab[n++].setRgbF(0.000000,0.000000,0.500000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.000000,0.500000,1.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.500000,1.000000,0.500000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.500000,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        break;

    case RainbowLight:
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        break;

    case Spectrum:
        cTab[n++].setRgbF(0.160000,0.000000,0.300000);
        cTab[n++].setRgbF(0.280000,0.000000,0.550000);
        cTab[n++].setRgbF(0.280000,0.000000,0.800000);
        cTab[n++].setRgbF(0.140000,0.000000,0.900000);
        cTab[n++].setRgbF(0.000000,0.250000,1.000000);
        cTab[n++].setRgbF(0.000000,0.500000,0.750000);
        cTab[n++].setRgbF(0.000000,0.750000,0.500000);
        cTab[n++].setRgbF(0.000000,0.750000,0.250000);
        cTab[n++].setRgbF(0.000000,0.750000,0.000000);
        cTab[n++].setRgbF(0.250000,0.750000,0.000000);
        cTab[n++].setRgbF(0.500000,0.750000,0.000000);
        cTab[n++].setRgbF(0.750000,0.750000,0.000000);
        cTab[n++].setRgbF(1.000000,0.600000,0.000000);
        cTab[n++].setRgbF(1.000000,0.450000,0.000000);
        cTab[n++].setRgbF(1.000000,0.300000,0.000000);
        cTab[n++].setRgbF(0.750000,0.150000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        break;

    case Thermal:
        cTab[n++].setRgbF(0.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.250000,0.000000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        cTab[n++].setRgbF(0.750000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.145098,0.000000);
        cTab[n++].setRgbF(1.000000,0.286275,0.000000);
        cTab[n++].setRgbF(1.000000,0.431373,0.000000);
        cTab[n++].setRgbF(1.000000,0.572549,0.000000);
        cTab[n++].setRgbF(1.000000,0.717647,0.000000);
        cTab[n++].setRgbF(1.000000,0.858824,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.200000);
        cTab[n++].setRgbF(1.000000,1.000000,0.400000);
        cTab[n++].setRgbF(1.000000,1.000000,0.600000);
        cTab[n++].setRgbF(1.000000,1.000000,0.800000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        break;

    case ThermalEquidistant:
        cTab[n++].setRgbF(0.000000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        break;

    case ThermalLight:
        cTab[n++].setRgbF(0.450000,0.000000,0.000000);
        cTab[n++].setRgbF(0.550000,1.000000,0.000000);
        cTab[n++].setRgbF(0.000000,1.000000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,1.000000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        break;

    case Traffic:
        cTab[n++].setRgbF(0.000000,0.666667,0.000000);
        cTab[n++].setRgbF(0.000000,1.000000,0.000000);
        cTab[n++].setRgbF(0.333333,1.000000,0.000000);
        cTab[n++].setRgbF(0.666667,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.666667,0.000000);
        cTab[n++].setRgbF(1.000000,0.333333,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.666667,0.000000,0.000000);
        break;

    case TrafficLight:
        cTab[n++].setRgbF(0.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,1.000000,0.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        break;

    case Twilight:
        cTab[n++].setRgbF(1.000000,0.753000,0.796000);
        cTab[n++].setRgbF(1.000000,0.725000,0.608000);
        cTab[n++].setRgbF(1.000000,0.761000,0.522000);
        cTab[n++].setRgbF(1.000000,0.851000,0.663000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        cTab[n++].setRgbF(0.851000,0.886000,0.965000);
        cTab[n++].setRgbF(0.699000,0.699000,0.961000);
        cTab[n++].setRgbF(0.522000,0.447000,0.973000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.000000,0.000000,0.742000);
        break;

    case Wave:
        cTab[n++].setRgbF(0.000000,0.000000,0.500000);
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(0.800000,0.800000,0.800000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        cTab[n++].setRgbF(0.500000,0.000000,0.000000);
        break;

    case WaveLight:
        cTab[n++].setRgbF(0.000000,0.000000,1.000000);
        cTab[n++].setRgbF(1.000000,1.000000,1.000000);
        cTab[n++].setRgbF(1.000000,0.000000,0.000000);
        break;

    }
    setColorInterval(cTab[0],cTab.last());
    for(int i = 1; i < n-1;i++){
        addColorStop( double(i/n), cTab.at(i));
    }
}

}// namespace Postoperation
