#pragma once

#include <QtGlobal>

#if defined(COMMONFEMPLUGIN_LIBRARY)
#  define COMMONFEMPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMONFEMPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif
