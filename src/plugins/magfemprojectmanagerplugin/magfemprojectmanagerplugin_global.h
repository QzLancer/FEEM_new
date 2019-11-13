#pragma once

#include <QtGlobal>

#if defined(MAGPLUGIN_LIBRARY)
#  define MAGPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAGPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif
