#include <cstdio>
#include <cstring>
#include <execution>

#include "lef_reader.hpp"

lef::Lef* LefReader::read(const char* t_fileName)
{
    // Init lef
    // ====================================================

    int initStatus = lefrInit();

    if (initStatus != 0) {
        throw std::runtime_error("Can't initialize lef parser!\n");
    }

    // Set lef callbacks
    // ====================================================

    lefrSetMacroBeginCbk(&macroBeginCallback);
    lefrSetMacroCbk(&macroCallback);
    lefrSetPinCbk(&pinCallback);
    lefrSetObstructionCbk(&obsCallback);

    // Open lef file and parser it
    // ====================================================

    FILE* file = fopen(t_fileName, "r");

    if (file == nullptr) {
        throw std::runtime_error("Can't open the file!");
    }

    lef::Lef* lefInstance = new lef::Lef();

    int readStatus = lefrRead(file, t_fileName, lefInstance);

    if (readStatus != 0) {
        throw std::runtime_error("Can't parser the file!");
    }

    fclose(file);
    lefrClear();

    return lefInstance;
}

// Static methods
// =================================================================================================

int LefReader::macroBeginCallback(lefrCallbackType_e t_type, const char* t_string, void* t_userData)
{
    if (t_type != lefrMacroBeginCbkType) {
        return 2;
    }

    lef::Lef* lefInstance = static_cast<lef::Lef*>(t_userData);
    lef::Macro macro {};

    lefInstance->addMacro(macro);

    return 0;
}

int LefReader::macroCallback(lefrCallbackType_e t_type, lefiMacro* t_macro, void* t_userData)
{
    if (t_type != lefrMacroCbkType) {
        return 2;
    }

    lef::Lef* lefInstance = static_cast<lef::Lef*>(t_userData);
    lef::Macro* macro = &lefInstance->macros_[lefInstance->_numMacros - 1];

    macro->name_ = (char*)malloc((strlen(t_macro->name()) + 1) * sizeof(char));
    strcpy(macro->name_, t_macro->name());

    if (t_macro->hasClass()) {
        macro->class_ = (char*)malloc((strlen(t_macro->macroClass()) + 1) * sizeof(char));
        strcpy(macro->class_, t_macro->macroClass());
    }

    if (t_macro->hasSource()) {
        macro->source_ = (char*)malloc((strlen(t_macro->source()) + 1) * sizeof(char));
        strcpy(macro->source_, t_macro->source());
    }

    if (t_macro->hasSiteName()) {
        macro->siteName_ = (char*)malloc((strlen(t_macro->siteName()) + 1) * sizeof(char));
        strcpy(macro->siteName_, t_macro->siteName());
    }

    if (t_macro->hasOrigin()) {
        macro->originX_ = t_macro->originX();
        macro->originY_ = t_macro->originY();
    }

    if (t_macro->hasSize()) {
        macro->sizeX_ = t_macro->sizeX();
        macro->sizeY_ = t_macro->sizeY();
    }

    if (t_macro->hasForeign()) {
        for (std::size_t i = 0; i < t_macro->numForeigns(); ++i) {
            macro->foreignName_ = (char*)malloc((strlen(t_macro->foreignName()) + 1) * sizeof(char));
            strcpy(macro->foreignName_, t_macro->foreignName(i));

            macro->foreignX_ = t_macro->foreignX(i);
            macro->foreignY_ = t_macro->foreignY(i);

            if (t_macro->hasForeignOrient(i)) {
                macro->foreignOrient_ = t_macro->foreignOrient(i);
            }
        }
    }

    return 0;
}

int LefReader::pinCallback(lefrCallbackType_e t_type, lefiPin* t_pin, void* t_userData)
{
    if (t_type != lefrPinCbkType) {
        return 2;
    }

    lef::Pin pin {};

    pin.name_ = (char*)malloc((strlen(t_pin->name()) + 1) * sizeof(char));
    strcpy(pin.name_, t_pin->name());

    if (t_pin->hasDirection()) {
        pin.direction_ = (char*)malloc((strlen(t_pin->direction()) + 1) * sizeof(char));
        strcpy(pin.direction_, t_pin->direction());
    }

    if (t_pin->hasUse()) {
        pin.use_ = (char*)malloc((strlen(t_pin->use()) + 1) * sizeof(char));
        strcpy(pin.use_, t_pin->use());
    }

    if (t_pin->hasShape()) {
        pin.shape_ = (char*)malloc((strlen(t_pin->shape()) + 1) * sizeof(char));
        strcpy(pin.shape_, t_pin->shape());
    }

    const char* layer {};

    for (std::size_t i = 0; i < t_pin->numPorts(); ++i) {
        lefiGeometries* portGeom = t_pin->port(i);
        lef::Port port {};

        for (std::size_t i = 0; i < portGeom->numItems(); ++i) {
            switch (portGeom->itemType(i)) {
            case lefiGeomEnum::lefiGeomLayerE: {
                layer = portGeom->getLayer(i);
                break;
            }
            case lefiGeomEnum::lefiGeomRectE: {
                lefiGeomRect* portRect = portGeom->getRect(i);

                port.addRect(lef::Rect(portRect->xl, portRect->yl, portRect->xh, portRect->yh, layer));
                break;
            }
            default:
                break;
            }
        }

        pin.addPort(port);
    }

    lef::Lef* lefInstance = static_cast<lef::Lef*>(t_userData);
    lef::Macro* macro = &lefInstance->macros_[lefInstance->_numMacros - 1];

    macro->addPin(pin);

    return 0;
}

int LefReader::obsCallback(lefrCallbackType_e t_type, lefiObstruction* t_obs, void* t_userData)
{
    if (t_type != lefrObstructionCbkType) {
        return 2;
    }

    lefiGeometries* osbGeom = t_obs->geometries();
    const char* layer {};
    lef::Obstruction obs {};

    for (std::size_t i = 0; i < osbGeom->numItems(); ++i) {
        switch (osbGeom->itemType(i)) {
        case lefiGeomEnum::lefiGeomLayerE: {
            layer = osbGeom->getLayer(i);
            break;
        }
        case lefiGeomEnum::lefiGeomRectE: {
            lefiGeomRect* portRect = osbGeom->getRect(i);

            obs.addRect(lef::Rect(portRect->xl, portRect->yl, portRect->xh, portRect->yh, layer));

            break;
        }
        default:
            break;
        }
    }

    lef::Lef* lefInstance = static_cast<lef::Lef*>(t_userData);
    lef::Macro* macro = &lefInstance->macros_[lefInstance->_numMacros - 1];

    macro->obs_ = obs;

    return 0;
}