#ifndef SINCALC_GLOBAL_H
#define SINCALC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SINCALC_LIBRARY)
#  define SINCALCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SINCALCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SINCALC_GLOBAL_H
