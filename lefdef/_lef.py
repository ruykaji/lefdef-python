__all__ = ["C_Lef"]

import ctypes
from typing import ByteString, List


class C_Lef_Rect(ctypes.Structure):
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


class C_Lef_Port(ctypes.Structure):
    _fields_ = [("c_rects", ctypes.POINTER(C_Lef_Rect)),
                ("c_num_rects", ctypes.c_int)
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_rects: List[C_Lef_Rect] | None = None
        self.c_num_rects: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[PORT]\033[0m")
        print(
            f"\033[92m{' ' *start}---| \033[93mnum rects: \033[94m", self.c_num_rects)

        for i in range(self.c_num_rects):
            self.c_rects[i].print(3 + start)


class C_Lef_Pin(ctypes.Structure):
    _fields_ = [("c_name", ctypes.c_char_p),
                ("c_direction", ctypes.c_char_p),
                ("c_use", ctypes.c_char_p),
                ("c_shape", ctypes.c_char_p),
                ("c_ports", ctypes.POINTER(C_Lef_Port)),
                ("c_num_ports", ctypes.c_int)
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_name: ByteString | None = None
        self.c_direction: ByteString | None = None
        self.c_use: ByteString | None = None
        self.c_shape: ByteString | None = None
        self.c_ports: List[C_Lef_Port] | None = None
        self.c_num_ports: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' * (start - 3)}[PIN]\033[0m")
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mname: \033[94m", self.c_name)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mdirection: \033[94m", self.c_direction)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93muse: \033[94m", self.c_use)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mshape: \033[94m", self.c_shape)
        print(
            f"\033[92m{' ' * (start - 3)}---| \033[93mnum ports: \033[94m", self.c_num_ports)

        for i in range(self.c_num_ports):
            self.c_ports[i].print(3 + start)


class C_Lef_Obstruction(ctypes.Structure):
    _fields_ = [("c_rects", ctypes.POINTER(C_Lef_Rect)),
                ("c_num_rects", ctypes.c_int)
                ]

    def __init__(self) -> None:
        super().__init__()

        self.c_rects: List[C_Lef_Rect] | None = None
        self.c_num_rects: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[OBS]\033[0m")
        print(
            f"\033[92m{' ' *start}---| \033[93mnum rects: \033[94m", self.c_num_rects)

        for i in range(self.c_num_rects):
            self.c_rects[i].print(3 + start)


class C_Lef_Macro(ctypes.Structure):
    # Fields description
    _fields_ = [("c_name", ctypes.c_char_p),
                ("c_class", ctypes.c_char_p),
                ("c_source", ctypes.c_char_p),
                ("c_site_name", ctypes.c_char_p),
                ("c_origin_x", ctypes.c_double),
                ("c_origin_y", ctypes.c_double),
                ("c_size_x", ctypes.c_double),
                ("c_size_y", ctypes.c_double),
                ("c_foreign_name", ctypes.c_char_p),
                ("c_foreign_x", ctypes.c_double),
                ("c_foreign_y", ctypes.c_double),
                ("c_foreign_orient", ctypes.c_int),
                ("c_pins", ctypes.POINTER(C_Lef_Pin)),
                ("c_obs", C_Lef_Obstruction),
                ("c_num_pins", ctypes.c_int),
                ]

    # Python interface
    def __init__(self) -> None:
        super().__init__()

        self.c_name: ByteString | None = None
        self.c_class: ByteString | None = None
        self.c_source: ByteString | None = None
        self.c_site_name: ByteString | None = None
        self.c_origin_x: float = 0.0
        self.c_origin_y: float = 0.0
        self.c_size_x: float = 0.0
        self.c_size_y: float = 0.0
        self.c_foreign_name: ByteString | None = None
        self.c_foreign_x: float = 0.0
        self.c_foreign_y: float = 0.0
        self.c_foreign_orient: int = 0
        self.c_pins: List[C_Lef_Pin] | None = None
        self.c_obs: C_Lef_Obstruction | None = None
        self.c_num_pins: int = 0

    def print(self, start: int = 0):
        print(f"\033[95m{' ' *(start - 3)}[MACRO]\033[0m")
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mname: \033[94m", self.c_name)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mclass: \033[94m", self.c_class)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93msource: \033[94m", self.c_source)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93msite name: \033[94m", self.c_site_name)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93morigin x: \033[94m", self.c_origin_x)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93morigin y: \033[94m", self.c_origin_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93msize x: \033[94m", self.c_size_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93msize y: \033[94m", self.c_size_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mforeign name: \033[94m", self.c_foreign_name)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mforeign x: \033[94m", self.c_foreign_x)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mforeign y: \033[94m", self.c_foreign_y)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mforeign orient: \033[94m", self.c_foreign_orient)
        print(
            f"\033[92m{' ' *(start - 3)}---| \033[93mnum pins: \033[94m", self.c_num_pins)

        for i in range(self.c_num_pins):
            self.c_pins[i].print(3 + start)

        self.c_obs.print(3 + start)


class C_Lef(ctypes.Structure):
    # Fields description
    _fields_ = [("c_macros", ctypes.POINTER(C_Lef_Macro)),
                ("c_num_macros", ctypes.c_int)
                ]

    # Python interface
    def __init__(self) -> None:
        super().__init__()

        self.c_macros: List[C_Lef_Macro] | None = None
        self.c_num_macros: int = 0

    def print(self):
        print("\033[95m[LEF]\033[0m")
        print("\033[92m---| \033[93mnum macros: \033[94m", self.c_num_macros)

        for i in range(self.c_num_macros):
            self.c_macros[i].print(6)
