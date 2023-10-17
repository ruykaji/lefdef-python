#include <cstdio>
#include <cstring>
#include <execution>

#include "def_reader.hpp"

Def* DefReader::read(const char* t_fileName)
{
    // Init def
    // ====================================================

    int initStatus = defrInit();

    if (initStatus != 0) {
        throw std::runtime_error("Can't initialize def parser!\n");
    }

    // Settings
    // ====================================================

    defrSetAddPathToNet();

    // Set def callbacks
    // ====================================================

    defrSetDieAreaCbk(&dieAreaCallback);
    defrSetComponentStartCbk(&componentStartCallback);
    defrSetComponentCbk(&componentCallback);
    defrSetComponentEndCbk(&componentEndCallback);
    defrSetPinCbk(&pinCallback);
    defrSetNetCbk(&netCallback);
    defrSetViaCbk(&viaCallback);

    // Open def file and parser it
    // ====================================================

    FILE* file = fopen(t_fileName, "r");

    if (file == nullptr) {
        throw std::runtime_error("Can't open the file!");
    }

    Def* defInstance = new Def();

    int readStatus = defrRead(file, t_fileName, defInstance, 0);

    if (readStatus != 0) {
        throw std::runtime_error("Can't parser the file!");
    }

    fclose(file);
    defrClear();

    return defiDebug_h;
}

// Static methods
// =================================================================================================

int DefReader::dieAreaCallback(defrCallbackType_e t_type, defiBox* t_box, void* t_userData){
    if(t_type != defrDieAreaCbkType){
        return 2;
    }



    return 0;
}