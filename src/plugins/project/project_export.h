#pragma once

#include <qglobal.h>

#if defined(PROJECT_LIBRARY)
#  define FEEM_PROJECT_EXPORT Q_DECL_EXPORT
#elif defined(PROJECT_STATIC_LIBRARY)
#  define FEEM_PROJECT_EXPORT
#else
#  define FEEM_PROJECT_EXPORT Q_DECL_IMPORT
#endif
