#ifndef OUTPUTPANEMANAGER_H
#define OUTPUTPANEMANAGER_H

#include <QWidget>

namespace OutputPlugin {
class OutputPaneManager : public QWidget
{
    Q_OBJECT
public:
    explicit OutputPaneManager(QWidget *parent = nullptr);

signals:

public slots:
};
} // namespace OutputPlugin
#endif // OUTPUTPANEMANAGER_H
