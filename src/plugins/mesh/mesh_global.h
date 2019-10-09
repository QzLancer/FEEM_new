#pragma once

#include <qglobal.h>

#if defined(MESH_LIBRARY)
#  define FEEM_MESH_EXPORT Q_DECL_EXPORT
#elif defined(MESH_STATIC_LIBRARY)
#  define FEEM_MESH_EXPORT
#else
#  define FEEM_MESH_EXPORT Q_DECL_IMPORT
#endif
