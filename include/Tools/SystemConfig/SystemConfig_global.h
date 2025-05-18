#pragma once

#include <QtCore/qglobal.h>

#if defined(SYSTEMCONFIG_LIBRARY)
#define SYSTEMCONFIG_EXPORT Q_DECL_EXPORT
#else
#define SYSTEMCONFIG_EXPORT Q_DECL_IMPORT
#endif