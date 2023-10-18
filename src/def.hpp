#ifndef __DEF_H__
#define __DEF_H__

namespace def {
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
    int _numGCellGridXAllocated {};

    GCellGrid* gCellGridY_ {};
    int _numGCellGridY {};
    int _numGCellGridYAllocated {};

    Component* components_ {};
    int _numComponents {};

    Net* nets {};
    int _numNuts {};

    Row* rows_ {};
    int _numRows {};
    int _numRowsAllocated {};

    Track* tracksX_ {};
    int _numTrackX {};
    int _numTrackXAllocated {};

    Track* tracksY_ {};
    int _numTrackY {};
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