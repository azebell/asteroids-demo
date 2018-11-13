
/// Miscellaneous helper functions

#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/////////////////////////////////////////////////
// helper function so that we can treat
// arrays like a circularly linked list
/////////////////////////////////////////////////
int positive_modulo(int i, int n);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTIL_H

