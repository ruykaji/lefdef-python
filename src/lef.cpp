#include <bits/stl_algobase.h>
#include <cstring>

#include "lef.hpp"

lef::Rect::Rect(const double& t_xl, const double& t_yl, const double& t_xh, const double& t_yh, const char* t_layer)
{
    layer_ = (char*)malloc((strlen(t_layer) + 1) * sizeof(char));
    strcpy(layer_, t_layer);

    xl_ = std::min(t_xl, t_xh);
    yl_ = std::min(t_yl, t_yh);
    xh_ = std::max(t_xl, t_xh);
    yh_ = std::max(t_yl, t_yh);
}

void lef::Rect::destroy()
{
    if (layer_) {
        free(layer_);
        layer_ = nullptr;
    }
}

void lef::Port::destroy()
{
    if (rects_) {
        for (std::size_t i = 0; i < _numRects; ++i) {
            rects_[i].destroy();
        }

        free(rects_);
        rects_ = nullptr;
    }
}

void lef::Port::addRect(const Rect& t_rect)
{
    if (_numRectsAllocated == _numRects) {
        if (_numRectsAllocated == 0) {
            _numRectsAllocated = 1;
        } else {
            _numRectsAllocated *= 2;
        }

        Rect* alloc = (Rect*)malloc(sizeof(Rect) * _numRectsAllocated);

        for (std::size_t i = 0; i < _numRects; ++i) {
            alloc[i] = rects_[i];
        }

        if (rects_) {
            free(rects_);
            rects_ = nullptr;
        }

        rects_ = alloc;
    }

    rects_[_numRects++] = t_rect;
}

void lef::Pin::destroy()
{
    if (ports_) {
        for (std::size_t i = 0; i < _numPorts; ++i) {
            ports_[i].destroy();
        }

        free(ports_);
        ports_ = nullptr;
    }

    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (direction_) {
        free(direction_);
        direction_ = nullptr;
    }

    if (use_) {
        free(use_);
        use_ = nullptr;
    }

    if (shape_) {
        free(shape_);
        shape_ = nullptr;
    }
}

void lef::Pin::addPort(const Port& t_port)
{
    if (_numPortsAllocated == _numPorts) {
        if (_numPortsAllocated == 0) {
            _numPortsAllocated = 1;
        } else {
            _numPortsAllocated *= 2;
        }

        Port* alloc = (Port*)malloc(sizeof(Port) * _numPortsAllocated);

        for (std::size_t i = 0; i < _numPorts; ++i) {
            alloc[i] = ports_[i];
        }

        if (ports_) {
            free(ports_);
            ports_ = nullptr;
        }

        ports_ = alloc;
    }

    ports_[_numPorts++] = t_port;
}

void lef::Obstruction::destroy()
{
    if (rects_) {
        for (std::size_t i = 0; i < _numRects; ++i) {
            rects_[i].destroy();
        }

        free(rects_);
        rects_ = nullptr;
    }
}

void lef::Obstruction::addRect(const Rect& t_rect)
{
    if (_numRectsAllocated == _numRects) {
        if (_numRectsAllocated == 0) {
            _numRectsAllocated = 1;
        } else {
            _numRectsAllocated *= 2;
        }

        Rect* alloc = (Rect*)malloc(sizeof(Rect) * _numRectsAllocated);

        for (std::size_t i = 0; i < _numRects; ++i) {
            alloc[i] = rects_[i];
        }

        if (rects_) {
            free(rects_);
            rects_ = nullptr;
        }

        rects_ = alloc;
    }

    rects_[_numRects++] = t_rect;
}

void lef::Macro::destroy()
{
    if (pins_) {
        for (std::size_t i = 0; i < _numPins; ++i) {
            pins_[i].destroy();
        }

        free(pins_);
        pins_ = nullptr;
    }

    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (class_) {
        free(class_);
        class_ = nullptr;
    }

    if (source_) {
        free(source_);
        source_ = nullptr;
    }

    if (siteName_) {
        free(siteName_);
        siteName_ = nullptr;
    }

    if (foreignName_) {
        free(foreignName_);
        foreignName_ = nullptr;
    }

    obs_.destroy();
}

void lef::Macro::addPin(const Pin& t_pin)
{
    if (_numPinsAllocated == _numPins) {
        if (_numPinsAllocated == 0) {
            _numPinsAllocated = 1;
        } else {
            _numPinsAllocated *= 2;
        }

        Pin* alloc = (Pin*)malloc(sizeof(Pin) * _numPinsAllocated);

        for (std::size_t i = 0; i < _numPins; ++i) {
            alloc[i] = pins_[i];
        }

        if (pins_) {
            free(pins_);
            pins_ = nullptr;
        }

        pins_ = alloc;
    }

    pins_[_numPins++] = t_pin;
}

void lef::Lef::destroy()
{
    if (macros_) {
        for (std::size_t i = 0; i < _numMacros; ++i) {
            macros_[i].destroy();
        }

        free(macros_);
        macros_ = nullptr;
    }
}

void lef::Lef::addMacro(const Macro& t_macro)
{
    if (_numMacrosAllocated == _numMacros) {
        if (_numMacrosAllocated == 0) {
            _numMacrosAllocated = 1;
        } else {
            _numMacrosAllocated *= 2;
        }

        Macro* alloc = (Macro*)malloc(sizeof(Macro) * _numMacrosAllocated);

        for (std::size_t i = 0; i < _numMacros; ++i) {
            alloc[i] = macros_[i];
        }

        if (macros_) {
            free(macros_);
            macros_ = nullptr;
        }

        macros_ = alloc;
    }

    macros_[_numMacros++] = t_macro;
}
