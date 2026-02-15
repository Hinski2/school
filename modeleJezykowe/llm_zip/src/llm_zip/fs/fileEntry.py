from dataclasses import dataclass
from typing import List

@dataclass
class FileEntry:
    directory: bool
    file_name: List[bool]
    data: List[bool] | None