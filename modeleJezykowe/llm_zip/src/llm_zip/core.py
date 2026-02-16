from .coders import Encoder, Decoder
from .models import Model
from typing import List


class LLMZip:
    def encode(self, coding: bool, model_name: str, file_names: List[str], output_name: str) -> None:
        LLMZip._validate(model_name)
        encoder = Encoder()
        encoder.encode(file_names, output_name, model_name, coding=coding)
        
    def decode(self, file_name: str, output_name: str) -> None:
        decoder = Decoder()
        decoder.decode(file_name, output_name)
    
    @staticmethod
    def _validate(model: str) -> None:
        models = Model.get_all_model_names()
        
        if not model in models: 
            raise Exception(f"Error: unknown model: {model}")