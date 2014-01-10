//=============================================================================
//
// Version number for the version of G++ being used, this should be used like:
// 
// #if GCC_VERSION > 30200
//   something
// #else
//   ...
// #endif

#define GCC_VERSION (\
  __GNUC__ * 10000 \
  + __GNUC_MINOR__ * 100 \
  + __GNUC_PATCHLEVEL__ \
)


/* Test for GCC > 3.2.0 */

