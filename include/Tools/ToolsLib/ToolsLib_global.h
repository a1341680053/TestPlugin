#pragma once

#include <QtCore/qglobal.h>

#if defined(TOOLS_LIBRARY)
#define TOOLSLIB_EXPORT Q_DECL_EXPORT
#else
#define TOOLSLIB_EXPORT Q_DECL_IMPORT
#endif