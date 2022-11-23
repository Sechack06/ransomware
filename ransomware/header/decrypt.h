#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "encrypt.h"

void InvSubBytes(char block[4][4]);
void InvShiftRows(char block[4][4]);
void InvMixColumns(char block[4][4]);
int decrypt(char* key, char* enc, char* pt, int enclen);