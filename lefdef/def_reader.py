__all__ = ["C_DefReader"]

import ctypes
import os
import platform
from ._def import C_Def


class C_DefReaderInstance(ctypes.Structure):
    pass


class C_DefReader():
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
        self.lefdef.createDefReader.restype = ctypes.POINTER(
            C_DefReaderInstance)
        self.lefdef.createDefReader.argtypes = []

        # Add delete reader function
        self.lefdef.deleteDefReader.restype = None
        self.lefdef.deleteDefReader.argtypes = [
            ctypes.POINTER(C_DefReaderInstance)]

        # Add delete lef function
        self.lefdef.deleteDef.restype = None
        self.lefdef.deleteDef.argtypes = [ctypes.POINTER(C_Def)]

        # Add read reader function
        self.lefdef.readDef.restype = ctypes.POINTER(C_Def)
        self.lefdef.readDef.argtypes = [
            ctypes.POINTER(C_DefReaderInstance), ctypes.c_char_p]

        # Create reader instance as pointer
        self.reader = self.lefdef.createDefReader()

    def read(self, file_name: str) -> C_Def:
        if (os.path.exists(file_name)):
            result = self.lefdef.readDef(
                self.reader, file_name.encode("utf-8"))

            self.sessions.append(result)

            return result.contents
        else:
            raise RuntimeError("Can't open file: " + file_name)

    def __del__(self):
        for _def in self.sessions:
            self.lefdef.deleteDef(_def)

        self.lefdef.deleteDefReader(self.reader)
