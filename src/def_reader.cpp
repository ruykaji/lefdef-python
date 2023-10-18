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
    // defrSetComponentEndCbk(&componentEndCallback);
    // defrSetPinCbk(&pinCallback);
    // defrSetNetCbk(&netCallback);
    // defrSetViaCbk(&viaCallback);

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

    return defInstance;
}

// Static methods
// =================================================================================================

int DefReader::dieAreaCallback(defrCallbackType_e t_type, defiBox* t_box, void* t_userData){
    if(t_type != defrDieAreaCbkType){
        return 2;
    }

    Def* defInstance = static_cast<Def*>(t_userData);
    defiPoints points = t_box->getPoint();

    defInstance->dieAreaWidth_ = (int*)malloc(sizeof(int)*points.numPoints);
    defInstance->dieAreaHeight_ = (int*)malloc(sizeof(int)*points.numPoints);
    
    for(std::size_t i =0 ;i < points.numPoints; ++i){
        defInstance->dieAreaWidth_[i] = points.x[i];
        defInstance->dieAreaHeight_[i] = points.y[i];
    }

    return 0;
}

int DefReader::componentStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData){
    if(t_type != defrComponentStartCbkType){
        return 2;
    }

    Def* defInstance = static_cast<Def*>(t_userData);

    defInstance->components_ = (Component*)malloc(sizeof(Component) * t_number);

    return 0;
}

int DefReader::componentCallback(defrCallbackType_e t_type, defiComponent* t_component, void* t_userData){
    if(t_type != defrComponentCbkType){
        return 2;
    }

    Def* defInstance = static_cast<Def*>(t_userData);

    return 0;
}

int DefReader::gcellGridCallback(defrCallbackType_e t_type, defiGcellGrid* t_grid, void* t_userData){
    if(t_type != defrGcellGridCbkType){
        return 2;
    }

    Def* defInstance = static_cast<Def*>(t_userData);

    return 0;
}