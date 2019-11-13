#pragma once

#include "utils_global.h"

#include <QList>
#include <QString>

QT_BEGIN_NAMESPACE
class QJsonValue;
QT_END_NAMESPACE

namespace Utils {

// Create a usable settings key from a category,
// for example Editor|C++ -> Editor_C__
FEEM_UTILS_EXPORT QString settingsKey(const QString &category);

// Return the common prefix part of a string list:
// "C:\foo\bar1" "C:\foo\bar2"  -> "C:\foo\bar"
FEEM_UTILS_EXPORT QString commonPrefix(const QStringList &strings);

// Return the common path of a list of files:
// "C:\foo\bar1" "C:\foo\bar2"  -> "C:\foo"
FEEM_UTILS_EXPORT QString commonPath(const QStringList &files);

// On Linux/Mac replace user's home path with ~
// Uses cleaned path and tries to use absolute path of "path" if possible
// If path is not sub of home path, or when running on Windows, returns the input
FEEM_UTILS_EXPORT QString withTildeHomePath(const QString &path);

// Removes first unescaped ampersand in text
FEEM_UTILS_EXPORT QString stripAccelerator(const QString &text);
// Quotes all ampersands
FEEM_UTILS_EXPORT QString quoteAmpersands(const QString &text);

FEEM_UTILS_EXPORT bool readMultiLineString(const QJsonValue &value, QString *out);

// Compare case insensitive and use case sensitive comparison in case of that being equal.
FEEM_UTILS_EXPORT int caseFriendlyCompare(const QString &a, const QString &b);

class FEEM_UTILS_EXPORT AbstractMacroExpander
{
public:
    virtual ~AbstractMacroExpander() {}
    // Not const, as it may change the state of the expander.
    //! Find an expando to replace and provide a replacement string.
    //! \param str The string to scan
    //! \param pos Position to start scan on input, found position on output
    //! \param ret Replacement string on output
    //! \return Length of string part to replace, zero if no (further) matches found
    virtual int findMacro(const QString &str, int *pos, QString *ret);
    //! Provide a replacement string for an expando
    //! \param name The name of the expando
    //! \param ret Replacement string on output
    //! \return True if the expando was found
    virtual bool resolveMacro(const QString &name, QString *ret, QSet<AbstractMacroExpander *> &seen) = 0;
private:
    bool expandNestedMacros(const QString &str, int *pos, QString *ret);
};

FEEM_UTILS_EXPORT void expandMacros(QString *str, AbstractMacroExpander *mx);
FEEM_UTILS_EXPORT QString expandMacros(const QString &str, AbstractMacroExpander *mx);

FEEM_UTILS_EXPORT int parseUsedPortFromNetstatOutput(const QByteArray &line);

template<typename T, typename Container>
T makeUniquelyNumbered(const T &preferred, const Container &reserved)
{
    if (!reserved.contains(preferred))
        return preferred;
    int i = 2;
    T tryName = preferred + QString::number(i);
    while (reserved.contains(tryName))
        tryName = preferred + QString::number(++i);
    return tryName;
}



} // namespace Utils
