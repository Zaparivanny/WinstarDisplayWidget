#ifndef GFX_UTILS_H
#define GFX_UTILS_H

#ifdef __cplusplus
 extern "C" {
#endif

int itoc(char *buffer, int maxsize, int value);
int ftoc(char *buffer, int maxsize, float value, unsigned char points);

#ifdef __cplusplus
 }
#endif

#endif
