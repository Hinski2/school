from .coders import Encoder, Decoder
from .models import Model
from .utils import FileReader
from typing import List, Tuple


class LLMZip:
    def encode(self, coding_name: str, model_name: str, file_names: List[str], output_name: str, recursive: bool) -> None:
        LLMZip._validate(model_name, coding_name)
        
        encoder = Encoder()
        encoder.encode(file_names, output_name, recursive)
        
    def decode(self, file_name: str, output_name: str) -> None:
        file_reader = FileReader(file_name)

        decoder = Decoder()
        decoder.decode(file_name, output_name)
    
    @staticmethod
    def _validate(model: str, coding: str) -> None:
        if not model in ["0"]: 
            raise Exception(f"Error: unknown model: {model}")
        
        if not coding in ["gamma"]:
            raise Exception(f"Error: unknown coding: {coding}")
        