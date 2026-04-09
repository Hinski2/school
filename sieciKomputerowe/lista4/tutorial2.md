# setup
### v1
// Zmiana nazw
sudo ip link set enp0s3 name en-rem1
sudo ip link set enp0s8 name en-rem4
sudo ip link set enp0s9 name en-all

// Aktywacja tylko sieci remote
sudo ip link set up dev en-rem1
sudo ip link set up dev en-rem4

// Nadanie adresów IP
sudo ip addr add 192.168.1.1/24 dev en-rem1
sudo ip addr add 192.168.4.1/24 dev en-rem4

### ...

# Poleceniem ip route sprawdź, że tablica routingu każdej maszyny zawiera dokładnie dwa wpisy
# dotyczące bezpośrednio połączonych z nią sieci. Sprawdź dostępność bezpośrednio połączonych
# maszyn poleceniem ping.

ip route

# ędziemy teraz przekazywać wszystkie pakiety do celu zgodnie ze wskazówkami zegara. Jako
# bramę domyślną dla każdej maszyny ustaw maszynę, która jest następna w cyklu (tj. tak jak
# pokazują strzałki na rysunku poniżej). Pamiętaj, że brama musi leżeć w bezpośrednio podłączonej
# sieci: przykładowo brama domyślna dla komputera Virbian2 powinna być równa 192.168.2.3 a
# nie 192.168.3.3. Upewnij się, że tablica routingu każdej maszyny zawiera dokładnie trzy wpisy.

### *
sudo sysctl net.ipv4.ip_forward=1

### v1
sudo ip route add default via 192.168.1.2
### v2
sudo ip route add default via 192.168.2.3
### v3
sudo ip route add default via 192.168.3.4
### v4
sudo ip route add default via 192.168.4.1

// ip route

# Na maszynie Virbian1 wykonaj polecenia
# traceroute -N 1 -q 1 -n adres_IP
# żeby wyświetlić ścieżkę do każdego z ośmiu interfejsów.
