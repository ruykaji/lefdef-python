__all__ = ["readLef"]

import ctypes
import os
from .lef import C_Lef

class C_LefReader(ctypes.Structure):
        pass

def readLef(file_name) -> C_Lef:
    lefdef = ctypes.CDLL(os.path.join(os.path.dirname(__file__), "lib/liblefdef.so"))

    lefdef.createLefReader.restype = ctypes.POINTER(C_LefReader)
    lefdef.createLefReader.argtypes = []

    lefdef.deleteLefReader.restype = None
    lefdef.deleteLefReader.argtypes = [ctypes.POINTER(C_LefReader)]

    lefdef.read.restype = ctypes.POINTER(C_Lef)
    lefdef.read.argtypes = [ctypes.POINTER(C_LefReader), ctypes.c_char_p]

    reader = lefdef.createLefReader()
    result = lefdef.read(reader, file_name.encode("utf-8"))

    lefdef.deleteLefReader(reader)

    return result.contents