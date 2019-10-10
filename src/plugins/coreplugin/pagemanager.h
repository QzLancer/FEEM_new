#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include "id.h"
#include <QObject>

namespace Core {
class IPage;
class PF_PageWidget;

class MainWindow;

class FEEM_CORE_EXPORT PageManager : public QObject
{
    Q_OBJECT
public:
    static PageManager* instance();

    static IPage* currentPage();
    static Id currentPageId();

    static void activatePage(Id id);
    static void setFocusToCurrentPage();
signals:
    void currentPageAboutToChange(Id page);
    void currentPageChanged(Id page, Id oldPage = Id());

private:
    explicit PageManager(MainWindow* mainWindow, PF_PageWidget* pageStack);
    ~PageManager() override;

    static void extensionsInitialized();

    static void addPage(IPage* page);
    static void removePage(IPage* page);
    void currentIndexAboutToChange(int index);
    void currentIndexChanged(int index);

    friend class IPage;
    friend class MainWindow;
};
}//namespace Core

#endif // PAGEMANAGER_H
