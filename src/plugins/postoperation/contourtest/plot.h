#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_spectrogram.h>

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    enum ColorMap
    {
        RGBMap,
        IndexMap,
        HueMap,
        AlphaMap,
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

    Plot( QWidget * = nullptr );

public Q_SLOTS:
    void showContour( bool on );
    void showSpectrogram( bool on );
    void setColorMap( int );
    void setAlpha( int );

#ifndef QT_NO_PRINTER
    void printPlot();
#endif

private:
    QwtPlotSpectrogram *d_spectrogram;

    int d_mapType;
    int d_alpha;
};
