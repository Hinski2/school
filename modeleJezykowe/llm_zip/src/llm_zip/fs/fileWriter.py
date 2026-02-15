from typing import List, IO
from .bitSet import BitSet
from .fileEntry import FileEntry
from ..utils import gamma_encode, beta_encode, alpha_encode

class FileWriter:
    def __init__(self, file: IO):
        self.file = file
    
    def write_bitset(self, file_entry: FileEntry) -> None:
        bit_set = BitSet() 
        
        if file_entry.directory:
            bit_set.write([True])
            bit_set.write(gamma_encode(len(file_entry.file_name)))
            bit_set.write(file_entry.file_name)
            
        else:
            if file_entry.data is None:
                raise ValueError("Data cannot be None for a file entry.")
              
            bit_set.write([False]) 
            bit_set.write(gamma_encode(len(file_entry.file_name)))
            bit_set.write(beta_encode(len(file_entry.data)))
            bit_set.write(file_entry.file_name)
            bit_set.write(file_entry.data)
            
        bit_set.fflush(self.file)
        
    def write_metadata(self, model_name: str, coding: bool, no_of_files: int) -> None:
        bit_set = BitSet()
       
        bit_set.write(alpha_encode(model_name))
        bit_set.write([coding])
        bit_set.write(beta_encode(no_of_files))
        
        bit_set.fflush(self.file)
        