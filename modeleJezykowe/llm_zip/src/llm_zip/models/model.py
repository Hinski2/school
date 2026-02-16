from typing import List

class Model:
    def __init__(self, name: str):
        pass
    
    def decode(self, bits: List[bool]) -> str:
        pass
    
    def encode(self, data: str) -> List[bool]:
        pass
    
    def get_name(self) -> str:
        pass
        
    @staticmethod
    def get_all_model_names() -> List[str]:
        # all model names are in models/models dir
        models = []
        with open("src/llm_zip/models/models.txt", "r") as f:
            for line in f:
                models.append(line.strip().split(".")[0])
        return models