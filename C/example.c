#include <stdio.h>
#include "IniReader\IniReader.h"

#define MAX_LINES 3

int main() {
    // writing values
    WriteString("SECTION1", "STRING", "IniReader V1.0", "IniFile.ini");
    WriteInteger("SECTION1", "INTEGER", 1, "IniFile.ini");
    WriteInteger("SECTION1", "DOUBLE", 1.0, "IniFile.ini");

    // all section strings
    char* dst[MAX_LINES] = {(0)};
    ReadAllStrings(dst, MAX_LINES, "STRING", "not found", "IniFile.ini");

    printf("\n***ALL SECTIONS STRINGS***\n\n");

    printf("%s\n", dst[0]);
    printf("%s\n", dst[1]);
    printf("%s\n", dst[2]);

    FreeAllStrings(dst, MAX_LINES);

    char str[IR_STRING_MAX];

    // section 1
    printf("\n***SECTION 1***\n\n");
    ReadString("SECTION1", "STRING", "not found", str, sizeof(str), "IniFile.ini");

    printf("%s\n", str);
    printf("%d\n", ReadInteger("SECTION1", "INTEGER", "IniFile.ini"));
    printf("%lf\n", ReadDouble("SECTION1", "DOUBLE", "IniFile.ini"));

    // section 2
    printf("\n***SECTION 2***\n\n");
    ReadString("SECTION2", "STRING", "not found", str, sizeof(str), "IniFile.ini");

    printf("%s\n", str);
    printf("%d\n", ReadInteger("SECTION2", "INTEGER", "IniFile.ini"));
    printf("%lf\n", ReadDouble("SECTION2", "DOUBLE", "IniFile.ini"));

    // section 3
    printf("\n***SECTION 3***\n\n");
    ReadString("SECTION3", "STRING", "not found", str, sizeof(str), "IniFile.ini");

    printf("%s\n", str);
    printf("%d\n", ReadInteger("SECTION3", "INTEGER", "IniFile.ini"));
    printf("%lf\n", ReadDouble("SECTION3", "DOUBLE", "IniFile.ini"));

    printf("\n");

    getchar();
    return 0;
}