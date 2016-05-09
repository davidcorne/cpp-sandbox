//=============================================================================

#ifndef Assert_H
#define Assert_H

#include <cassert>

#define ASSERT(condiditon, message) \
  assert(message && (condiditon))

#endif
