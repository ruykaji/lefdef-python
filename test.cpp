#include "src/lef_reader.hpp"

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

int main()
{
    LefReader* reader = createLefReader();
    Lef* lef = read(reader, "/home/alaie/Nangate.lef");
    deleteLefReader(reader);

    Macro macro {};

    for (std::size_t i = 0; i < lef->_numMacros; ++i) {
        macro = lef->macros_[i];
    }

    lef->destroy();

    delete lef;

    return 0;
}
