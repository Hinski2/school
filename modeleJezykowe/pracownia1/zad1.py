from transformers import AutoTokenizer, AutoModelForCausalLM
from typing import List, Tuple
import torch
from torch.nn import functional as F

# PAPUGA = 'flax-community/papuGaPT2'
# PAPUGA = 'radlab/polish-gpt2-large-v2A
PAPUGA = 'sdadas/polish-roberta-large-v2'
DEVICE = "cuda"

tokenizer = AutoTokenizer.from_pretrained(PAPUGA)
model = AutoModelForCausalLM.from_pretrained(PAPUGA).to(DEVICE)
model.device


class Chat:
    def __init__(self) -> None:
        self.chat_history: List[Tuple[str, str]] = []
        self.persona: str = "Sprzedawca w sklepie wspinaczkowym odpowiada na pytania klienta i mu pomaga"
        
    def build_prompt(self) -> str:
        history = self.chat_history[-8:]
        conversation = [f"System mówi: {self.persona}"]
        for role, text in history:
            conversation.append(f"{role}: {text}")
        conversation.append(f"Sprzedawca odpowiada:")
        return "\n".join(conversation)
        
    def generate_candidates(self, prompt: str, num: int = 100, max_new_tokens: int = 40) -> List[str]:
        # print(f"\n{prompt}\n")
        input_ids = tokenizer(prompt, return_tensors="pt").to(DEVICE)
        
        out = model.generate(
            **input_ids,
            no_repeat_ngram_size=3,
            max_new_tokens=max_new_tokens,
            do_sample=True,
            num_return_sequences=num,
            eos_token_id=tokenizer.eos_token_id,
            pad_token_id=tokenizer.eos_token_id,
        )
        
        texts: List[str] = []
        for seq in out:
            full = tokenizer.decode(seq, skip_special_tokens=True)
            new = full[len(prompt):]
            texts.append(new.strip())
            
        return self.handle_text(texts)
    
    def handle_text(self, texts: List[str]) -> List[str]:
        ans: List[str] = []
        for text in texts: 
            dot_pos: int = text.rfind('.')
            
            if dot_pos != -1:
                ans.append(text[:dot_pos + 1])
            else:
                ans.append(text + '.')
                
                
        return ans
    
    def select_output(self, candidates: List[str]) -> str:
        
        def heuristic(candidate: str) -> int:
            score = 0
            for char in candidate.lower():
                if  ord('a') <= ord(char) <= ord('z') or \
                    ord('0') <= ord(char) <= ord('9') or \
                    char in [' ', ',', '.', '!', '?', 'ń', 'ż', 'ć', 'ź', 'ś', 'ó']:
                    score += 5
                else:
                    score -= 500
            
            for s in ['klient', 'sprzedawca', 'sprzedawcy', 'sprzedawcowi', 'sprzedający', 'klienta']:
                if s in candidate.lower(): score -= 1000
                
            user_input = ' '.join([text.lower() for (role, text) in self.chat_history[0::2]])
            for word in candidate.split():
                if word.lower() in user_input: score += 100
                    
            return score
        
        def log_probs_from_logits(logits, labels):
            logp = F.log_softmax(logits, dim=-1)
            logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
            return logp_label
        
        def sentence_prob(text):
            input_ids = tokenizer(f"Sprzedawca odpowiada klientowi: {text}", return_tensors='pt')['input_ids'].to(DEVICE)
            
            with torch.no_grad():
                output = model(input_ids=input_ids)
                log_probs = log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
                
            return float(log_probs[:, -1])
        
        k_best = list(sorted(candidates, key=heuristic, reverse=True)[:10])
        return max(k_best, key=sentence_prob)

    def run(self) -> None:
        while True:
            user_input: str = input().strip()
            self.chat_history.append(("Klient mówi", user_input))
            
            prompt: str = self.build_prompt()
            candidates: List[str] = self.generate_candidates(prompt)
            output = self.select_output(candidates)
            print(output)
            
            self.chat_history.append(("Sprzedawca odpowiada", output))
            
chat = Chat()
chat.run()