#include "contourtestwidget.h"
#include "plot.h"

#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>

ContourTestWidget::ContourTestWidget(QWidget *parent)
    :QWidget (parent)
    ,m_Plot(new Plot(this))
{
    QWidget* toolbar = new QWidget(this);
    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(new QLabel("Color Map " ));

    QComboBox *mapBox = new QComboBox(toolbar);
    mapBox->addItem( "RGB" );
    mapBox->addItem( "Indexed Colors" );
    mapBox->addItem( "Hue" );
    mapBox->addItem( "Alpha" );
    mapBox->addItem("AuroraAustralis");
    mapBox->addItem("AuroraBorealis");
    mapBox->addItem("Cividis");
    mapBox->addItem("Cyclic");
    mapBox->addItem("Disco");
    mapBox->addItem("DiscoLight");
    mapBox->addItem("GrayPrint");
    mapBox->addItem("GrayScale");
    mapBox->addItem("HeatCamera");
    mapBox->addItem("HeatCameraLight");
    mapBox->addItem("JupiterAuroraBorealis");
    mapBox->addItem("Rainbow");
    mapBox->addItem("RainbowLight");
    mapBox->addItem("Spectrum");
    mapBox->addItem("Thermal");
    mapBox->addItem("ThermalEquidistant");
    mapBox->addItem("ThermalLight");
    mapBox->addItem("Traffic");
    mapBox->addItem("TrafficLight");
    mapBox->addItem("Twilight");
    mapBox->addItem("Wave");
    mapBox->addItem("WaveLight");
    mapBox->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    hbox->addWidget( mapBox );
    connect( mapBox, SIGNAL( currentIndexChanged( int ) ),
             m_Plot, SLOT( setColorMap( int ) ) );

    hbox->addWidget( new QLabel( " Opacity " ) );
    QSlider *slider = new QSlider( Qt::Horizontal );
    slider->setRange( 0, 255 );
    slider->setValue( 255 );
    connect( slider, SIGNAL( valueChanged( int ) ),
        m_Plot, SLOT( setAlpha( int ) ) );

    hbox->addWidget( slider );
    hbox->addWidget( new QLabel("   " ) );

    QCheckBox *btnSpectrogram = new QCheckBox( "Spectrogram", toolbar );
    hbox->addWidget( btnSpectrogram );
    connect( btnSpectrogram, SIGNAL( toggled( bool ) ),
        m_Plot, SLOT( showSpectrogram( bool ) ) );

    QCheckBox *btnContour = new QCheckBox( "Contour", toolbar );
    hbox->addWidget( btnContour );
    connect( btnContour, SIGNAL( toggled( bool ) ),
        m_Plot, SLOT( showContour( bool ) ) );

    toolbar->setLayout(hbox);
    hbox->setMargin(0);

    btnSpectrogram->setChecked( true );
    btnContour->setChecked( false );

    auto* vbox = new QVBoxLayout;
    vbox->addWidget(toolbar);
    vbox->addWidget(m_Plot);

    this->setLayout(vbox);
}

ContourTestWidget::~ContourTestWidget()
{
    delete m_Plot;
}
