#pragma once

#include <QtCore/qglobal.h>

#if defined(PLUGIN_CREATE_LIBRARY)
#define PLUGINCREATE_EXPORT Q_DECL_EXPORT
#else
#define PLUGINCREATE_EXPORT Q_DECL_IMPORT
#endif