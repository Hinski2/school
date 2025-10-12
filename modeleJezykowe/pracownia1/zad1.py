from transformers import AutoTokenizer, AutoModelForCausalLM
from typing import List, Tuple
import torch
import torch.nn.functional as F 

PAPUGA = 'sdadas/polish-gpt2-large'
DEVICE = "cuda"

tokenizer = AutoTokenizer.from_pretrained(PAPUGA)
model = AutoModelForCausalLM.from_pretrained(PAPUGA).to(DEVICE)
model.device

class Chat:
    def __init__(self) -> None:
        self.chat_history: List[Tuple[str, str]] = []
        self.persona: str = "Asystent pracuje w sklepie wspinaczkowym. Odpowiada zwięźle (1–2 zdania), konkretnie, po polsku."
        
    def build_prompt(self, user_input: str) -> str:
        history = self.chat_history[-4:]
        conversation = [f"{self.persona}"]
        for role, text in history:
            conversation.append(f"{role}: {text}")
            
        conversation.append(f"Klient: {user_input}")
        conversation.append(f"Asystent: ")
        return "\n".join(conversation)
        
    def generate_candidates(self, prompt: str, num: int = 4, max_new_tokens: int = 30) -> List[str]:
        input_ids = tokenizer(prompt, return_tensors="pt").to(DEVICE)
        
        out = model.generate(
            **input_ids,
            temperature=0.8,
            top_p=0.90,
            repetition_penalty=1.15,
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
            
        return texts
    
    def select_output(self, candidates: List[str]) -> str:
        return min(candidates, key=len)     
    
    def run(self) -> None:
        while True:
            user_input: str = input().strip()
            prompt: str = self.build_prompt(user_input)
            candidates: List[str] = self.generate_candidates(prompt)
            output = self.select_output(candidates)
            print(output)
            
            self.chat_history.append(("Klient", user_input))
            self.chat_history.append(("Asystent", output))
            
chat = Chat()
chat.run()