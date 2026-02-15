from typing import List, IO
from array import array, ArrayType
from ..utils import gamma_encode

class BitSet:
    def __init__(self) -> None:
        self.arr: ArrayType = array('I') 
        self.pos_in_chunk: int = 32
        
    def write(self, data_to_add: List[bool]) -> None:
        for b in data_to_add:
            if self.pos_in_chunk == 32:
                self.pos_in_chunk = 0
                self.arr.append(0)

            self.arr[-1] |= (b << self.pos_in_chunk)
            self._chunk_pos += 1
    
    def read(self, len: int, file: IO) -> List[bool]:
        res = []
        for _ in range(len):
            if self.pos_in_chunk == 32:
                self.pos_in_chunk = 0
                self.arr.append(int.from_bytes(file.read(4), byteorder='little'))
            
            res.append((self.arr[-1] >> self.pos_in_chunk) & 1)
            self.pos_in_chunk += 1
            
        return res
    
    def read_length(self, file: IO) -> int: 
        res = 0 
        while True:
            if self.pos_in_chunk == 32:
                self.pos_in_chunk = 0
                self.arr.append(int.from_bytes(file.read(4), byteorder='little'))
            
            bit = (self.arr[-1] >> self.pos_in_chunk) & 1 
            if bit == 0:
                res += 1 
            else:
                break 
            
        return res 

    def read_beta(self, file: IO) -> int: 
        len = self.read_length(file)
        bits = self.read(len, file) 
        return int(''.join(str(bit) for bit in bits), 2) 
    
    def read_gamma(self, file: IO) -> int: 
        len = self.read_length(file) + 1
        bits = self.read(len, file) 
        return int(''.join(str(bit) for bit in bits), 2)
    
    def read_alpha(self, file: IO) -> str:
        res = ""
        len = self.read_length(file) 
        
        for _ in range(len): 
            res += chr(self.read_gamma(file))
        
        return res
    
    def fflush(self, file: IO) -> None:
        for num in self.arr:
            file.write(num.to_bytes(4, byteorder='little'))