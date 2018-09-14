#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LIBSTDFRAME_QT_LIB)
#  define LIBSTDFRAME_QT_EXPORT Q_DECL_EXPORT
# else
#  define LIBSTDFRAME_QT_EXPORT Q_DECL_IMPORT
# endif
#else
# define LIBSTDFRAME_QT_EXPORT
#endif
