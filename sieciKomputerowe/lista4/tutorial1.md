# Interfejsom en-loc przypisz adresy IP z sieci 172.18.0.0/16 jak na rysunku.
### v0
ip addr add 172.18.0.1/16 dev en-loc
### v1
ip addr add 172.18.0.2/16 dev en-loc

# Z maszyny Virbian0 pingnij adres 1.1.1.1; sprawdź, że otrzymywana jest odpowiedź.
### v0
ping 1.1.1.1

# Dodaj maszynę Virbian0 jako bramę domyślną dla maszyny Virbian1. Co się wydarzy,
# gdy z maszyny Virbian1 pingniesz teraz adres 1.1.1.1? Dlaczego?
### V1
ip route add default via 172.18.0.1
ping 1.1.1.1
bo pakiet z V1 -> V0 -> internet przez en-ext, serwer 1.1.1 otrzymuje zapytanie, ale widzi adres źródłowy 172.18.0.2. jest to adres prywatny, serwer nie wie jak odesłać odpowiedź do sieci wewnętrznej 

# Skonfiguruj NAT na maszynie Virbian0 dodając odpowiednie reguły za pomocą polecenia nft:
### v0 
nft add table inet my_table
nft add chain inet my_table my_rules { type nat hook postrouting priority srcnat\; }
nft add rule inet my_table my_rules ip saddr 172.18.0.0/16 snat to en-ext-IP
// ip -4 addr show dev en-ext
// nft list ruleset po

# Sprawdź, że teraz możesz pingnąć adres 1.1.1.1 z maszyny Virbian1. W Wiresharku na maszynie
# Virbian0 zaobserwuj, że pakiety od maszyny Virbian1 (a także odpowiedzi dla niej) są rejestrowane
# dwukrotnie, tj. przed podmianą źródłowego adresu IP i po niej.

# Sprawdź to również dla pakietów generowanych przez polecenie
traceroute -N 1 -q 1 -n 1.1.1.1.

# Przypisz interfejsom en-add adresy IP z sieci 192.168.0.0/24 jak na rysunku powyżej. Z maszyny
# Virbian1 pingnij maszynę Virbian2. Jaki jest adres źródłowy pakietów, które przychodzą do
# maszyny Virbian2 ?
### V0 
ip addr add 192.168.0.1/24 dev en-add
### V2 
ip route add default via 192.168.0.1
ip addr add 192.168.0.2/24 dev en-add
### V1
ping 192.168.0.2

### v0
nft flush ruleset 
nft add table inet my_table
nft add chain inet my_table my_rules \
    { type nat hook postrouting priority srcnat\; }
nft add rule inet my_table my_rules ip saddr 172.18.0.0/16 \
    oifname en-ext snat to en-ext-IP

# Dodaj trasę domyślną dla maszyny Virbian2 wskazującą na maszynę Virbian0. Sprawdź, że
# maszyny Virbian1 i Virbian2 są teraz wzajemnie osiągalne za pomocą polecenia ping.
### v2 
sudo ip route add default via 192.168.0.1
### v1
ping 192.168.0.2

# Na maszynie Virbian1 wpisz do pliku /etc/resolv.conf następujący wiersz:
nameserver 1.1.1.1

# Sprawdź, że na maszynie Virbian1 można również korzystać z przeglądarki uruchamiając Firefoksa
# i otwierając w nim stronę example.com lub inną. Obejrzyj w Wiresharku przechodzące przez
# maszynę Virbian0 zapytania HTTP (przed i po podmianie adresu źródłowego).
