#ifndef WELCOMEPLUGIN_H
#define WELCOMEPLUGIN_H
#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/constants.h>
#include <coreplugin/icore.h>
#include <coreplugin/ipage.h>
#include <coreplugin/iwelcomepage.h>
//#include <coreplugin/iwizardfactory.h>
#include <coreplugin/pagemanager.h>

//#include <utils/algorithm.h>
//#include <utils/icon.h>
//#include <utils/fileutils.h>
//#include <utils/hostosinfo.h>
//#include <utils/qtcassert.h>
//#include <utils/styledbar.h>
//#include <utils/treemodel.h>
//#include <utils/theme/theme.h>

#include <QDesktopServices>
#include <QHeaderView>
#include <QLabel>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPainter>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>

using namespace Core;
using namespace ExtensionSystem;

namespace Welcome {
namespace Internal {
static void addWeakVerticalSpacerToLayout(QVBoxLayout *layout, int maximumSize)
{
    auto weakSpacer = new QWidget;
    weakSpacer->setMaximumHeight(maximumSize);
    weakSpacer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    layout->addWidget(weakSpacer);
    layout->setStretchFactor(weakSpacer, 1);
}

class WelcomePage : public IPage
{
    Q_OBJECT
public:
    WelcomePage();
    ~WelcomePage();

    void initPlugins();

//    Q_INVOKABLE bool openDroppedFiles(const QList<QUrl> &urls);

private:
    void addPage(IWelcomePage *page);

    QWidget *m_pageWidget;
    QStackedWidget *m_pageStack;
//    SideBar *m_sideBar;
    QList<IWelcomePage *> m_pluginList;
    QList<WelcomePageButton *> m_pageButtons;
    Id m_activePage;
};

class WelcomePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.hit.feem.feemPlugin" FILE "Welcome.json")

public:
    ~WelcomePlugin() final { delete m_welcomePage; }

    bool initialize(const QStringList &, QString *) final
    {
        m_welcomePage = new WelcomePage;
        return true;
    }

    void extensionsInitialized() final
    {
        m_welcomePage->initPlugins();
        PageManager::activatePage(m_welcomePage->id());
    }

    WelcomePage *m_welcomePage = nullptr;
};

//class IconAndLink : public QWidget
//{
//public:
//    IconAndLink(const QString &iconSource,
//                const QString &title,
//                const QString &openUrl,
//                QWidget *parent)
//        : QWidget(parent), m_iconSource(iconSource), m_title(title), m_openUrl(openUrl)
//    {
//        setAutoFillBackground(true);
//        setMinimumHeight(30);
//        setToolTip(m_openUrl);

//        const QString fileName = QString(":/welcome/images/%1.png").arg(iconSource);
////        const Icon icon({{fileName, Theme::Welcome_ForegroundPrimaryColor}}, Icon::Tint);

////        m_icon = new QLabel;
////        m_icon->setPixmap(icon.pixmap());

//        m_label = new QLabel(title);
////        m_label->setFont(sizedFont(11, m_label, false));

//        auto layout = new QHBoxLayout;
//        layout->setContentsMargins(lrPadding, 0, lrPadding, 0);
//        layout->addWidget(m_icon);
//        layout->addSpacing(2);
//        layout->addWidget(m_label);
//        layout->addStretch(1);
//        setLayout(layout);
//    }

//    void enterEvent(QEvent *) override
//    {
//        QPalette pal;
//        pal.setColor(QPalette::Background, themeColor(Theme::Welcome_HoverColor));
//        setPalette(pal);
//        m_label->setFont(sizedFont(11, m_label, true));
//        update();
//    }

//    void leaveEvent(QEvent *) override
//    {
//        QPalette pal;
//        pal.setColor(QPalette::Background, themeColor(Theme::Welcome_BackgroundColor));
//        setPalette(pal);
//        m_label->setFont(sizedFont(11, m_label, false));
//        update();
//    }

//    void mousePressEvent(QMouseEvent *) override
//    {
//        QDesktopServices::openUrl(m_openUrl);
//    }

//    QString m_iconSource;
//    QString m_title;
//    const QString m_openUrl;

//    QLabel *m_icon;
//    QLabel *m_label;
//};

//class SideBar : public QWidget
//{
//    Q_OBJECT
//public:
//    SideBar(QWidget *parent)
//        : QWidget(parent)
//    {
//        setAutoFillBackground(true);
//        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//        setPalette(QColor("#000000"));

//        auto vbox = new QVBoxLayout(this);
//        vbox->setSpacing(0);
//        vbox->setContentsMargins(0, 27, 0, 0);

//        {
//            auto l = m_pluginButtons = new QVBoxLayout;
//            l->setContentsMargins(lrPadding, 0, lrPadding, 0);
//            l->setSpacing(19);
//            vbox->addItem(l);
//        }

//        addWeakVerticalSpacerToLayout(vbox, 62);

//        {
//            auto l = new QVBoxLayout;
//            l->setContentsMargins(lrPadding, 0, lrPadding, 0);
//            l->setSpacing(12);

//            auto newLabel = new QLabel(tr("New to Qt?"), this);
//            newLabel->setFont(sizedFont(18, this));
//            l->addWidget(newLabel);

//            auto learnLabel = new QLabel(tr("Learn how to develop your own applications "
//                                            "and explore %1.")
//                                         .arg(Core::Constants::IDE_DISPLAY_NAME), this);
//            learnLabel->setMaximumWidth(200);
//            learnLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//            learnLabel->setWordWrap(true);
////            learnLabel->setFont(sizedFont(12, this));
////            learnLabel->setPalette(lightText());
//            l->addWidget(learnLabel);

//            l->addSpacing(8);

//            auto getStartedButton = new WelcomePageButton(this);
//            getStartedButton->setText(tr("Get Started Now"));
//            getStartedButton->setOnClicked([] {
//                QDesktopServices::openUrl(QString("qthelp://org.qt-project.qtcreator/doc/index.html"));
//            });
//            l->addWidget(getStartedButton);

//            vbox->addItem(l);
//        }

//        vbox->addStretch(1);

//        {
//            auto l = new QVBoxLayout;
//            l->setContentsMargins(0, 0, 0, 0);
//            l->setSpacing(5);
//            l->addWidget(new IconAndLink("qtaccount", tr("Qt Account"), "https://account.qt.io", this));
//            l->addWidget(new IconAndLink("community", tr("Online Community"), "https://forum.qt.io", this));
//            l->addWidget(new IconAndLink("blogs", tr("Blogs"), "https://planet.qt.io", this));
//            l->addWidget(new IconAndLink("userguide", tr("User Guide"),
//                                         "qthelp://org.qt-project.qtcreator/doc/index.html", this));
//            vbox->addItem(l);
//        }

//        addWeakVerticalSpacerToLayout(vbox, vbox->contentsMargins().top());
//    }

//    QVBoxLayout *m_pluginButtons = nullptr;
//};
} // namespace Internal
} // namespace Welcome
#endif // WELCOMEPLUGIN_H
