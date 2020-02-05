#pragma once

#include <QString>
#include <QHash>
#include <QDebug>

namespace ProjectExplorer {

class ExpandData
{
public:
    ExpandData() = default;
    ExpandData(const QString &displayName_);
    bool operator==(const ExpandData &other) const;

//    static ExpandData fromSettings(const QVariant &v);
//    QVariant toSettings() const;

    QString displayName;
};
int qHash(const ExpandData &data);
}// ProjectExplorer

