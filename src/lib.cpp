#include "lef_reader.hpp"
#include "def_reader.hpp"

#if defined(_WIN32)
#define DLL00_EXPORT_API __declspec(dllexport)
#else
#define DLL00_EXPORT_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    // Lef section
    // ============================================================

    DLL00_EXPORT_API LefReader *createLefReader()
    {
        return new LefReader();
    }

    DLL00_EXPORT_API void deleteLefReader(LefReader *t_reader)
    {
        delete t_reader;
    }

    DLL00_EXPORT_API void deleteLef(lef::Lef *t_lef)
    {
        delete t_lef;
    }

    DLL00_EXPORT_API lef::Lef *readLef(LefReader *t_reader, const char *t_fileName)
    {
        return t_reader->read(t_fileName);
    }

    // Def section
    // ============================================================

    DLL00_EXPORT_API DefReader *createDefReader()
    {
        return new DefReader();
    }

    DLL00_EXPORT_API void deleteDefReader(DefReader *t_reader)
    {
        delete t_reader;
    }

    DLL00_EXPORT_API void deleteDef(def::Def *t_lef)
    {
        delete t_lef;
    }

    DLL00_EXPORT_API def::Def *readDef(DefReader *t_reader, const char *t_fileName)
    {
        return t_reader->read(t_fileName);
    }

#ifdef __cplusplus
}
#endif