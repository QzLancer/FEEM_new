#include "messageoutputpane.h"
#include "outputwindow.h"

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

namespace OutputPlugin {
static MessageOutputPane *m_instance = nullptr;

MessageOutputPane::MessageOutputPane()
    :m_mainWidget(new QWidget)
    ,m_outputWindow(new OutputWindow(Core::Context(Core::Id("MessageOutputPane")),m_mainWidget))
    ,m_clearButton(new QToolButton)
    ,m_zoomInButton(new QToolButton)
    ,m_zoomOutButton(new QToolButton)
{
    m_instance = this;

    m_clearButton->setIcon(QIcon(":/imgs/clear16.png"));
    m_clearButton->setAutoRaise(true);
    m_clearButton->setToolTip(tr("Clear"));
    connect(m_clearButton,&QToolButton::clicked,[this]()
    {
        this->clearContents();
    });
    m_zoomInButton->setIcon(QIcon(":/imgs/zoomin16.png"));
    m_zoomInButton->setAutoRaise(true);
    m_zoomInButton->setToolTip(tr("Zoom in"));
    m_zoomOutButton->setIcon(QIcon(":/imgs/zoomout16.png"));
    m_zoomOutButton->setAutoRaise(true);
    m_zoomOutButton->setToolTip(tr("Zoom out"));

    /** toolbar **/
    auto toolbarlayout = new QHBoxLayout(m_mainWidget);
    toolbarlayout->setSpacing(1);
    toolbarlayout->setMargin(0);
    toolbarlayout->setContentsMargins(0,0,0,0);
    toolbarlayout->addWidget(m_clearButton);
    toolbarlayout->addWidget(m_zoomInButton);
    toolbarlayout->addWidget(m_zoomOutButton);
    toolbarlayout->addStretch(1);

    auto toolbar = new QWidget(m_mainWidget);
    toolbar->setLayout(toolbarlayout);
    toolbar->setContentsMargins(0,0,0,0);
    toolbar->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    auto vbox = new QVBoxLayout(m_mainWidget);
    vbox->addWidget(toolbar);
    vbox->addWidget(m_outputWindow);
}

MessageOutputPane::~MessageOutputPane()
{
    m_instance = nullptr;
}

MessageOutputPane *MessageOutputPane::instance()
{
    return m_instance;
}

QWidget *MessageOutputPane::outputWidget() const
{
    return m_mainWidget;
}

QString MessageOutputPane::displayName() const
{
    return QString(tr("Message Outputpane"));
}

void MessageOutputPane::clearContents()
{
    m_outputWindow->clear();
}

void MessageOutputPane::appendMessage(const QString &out)
{
    m_outputWindow->appendText(out);
}

void MessageOutputPane::write(const QString &out)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ");
    m_outputWindow->appendText(current_date+out+QLatin1Char('\n'));
}

void MessageOutputPane::operator <<(const QString &out)
{
    this->write(out);
}

void MessageOutputPane::operator<<(const char *out)
{
    this->write(QString::fromUtf8(out));
}



}// namespace OutputPlugin
