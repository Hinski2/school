import random

class Karta:
    def __init__(self, kolor, wartosc):
        self.kolor = kolor
        self.wartosc = wartosc
        
def strit(wartosci):
    w = wartosci
    w.sort()
    
    for i in range(1, 5):
        if w[i] != w[i - 1] + 1: return False
    return True

class Zestaw:
    def __init__(self, karty):
        self.karty = karty
    
    def wynik(self):
        kolory = [k.kolor for k in self.karty]
        wartosci = [k.wartosc for k in self.karty]
        
        wartosci_dic = {}
        for i in wartosci:
            wartosci_dic[i] = wartosci_dic.get(i, 0) + 1
            
        kolor_set = set()
        for i in kolory:
            kolor_set.add(i)
            
        ile_dwujek, ile_trujek, ile_czwurek = 0, 0, 0
        for i in wartosci_dic:
            if wartosci_dic[i] == 2: ile_dwujek += 1
            elif wartosci_dic[i] == 3: ile_trujek += 1
            elif wartosci_dic[i] == 4: ile_czwurek += 1
        
        
        ans = 0
        if strit(wartosci) and len(kolor_set) == 1: ans = 10 #poker
        elif ile_czwurek == 1: ans = 9 #kareta
        elif ile_dwujek == 1 and ile_trujek == 1: ans = 8 #ful
        elif len(kolor_set) == 1: ans = 7 #kolor
        elif strit(wartosci): ans = 6 #strit
        elif ile_trujek == 1: ans = 5 #trójka
        elif ile_dwujek == 2: ans = 4 #dwie pary
        elif ile_dwujek == 1: ans = 3 #para
        else: ans = 2 #nic
        
        return ans
    
def make_talia(od_jakiej_karty, ile_kolorow):
    talia = []
    for i in range(od_jakiej_karty, 11):
        for j in range(1, ile_kolorow + 1):
            k = Karta(j, i)
            talia.append(k)
    return talia

def wylosuj_karty(talia):
    z = random.sample(talia, 5)
    return z    

def test(talia_blotkarz, talia_figurant):
    zestaw_blotkarza = Zestaw(wylosuj_karty(talia_blotkarz))
    zestaw_figurant = Zestaw(wylosuj_karty(talia_figurant))
    
    wynik_blotkarz = zestaw_blotkarza.wynik()
    wynik_figurant = zestaw_figurant.wynik()
    
    if wynik_blotkarz > wynik_figurant: return 0
    else: return 1
    

def przeprowadz_testy(talia_blotkarz, talia_figurant):
    wygrane_blotkrz, wygrane_figurant = 1, 1
    
    for _ in range(50000):
        t = test(talia_blotkarz, talia_figurant)
        if t == 0: wygrane_blotkrz += 1
        else: wygrane_figurant += 1
        
    return wygrane_blotkrz / (wygrane_figurant + wygrane_blotkrz)
        
        
def main():
    wyniki = []
    wyniki_ok = []
    
    talia_figurant = []
    for number in range(1, 5):
        for kolor in range(1, 5):
            k = Karta(number, kolor)
            talia_figurant.append(k)
        
    for od_jakiej_karty in range(1, 11):
        for ile_kolorow in range(1, 5):
            talia_blotkarz = make_talia(od_jakiej_karty, ile_kolorow)
            if len(talia_blotkarz) < 5: continue
            
            szansa = przeprowadz_testy(talia_blotkarz, talia_figurant)
            wyniki.append((szansa, od_jakiej_karty, ile_kolorow))
            if szansa > 0.5:
                wyniki_ok.append((ile_kolorow * (10 - od_jakiej_karty + 1), szansa, od_jakiej_karty, ile_kolorow))
    
    
    wyniki_ok.sort(reverse=True) 
    print("ogólnie wyniki: (szansa, od_jakiej_karty, ile_kolorów")
    for wynik in wyniki:
        print(wynik)
        
    print("\n\nwyniki ok: (ile_kart, szansa, od_jakiej_karty, ile_kolorów")
    for wynik in wyniki_ok:
        print(wynik)

if __name__ == "__main__":
    main()