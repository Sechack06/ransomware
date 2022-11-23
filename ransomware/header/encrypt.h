#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <io.h>
#include <string.h>

#define BUFF_SIZE 1024
#define BLOCK_SIZE 16

#define Multiply(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * xtime(x)) ^                       \
      ((y>>2 & 1) * xtime(xtime(x))) ^                \
      ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
      ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

void addRoundKey(char block[4][4], char roundkey[4][4]);
void SubBytes(char block[4][4]);
void ShiftRows(char block[4][4]);
char xtime(char x);
void MixColumns(char block[4][4]);
void cbc(char block[4][4], char prev[4][4]);
void RotWord(char w[4]);
void SubWord(char w[4]);
void KeyExpansion(char expandedKey[44][4], char* key);
void padding(char* pt, int ptlen);
int encrypt(char* key, char* pt, char* enc, int ptlen);