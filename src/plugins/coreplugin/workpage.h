#ifndef WORKPAGE_H
#define WORKPAGE_H

#include <coreplugin/ipage.h>

class QSplitter;
class QVBoxLayout;

namespace Core {
class WorkPage : public IPage
{
    Q_OBJECT
public:
    WorkPage();
    ~WorkPage() override;
private:
    QSplitter *m_splitter;
};
}//namespace Core

#endif // WORKPAGE_H
