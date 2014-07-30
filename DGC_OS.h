//=============================================================================
// Are we in a windows development environment?

#ifndef DGC_OS_H
#define DGC_OS_H

#if defined(_WIN32) || defined(WIN32)
#define DGC_WINDOWS_DEV 1
#else
#define DGC_WINDOWS_DEV 0
#endif

#endif
