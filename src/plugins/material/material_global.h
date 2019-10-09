#pragma once

#include <qglobal.h>

#if defined(MATERIAL_LIBRARY)
#  define FEEM_MATERIAL_EXPORT Q_DECL_EXPORT
#elif defined(MATERIAL_STATIC_LIBRARY)
#  define FEEM_MATERIAL_EXPORT
#else
#  define FEEM_MATERIAL_EXPORT Q_DECL_IMPORT
#endif
