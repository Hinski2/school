from .bitSet import BitSet
from typing import List, IO, Tuple
from .fileEntry import FileEntry

class FileReader:
    def __init__(self, file: IO):
        self.file = file 
        
    def read_bitset(self) -> FileEntry:
        bit_set = BitSet()
        file_entry = FileEntry(directory=False, file_name=[], data=None)
        
        file_entry.directory = bit_set.read(1, self.file)[0]
        if file_entry.directory: 
            file_name_len: int = bit_set.read_gamma(self.file)
            file_entry.file_name = bit_set.read(file_name_len, self.file)
        else:
            file_name_len: int = bit_set.read_gamma(self.file)
            data_len: int = bit_set.read_beta(self.file)
            
            file_entry.file_name = bit_set.read(file_name_len, self.file)
            file_entry.data = bit_set.read(data_len, self.file)
        
        return file_entry 
    
    def read_metadata(self) -> Tuple[str, bool, int]:
        bit_set = BitSet()
        
        model_name = bit_set.read_alpha(self.file)
        coding = bit_set.read(1, self.file)[0]
        no_of_files = bit_set.read_beta(self.file)
        
        return model_name, coding, no_of_files 