__all__ = ["C_Def"]

import ctypes
from typing import ByteString, List


class C_Def_Rect(ctypes.Structure):
    _fields_ = [("c_layer", ctypes.c_char_p),
                ("c_xl", ctypes.c_double),
                ("c_yl", ctypes.c_double),
                ("c_xh", ctypes.c_double),
                ("c_yh", ctypes.c_double),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_layer: ByteString | None = None
        self.c_xl: float = 0.0
        self.c_xh: float = 0.0
        self.c_yl: float = 0.0
        self.c_yh: float = 0.0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[RECT]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mlayer: \033[94m", self.c_layer)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mxl: \033[94m", self.c_xl)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93myl: \033[94m", self.c_yl)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mxh: \033[94m", self.c_xh)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93myh: \033[94m", self.c_yh)


class C_Def_Port(ctypes.Structure):
    _fields_ = [("c_rects", ctypes.POINTER(C_Def_Rect)),
                ("c_num_rects", ctypes.c_int)
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_rects: List[C_Def_Rect] | None = None
        self.c_num_rects: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[PORT]\033[0m")
        print(
            f"\033[92m{' ' *start}---| \033[93mnum rects: \033[94m", self.c_num_rects)

        for i in range(self.c_num_rects):
            self.c_rects[i].print(3 + start)


class C_Def_Row(ctypes.Structure):
    _fields_ = [("c_name", ctypes.c_char_p),
                ("c_macro", ctypes.c_char_p),
                ("c_x", ctypes.c_double),
                ("c_y", ctypes.c_double),
                ("c_num_x", ctypes.c_double),
                ("c_num_y", ctypes.c_double),
                ("c_step_x", ctypes.c_double),
                ("c_step_y", ctypes.c_double),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_name: ByteString | None = None
        self.c_macro: ByteString | None = None
        self.c_x: float = 0.0
        self.c_y: float = 0.0
        self.c_num_x: float = 0.0
        self.c_num_y: float = 0.0
        self.c_step_x: float = 0.0
        self.c_step_y: float = 0.0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[ROW]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mrow: \033[94m", self.c_name)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mmacro: \033[94m", self.c_macro)
        print(f"\033[92m{' ' *(start - 3)}---| \033[93mx: \033[94m", self.c_x)
        print(f"\033[92m{' ' *(start - 3)}---| \033[93my: \033[94m", self.c_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum_x: \033[94m", self.c_num_x)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum_y: \033[94m", self.c_num_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mstep_x: \033[94m", self.c_step_x)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mstep_y: \033[94m", self.c_step_y)


class C_Def_Track(ctypes.Structure):
    _fields_ = [("c_layer", ctypes.c_char_p),
                ("c_offset", ctypes.c_double),
                ("c_num", ctypes.c_double),
                ("c_step", ctypes.c_double),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_layer: ByteString | None = None
        self.c_offset: float = 0.0
        self.c_num: float = 0.0
        self.c_step: float = 0.0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[TRACK]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mlayer: \033[94m", self.c_layer)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93moffset: \033[94m", self.c_offset)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum: \033[94m", self.c_num)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mstep: \033[94m", self.c_step)


class C_Def_GCellGrid(ctypes.Structure):
    _fields_ = [("c_offset", ctypes.c_int),
                ("c_num", ctypes.c_int),
                ("c_step", ctypes.c_double),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_offset: float = 0.0
        self.c_num: float = 0.0
        self.c_step: float = 0.0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[GCELLGRID]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93moffset: \033[94m", self.c_offset)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum: \033[94m", self.c_num)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mstep: \033[94m", self.c_step)


class C_Def_Component(ctypes.Structure):
    _fields_ = [("c_id", ctypes.c_char_p),
                ("c_name", ctypes.c_char_p),
                ("c_status", ctypes.c_char_p),
                ("c_source", ctypes.c_char_p),
                ("c_orient", ctypes.c_int),
                ("c_x", ctypes.c_int),
                ("c_y", ctypes.c_int),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_id: ByteString | None = None
        self.c_name: ByteString | None = None
        self.c_status: ByteString | None = None
        self.c_source: ByteString | None = None
        self.c_orient: float = 0.0
        self.c_x: float = 0.0
        self.c_y: float = 0.0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[COMPONENT]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mid: \033[94m", self.c_id)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum: \033[94m", self.c_name)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mstatus: \033[94m", self.c_status)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93msource: \033[94m", self.c_source)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93morient: \033[94m", self.c_orient)
        print(f"\033[92m{' ' *(start - 3)}---| \033[93mx: \033[94m", self.c_x)
        print(f"\033[92m{' ' *(start - 3)}---| \033[93my: \033[94m", self.c_y)


class C_Def_Pin(ctypes.Structure):
    _fields_ = [("c_name", ctypes.c_char_p),
                ("c_net", ctypes.c_char_p),
                ("c_use", ctypes.c_char_p),
                ("c_status", ctypes.c_char_p),
                ("c_direction", ctypes.c_char_p),
                ("c_orient", ctypes.c_int),
                ("c_x", ctypes.c_int),
                ("c_y", ctypes.c_int),
                ("c_rects", ctypes.POINTER(C_Def_Rect)),
                ("c_num_rects", ctypes.c_int),
                ("c_ports", ctypes.POINTER(C_Def_Port)),
                ("c_num_ports", ctypes.c_int),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_name: ByteString | None = None
        self.c_net: ByteString | None = None
        self.c_use: ByteString | None = None
        self.c_status: ByteString | None = None
        self.c_direction: ByteString | None = None
        self.c_orient: int = 0
        self.c_x: int = 0
        self.c_y: int = 0
        self.c_rects: List[C_Def_Rect] | None = None
        self.c_num_rects: int = 0
        self.c_ports: List[C_Def_Port] | None = None
        self.c_num_ports: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' * (start - 3)}[PIN]\033[0m")
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mname: \033[94m", self.c_name)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mnet: \033[94m", self.c_net)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93muse: \033[94m", self.c_use)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mstatus: \033[94m", self.c_status)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mdirection: \033[94m", self.c_direction)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93morient: \033[94m", self.c_orient)
        print(f"\033[92m{' ' * (start - 3)}---| \033[93mx: \033[94m", self.c_x)
        print(f"\033[92m{' ' * (start - 3)}---| \033[93my: \033[94m", self.c_y)

        for i in range(self.c_num_rects):
            self.c_rects[i].print(3 + start)

        for i in range(self.c_num_ports):
            self.c_ports[i].print(3 + start)


class C_Def_Net(ctypes.Structure):
    _fields_ = [("c_name", ctypes.c_char_p),
                ("c_instances", ctypes.POINTER(ctypes.c_char_p)),
                ("c_pins", ctypes.POINTER(ctypes.c_char_p)),
                ("c_num_pins", ctypes.c_int),
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_name: ByteString | None = None
        self.c_instances: List[ByteString] | None = None
        self.c_pins: List[ByteString] | None = None
        self.c_num_pins: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[NET]\033[0m")
        print(
            f"\033[92m{' ' *start}---| \033[93mnum pins: \033[94m", self.c_num_pins)

        for i in range(self.c_num_pins):
            print(f"({self.c_instances[i]} + {self.c_pins[i]})")


class C_Def(ctypes.Structure):
    # Fields description
    _fields_ = [("c_die_area_width", ctypes.POINTER(ctypes.c_int)),
                ("c_die_area_height", ctypes.POINTER(ctypes.c_int)),
                ("c_num_points", ctypes.c_int),

                ("c_g_cell_grid_x", ctypes.POINTER(C_Def_GCellGrid)),
                ("c_num_g_cell_grid_x", ctypes.c_int),

                ("c_g_cell_grid_y", ctypes.POINTER(C_Def_GCellGrid)),
                ("c_num_g_cell_grid_y", ctypes.c_int),

                ("c_components", ctypes.POINTER(C_Def_Component)),
                ("c_num_components", ctypes.c_int),

                ("c_pins", ctypes.POINTER(C_Def_Pin)),
                ("c_num_pins", ctypes.c_int),

                ("c_nets", ctypes.POINTER(C_Def_Net)),
                ("c_num_nets", ctypes.c_int),

                ("c_rows", ctypes.POINTER(C_Def_Row)),
                ("c_num_rows", ctypes.c_int),

                ("c_tracks_x", ctypes.POINTER(C_Def_Track)),
                ("c_num_tracks_x", ctypes.c_int),

                ("c_tracks_y", ctypes.POINTER(C_Def_Track)),
                ("c_num_tracks_y", ctypes.c_int),
                ]

    # Python interface
    def __init__(self) -> None:
        super().__init__()

        self.c_die_area_width: List[int] | None = None,
        self.c_die_area_height: List[int] | None = None,
        self.c_num_points: int = 0,
        self.c_g_cell_grid_x: List[C_Def_GCellGrid] | None = None,
        self.c_num_g_cell_grid_x: int = 0
        self.c_g_cell_grid_y: List[C_Def_GCellGrid] | None = None,
        self.c_num_g_cell_grid_y: int = 0
        self.c_pins: List[C_Def_Pin] | None = None
        self.c_num_pins: int = 0,
        self.c_nets: List[C_Def_Net] | None = None
        self.c_num_nets: int = 0,
        self.c_rows: List[C_Def_Row] | None = None
        self.c_num_rows: int = 0,
        self.c_tracks_x: List[C_Def_Track] | None = None
        self.c_num_tracks_x: int = 0,
        self.c_tracks_y: List[C_Def_Track] | None = None
        self.c_num_tracks_y: int = 0,

    def print(self):
        print("\033[95m[LEF]\033[0m")
        print("\033[92m---| \033[93m:num points \033[94m", self.c_num_points)
        print("\033[92m---| \033[93m:points: \033[94m",
              [f"({self.c_die_area_width[i]}, {self.c_die_area_height[i]})" for i in range(self.c_num_points)])
        print("\033[92m---| \033[93m:num g cell_grid x \033[94m",
              self.c_num_g_cell_grid_x)
        print("\033[92m---| \033[93m:num g cell grid y \033[94m",
              self.c_num_g_cell_grid_y)
        print("\033[92m---| \033[93m:num components \033[94m",
              self.c_num_components)
        print("\033[92m---| \033[93m:num pins \033[94m", self.c_num_pins)
        print("\033[92m---| \033[93m:num nets \033[94m", self.c_num_nets)
        print("\033[92m---| \033[93m:num rows \033[94m", self.c_num_rows)
        print("\033[92m---| \033[93m:num tracks x \033[94m",
              self.c_num_tracks_x)
        print("\033[92m---| \033[93m:num tracks y \033[94m",
              self.c_num_tracks_y)

        for i in range(self.c_num_g_cell_grid_x):
            self.c_g_cell_grid_x[i].print(6)

        for i in range(self.c_num_g_cell_grid_y):
            self.c_g_cell_grid_y[i].print(6)

        for i in range(self.c_num_components):
            self.c_components[i].print(6)

        for i in range(self.c_num_pins):
            self.c_pins[i].print(6)

        for i in range(self.c_num_nets):
            self.c_nets[i].print(6)

        for i in range(self.c_num_rows):
            self.c_rows[i].print(6)

        for i in range(self.c_num_tracks_x):
            self.c_tracks_x[i].print(6)

        for i in range(self.c_num_tracks_y):
            self.c_tracks_y[i].print(6)
