//=============================================================================

#ifndef Assert_H
#define Assert_H

#include <assert.h>

#define ASSERT(condiditon, message) \
  assert(message && (condiditon))

#endif
