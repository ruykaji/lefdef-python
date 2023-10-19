#include <bits/stl_algobase.h>
#include <cstring>

#include "def.hpp"

def::Rect::Rect(const double& t_xl, const double& t_yl, const double& t_xh, const double& t_yh, const char* t_layer)
{
    layer_ = (char*)malloc((strlen(t_layer) + 1) * sizeof(char));
    strcpy(layer_, t_layer);

    xl_ = std::min(t_xl, t_xh);
    yl_ = std::min(t_yl, t_yh);
    xh_ = std::max(t_xl, t_xh);
    yh_ = std::max(t_yl, t_yh);
}

void def::Rect::destroy()
{
    if (layer_) {
        free(layer_);
        layer_ = nullptr;
    }
}

void def::Port::destroy()
{
    if (rects_) {
        for (std::size_t i = 0; i < _numRects; ++i) {
            rects_[i].destroy();
        }

        free(rects_);
        rects_ = nullptr;
    }
}

void def::Row::destroy()
{
    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (macro_) {
        free(macro_);
        macro_ = nullptr;
    }
}

void def::Track::destroy()
{
    if (layer_) {
        free(layer_);
        layer_ = nullptr;
    }
}

void def::Component::destroy()
{
    if (id_) {
        free(id_);
        id_ = nullptr;
    }

    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (status_) {
        free(status_);
        status_ = nullptr;
    }

    if (source_) {
        free(source_);
        source_ = nullptr;
    }
}

void def::Pin::destroy()
{
    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (net_) {
        free(net_);
        net_ = nullptr;
    }

    if (use_) {
        free(use_);
        use_ = nullptr;
    }

    if (status_) {
        free(status_);
        status_ = nullptr;
    }

    if (direction_) {
        free(direction_);
        direction_ = nullptr;
    }

    if (rects_) {
        for (std::size_t i = 0; i < _numRects; ++i) {
            rects_[i].destroy();
        }

        free(rects_);
        rects_ = nullptr;
    }

    if (ports_) {
        for (std::size_t i = 0; i < _numPorts; ++i) {
            ports_[i].destroy();
        }

        free(ports_);
        ports_ = nullptr;
    }
}

void def::Net::destroy()
{
    if (name_) {
        free(name_);
        name_ = nullptr;
    }

    if (pins_ && instances_) {
        for (std::size_t i = 0; i < _numPins; ++i) {
            free(pins_[i]);
            pins_[i] = nullptr;

            free(instances_[i]);
            instances_[i] = nullptr;
        }

        free(pins_);
        pins_ = nullptr;

        free(instances_);
        instances_ = nullptr;
    }
}

void def::Def::destroy()
{
    if (dieAreaWidth_) {
        free(dieAreaWidth_);
        dieAreaWidth_ = nullptr;
    }

    if (dieAreaHeight_) {
        free(dieAreaHeight_);
        dieAreaHeight_ = nullptr;
    }

    if (gCellGridX_) {
        free(gCellGridX_);
        gCellGridX_ = nullptr;
    }

    if (gCellGridY_) {
        free(gCellGridY_);
        gCellGridY_ = nullptr;
    }

    if (components_) {
        for (std::size_t i = 0; i < _numComponents; ++i) {
            components_[i].destroy();
        }

        free(components_);
        components_ = nullptr;
    }

    if (pins_) {
        for (std::size_t i = 0; i < _numPins; ++i) {
            pins_[i].destroy();
        }

        free(pins_);
        pins_ = nullptr;
    }

    if (nets_) {
        for (std::size_t i = 0; i < _numNets; ++i) {
            nets_[i].destroy();
        }

        free(nets_);
        nets_ = nullptr;
    }

    if (rows_) {
        for (std::size_t i = 0; i < _numRows; ++i) {
            rows_[i].destroy();
        }

        free(rows_);
        rows_ = nullptr;
    }

    if (tracksX_) {
        for (std::size_t i = 0; i < _numTrackX; ++i) {
            tracksX_[i].destroy();
        }

        free(tracksX_);
        tracksX_ = nullptr;
    }

    if (tracksY_) {
        for (std::size_t i = 0; i < _numTrackY; ++i) {
            tracksY_[i].destroy();
        }

        free(tracksY_);
        tracksY_ = nullptr;
    }
}

void def::Def::addGCellGrid(const GCellGrid& t_gCellGrid, const int& t_way)
{
    if (t_way == 0) {
        if (_numGCellGridXAllocated == _numGCellGridX) {
            if (_numGCellGridXAllocated == 0) {
                _numGCellGridXAllocated = 1;
            } else {
                _numGCellGridXAllocated *= 2;
            }

            GCellGrid* alloc = (GCellGrid*)malloc(sizeof(GCellGrid) * _numGCellGridXAllocated);

            for (std::size_t i = 0; i < _numGCellGridX; ++i) {
                alloc[i] = gCellGridX_[i];
            }

            if (gCellGridX_) {
                free(gCellGridX_);
                gCellGridX_ = nullptr;
            }

            gCellGridX_ = alloc;
        }

        gCellGridX_[_numGCellGridX++] = t_gCellGrid;
    } else {
        if (_numGCellGridYAllocated == _numGCellGridY) {
            if (_numGCellGridYAllocated == 0) {
                _numGCellGridYAllocated = 1;
            } else {
                _numGCellGridYAllocated *= 2;
            }

            GCellGrid* alloc = (GCellGrid*)malloc(sizeof(GCellGrid) * _numGCellGridYAllocated);

            for (std::size_t i = 0; i < _numGCellGridY; ++i) {
                alloc[i] = gCellGridY_[i];
            }

            if (gCellGridY_) {
                free(gCellGridY_);
                gCellGridY_ = nullptr;
            }

            gCellGridY_ = alloc;
        }

        gCellGridY_[_numGCellGridY++] = t_gCellGrid;
    }
}

void def::Def::addRow(const Row& t_row)
{
    if (_numRowsAllocated == _numRows) {
        if (_numRowsAllocated == 0) {
            _numRowsAllocated = 1;
        } else {
            _numRowsAllocated *= 2;
        }

        Row* alloc = (Row*)malloc(sizeof(Row) * _numRowsAllocated);

        for (std::size_t i = 0; i < _numRows; ++i) {
            alloc[i] = rows_[i];
        }

        if (rows_) {
            free(rows_);
            rows_ = nullptr;
        }

        rows_ = alloc;
    }

    rows_[_numRows++] = t_row;
}

void def::Def::addTrack(const Track& t_track, const int& t_way)
{
    if (t_way == 0) {
        if (_numTrackXAllocated == _numTrackX) {
            if (_numTrackXAllocated == 0) {
                _numTrackXAllocated = 1;
            } else {
                _numTrackXAllocated *= 2;
            }

            Track* alloc = (Track*)malloc(sizeof(Track) * _numTrackXAllocated);

            for (std::size_t i = 0; i < _numTrackX; ++i) {
                alloc[i] = tracksX_[i];
            }

            if (tracksX_) {
                free(tracksX_);
                tracksX_ = nullptr;
            }

            tracksX_ = alloc;
        }

        tracksX_[_numTrackX++] = t_track;
    } else {
        if (_numTrackYAllocated == _numTrackY) {
            if (_numTrackYAllocated == 0) {
                _numTrackYAllocated = 1;
            } else {
                _numTrackYAllocated *= 2;
            }

            Track* alloc = (Track*)malloc(sizeof(Track) * _numTrackYAllocated);

            for (std::size_t i = 0; i < _numTrackY; ++i) {
                alloc[i] = tracksY_[i];
            }

            if (tracksY_) {
                free(tracksY_);
                tracksY_ = nullptr;
            }

            tracksY_ = alloc;
        }

        tracksY_[_numTrackY++] = t_track;
    }
}