#ifndef __DEF_READER_H__
#define __DEF_READER_H__

#include "def.hpp"
#include <defrReader.hpp>

struct DefReader {
    DefReader() = default;
    ~DefReader() = default;

    DefReader(const DefReader&) = delete;
    DefReader& operator=(const DefReader&) = delete;

    Def* read(const char* t_fileName);

private:
    // static int blockageCallback(defrCallbackType_e t_type, defiBlockage* t_blockage, void* t_userData);

    static int dieAreaCallback(defrCallbackType_e t_type, defiBox* t_box, void* t_userData);

    static int componentStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData);

    static int componentCallback(defrCallbackType_e t_type, defiComponent* t_component, void* t_userData);

    // static int componentEndCallback(defrCallbackType_e t_type, void* t, void* t_userData);

    // static int componentMaskShiftLayerCallback(defrCallbackType_e t_type, defiComponentMaskShiftLayer* t_shiftLayers, void* t_userData);

    // static int doubleCallback(defrCallbackType_e t_type, double* t_number, void* t_userData);

    // static int fillCallback(defrCallbackType_e t_type, defiFill* t_shiftLayers, void* t_userData);

    static int gcellGridCallback(defrCallbackType_e t_type, defiGcellGrid* t_grid, void* t_userData);

    // static int groupCallback(defrCallbackType_e t_type, defiGroup* t_shiftLayers, void* t_userData);

    // static int integerCallback(defrCallbackType_e t_type, int t_number, void* t_userData);

    // static int netCallback(defrCallbackType_e t_type, defiNet* t_net, void* t_userData);

    // static int specialNetCallback(defrCallbackType_e t_type, defiNet* t_net, void* t_userData);

    // static int nonDefaultCallback(defrCallbackType_e t_type, defiNonDefault* t_rul, void* t_userData);

    // static int pathCallback(defrCallbackType_e t_type, defiPath* t_path, void* t_userData);

    // static int pinCallback(defrCallbackType_e t_type, defiPin* t_pinProp, void* t_userData);

    // static int propCallback(defrCallbackType_e t_type, defiProp* t_prop, void* t_userData);

    // static int regionCallback(defrCallbackType_e t_type, defiRegion* t_region, void* t_userData);

    static int rowCallback(defrCallbackType_e t_type, defiRow* t_row, void* t_userData);

    // static int scanchainCallback(defrCallbackType_e t_type, defiScanchain* t_scanchain, void* t_userData);

    // static int slotCallback(defrCallbackType_e t_type, defiSlot* t_slot, void* t_userData);

    // static int stringCallback(defrCallbackType_e t_type, const char* t_string, void* t_userData);

    // static int stylesCallback(defrCallbackType_e t_type, defiStyles* t_style, void* t_userData);

    static int trackCallback(defrCallbackType_e t_type, defiTrack* t_track, void* t_userData);

    // static int viaCallback(defrCallbackType_e t_type, defiVia* t_via, void* t_userData);

    // static int voidCallback(defrCallbackType_e t_type, void* t_variable, void* t_userData);
};

#endif