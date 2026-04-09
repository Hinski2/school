# konfiguracja wewnętrzna linuxa
### v0
ip linke set enp0s3 name en-ext
ip link set enp0s8 name en-loc
ip link set enp0s9 name en-add

ip link set up dev en-ext
ip link set up dev en-loc
ip link set up dev en-add

dhcpcd en-ext

ip addr show dev en-ext

### v1
ip link set enp0s3 name en-loc
ip link set up dev en-loc

### v2
ip link set enp0s3 name en-add
ip link set up dev en-add
