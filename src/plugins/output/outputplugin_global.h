#pragma once

#include <QtGlobal>

#if defined(OUTPUTPLUGIN_LIBRARY)
#  define OUTPUTPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OUTPUTPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif
