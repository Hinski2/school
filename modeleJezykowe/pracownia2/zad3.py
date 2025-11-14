from transformers import AutoTokenizer, AutoModelForCausalLM
from typing import List, Tuple
import torch
import numpy as np
from torch.nn import functional as F
import random
from tqdm import tqdm

PAPUGA = 'flax-community/papuGaPT2'
DEVICE = "cuda"
NO_SEARCHES = 45
ATTEMPTS_BEFORE_GIVING_UP = 50

tokenizer = AutoTokenizer.from_pretrained(PAPUGA)
model = AutoModelForCausalLM.from_pretrained(PAPUGA).to(DEVICE)

class Explorer: 
    def __init__(self, data: List[List[str]]):
        self.data: List[List[str]] = data
        self.sentence: List[str] = [random.choice(options) for options in data]
        
    def search_for_local_peak(self) -> Tuple[float, str]:
        attempts: int = ATTEMPTS_BEFORE_GIVING_UP
        while attempts > 0:
            if self.try_climb(): 
                attempts = ATTEMPTS_BEFORE_GIVING_UP
            else:
                attempts -= 1 
        
        return Explorer.compute_sentence_prob(self.sentence), " ".join(self.sentence)
         
    
    def try_climb(self) -> bool: # 1 climbed, 0 no
        old_score: float = Explorer.compute_sentence_prob(self.sentence)
        
        option_idx = random.randint(0, len(self.data) - 1)
        old_word = self.sentence[option_idx]
        new_word = random.choice(self.data[option_idx])
        
        self.sentence[option_idx] = new_word
        new_score: float = Explorer.compute_sentence_prob(self.sentence) 
        
        if new_score > old_score:
            return True
        else:
            self.sentence[option_idx] = old_word
            return False
    
    @staticmethod
    def compute_sentence_prob(sentence: List[str]) -> float:
        def _log_probs_from_logits(logits, labels):
            logp = F.log_softmax(logits, dim=-1)
            logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
            return logp_label
        
        def _sentence_prob(text: str):
            input_ids = tokenizer(text, return_tensors='pt')['input_ids'].to(DEVICE)
            with torch.no_grad():
                output = model(input_ids=input_ids)
                log_probs = _log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
                
            return float(log_probs.sum().item())
        
        return _sentence_prob(" ".join(sentence))

if __name__ == "__main__":
    with open('zad3.in', 'r') as inpF:
        inp: List[List[str]] = [list(options.split('|')) for options in inpF.readline().split()]
        
    results: List[Tuple[float, str]] = []

    for _ in tqdm(range(NO_SEARCHES)):
        explorer = Explorer(inp)
        results.append(explorer.search_for_local_peak())
        
    print(*sorted(results, reverse=True), sep='\n')
    
    with open('zad3.out', 'w') as out:
        for result in sorted(results, reverse=True):
            out.write(f"{result}\n")