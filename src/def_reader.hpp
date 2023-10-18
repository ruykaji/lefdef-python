#ifndef __DEF_READER_H__
#define __DEF_READER_H__

#include "def.hpp"
#include <defrReader.hpp>

struct DefReader {
    DefReader() = default;
    ~DefReader() = default;

    DefReader(const DefReader&) = delete;
    DefReader& operator=(const DefReader&) = delete;

    def::Def* read(const char* t_fileName);

private:
    static int dieAreaCallback(defrCallbackType_e t_type, defiBox* t_box, void* t_userData);

    static int componentStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData);

    static int componentCallback(defrCallbackType_e t_type, defiComponent* t_component, void* t_userData);

    static int gcellGridCallback(defrCallbackType_e t_type, defiGcellGrid* t_grid, void* t_userData);

    static int netStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData);

    static int netCallback(defrCallbackType_e t_type, defiNet* t_net, void* t_userData);

    static int specialNetCallback(defrCallbackType_e t_type, defiNet* t_net, void* t_userData);

    static int pinStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData);

    static int pinCallback(defrCallbackType_e t_type, defiPin* t_pinProp, void* t_userData);

    static int rowCallback(defrCallbackType_e t_type, defiRow* t_row, void* t_userData);

    static int trackCallback(defrCallbackType_e t_type, defiTrack* t_track, void* t_userData);

    static int viaCallback(defrCallbackType_e t_type, defiVia* t_via, void* t_userData);
};

#endif