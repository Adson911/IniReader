/*
*   IniReader v1.0
*/

#pragma once

#include <windows.h>
#include <string>
#include <vector>

typedef std::vector<std::string> VECTOR;

class IniReader {
    enum MaxValues : UINT {
        IR_STRING_MAX = 256,
        IR_INT_MAX    = 16,
        IR_DOUBLE_MAX = 32,
        MAX_SECTIONS  = 512
    };

    char filePath[MAX_PATH];

public:
    inline std::string ReadString(PCSTR section, PCSTR key) {
        char buffer[IR_STRING_MAX];
        if (GetPrivateProfileStringA(section, key, NULL, buffer, sizeof(buffer), filePath)) {
            std::string text(buffer);

            if (strstr(text.c_str(), "#") || strstr(text.c_str(), ";")) {
                size_t position = text.find('#') != text.npos ? text.find('#') : text.find(';');

                if (position == 0) return std::string();

                do {
                    text.erase(position ? position-- : position);
                } while (text.back() == ' ');
            }
            return text;
        }

        return std::string();
    }

    inline int ReadInteger(PCSTR section, PCSTR key) {
        char buffer[IR_INT_MAX];
        if (!GetPrivateProfileStringA(section, key, NULL, buffer, sizeof(buffer), filePath)) {
            return 0;
        }

        return std::atoi(buffer);
    }

    inline double ReadDouble(PCSTR section, PCSTR key) {
        char buffer[IR_DOUBLE_MAX];
        if (!GetPrivateProfileStringA(section, key, NULL, buffer, sizeof(buffer), filePath)) {
            return 0.0;
        }

        return std::strtod(buffer, NULL);
    }

    inline void ReadAllStrings(VECTOR& out, UINT rows, PCSTR key) {
        char buffer[MAX_SECTIONS];
        DWORD bytes = GetPrivateProfileSectionNamesA(buffer, sizeof(buffer), filePath);
        UINT row = 0;

        if (bytes) {
            UINT pos = 0;
            char section[16] = {(0)};

            for (DWORD i = 0; i < bytes; i++) {
                if (row == rows) break;
                section[pos++] = buffer[i];

                if (buffer[i] == '\0') {
                    out.push_back(ReadString(section, key));
                    row++;
                    pos = 0;
                }
            }
        }

        if (row < rows) {
            for (UINT i = row; i < rows; i++) {
                out.push_back(std::string());
            }
        }
    }

    inline bool WriteString(PCSTR section, PCSTR key, PCSTR text) {
        return WritePrivateProfileStringA(section, key, std::string(" " + std::string(text)).c_str(), filePath);
    }

    inline bool WriteInteger(PCSTR section, PCSTR key, int value) {
        return WritePrivateProfileStringA(section, key, std::string(" " + std::to_string(value)).c_str(), filePath);
    }

    inline bool WriteDouble(PCSTR section, PCSTR key, double value) {
        return WritePrivateProfileStringA(section, key, std::string(" " + std::to_string(value)).c_str(), filePath);
    }

    IniReader(PCSTR file) {
        GetFullPathNameA(file, sizeof(filePath), filePath, NULL);
    }
};