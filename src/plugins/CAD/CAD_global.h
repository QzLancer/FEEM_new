#pragma once

#include <qglobal.h>

#if defined(CAD_LIBRARY)
#  define CAD_EXPORT Q_DECL_EXPORT
#elif defined(CAD_STATIC_LIBRARY)
#  define CAD_EXPORT
#else
#  define CAD_EXPORT Q_DECL_IMPORT
#endif
