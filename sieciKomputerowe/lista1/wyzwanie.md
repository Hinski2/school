startx

--- 

1. Utwórz dodatkową maszynę wirtualną Virbian2. Podłącz karty sieciowe Adapter1 maszyn Virbian1
i Virbian2 do wirtualnej sieci local1 i następnie uruchom obie maszyny

ustawione

--- 

2.  Aktywuj karty sieciowe w obu urządzeniach poleceniem ip i sprawdź stan warstwy fizycznej kart
poleceniem ethtool.

* sudo ip link set up dev enp0s3
* ethtool enp0s3

---

3. Karcie sieciowej maszyny Virbian1 przypisz adres IP równy 192.168.100.1, zaś karcie maszyny
Virbian2 adres 192.168.100.2. Pamiętaj o masce podsieci /24.

* sudo ip addr add 192.168.0.1/24 dev enp0s3
* sudo ip addr add 192.168.0.2/24 dev enp0s3

--- 

4. Poleceniem ping sprawdź, czy jedna maszyna jest osiągalna z drugiej. Jaki jest RTT? Obejrzyj
przesyłane pakiety Wiresharkiem. Wskaż w pakiecie miejsce w którym przechowywany jest
źródłowy i docelowy adres IP

* ping ... 
* rtt to time= ... w ping (round trip time)
* infor w Internet Protocol Version 4 (ICMP)

--- 

5. Wykorzystaj program iperf3, żeby zbadać przepustowość połączenia między maszynami.

* V2> iperf3 -s
* V1> iperf3 -c 192.168.0.1

--- 

6. Z maszyny Virbian1 połącz się z serwerem echa maszyny Virbian2. Zaobserwuj przesyłane pakiety
w Wiresharkach uruchomionych jednocześnie na obu maszynach.

* ss -lntu
* ss -ltu
/etc/services

* telnet 192.168.0.2 7
tcp.port == 7

---

7. Zdekonfiguruj karty sieciowe obu maszyn i wyłącz wirtualne maszyny.

* ip addr flush dev enp0s3
* ip link set down dev enp0s3
