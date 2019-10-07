#pragma once

#include <qglobal.h>

#if defined(MATERIAL_LIBRARY)
#  define MATERIAL_EXPORT Q_DECL_EXPORT
#elif defined(MATERIAL_STATIC_LIBRARY)
#  define MATERIAL_EXPORT
#else
#  define MATERIAL_EXPORT Q_DECL_IMPORT
#endif
