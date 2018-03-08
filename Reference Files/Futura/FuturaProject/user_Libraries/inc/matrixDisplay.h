#ifndef MATRIXDISPLAY_H
#define MATRIXDISPLAY_H

static const char fontTable[];

void displayMatrix(const char *s);
void clearScreen(void);
void displayFloat(float f);
void displayInt(int i);
void displayMatrixScroll(char* str);
void displayErr(int err);

#endif
