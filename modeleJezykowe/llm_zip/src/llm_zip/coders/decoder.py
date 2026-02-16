from ..models import Model
from ..fs import FileEntry, FileReader
from typing import Tuple, List

# TODO handle condign int the future
class Decoder:
    def decode(self, file_name: str, output_name: str) -> None:
        file = open(file_name, "rb")
        file_reader = FileReader(file)
        
        model_name, coding, no_files = self._decode_file_metadata(file_reader)
        model = Model(model_name) 
        
        file_entries = self._get_file_entries(file_reader, no_files)
        for file_entry in file_entries:
            decoded_file_name, decoded_data = self._decode_with_model(file_entry.file_name, model), self._decode_with_model(file_entry.data, model)
            
            with open(f"{output_name}/{decoded_file_name}", "w") as f:
                if decoded_data is not None:
                    f.write(decoded_data)
    
    def _decode_file_metadata(self, file_reader: FileReader) -> Tuple[str, bool, int]:
        return file_reader.read_metadata()
    
    def _get_file_entries(self, file_reader: FileReader, no_files) -> List[FileEntry]:
        return [file_reader.read_bitset() for _ in range(no_files)]
    
    @staticmethod 
    def _decode_with_model(data: List[bool] | None, model: Model) -> str | None:
        if data is None:
            return None
        
        return model.decode(data)