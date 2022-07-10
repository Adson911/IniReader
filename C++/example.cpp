#include <iostream>
#include <iomanip> // for std::setprecision
#include "IniReader/IniReader.hpp"

using namespace std;

int main() {
    IniReader ini("IniFile.ini");

    // writing values
    ini.WriteString("SECTION1", "STRING", "IniReader V1.0");
    ini.WriteInteger("SECTION1", "INTEGER", 1);
    ini.WriteDouble("SECTION1", "DOUBLE", 1.0);

    // all sections strings
    VECTOR strings;
    ini.ReadAllStrings(strings, 3, "STRING");

    cout << "\n***ALL SECTIONS STRINGS***" << endl << endl;

    cout << strings.at(0) << endl;
    cout << strings.at(1) << endl;
    cout << strings.at(2) << endl;

    cout << fixed << showpoint << setprecision(2);

    // section 1
    cout << "\n***SECTION 1***" << endl << endl;

    cout << ini.ReadString("SECTION1", "STRING") << endl;
    cout << ini.ReadInteger("SECTION1", "INTEGER") << endl;
    cout << ini.ReadDouble("SECTION1", "DOUBLE") << endl;

    cout << "\n***SECTION 2***" << endl << endl;

    // section 2
    cout << ini.ReadString("SECTION2", "STRING") << endl;
    cout << ini.ReadInteger("SECTION2", "INTEGER") << endl;
    cout << ini.ReadDouble("SECTION2", "DOUBLE") << endl;

    cout << "\n***SECTION 3***" << endl << endl;

    // section 3
    cout << ini.ReadString("SECTION3", "STRING") << endl;
    cout << ini.ReadInteger("SECTION3", "INTEGER") << endl;
    cout << ini.ReadDouble("SECTION3", "DOUBLE") << endl;

    cout << endl;

    getchar();
    return 0;
}