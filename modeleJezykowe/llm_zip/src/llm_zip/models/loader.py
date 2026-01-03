from datasets import IterableDataset, load_dataset

class Loader:
    def __init__(self, ds_name: str) -> None:
        """
            name:
                wikipedia-pl
                wikipedia-en
                _ -> error
        """
        
        self.ds_name = ds_name
        
    def get_IterableDataset(self) -> IterableDataset:
        if self.ds_name == "wikipedia-pl":
            return load_dataset("wikimedia/wikipedia", "20231101.pl", split="train", streaming=True)
        if self.ds_name == "wikipedia-en":
            return load_dataset("wikimedia/wikipedia", "20231101.en", split="train", streaming=True)
        
        raise Exception("innapropriate ds_name")