#include <cstdio>
#include <cstring>
#include <execution>

#include "def_reader.hpp"

def::Def* DefReader::read(const char* t_fileName)
{
    // Init def
    // ====================================================

    int initStatus = defrInit();

    if (initStatus != 0) {
        throw std::runtime_error("Can't initialize def parser!\n");
    }

    // Settings
    // ====================================================

    defrSetAddPathToNet();

    // Set def callbacks
    // ====================================================

    defrSetDieAreaCbk(&dieAreaCallback);
    defrSetComponentStartCbk(&componentStartCallback);
    defrSetComponentCbk(&componentCallback);
    defrSetGcellGridCbk(&gcellGridCallback);
    defrSetNetStartCbk(&netStartCallback);
    defrSetNetCbk(&netCallback);
    defrSetStartPinsCbk(&pinStartCallback);
    defrSetPinCbk(&pinCallback);
    defrSetRowCbk(&rowCallback);
    defrSetTrackCbk(&trackCallback);

    // Open def file and parser it
    // ====================================================

    FILE* file = fopen(t_fileName, "r");

    if (file == nullptr) {
        throw std::runtime_error("Can't open the file!");
    }

    def::Def* defInstance = new def::Def();

    int readStatus = defrRead(file, t_fileName, defInstance, 0);

    if (readStatus != 0) {
        throw std::runtime_error("Can't parser the file!");
    }

    fclose(file);
    defrClear();

    return defInstance;
}

// Static methods
// =================================================================================================

int DefReader::dieAreaCallback(defrCallbackType_e t_type, defiBox* t_box, void* t_userData)
{
    if (t_type != defrDieAreaCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);
    defiPoints points = t_box->getPoint();

    defInstance->dieAreaWidth_ = (int*)malloc(sizeof(int) * points.numPoints);
    defInstance->dieAreaHeight_ = (int*)malloc(sizeof(int) * points.numPoints);

    for (std::size_t i = 0; i < points.numPoints; ++i) {
        defInstance->dieAreaWidth_[i] = points.x[i];
        defInstance->dieAreaHeight_[i] = points.y[i];
    }

    defInstance->_numPoints = points.numPoints;

    return 0;
}

int DefReader::componentStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData)
{
    if (t_type != defrComponentStartCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    defInstance->components_ = (def::Component*)malloc(sizeof(def::Component) * t_number);

    return 0;
}

int DefReader::componentCallback(defrCallbackType_e t_type, defiComponent* t_component, void* t_userData)
{
    if (t_type != defrComponentCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);
    def::Component component {};

    component.id_ = (char*)malloc((strlen(t_component->id()) + 1) * sizeof(char));
    strcpy(component.id_, t_component->id());

    component.name_ = (char*)malloc((strlen(t_component->name()) + 1) * sizeof(char));
    strcpy(component.name_, t_component->name());

    if (t_component->isPlaced()) {
        component.status_ = (char*)malloc(7 * sizeof(char));
        strcpy(component.status_, "PLACED");
    } else if (t_component->isFixed()) {
        component.status_ = (char*)malloc(6 * sizeof(char));
        strcpy(component.status_, "FIXED");
    } else if (t_component->isCover()) {
        component.status_ = (char*)malloc(6 * sizeof(char));
        strcpy(component.status_, "COVER");
    } else if (t_component->isUnplaced()) {
        component.status_ = (char*)malloc(9 * sizeof(char));
        strcpy(component.status_, "UNPLACED");
    }

    if (t_component->hasSource()) {
        component.source_ = (char*)malloc((strlen(t_component->source()) + 1) * sizeof(char));
        strcpy(component.source_, t_component->source());
    }

    component.orient_ = t_component->placementOrient();
    component.x_ = t_component->placementX();
    component.y_ = t_component->placementY();

    defInstance->components_[defInstance->_numComponents++] = component;

    return 0;
}

int DefReader::gcellGridCallback(defrCallbackType_e t_type, defiGcellGrid* t_grid, void* t_userData)
{
    if (t_type != defrGcellGridCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    if (strcmp(t_grid->macro(), "X") == 0) {
        defInstance->addGCellGrid(def::GCellGrid(), 0);

        defInstance->gCellGridX_[defInstance->_numGCellGridX - 1].offset = t_grid->x();
        defInstance->gCellGridX_[defInstance->_numGCellGridX - 1].num = t_grid->xNum();
        defInstance->gCellGridX_[defInstance->_numGCellGridX - 1].step = t_grid->xStep();
    } else if (strcmp(t_grid->macro(), "Y") == 0) {
        defInstance->addGCellGrid(def::GCellGrid(), 1);

        defInstance->gCellGridY_[defInstance->_numGCellGridY - 1].offset = t_grid->x();
        defInstance->gCellGridY_[defInstance->_numGCellGridY - 1].num = t_grid->xNum();
        defInstance->gCellGridY_[defInstance->_numGCellGridY - 1].step = t_grid->xStep();
    }

    return 0;
}

int DefReader::netStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData)
{
    if (t_type != defrNetStartCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    defInstance->nets_ = (def::Net*)malloc(t_number * sizeof(def::Net));

    return 0;
}

int DefReader::netCallback(defrCallbackType_e t_type, defiNet* t_net, void* t_userData)
{
    if (t_type != defrNetCbkType) {
        return 2;
    }

    def::Net net {};

    net.name_ = (char*)malloc((strlen(t_net->name()) + 1) * sizeof(char));
    strcpy(net.name_, t_net->name());

    net.instances_ = (char**)malloc(t_net->numConnections() * sizeof(char*));
    net.pins_ = (char**)malloc(t_net->numConnections() * sizeof(char*));

    net._numPins = t_net->numConnections();

    for (std::size_t i = 0; i < t_net->numConnections(); ++i) {
        net.instances_[i] = (char*)malloc((strlen(t_net->instance(i)) + 1) * sizeof(char));
        net.pins_[i] = (char*)malloc((strlen(t_net->pin(i)) + 1) * sizeof(char));

        strcpy(net.instances_[i], t_net->instance(i));
        strcpy(net.pins_[i], t_net->pin(i));
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    defInstance->nets_[defInstance->_numNets++] = net;

    return 0;
}

int DefReader::pinStartCallback(defrCallbackType_e t_type, int t_number, void* t_userData)
{
    if (t_type != defrStartPinsCbkType) {
        return 2;
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    defInstance->pins_ = (def::Pin*)malloc(t_number * sizeof(def::Pin));

    return 0;
}

int DefReader::pinCallback(defrCallbackType_e t_type, defiPin* t_pin, void* t_userData)
{
    if (t_type != defrPinCbkType) {
        return 2;
    }

    def::Pin pin {};

    pin.name_ = (char*)malloc((strlen(t_pin->pinName()) + 1) * sizeof(char));
    strcpy(pin.name_, t_pin->pinName());

    pin.net_ = (char*)malloc((strlen(t_pin->netName()) + 1) * sizeof(char));
    strcpy(pin.net_, t_pin->netName());

    if (t_pin->hasUse()) {
        pin.use_ = (char*)malloc((strlen(t_pin->use()) + 1) * sizeof(char));
        strcpy(pin.use_, t_pin->use());
    }

    if (t_pin->isPlaced()) {
        pin.status_ = (char*)malloc(7 * sizeof(char));
        strcpy(pin.status_, "PLACED");
    } else if (t_pin->isFixed()) {
        pin.status_ = (char*)malloc(6 * sizeof(char));
        strcpy(pin.status_, "FIXED");
    } else if (t_pin->isCover()) {
        pin.status_ = (char*)malloc(6 * sizeof(char));
        strcpy(pin.status_, "COVER");
    } else if (t_pin->isUnplaced()) {
        pin.status_ = (char*)malloc(9 * sizeof(char));
        strcpy(pin.status_, "UNPLACED");
    }

    if (t_pin->hasDirection()) {
        pin.direction_ = (char*)malloc((strlen(t_pin->direction()) + 1) * sizeof(char));
        strcpy(pin.direction_, t_pin->direction());
    }

    pin.x_ = t_pin->placementX();
    pin.y_ = t_pin->placementY();
    pin.orient_ = t_pin->orient();

    if (t_pin->numLayer() != 0) {
        int32_t xl {}, yl {}, xh {}, yh {};
        pin.rects_ = (def::Rect*)malloc(t_pin->numLayer() * sizeof(def::Rect));

        for (std::size_t i = 0; i < t_pin->numLayer(); ++i) {
            t_pin->bounds(i, &xl, &yl, &xh, &yh);

            pin.rects_[pin._numRects++] = def::Rect(xl, yl, xh, yh, t_pin->layer(i));
        }
    }

    if (t_pin->numPorts() != 0) {
        pin.ports_ = (def::Port*)malloc(t_pin->numPorts() * sizeof(def::Port));

        for (std::size_t i = 0; i < t_pin->numPorts(); ++i) {
            defiPinPort* pinPort = t_pin->pinPort(i);
            int32_t xl {}, yl {}, xh {}, yh {};
            def::Port port {};

            port.rects_ = (def::Rect*)malloc(pinPort->numLayer() * sizeof(def::Rect));

            for (std::size_t j = 0; j < pinPort->numLayer(); ++j) {
                pinPort->bounds(j, &xl, &yl, &xh, &yh);

                if (pinPort->isPlaced() || pinPort->isFixed() || pinPort->isCover()) {
                    int32_t xPlacement = pinPort->placementX();
                    int32_t yPlacement = pinPort->placementY();

                    xl += xPlacement;
                    yl += yPlacement;
                    xh += xPlacement;
                    yh += yPlacement;
                }

                port.rects_[port._numRects++] = def::Rect(xl, yl, xh, yh, pinPort->layer(j));
            }

            pin.ports_[pin._numPorts++] = port;
        }
    }

    def::Def* defInstance = static_cast<def::Def*>(t_userData);
    defInstance->pins_[defInstance->_numPins++] = pin;

    return 0;
}

int DefReader::rowCallback(defrCallbackType_e t_type, defiRow* t_row, void* t_userData)
{
    if (t_type != defrRowCbkType) {
        return 2;
    }

    def::Row row {};

    row.name_ = (char*)malloc((strlen(t_row->name()) + 1) * sizeof(char));
    strcpy(row.name_, t_row->name());

    row.macro_ = (char*)malloc((strlen(t_row->macro()) + 1) * sizeof(char));
    strcpy(row.macro_, t_row->macro());

    row.x_ = t_row->x();
    row.y_ = t_row->y();

    row.numX_ = t_row->xNum();
    row.numY_ = t_row->yNum();

    row.stepX_ = t_row->xStep();
    row.stepY_ = t_row->yStep();

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    defInstance->addRow(row);

    return 0;
}

int DefReader::trackCallback(defrCallbackType_e t_type, defiTrack* t_track, void* t_userData)
{
    if (t_type != defrTrackCbkType) {
        return 2;
    }

    def::Track track {};

    if (t_track->numLayers() != 0) {
        track.layer_ = (char*)malloc((strlen(t_track->layer(0)) + 1) * sizeof(char));
        strcpy(track.layer_, t_track->layer(0));
    }

    track.offset_ = t_track->x();
    track.num_ = t_track->xNum();
    track.step_ = t_track->xStep();

    def::Def* defInstance = static_cast<def::Def*>(t_userData);

    if (strcmp(t_track->macro(), "X") == 0) {
        defInstance->addTrack(track, 0);
    } else if (strcmp(t_track->macro(), "Y") == 0) {
        defInstance->addTrack(track, 1);
    }

    return 0;
}