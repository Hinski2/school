def wynik(ciag, n):
    n = int(n)
    ciag = '#' + ciag
    
    pref = [0 for _ in range(len(ciag) + 1)]
    for i in range(1, len(ciag)):
        pref[i] = pref[i - 1] + (ciag[i] == '1')
    pref[-1] = pref[-2]
    
    ans = len(ciag)
    for i in range(n, len(ciag)):
        subAns = pref[i - n]
        subAns += pref[-1] - pref[i]
        subAns += n - (pref[i] - pref[i - n])
        
        ans = min(ans, subAns)
    
    return str(ans) + '\n'

def main():
    out = open("zad4_output.txt", 'w') 
    with open("zad4_input.txt", 'r') as file:
        for linia in file:
            ciag, n = linia.split()
            out.write(wynik(ciag, n))
    out.close()
        

if __name__ == "__main__":
    main()