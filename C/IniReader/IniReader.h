/*
*   IniReader v1.0
*/

#ifndef INI_H
#define INI_H

#include <windows.h>

#define IR_STRING_MAX 256
#define IR_INT_MAX    16
#define IR_DOUBLE_MAX 32
#define MAX_SECTIONS  512

BOOL ReadString(PCSTR section, PCSTR key, PCSTR defValue, PSTR out, size_t outSize, PCSTR file);
int ReadInteger(PCSTR section, PCSTR key, PCSTR file);
double ReadDouble(PCSTR section, PCSTR key, PCSTR file);
void ReadAllStrings(PSTR* out, UINT rows, PCSTR key, PCSTR defValue, PCSTR file);
BOOL WriteString(PCSTR section, PCSTR key, PCSTR text, PCSTR file);
BOOL WriteInteger(PCSTR section, PCSTR key, int value, PCSTR file);
BOOL WriteDouble(PCSTR section, PCSTR key, double value, PCSTR file);
void FreeAllStrings(PSTR* m, UINT lines);

inline BOOL ReadString(PCSTR section, PCSTR key, PCSTR defValue, PSTR out, size_t outSize, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char buffer[IR_STRING_MAX];
    if (!GetPrivateProfileStringA(section, key, defValue, buffer, sizeof(buffer), filePath)) {
        strcpy_s(out, outSize, buffer);
        return FALSE;
    }

    char* hash = strstr(buffer, "#"), *semicolon = strstr(buffer, ";");
    if (hash || semicolon) {
        size_t position = hash ? hash - buffer : semicolon - buffer;

        if (position == 0) {
            strcpy_s(out, outSize, defValue);
            return FALSE;
        }

        do {
            for (size_t i = position ? position-- : position; i < strlen(buffer); i++) {
                buffer[i] = '\0';
            }
        } while (buffer[position] == ' ');
    }

    strcpy_s(out, outSize, buffer);
    return TRUE;
}

inline int ReadInteger(PCSTR section, PCSTR key, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char buffer[IR_INT_MAX];
    if (!GetPrivateProfileStringA(section, key, NULL, buffer, sizeof(buffer), filePath)) {
        return 0;
    }

    return atoi(buffer);
}

inline double ReadDouble(PCSTR section, PCSTR key, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char buffer[IR_DOUBLE_MAX];
    if (!GetPrivateProfileStringA(section, key, NULL, buffer, sizeof(buffer), filePath)) {
        return 0.0;
    }

    return strtod(buffer, NULL);
}

inline void ReadAllStrings(PSTR* out, UINT rows, PCSTR key, PCSTR defValue, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char buffer[MAX_SECTIONS];
    DWORD bytes = GetPrivateProfileSectionNamesA(buffer, sizeof(buffer), filePath);
    UINT row = 0;

    if (bytes) {
        UINT pos = 0;
        char section[16] = { (0) };

        for (DWORD i = 0; i < bytes; i++) {
            if (row == rows) break;
            section[pos++] = buffer[i];
            
            if (buffer[i] == '\0') {
                char strBuffer[IR_STRING_MAX];
                ReadString(section, key, defValue, strBuffer, sizeof(strBuffer), file);

                out[row++] = _strdup(strBuffer);
                pos = 0;
            }
        }
    }

    if (row < rows) {
        for (UINT i = row; i < rows; i++) {
            out[i] = _strdup(defValue);
        }
    }
}

inline BOOL WriteString(PCSTR section, PCSTR key, PCSTR text, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    return WritePrivateProfileStringA(section, key, text, filePath);
}

inline BOOL WriteInteger(PCSTR section, PCSTR key, int value, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char conversion[IR_INT_MAX];
    _itoa_s(value, conversion, sizeof(conversion), 10);

    return WritePrivateProfileStringA(section, key, conversion, filePath);
}

inline BOOL WriteDouble(PCSTR section, PCSTR key, double value, PCSTR file) {
    char filePath[MAX_PATH];
    GetFullPathNameA(file, sizeof(filePath), filePath, NULL);

    char conversion[IR_DOUBLE_MAX];
    _gcvt_s(conversion, sizeof(conversion), value, 15);

    return WritePrivateProfileStringA(section, key, conversion, filePath);
}

inline void FreeAllStrings(PSTR* m, UINT rows) {
    if (m) {
        for (UINT i = 0; i < rows; i++) {
            if (m[i]) free(m[i]);
        }
    }
}

#endif