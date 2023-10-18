#ifndef __LEF_H__
#define __LEF_H__

#include <vector>

namespace lef {
struct Rect {
    char* layer_ {};

    double xl_ {};
    double yl_ {};
    double xh_ {};
    double yh_ {};

    Rect() = default;
    ~Rect() = default;

    Rect(const double& t_xl, const double& t_yl, const double& t_xh, const double& t_yh, const char* t_layer);

    void destroy();
};

struct Port {
    Rect* rects_ {};

    int _numRects {};
    int _numRectsAllocated {};

    Port() = default;
    ~Port() = default;

    void destroy();
    void addRect(const Rect& t_rect);
};
struct Pin {
    char* name_ {};

    char* direction_ {};
    char* use_ {};
    char* shape_ {};

    Port* ports_ {};

    int _numPorts {};
    int _numPortsAllocated {};

    Pin() = default;
    ~Pin() = default;

    void destroy();
    void addPort(const Port& t_port);
};

struct Obstruction {
    Rect* rects_ {};

    int _numRects {};
    int _numRectsAllocated {};

    Obstruction() = default;
    ~Obstruction() = default;

    void destroy();
    void addRect(const Rect& t_rect);
};

struct Macro {
    char* name_ {};

    char* class_ {};
    char* source_ {};
    char* siteName_ {};

    double originX_ {};
    double originY_ {};

    double sizeX_ {};
    double sizeY_ {};

    char* foreignName_ {};
    double foreignX_ {};
    double foreignY_ {};
    int foreignOrient_ {};

    Pin* pins_ {};
    Obstruction obs_ {};

    int _numPins {};
    int _numPinsAllocated {};

    Macro() = default;
    ~Macro() = default;

    void destroy();
    void addPin(const Pin& t_pin);
};

struct Lef {
    Macro* macros_ {};

    int _numMacros {};
    int _numMacrosAllocated {};

    Lef() = default;
    ~Lef() = default;

    void destroy();
    void addMacro(const Macro& t_macro);
};
}

#endif