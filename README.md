# LEFDEF Python

This repository provides a Python interface to parse LEF (Library Exchange Format) and DEF (Design Exchange Format) files.

## Install

You can install library using pip


```bash
pip install lefdef
```

## Usage

To use the LEF reader, you can follow the example provided in the `test.py` file:

```python
from lefdef import C_LefReader
from lefdef import C_DefReader

lef_reader = C_LefReader()
_lef = lef_reader.read("/path/to/lef/file.lef")
_lef.print()

def_reader = C_DefReader()
_def = def_reader.read("/path/to/def/file.def")
_def.print()
```

It will read and print all information that have been read.

## Data structure

- **LEF/DEF Reader**: A Python classes `C_LefReader` and `C_DefReader` that allows reading LEF/DEF files and extracting the design data.
  
- **LEF Data Structures**:  
    - ### **C_Lef** - top level container of lef file
        - `c_macros` - a list of all macros in lef file
        - `c_num_macros` - the number of macros in lef (use this to iterate over `c_macros`)

    - ### **C_Lef_Macro** - container for `MACRO` statement
        - `c_name` - the name of macro
        -  `c_class` - the value of `CLASS` statement
        -  `c_source` - the value of `SOURCE` statement
        -  `c_site_name` - the value of `SITE` statemen
        -  `c_origin_x` - the postion of macro by x axis
        -  `c_origin_y` -the  postion of macro by y axis
        -  `c_size_x` -the  width of macro
        -  `c_size_y` - the height of macro
        -  `c_foreign_name` - the name of foreign
        -  `c_foreign_x` - the foreing's position by x axis
        -  `c_foreign_y` - the foreing's position by y axis
        -  `c_pins` - a list of macro's pins
        -  `c_num_pins` - the number of pins (use this to iterate over `c_pins`)

    - ### **C_Lef_Obstruction** - container for `OBS` statement
        - `c_rects` - the obstruction's geometry
        - `c_num_rects` - the number of rectangles in obstruction (use this to iterate over `c_rects`)
 
    - ### **C_Lef_Pin** - container for `PIN` statement
        - `c_name` - the pin's name
        - `c_direction` - the value of `DIRECTION` statement
        - `c_use` - the value of `USE` statement
        - `c_shape` - the value of `SHAPE` statement
        - `c_ports` - a list pf pin's ports
        - `c_num_ports` - the number of porst in pin (use this to iterate over `c_ports`)
    
    - ### **C_Lef_Port** - container for `PORT` statement
        - `c_rects` - the port's geometry
        - `c_num_rects` - the number of rectangles in port (use this to iterate over `c_rects`)
    
    - ### **C_Lef_Rect** - container for `LAYER` statement
        - `c_layer` - the layer name
        - `c_xl` - the x value of lef top corner
        - `c_yl` - the y value of lef top corner
        - `c_xh` - the x value of right bottom corner
        - `c_yh` - the y value of right bottom corner

LEF Example

```python
from lefdef import C_LefReader

lef_reader = C_LefReader()
lef = lef_reader.read("/path/to/lef/file.lef")

for i in range(lef.c_num_macros):
    class_ = lef.c_macros[i].c_class
    source = lef.c_macros[i].c_source
    site_name = lef.c_macros[i].c_site_name
    origin_x = lef.c_macros[i].c_origin_x
    origin_y = lef.c_macros[i].c_origin_y
    foreign_name = lef.c_macros[i].c_foreign_name
    foreign_x = lef.c_macros[i].c_foreign_x
    foreign_y = lef.c_macros[i].c_foreign_y
    foreign_orient = lef.c_macros[i].c_foreign_orient
    pins = lef.c_macros[i].c_pins
    obs = lef.c_macros[i].c_obs

    # Access pins
    for j in range(lef.c_macros[i].c_num_pins):
        name = pins[j].c_name
        direction = pins[j].c_direction
        use = pins[j].c_use
        shape = pins[j].c_shape
        ports = pins[j].c_ports

        # Access pins's ports
        for k in range(pins[j].c_num_ports):
            rects = ports[k].c_rects

            # Access ports's rectangles
            for l in range(ports[k].c_num_rects):
                layer = rects[l].c_layer
                xl = rects[l].c_xl
                yl = rects[l].c_yl
                xh = rects[l].c_xh
                yh = rects[l].c_yh

    # Access obs's rectangles
    for j in range(obs.c_num_rects):
        layer = obs.rects[j].c_layer
        xl = obs.rects[j].c_xl
        yl = obs.rects[j].c_yl
        xh = obs.rects[j].c_xh
        yh = obs.rects[j].c_yh
```

- **DEF Data Structures**:
    - ### **C_Def** - top level container of def file
        - `c_die_area_width` - a list of x points of die area
        - `c_die_area_height` - a list of y points of die arae
        - `c_num_points` - the number of points of die arae (use this to iterate over `c_die_area_width` and `c_die_area_height`)
        - `c_g_cell_grid_x` - a list of gCellGrid by x axis
        -  `c_num_g_cell_grid_x` - the number of gCellGrid by x axis (use this to iterate over `c_num_g_cell_grid_x`)
        - `c_g_cell_grid_y` - a list of gCellGrid by y axis
        - `c_num_g_cell_grid_y` - the number of gCellGrid by y axis (use this to iterate over `c_num_g_cell_grid_x`)
        - `c_pins` - a list of def's pins
        - `c_num_pins` - the number of pins (use this to iterate over `c_pins`)
        - `c_nets` - a list of def's nets
        - `c_num_nets` - the number of nets (use this to iterate over `c_nets`)
        - `c_rows` - a list of def's rows
        - `c_num_rows` - the number of rows (use this to iterate over `c_rows`)
        - `c_tracks_x` - a list of def's tracks by x axis
        - `c_num_tracks_x` - the number of tracks by x axis (use this to iterate over `c_tracks_x`)
        - `c_tracks_y` - a list of def's tracks by y axis
        - `c_num_tracks_y`- the number of tracks by y axis (use this to iterate over `c_tracks_y`)

    - ### **C_Def_Net** - container for net in `NETS` statement
        - `c_name` - the net's name
        - `c_instances` - a list of names of components in this net
        - `c_pins` - a list of names of pins in this net, list length is equal to `c_instances`'s length
        - `c_num_pins` - the number of pins in this net

    - ### **C_Def_Pin** - container of pin in `PINS` statement
        - `c_name` - the pin name
        - `c_net` - the pin's net name
        - `c_use` - the value of `USE` statement
        - `c_status` - the value of `STATUS` statement
        - `c_direction` - the value of `DIRECTOIN` statement
        - `c_orient` - the pin's orientation
        - `c_rects` - the pin's geometry
        - `c_num_rects` - a number of rectangles (use this to iterate over `c_rects`)
        - `c_ports` - a list of pin's ports
        - `c_num_ports` -  a number of ports (use this to iterate over `c_ports`)
  
    - ### **C_Def_Component** - container of standart cell in `COMPONENTS` statement
      - `c_id` - the component name in the design
      - `c_name` - the name of a model defined in the library
      - `c_status` - the value of `STATUS` statement
      - `c_source` - the value of `SOURCE` statement
      - `c_oirent` - the component's orientation
      - `c_x` - the  location by x axis
      - `c_y` - the  location by y axis
     
    - ### **C_Def_GCellGrid** - container of `GCELLGRID` statement
      - `c_offest` - the location of the first row/column
      - `c_num` - the number of rows/columns
      - `c_step` - the spacing between rows/columns
     
    - ### **C_Def_Track** - container of `TRACK` statement
      - `c_layer` - the routing layer used for the tracks
      - `c_offest` - location  of the first track (column/row)
      - `c_num` - the number of tracks to create for the grid by x or y axis
      - `c_step` - he spacing between the tracks (column/row)

    - ### **C_Def_Row** - container of `ROW` statement
      - `c_name` - the row's name
      - `c_macro` - the value of `SITE` statement
      - `c_x` - the location of the first site in the row by x axsis
      - `c_y` - the location of the first site in the row by y axsis
      - `c_num_x` - a repeating set of sites that create the row by x axsis
      - `c_num_y` - a repeating set of sites that create the row by y axsis
      - `c_step_x` - the spacing between sites in vertical rows
      - `c_step_y` - the spacing between sites in horizontal rows

    - ### **C_Def_Port** - container for `PORT` statement
        - `c_rects` - the port's geometry
        - `c_num_rects` - the number of rectangles in port (use this to iterate over `c_rects`)

    - ### **C_Lef_Rect** - container for `LAYER` statement
        - `c_layer` - the layer name
        - `c_xl` - the x value of lef top corner
        - `c_yl` - the y value of lef top corner
        - `c_xh` - the x value of right bottom corner
        - `c_yh` - the y value of right bottom corner

DEF Example

```python
from lefdef import C_DefReader

def_reader = C_DefReader()
_def = def_reader.read("/path/to/def/file.def")

die_area_width = _def.c_die_area_width
die_area_height = _def.c_die_area_height
g_cell_grid_x = _def.g_cell_grid_x
num_g_cell_grid_x = _def.c_num_g_cell_grid_x
g_cell_grid_y = _def.c_g_cell_grid_y
components = _def.c_components
pins = _def.c_pins
nets = _def.c_nets
rows = _def.c_rows
tracks_x = _def.c_tracks_x
tracks_y = _def.c_tracks_y

# Access gCellGrid by x axis
for i in range(_def.c_num_g_cell_grid_x):
    offset_x = g_cell_grid_x[i]
    num_x = g_cell_grid_x[i]
    step_y = g_cell_grid_x[i]

# Access gCellGrid by y axis
for i in range(_def.c_num_g_cell_grid_y):
    offset_y = g_cell_grid_y[i]
    num_y = g_cell_grid_y[i]
    step_y = g_cell_grid_y[i]

# Access components
for i in range(_def.c_num_components):
    id = components[i].c_id
    name = components[i].c_name
    status = components[i].c_status
    source = components[i].c_source
    orient = components[i].c_orient
    x = components[i].c_x
    y = components[i].c_y

# Access pins
for i in range(_def.c_num_pins):
    name = pins[i].c_name
    net = pins[i].c_net
    use = pins[i].c_use
    status = pins[i].c_status
    direction = pins[i].c_direction
    orient = pins[i].c_orient
    x = pins[i].c_x
    y = pins[i].c_y
    rects = pins[i].c_rects
    ports = pins[i].c_ports

    # Access pin's rectangles
    for j in range(pins[i].c_num_rects):
        layer = rects[j].c_layer
        xl = rects[j].c_xl
        yl = rects[j].c_yl
        xh = rects[j].c_xh
        yh = rects[j].c_yh

    # Access pin's ports
    for j in range(pins[i].c_num_ports):
        rects = ports[j].c_rects

        # Access ports's rectangles
        for k in range(ports[j].c_num_rects):
            layer = rects[k].c_layer
            xl = rects[k].c_xl
            yl = rects[k].c_yl
            xh = rects[k].c_xh
            yh = rects[k].c_yh

# Access nets
for i in range(_def.c_num_nets):
    name = nets[i].c_name

    for j in range(nets[i].c_num_pins):
        isinstance = nets[i].c_isinstance[j]
        pins = nets[i].c_pins[j]

# Access rows
for i in range(_def.c_num_rows):
    name = rows[i].c_name
    macro = rows[i].c_macro
    x = rows[i].c_x
    y = rows[i].c_y
    num_x = rows[i].c_num_x
    num_y = rows[i].c_num_y
    step_x = rows[i].c_step_x
    step_y = rows[i].c_step_y

# Access tracks by x axis
for i in range(_def.c_num_tracks_x):
    layer = tracks_x[i].c_layer
    offset = tracks_x[i].c_offset
    num = tracks_x[i].c_num
    step = tracks_x[i].c_step

# Access tracks by y axis
for i in range(_def.c_num_tracks_y):
    layer = tracks_y[i].c_layer
    offset = tracks_y[i].c_offset
    num = tracks_y[i].c_num
    step = tracks_y[i].c_step

```

## Contributing

We welcome contributions from the community! Whether it's a bug report, new feature, or a correction, your help is greatly appreciated. Here's how you can contribute:

1. **Fork the Repository**: Start by forking the [lefdef-python repository](https://github.com/ruykaji/lefdef-python).

2. **Clone Your Fork**:
   ```bash
   git clone https://github.com/YOUR_USERNAME/lefdef-python.git
   cd lefdef-python
   ```

3. **Create a New Branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

4. **Make Your Changes**: Implement your changes, enhancements, or bug fixes.

5. **Commit and Push**:
   ```bash
   git add .
   git commit -m "Your detailed commit message"
   git push origin feature/your-feature-name
   ```

6. **Open a Pull Request**: Go to the [lefdef-python repository](https://github.com/ruykaji/lefdef-python) on GitHub and click on the "New Pull Request" button. Select your fork and the branch you created to submit a pull request.

7. **Wait for Review**: Once your pull request is submitted, maintainers will review your changes. Address any feedback to get your changes merged.

### Reporting Bugs

If you find a bug or an issue, please create a new issue in the [issue tracker](https://github.com/ruykaji/lefdef-python/issues) describing the problem and providing steps to reproduce it.
