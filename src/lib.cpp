#include "lef_reader.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// Lef section
// ============================================================

LefReader* createLefReader()
{
    return new LefReader();
}

void deleteLefReader(LefReader* t_reader)
{
    delete t_reader;
}

void deleteLef(Lef* t_lef)
{
    delete t_lef;
}

Lef* read(LefReader* t_reader, const char* t_fileName)
{
    return t_reader->read(t_fileName);
}

// Def section
// ============================================================


#ifdef __cplusplus
}
#endif