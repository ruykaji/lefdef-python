#include "src/lef_reader.hpp"
#include "src/def_reader.hpp"


// Lef methods
// =========================================================

LefReader* createLefReader()
{
    return new LefReader();
}

void deleteLefReader(LefReader* t_reader)
{
    delete t_reader;
}

lef::Lef* read(LefReader* t_reader, const char* t_fileName)
{
    return t_reader->read(t_fileName);
}

// Def methods
// =========================================================

DefReader* createDefReader()
{
    return new DefReader();
}

void deleteDefReader(DefReader* t_reader)
{
    delete t_reader;
}

def::Def* read(DefReader* t_reader, const char* t_fileName)
{
    return t_reader->read(t_fileName);
}

int main()
{
    LefReader* lefReader = createLefReader();
    lef::Lef* lef = read(lefReader, "/home/alaie/Nangate.lef");
    deleteLefReader(lefReader);

    lef::Macro macro {};

    for (std::size_t i = 0; i < lef->_numMacros; ++i) {
        macro = lef->macros_[i];
    }

    lef->destroy();

    delete lef;

    DefReader* defReader = createDefReader();
    def::Def* def = read(defReader, "/home/alaie/bsg_chip.def");
    deleteDefReader(defReader);

    def->destroy();

    delete def;

    return 0;
}
