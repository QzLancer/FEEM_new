#pragma once

#include "mimetype.h"
#include "mimemagicrule_p.h"

#include <utils/utils_global.h>

QT_BEGIN_NAMESPACE
class QFileInfo;
QT_END_NAMESPACE

namespace Utils {

// Wrapped QMimeDataBase functions
FEEM_UTILS_EXPORT MimeType mimeTypeForName(const QString &nameOrAlias);

enum class MimeMatchMode {
    MatchDefault = 0x0,
    MatchExtension = 0x1,
    MatchContent = 0x2
};

FEEM_UTILS_EXPORT MimeType mimeTypeForFile(const QString &fileName, MimeMatchMode mode = MimeMatchMode::MatchDefault);
FEEM_UTILS_EXPORT MimeType mimeTypeForFile(const QFileInfo &fileInfo, MimeMatchMode mode = MimeMatchMode::MatchDefault);
FEEM_UTILS_EXPORT QList<MimeType> mimeTypesForFileName(const QString &fileName);
FEEM_UTILS_EXPORT MimeType mimeTypeForData(const QByteArray &data);
FEEM_UTILS_EXPORT QList<MimeType> allMimeTypes();

// Qt Creator additions
// For debugging purposes.
enum class MimeStartupPhase {
    BeforeInitialize,
    PluginsLoading,
    PluginsInitializing, // Register up to here.
    PluginsDelayedInitializing, // Use from here on.
    UpAndRunning
};

FEEM_UTILS_EXPORT void setMimeStartupPhase(MimeStartupPhase);
FEEM_UTILS_EXPORT void addMimeTypes(const QString &id, const QByteArray &data);
FEEM_UTILS_EXPORT QString allFiltersString(QString *allFilesFilter = nullptr);
FEEM_UTILS_EXPORT QString allFilesFilterString();
FEEM_UTILS_EXPORT QStringList allGlobPatterns();
FEEM_UTILS_EXPORT QMap<int, QList<Internal::MimeMagicRule> > magicRulesForMimeType(const MimeType &mimeType); // priority -> rules
FEEM_UTILS_EXPORT void setGlobPatternsForMimeType(const MimeType &mimeType, const QStringList &patterns);
FEEM_UTILS_EXPORT void setMagicRulesForMimeType(const MimeType &mimeType,
                                     const QMap<int, QList<Internal::MimeMagicRule> > &rules); // priority -> rules

} // Utils
