__all__ = ["C_LefReader"]

import ctypes
import os
import platform
from ._lef import C_Lef


class C_LefReaderInstance(ctypes.Structure):
    pass


class C_LefReader():
    def __init__(self) -> None:
        # Store all open pointers of lef files
        self.sessions = []

        # Open library
        if (platform.system() == "Windows"):
            self.lefdef = ctypes.CDLL(os.path.join(
                os.path.dirname(__file__), "lib/lefdef.dll"), winmode=0)

        # Open library
        if (platform.system() == "Linux"):
            self.lefdef = ctypes.CDLL(os.path.join(
                os.path.dirname(__file__), "lib/liblefdef.so"))

        # Add create reader function
        self.lefdef.createLefReader.restype = ctypes.POINTER(
            C_LefReaderInstance)
        self.lefdef.createLefReader.argtypes = []

        # Add delete reader function
        self.lefdef.deleteLefReader.restype = None
        self.lefdef.deleteLefReader.argtypes = [
            ctypes.POINTER(C_LefReaderInstance)]

        # Add delete lef function
        self.lefdef.deleteLef.restype = None
        self.lefdef.deleteLef.argtypes = [ctypes.POINTER(C_Lef)]

        # Add read reader function
        self.lefdef.readLef.restype = ctypes.POINTER(C_Lef)
        self.lefdef.readLef.argtypes = [
            ctypes.POINTER(C_LefReaderInstance), ctypes.c_char_p]

        # Create reader instance as pointer
        self.reader = self.lefdef.createLefReader()

    def read(self, file_name: str) -> C_Lef:
        if(os.path.exists(file_name)):
            result = self.lefdef.readLef(self.reader, file_name.encode("utf-8"))

            self.sessions.append(result)

            return result.contents

        else:
            raise RuntimeError("Can't open file: " + file_name)
        
    def __del__(self):
        for _lef in self.sessions:
            self.lefdef.deleteLef(_lef)

        self.lefdef.deleteLefReader(self.reader)
