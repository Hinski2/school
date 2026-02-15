"""
    file:
        [model_name in beta coding]
        [0 if we use gamma coding, 1 if we use huffman coding]
        [no of files]
        [table of file names]
        (BitSet)
        (BitSet)
        ...
        (BitSet)
"""

"""
    bitset:
        file:
            [0]
            [len of file name in beta coding] 
            [len of data in beta coding]
            [file_name]
            [data]
            
        directory:
            [1]
            [len of file name in beta coding] 
            [file_name]
"""

class FileReader:
    def __init__(self, file_name: str):
        self.file_name = file_name
        
        with open(file_name, "br") as file:
            self.file = file.read()
        
        self._load_model_name()
        self._load_coding()
        self._load_no_of_files()
        self._load_forest_of_files()
        self._load_bitsets()
        
    def _load_model_name(self) -> None:
        pass 
     
    def _load_coding(self) -> None:
        pass 
    
    def _load_no_of_files(self) -> None:
        pass 
    
    def _load_forest_of_files(self) -> None:
        pass 
    
    def _load_bitsets(self) -> None: 
        pass