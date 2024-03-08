
    for od_jakiej_karty in range(1, 11):
        for ile_kolorow in range(1, 5):
            talia_blotkarz = make_talia(od_jakiej_karty, ile_kolorow)
            if len(talia_blotkarz) < 5: continue
            
            szansa = przeprowadz_testy(talia_blotkarz, talia_figurant)
            wyniki.append((szansa, od_jakiej_karty, ile_kolorow))
            if szansa > 0.5:
                wyniki_ok.append((ile_kolorow * (10 - od_jakiej_ka