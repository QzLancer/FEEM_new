#include "welcomeplugin.h"

using namespace Core;
using namespace ExtensionSystem;
//using namespace Utils;

namespace Welcome {
namespace Internal {
//class SideBar;
const int lrPadding = 34;
const char currentPageSettingsKeyC[] = "Welcome2Tab";

WelcomePage::WelcomePage()
{
//    setDisplayName(tr("Welcome"));

//    const Icon CLASSIC(":/welcome/images/mode_welcome.png");
//    const Icon FLAT({{":/welcome/images/mode_welcome_mask.png",
//                      Theme::IconsBaseColor}});
//    const Icon FLAT_ACTIVE({{":/welcome/images/mode_welcome_mask.png",
//                             Theme::IconsModeWelcomeActiveColor}});
//    setIcon(Icon::modeIcon(CLASSIC, FLAT, FLAT_ACTIVE));

    setPriority(Constants::P_PAGE_WELCOME);
    setId(Constants::PAGE_WELCOME);
    setContextHelpId("Qt Creator Manual");
//    setContext(Context(Constants::C_WELCOME_MODE));

//    QPalette palette = creatorTheme()->palette();
//    palette.setColor(QPalette::Background, themeColor(Theme::Welcome_BackgroundColor));

    m_pageWidget = new QWidget;
//    m_pageWidget->setPalette(palette);

//    m_sideBar = new SideBar(m_pageWidget);
//    auto scrollableSideBar = new QScrollArea(m_pageWidget);
//    scrollableSideBar->setWidget(m_sideBar);
//    scrollableSideBar->setWidgetResizable(true);
//    scrollableSideBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    scrollableSideBar->setFrameShape(QFrame::NoFrame);

    auto divider = new QWidget(m_pageWidget);
    divider->setMaximumWidth(1);
    divider->setMinimumWidth(1);
    divider->setAutoFillBackground(true);
//    divider->setPalette(themeColor(Theme::Welcome_DividerColor));

    m_pageStack = new QStackedWidget(m_pageWidget);
    m_pageStack->setObjectName("WelcomeScreenStackedWidget");
    m_pageStack->setAutoFillBackground(true);

    auto hbox = new QHBoxLayout;
//    hbox->addWidget(scrollableSideBar);
    hbox->addWidget(divider);
    hbox->addWidget(m_pageStack);
    hbox->setStretchFactor(m_pageStack, 10);

    auto layout = new QVBoxLayout(m_pageWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
//    layout->addWidget(new StyledBar(m_pageWidget));
    layout->addItem(hbox);

//    if (Utils::HostOsInfo::isMacHost()) { // workaround QTBUG-61384
//        auto openglWidget = new QOpenGLWidget;
//        openglWidget->hide();
//        layout->addWidget(openglWidget);
//    }

    setWidget(m_pageWidget);
}

WelcomePage::~WelcomePage()
{
//    QSettings *settings = ICore::settings();
//    settings->setValue(currentPageSettingsKeyC, m_activePage.toSetting());
    delete m_pageWidget;
}

void WelcomePage::initPlugins()
{
//    QSettings *settings = ICore::settings();
//    m_activePage = Id::fromSetting(settings->value(currentPageSettingsKeyC));

    for (IWelcomePage *page : IWelcomePage::allWelcomePages())
        addPage(page);

//    if (!m_activePage.isValid() && !m_pageButtons.isEmpty()) {
//        const int welcomeIndex = Utils::indexOf(m_pluginList,
//                                                Utils::equal(&IWelcomePage::id,
//                                                             Core::Id("Examples")));
//        const int defaultIndex = welcomeIndex >= 0 ? welcomeIndex : 0;
//        m_activePage = m_pluginList.at(defaultIndex)->id();
//        m_pageButtons.at(defaultIndex)->click();
//    }
}

//bool WelcomePage::openDroppedFiles(const QList<QUrl> &urls)
//{
//    DropArea {
//        anchors.fill: parent
//        keys: ["text/uri-list"]
//        onDropped: {
//            if ((drop.supportedActions & Qt.CopyAction != 0)
//                    && welcomeMode.openDroppedFiles(drop.urls))
//                drop.accept(Qt.CopyAction);
//        }
//    }
//    const QList<QUrl> localUrls = Utils::filtered(urls, &QUrl::isLocalFile);
//    if (!localUrls.isEmpty()) {
//        QTimer::singleShot(0, [localUrls]() {
//            ICore::openFiles(Utils::transform(localUrls, &QUrl::toLocalFile), ICore::SwitchMode);
//        });
//        return true;
//    }
//    return false;
//}

void WelcomePage::addPage(IWelcomePage *page)
{
    int idx;
    int pagePriority = page->priority();
    for (idx = 0; idx != m_pluginList.size(); ++idx) {
        if (m_pluginList.at(idx)->priority() >= pagePriority)
            break;
    }
//    auto pageButton = new WelcomePageButton(m_sideBar);
    auto pageId = page->id();
//    pageButton->setText(page->title());
//    pageButton->setActiveChecker([this, pageId] { return m_activePage == pageId; });

    m_pluginList.append(page);
//    m_pageButtons.append(pageButton);

//    m_sideBar->m_pluginButtons->insertWidget(idx, pageButton);

    QWidget *stackPage = page->createWidget();
    stackPage->setAutoFillBackground(true);
    m_pageStack->insertWidget(idx, stackPage);

//    auto onClicked = [this, pageId, stackPage] {
//        m_activePage = pageId;
//        m_pageStack->setCurrentWidget(stackPage);
//        for (WelcomePageButton *pageButton : m_pageButtons)
//            pageButton->recheckActive();
//    };

//    pageButton->setOnClicked(onClicked);
//    if (pageId == m_activePage)
//        onClicked();
}

} // namespace Internal
} // namespace Welcome

//#include "welcomeplugin.moc"
