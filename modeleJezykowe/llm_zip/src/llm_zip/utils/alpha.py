from typing import List
from .beta import beta_encode
from .gamma import gamma_encode

def alpha_encode(s: str) -> List[bool]:
    bits = beta_encode(len(s))
    for c in s:
        bits += gamma_encode(ord(c))
    return bits