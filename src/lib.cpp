#include "lef_reader.hpp"

#ifdef __cplusplus
extern "C" {
#endif

LefReader* createLefReader()
{
    return new LefReader();
}

void deleteLefReader(LefReader* reader)
{
    delete reader;
}

Lef* read(LefReader* reader, const char* t_fileName)
{
    return reader->read(t_fileName);
}

#ifdef __cplusplus
}
#endif