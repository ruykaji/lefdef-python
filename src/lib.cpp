#include "lef_reader.hpp"
#include "def_reader.hpp"

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

void deleteLef(lef::Lef* t_lef)
{
    delete t_lef;
}

lef::Lef* readLef(LefReader* t_reader, const char* t_fileName)
{
    return t_reader->read(t_fileName);
}

// Def section
// ============================================================

DefReader* createDefReader()
{
    return new DefReader();
}

void deleteDefReader(DefReader* t_reader)
{
    delete t_reader;
}

void deleteDef(def::Def* t_lef)
{
    delete t_lef;
}

def::Def* readDef(DefReader* t_reader, const char* t_fileName)
{
    return t_reader->read(t_fileName);
}

#ifdef __cplusplus
}
#endif