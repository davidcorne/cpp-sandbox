//=============================================================================
// There seem to be some edge cases where G++ will (correctly?) not compile
// with the keyword typename. However VS will (incorrectly?) not compile
// without typename in the same place. This header gives you a define which
// can be used as typename in those cases.

#ifndef ContestedTypename_H
#define ContestedTypename_H

#include "Compiler.h"

#if COMPILER_TYPE == COMPILER_TYPE_VS
#define CONTESTED_TYPENAME typename
#else
#define CONTESTED_TYPENAME
#endif
#endif
