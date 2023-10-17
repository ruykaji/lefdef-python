#ifndef __LEF_READER_H__
#define __LEF_READER_H__

#include "lef.hpp"
#include <lefrReader.hpp>

struct LefReader {
    LefReader() = default;
    ~LefReader() = default;

    LefReader(const LefReader&) = delete;
    LefReader& operator=(const LefReader&) = delete;

    Lef* read(const char* t_fileName);

private:
    static int macroCallback(lefrCallbackType_e t_type, lefiMacro* t_macro, void* t_userData);
};

#endif