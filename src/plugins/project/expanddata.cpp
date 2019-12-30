#include "expanddata.h"

namespace ProjectExplorer {

ExpandData::ExpandData(const QString& displayName_)
    :displayName(displayName_)
{

}

bool ExpandData::operator==(const ProjectExplorer::ExpandData& other) const
{
    return displayName == other.displayName;
}

int qHash(const ExpandData &data)
{
    return qHash(data.displayName);
}

}// ProjectExplorer

