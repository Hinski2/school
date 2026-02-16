from typing import List
from ..models import Model
from ..fs import FileWriter, FileEntry
import os

class Encoder:
    def encode(self, file_names: List[str], output_name: str, model_name: str, coding: bool) -> None:
        model = Model(model_name)
        output_file = open(output_name, "wb") 
        file_writer = FileWriter(output_file)
        
        # encode metadata 
        self._encode_file_metadata(file_writer, model, len(file_names), coding)
        
        # get all file nemes recursively 
        all_file_names = [] 
        for file_name in file_names:
            if os.path.isdir(file_name):
                for root, _, files in os.walk(file_name):
                    all_file_names.extend(os.path.join(root, file) for file in files)
            else:
                all_file_names.append(file_name)
        
        # encode file entries 
        for file_name in all_file_names:
            self._encode_file_entry(file_name, file_writer, model)
    
    def _encode_file_metadata(self, file_writer: FileWriter, model: Model, no_of_files: int, coding: bool) -> None:
        file_writer.write_metadata(model.get_name(), coding=coding, no_of_files=no_of_files)
    
    def _encode_file_entry(self, file_name: str, file_writer: FileWriter, model: Model) -> None:
        directory = os.path.isdir(file_name)
        encoded_file_name = Encoder._encode_with_model(file_name, model)
        data = Encoder._encode_with_model(open(file_name, "r").read(), model) if not directory else None
        
        file_entry = FileEntry(directory=directory, file_name=encoded_file_name, data=data)
        file_writer.write_bitset(file_entry)
    
    @staticmethod
    def _encode_with_model(data: str | None, model: Model) -> List[bool]:
        if data is None:
            return []
        
        return model.encode(data)