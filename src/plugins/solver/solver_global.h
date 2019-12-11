#pragma once

#include <qglobal.h>

#if defined(SOLVER_LIBRARY)
#  define FEEM_SOLVER_EXPORT Q_DECL_EXPORT
#elif defined(MESH_STATIC_LIBRARY)
#  define FEEM_SOLVER_EXPORT
#else
#  define FEEM_SOLVER_EXPORT Q_DECL_IMPORT
#endif
