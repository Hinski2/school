from typing import List
from array import array, ArrayType
from ..utils import gamma_encode

class BitSet:
    """
        file:
            [0]
            [len of file name in gamma coding] 
            [len of data in gamma coding]
            [file_name]
            [data]
            
        directory:
            [1]
            [len of file name in gamma coding] 
            [file_name]
            
        in gamma conding we cant encode 0 => we have to add to every file 0 at the beggining of the data
    """
    
    def __init__(self, file_name: List[bool], data: List[bool], directory: bool) -> None:
        assert len(file_name) > 0, "Error: every file must have a name"
        
        self.data: ArrayType = array('I')
        self.directory = directory
        self._chunk_pos = 32
        
        if directory:
            self.add([True])
            self.add(gamma_encode(len(file_name)))
            self.add(file_name)
            
        else:
            self.add([False]) 
            self.add(gamma_encode(len(file_name)))
            self.add(gamma_encode(len(data)))
            self.add(file_name)
            
            data.insert(0, False) # read desc  
            self.add(data)
        
    def add(self, data_to_add: List[bool]) -> None:
        for b in data_to_add:
            if self._chunk_pos == 32:
                self._chunk_pos = 0
                self.data.append(0)

            self.data[-1] |= (b << self._chunk_pos)
            self._chunk_pos += 1
   