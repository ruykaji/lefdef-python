#ifndef __DEF_H__
#define __DEF_H__

struct Row{

};

struct Track{

};

struct GCellGrid{
    int offsetX {};
    int offsetY {};
    int numX{};
    int numY{};
    double stepX{};
    double stepY{};

    GCellGrid() = default;
    GCellGrid() = default;
};

struct Component{

};

struct Pin{

};

struct Net{

};

struct Def {
    int* dieAreaWidth_ {};
    int* dieAreaHeight_ {};
    int numPoints {};

    Component* components_{};


    Def() = default;
    ~Def() = default;

    void destroy();
};

#endif