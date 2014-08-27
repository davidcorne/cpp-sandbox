//=============================================================================

#ifndef Version_H
#define Version_H

#include "Compiler.h"

#if COMPILER_TYPE == COMPILER_TYPE_GCC
#define VERSION (\
  __GNUC__ * 10000 \
  + __GNUC_MINOR__ * 100 \
  + __GNUC_PATCHLEVEL__ \
)
#endif

#ifndef VERSION
#error "Unknown compiler type."
#endif

#endif
