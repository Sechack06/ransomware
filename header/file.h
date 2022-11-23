#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "encrypt.h"
#include "decrypt.h"

void all_files_enc_dec(char* dir, char *key, BOOL mode);