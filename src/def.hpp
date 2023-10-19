#ifndef __DEF_H__
#define __DEF_H__

#include <stdlib.h>

namespace def {
struct Rect {
    char* layer_ {};

    int xl_ {};
    int yl_ {};
    int xh_ {};
    int yh_ {};

    Rect() = default;
    ~Rect() = default;

    Rect(const double& t_xl, const double& t_yl, const double& t_xh, const double& t_yh, const char* t_layer);

    void destroy();
};

struct Port {
    Rect* rects_ {};
    int _numRects {};

    Port() = default;
    ~Port() = default;

    void destroy();
};

struct Row {
    char* name_ {};
    char* macro_ {};

    double x_ {};
    double y_ {};

    double numX_ {};
    double numY_ {};

    double stepX_ {};
    double stepY_ {};

    Row() = default;
    ~Row() = default;

    void destroy();
};

struct Track {
    char* layer_ {};

    double offset_ {};
    double num_ {};
    double step_ {};

    Track() = default;
    ~Track() = default;

    void destroy();
};

struct GCellGrid {
    int offset {};
    int num {};
    double step {};

    GCellGrid() = default;
    ~GCellGrid() = default;
};

struct Component {
    char* id_ {};
    char* name_ {};
    char* status_ {};
    char* source_ {};

    int orient_ {};
    int x_ {};
    int y_ {};

    Component() = default;
    ~Component() = default;

    void destroy();
};

struct Pin {
    char* name_ {};
    char* net_ {};
    char* use_ {};
    char* status_ {};
    char* direction_ {};

    int orient_ {};
    int x_ {};
    int y_ {};

    Rect* rects_ {};
    int _numRects {};

    Port* ports_ {};
    int _numPorts {};

    Pin() = default;
    ~Pin() = default;

    void destroy();
};

struct Net {
    char* name_ {};

    char** instances_ {};
    char** pins_ {};
    int _numPins {};

    Net() = default;
    ~Net() = default;

    void destroy();
};

struct Def {
    int* dieAreaWidth_ {};
    int* dieAreaHeight_ {};
    int _numPoints {};

    GCellGrid* gCellGridX_ {};
    int _numGCellGridX {};

    GCellGrid* gCellGridY_ {};
    int _numGCellGridY {};

    Component* components_ {};
    int _numComponents {};

    Pin* pins_ {};
    int _numPins {};

    Net* nets_ {};
    int _numNets {};

    Row* rows_ {};
    int _numRows {};

    Track* tracksX_ {};
    int _numTrackX {};

    Track* tracksY_ {};
    int _numTrackY {};

    int _numGCellGridXAllocated {};
    int _numGCellGridYAllocated {};
    int _numRowsAllocated {};
    int _numTrackXAllocated {};
    int _numTrackYAllocated {};

    Def() = default;
    ~Def() = default;

    void destroy();
    void addGCellGrid(const GCellGrid& t_gCellGrid, const int& t_way);
    void addRow(const Row& t_row);
    void addTrack(const Track& t_track, const int& t_way);
};
}

#endif