#include <cstdio>
#include <execution>

#include "lef_reader.hpp"

Lef* LefReader::read(const char* t_fileName)
{
    // Init lef
    // ====================================================

    int initStatus = lefrInit();

    if (initStatus != 0) {
        throw std::runtime_error("Can't initialize lef parser!\n");
    }

    // Set lef callbacks
    // ====================================================

    lefrSetMacroCbk(&macroCallback);

    // Open lef file and parser it
    // ====================================================

    FILE* file = fopen(t_fileName, "r");

    if (file == nullptr) {
        throw std::runtime_error("Can't open the file!");
    }

    Lef* lefInstance = new Lef();

    int readStatus = lefrRead(file, t_fileName, lefInstance);

    if (readStatus != 0) {
        throw std::runtime_error("Can't parser the file!");
    }

    fclose(file);

    return lefInstance;
}

// Static methods
// =================================================================================================

int LefReader::macroCallback(lefrCallbackType_e t_type, lefiMacro* t_macro, void* t_userData)
{
    if (t_type == lefrMacroCbkType) {
        Lef* lefInstance = static_cast<Lef*>(t_userData);

        lefInstance->name = t_macro->name();

        return 0;
    }

    return 2;
}