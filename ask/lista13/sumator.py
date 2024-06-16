sumaID, sumaRSS, sumaVSZ = 0, 0, 0

with open('plik.txt', 'r') as file:
    header = file.readline()
    
    for line in file:
        parts = list(map(int, line.split()))
        sumaID += parts[0]
        sumaRSS += parts[1]
        sumaVSZ += parts[2]
    
    print("sumaID:", sumaID, "\nsumaRSS:", sumaRSS, "\nsumaVSZ:", sumaVSZ)
    print("sumaVSZ / sumaRSS:", sumaVSZ / sumaRSS)