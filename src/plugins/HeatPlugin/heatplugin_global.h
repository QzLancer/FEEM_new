#pragma once

#include <QtGlobal>

#if defined(HEATPLUGIN_LIBRARY)
#  define HEATPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HEATPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif
