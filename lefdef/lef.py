__all__ = ["C_Lef"]

import ctypes
from typing import ByteString

class C_Lef(ctypes.Structure): 
    # Fields description
    _fields_ = [("name", ctypes.c_char_p)]

    # Python interface
    def __init__(self) -> None:
        super().__init__()

        # Macro name
        self.name : ByteString = None