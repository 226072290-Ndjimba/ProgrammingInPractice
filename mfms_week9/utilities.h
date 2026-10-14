
#ifndef UTILITIES_H
#define UTILITIES_H

void clearInputBuffer(void);
int readInt(const char *prompt, int *value);
int readDouble(const char *prompt, double *value);
int readString(const char *prompt, char *text, int size);

#endif
