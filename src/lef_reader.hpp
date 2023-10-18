#ifndef __LEF_READER_H__
#define __LEF_READER_H__

#include "lef.hpp"
#include <lefrReader.hpp>

struct LefReader {
    LefReader() = default;
    ~LefReader() = default;

    LefReader(const LefReader&) = delete;
    LefReader& operator=(const LefReader&) = delete;

    lef::Lef* read(const char* t_fileName);

private:
    static int macroBeginCallback(lefrCallbackType_e t_type, const char* t_string, void* t_userData);

    static int macroCallback(lefrCallbackType_e t_type, lefiMacro* t_macro, void* t_userData);

    static int pinCallback(lefrCallbackType_e t_type, lefiPin* t_pin, void* t_userData);

    static int obsCallback(lefrCallbackType_e t_type, lefiObstruction* t_obs, void* t_userData);
};

#endif