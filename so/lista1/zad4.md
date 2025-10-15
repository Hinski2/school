# zad 4

---

* `segmenty programu` -  grupa sekcji o podobnych właściwościach załadowana do pamięci RAM, np text, data, bss, heap, stack
* `pamięć anonimowa` - obszary pamięci, które nie są powiazane z żadnym plikiem na dysku, towrzone są przez system z użyciem np malloc(), brk() z flagą MAP_ANONYMOUS. np. sterta, stos. po zakończeniu procesu znikają, istnieją tylko w ram (lub swap).
* `pliki odwzorowane w pamięci` - obszary pamięci, które są bezpośrednim odwzorowaniem zawartości pliku z dysku. np. semgent text, segment data, załadowane biblioteki

---

### jak znaleźć to pid: 
`pidof Xwayland`

### co oznaczaja kolumny
``` bash
00007f69a951f000   5128K rw---   [ anon ]
00007f69a9aa1000   2048K rw-s- nvidiactl
```
1. adres
2. rozmiar
3. prawa dostępu
4. opis: 
    * pełna ścieżka do pliku lub biblioteki
    * pamięć anonimowwa
    * mapowanie urządzenia np nvidiactl

* r - odczyt
* w - zapis
* x - wykonanie
* p/s - sposób mapowania p - prywatne, s - współdzelone


[ shmid ] oznacza pamięć współdzielona 

jak rozpoznać:
* stos - ma opis: [stack]
* strete - zazwyczaj opis [heap], jeśli go nie ma to znajduje się ona blisko mapowiana pliku wykonywalnego, u nas
``` bash
0000560efc055000   1732K r-x-- Xwayland
0000560efc206000    340K r---- Xwayland
0000560efc25b000     44K r---- Xwayland
0000560efc266000     28K rw--- Xwayland
0000560efc26d000    240K rw---   [ anon ] -- tutaj
0000560f1fca1000   7476K rw---   [ anon ] -- tutaj
```

ewentualnie użyć `cat /proc/1444/maps` 
* segmenty programu - jest tu:
``` bash
0000560efc046000     60K r---- Xwayland     -- text
0000560efc055000   1732K r-x-- Xwayland     -- rodata
0000560efc206000    340K r---- Xwayland     -- rodata
0000560efc25b000     44K r---- Xwayland     -- rodata
0000560efc266000     28K rw--- Xwayland     -- data / bss

```
* pamięć anonimową - ma opis [anon]
* pliko odwzorowane w pamięci - nie [anon]

---

specjalne rzeczy: 
```
00000000416de000      8K r-xs- .glXXXXXX (deleted)
0000000041a77000    688K rw---   [ anon ]
```
chyba jest to cos wykorzystywanego przez gpu ???

`00007ffd094fc000    132K rw---   [ stack ]` jest to stos
`ffffffffff600000      4K --x--   [ anon ]` jest to tzw virtual system call page, kernel umieszcza w przestrzeni procesu specjalny fragment pamięci, który zawiera kilka prostych fukcji systemowych np time(), które można wywołać bez syscall. dzięki temu można zrobic optymalizacje

``` bash
 pmap 1444

1444:   Xwayland :0 -rootless -core -listenfd 76 -listenfd 77 -displayfd 115 -wm 112
00000000416de000      8K r-xs- .glXXXXXX (deleted)
0000000041a77000    688K rw---   [ anon ]
0000560efc046000     60K r---- Xwayland
0000560efc055000   1732K r-x-- Xwayland
0000560efc206000    340K r---- Xwayland
0000560efc25b000     44K r---- Xwayland
0000560efc266000     28K rw--- Xwayland
0000560efc26d000    240K rw---   [ anon ]
0000560f1fca1000   7292K rw---   [ anon ]
00007f69a8e9f000   2048K rw-s- nvidiactl
00007f69a909f000   2048K rw-s- nvidiactl
00007f69a929f000    512K rw-s-   [ shmid=0x2 ]
00007f69a931f000   2048K rw-s- nvidiactl
00007f69a951f000   5148K rw---   [ anon ]
00007f69a9aa1000   2048K rw-s- nvidiactl
00007f69a9ca1000    512K rw-s- nvidiactl
00007f69a9d21000    512K rw-s- nvidiactl
00007f69a9da1000    516K rw---   [ anon ]
00007f69a9e22000   2048K rw-s- nvidiactl
00007f69aa022000    472K rw---   [ anon ]
00007f69aa098000    512K rw-s- nvidiactl
00007f69aa218000    512K rw-s- nvidiactl
00007f69aa298000    544K rw---   [ anon ]
00007f69aa320000    256K rw-s- nvidiactl
00007f69aa360000    128K rw-s- nvidiactl
00007f69aa380000    512K rw-s- nvidia0
00007f69aa400000  31112K r---- libicudata.so.76.1
00007f69ac262000      4K r---- libicudata.so.76.1
00007f69ac276000    256K rw-s- nvidiactl
00007f69ac2b6000    128K rw-s- nvidiactl
00007f69ac2d6000    256K rw-s- nvidiactl
00007f69ac336000    808K rw---   [ anon ]
00007f69ac400000    288K r---- libicuuc.so.76.1
00007f69ac448000   1116K r-x-- libicuuc.so.76.1
00007f69ac55f000    564K r---- libicuuc.so.76.1
00007f69ac5ec000     76K r---- libicuuc.so.76.1
00007f69ac5ff000      4K rw--- libicuuc.so.76.1
00007f69ac600000      8K rw---   [ anon ]
00007f69ac60a000     72K r---- 2b3ced44-dc47-48fd-b12a-394b196c390c (deleted)
00007f69ac61c000   1604K rw---   [ anon ]
00007f69ac7ad000     56K r---- libdbus-1.so.3.38.3
00007f69ac7bb000    196K r-x-- libdbus-1.so.3.38.3
00007f69ac7ec000     68K r---- libdbus-1.so.3.38.3
00007f69ac7fd000      8K r---- libdbus-1.so.3.38.3
00007f69ac7ff000      4K rw--- libdbus-1.so.3.38.3
00007f69ac800000    604K r---- libstdc++.so.6.0.34
00007f69ac897000   1364K r-x-- libstdc++.so.6.0.34
00007f69ac9ec000    584K r---- libstdc++.so.6.0.34
00007f69aca7e000     68K r---- libstdc++.so.6.0.34
00007f69aca8f000      4K rw--- libstdc++.so.6.0.34
00007f69aca90000     16K rw---   [ anon ]
00007f69aca9a000     76K rw-s- nvidiactl
00007f69acaad000    476K rw---   [ anon ]
00007f69acb24000    104K r---- libxml2.so.16.1.0
00007f69acb3e000    844K r-x-- libxml2.so.16.1.0
00007f69acc11000    244K r---- libxml2.so.16.1.0
00007f69acc4e000     36K r---- libxml2.so.16.1.0
00007f69acc57000      4K rw--- libxml2.so.16.1.0
00007f69acc58000      4K rw---   [ anon ]
00007f69acc59000     84K r---- libSPIRV-Tools.so
00007f69acc6e000   1128K r-x-- libSPIRV-Tools.so
00007f69acd88000    464K r---- libSPIRV-Tools.so
00007f69acdfc000     12K r---- libSPIRV-Tools.so
00007f69acdff000      4K rw--- libSPIRV-Tools.so
00007f69ace00000   5404K r---- libLLVM.so.20.1
00007f69ad347000  88692K r-x-- libLLVM.so.20.1
00007f69b29e4000  57040K r---- libLLVM.so.20.1
00007f69b6198000   1976K r---- libLLVM.so.20.1
00007f69b6386000    288K rw--- libLLVM.so.20.1
00007f69b63ce000    776K rw---   [ anon ]
00007f69b6492000    548K rw---   [ anon ]
00007f69b651b000     48K r---- libzstd.so.1.5.7
00007f69b6527000    792K r-x-- libzstd.so.1.5.7
00007f69b65ed000     68K r---- libzstd.so.1.5.7
00007f69b65fe000      4K r---- libzstd.so.1.5.7
00007f69b65ff000      4K rw--- libzstd.so.1.5.7
00007f69b6600000    100K r---- libgallium-25.2.4-arch1.1.so
00007f69b6619000  27236K r-x-- libgallium-25.2.4-arch1.1.so
00007f69b80b2000  15976K r---- libgallium-25.2.4-arch1.1.so
00007f69b904c000   1116K r---- libgallium-25.2.4-arch1.1.so
00007f69b9163000    132K rw--- libgallium-25.2.4-arch1.1.so
00007f69b9184000   1836K rw---   [ anon ]
00007f69b9350000    260K rw---   [ anon ]
00007f69b9391000     52K r---- libncursesw.so.6.5
00007f69b939e000    284K r-x-- libncursesw.so.6.5
00007f69b93e5000     88K r---- libncursesw.so.6.5
00007f69b93fb000     16K r---- libncursesw.so.6.5
00007f69b93ff000      4K rw--- libncursesw.so.6.5
00007f69b9400000   2732K r---- libnvidia-gpucomp.so.580.95.05
00007f69b96ab000  50100K r-x-- libnvidia-gpucomp.so.580.95.05
00007f69bc798000  14784K r---- libnvidia-gpucomp.so.580.95.05
00007f69bd608000      4K ----- libnvidia-gpucomp.so.580.95.05
00007f69bd609000   1884K r---- libnvidia-gpucomp.so.580.95.05
00007f69bd7e0000   1068K rw--- libnvidia-gpucomp.so.580.95.05
00007f69bd8eb000    640K rw---   [ anon ]
00007f69bd991000     12K r---- libnvidia-allocator.so.580.95.05
00007f69bd994000    100K r-x-- libnvidia-allocator.so.580.95.05
00007f69bd9ad000     44K r---- libnvidia-allocator.so.580.95.05
00007f69bd9b8000      4K r---- libnvidia-allocator.so.580.95.05
00007f69bd9b9000      4K rw--- libnvidia-allocator.so.580.95.05
00007f69bd9ba000      4K rw---   [ anon ]
00007f69bd9bb000      8K r---- libpciaccess.so.0.11.1
00007f69bd9bd000     20K r-x-- libpciaccess.so.0.11.1
00007f69bd9c2000      8K r---- libpciaccess.so.0.11.1
00007f69bd9c4000      4K r---- libpciaccess.so.0.11.1
00007f69bd9c5000      4K rw--- libpciaccess.so.0.11.1
00007f69bd9c6000     24K r---- libedit.so.0.0.75
00007f69bd9cc000    132K r-x-- libedit.so.0.0.75
00007f69bd9ed000     52K r---- libedit.so.0.0.75
00007f69bd9fa000      8K r---- libedit.so.0.0.75
00007f69bd9fc000      4K rw--- libedit.so.0.0.75
00007f69bd9fd000     12K rw---   [ anon ]
00007f69bda00000   2312K r---- libnvidia-eglcore.so.580.95.05
00007f69bdc42000  13068K r-x-- libnvidia-eglcore.so.580.95.05
00007f69be905000  17032K r---- libnvidia-eglcore.so.580.95.05
00007f69bf9a7000   1504K r---- libnvidia-eglcore.so.580.95.05
00007f69bfb1f000    336K rw--- libnvidia-eglcore.so.580.95.05
00007f69bfb73000     88K rw---   [ anon ]
00007f69bfb8b000     12K rw-s- nvidiactl
00007f69bfb8e000     12K r---- libdrm_intel.so.1.126.0
00007f69bfb91000     92K r-x-- libdrm_intel.so.1.126.0
00007f69bfba8000     36K r---- libdrm_intel.so.1.126.0
00007f69bfbb1000      4K r---- libdrm_intel.so.1.126.0
00007f69bfbb2000      4K rw--- libdrm_intel.so.1.126.0
00007f69bfbb3000     12K r---- libelf-0.193.so
00007f69bfbb6000     76K r-x-- libelf-0.193.so
00007f69bfbc9000     16K r---- libelf-0.193.so
00007f69bfbcd000      4K r---- libelf-0.193.so
00007f69bfbce000      4K rw--- libelf-0.193.so
00007f69bfbcf000     12K r---- libdrm_amdgpu.so.1.126.0
00007f69bfbd2000     24K r-x-- libdrm_amdgpu.so.1.126.0
00007f69bfbd8000      8K r---- libdrm_amdgpu.so.1.126.0
00007f69bfbda000      4K r---- libdrm_amdgpu.so.1.126.0
00007f69bfbdb000      4K rw--- libdrm_amdgpu.so.1.126.0
00007f69bfbdc000     12K r---- libxcb-sync.so.1.0.0
00007f69bfbdf000     12K r-x-- libxcb-sync.so.1.0.0
00007f69bfbe2000      4K r---- libxcb-sync.so.1.0.0
00007f69bfbe3000      4K r---- libxcb-sync.so.1.0.0
00007f69bfbe4000      4K rw--- libxcb-sync.so.1.0.0
00007f69bfbe5000      8K r---- libsensors.so.5.0.0
00007f69bfbe7000     32K r-x-- libsensors.so.5.0.0
00007f69bfbef000     16K r---- libsensors.so.5.0.0
00007f69bfbf3000      4K r---- libsensors.so.5.0.0
00007f69bfbf4000      4K rw--- libsensors.so.5.0.0
00007f69bfbf5000      4K r---- libxcb-shm.so.0.0.0
00007f69bfbf6000      4K r-x-- libxcb-shm.so.0.0.0
00007f69bfbf7000      4K r---- libxcb-shm.so.0.0.0
00007f69bfbf8000      4K r---- libxcb-shm.so.0.0.0
00007f69bfbf9000      4K rw--- libxcb-shm.so.0.0.0
00007f69bfbfa000     12K r---- libxcb-xfixes.so.0.0.0
00007f69bfbfd000     12K r-x-- libxcb-xfixes.so.0.0.0
00007f69bfc00000      4K r---- libxcb-xfixes.so.0.0.0
00007f69bfc01000      4K r---- libxcb-xfixes.so.0.0.0
00007f69bfc02000      4K rw--- libxcb-xfixes.so.0.0.0
00007f69bfc03000     28K r---- libxcb-randr.so.0.1.0
00007f69bfc0a000     24K r-x-- libxcb-randr.so.0.1.0
00007f69bfc10000     12K r---- libxcb-randr.so.0.1.0
00007f69bfc13000      4K r---- libxcb-randr.so.0.1.0
00007f69bfc14000      4K rw--- libxcb-randr.so.0.1.0
00007f69bfc15000     24K r---- libEGL_mesa.so.0.0.0
00007f69bfc1b000    168K r-x-- libEGL_mesa.so.0.0.0
00007f69bfc45000     76K r---- libEGL_mesa.so.0.0.0
00007f69bfc58000     48K r---- libEGL_mesa.so.0.0.0
00007f69bfc64000      4K rw--- libEGL_mesa.so.0.0.0
00007f69bfc65000      4K r---- libX11-xcb.so.1.0.0
00007f69bfc66000      4K r-x-- libX11-xcb.so.1.0.0
00007f69bfc67000      4K r---- libX11-xcb.so.1.0.0
00007f69bfc68000      4K r---- libX11-xcb.so.1.0.0
00007f69bfc69000      4K rw--- libX11-xcb.so.1.0.0
00007f69bfc6a000     12K r---- libnvidia-egl-xlib.so.1.0.3
00007f69bfc6d000     44K r-x-- libnvidia-egl-xlib.so.1.0.3
00007f69bfc78000     16K r---- libnvidia-egl-xlib.so.1.0.3
00007f69bfc7c000      4K r---- libnvidia-egl-xlib.so.1.0.3
00007f69bfc7d000      4K rw--- libnvidia-egl-xlib.so.1.0.3
00007f69bfc7e000      8K r---- libxcb-dri3.so.0.1.0
00007f69bfc80000      8K r-x-- libxcb-dri3.so.0.1.0
00007f69bfc82000      4K r---- libxcb-dri3.so.0.1.0
00007f69bfc83000      4K r---- libxcb-dri3.so.0.1.0
00007f69bfc84000      4K rw--- libxcb-dri3.so.0.1.0
00007f69bfc85000      4K r---- libxcb-present.so.0.0.0
00007f69bfc86000      4K r-x-- libxcb-present.so.0.0.0
00007f69bfc87000      4K r---- libxcb-present.so.0.0.0
00007f69bfc88000      4K r---- libxcb-present.so.0.0.0
00007f69bfc89000      4K rw--- libxcb-present.so.0.0.0
00007f69bfc8a000     12K r---- libnvidia-egl-xcb.so.1.0.3
00007f69bfc8d000     40K r-x-- libnvidia-egl-xcb.so.1.0.3
00007f69bfc97000     16K r---- libnvidia-egl-xcb.so.1.0.3
00007f69bfc9b000      4K r---- libnvidia-egl-xcb.so.1.0.3
00007f69bfc9c000      4K rw--- libnvidia-egl-xcb.so.1.0.3
00007f69bfc9d000      4K r---- libnvidia-egl-gbm.so.1.1.2
00007f69bfc9e000     12K r-x-- libnvidia-egl-gbm.so.1.1.2
00007f69bfca1000      8K r---- libnvidia-egl-gbm.so.1.1.2
00007f69bfca3000      4K r---- libnvidia-egl-gbm.so.1.1.2
00007f69bfca4000      4K rw--- libnvidia-egl-gbm.so.1.1.2
00007f69bfca5000    300K rw---   [ anon ]
00007f69bfcf0000     20K r---- libwayland-server.so.0.24.0
00007f69bfcf5000     36K r-x-- libwayland-server.so.0.24.0
00007f69bfcfe000     16K r---- libwayland-server.so.0.24.0
00007f69bfd02000      8K r---- libwayland-server.so.0.24.0
00007f69bfd04000      4K rw--- libwayland-server.so.0.24.0
00007f69bfd05000     12K r---- libnvidia-egl-wayland.so.1.1.20
00007f69bfd08000     40K r-x-- libnvidia-egl-wayland.so.1.1.20
00007f69bfd12000     16K r---- libnvidia-egl-wayland.so.1.1.20
00007f69bfd16000      8K r---- libnvidia-egl-wayland.so.1.1.20
00007f69bfd18000      4K rw--- libnvidia-egl-wayland.so.1.1.20
00007f69bfd19000     64K r---- libnvidia-glsi.so.580.95.05
00007f69bfd29000    384K r-x-- libnvidia-glsi.so.580.95.05
00007f69bfd89000    116K r---- libnvidia-glsi.so.580.95.05
00007f69bfda6000     24K r---- libnvidia-glsi.so.580.95.05
00007f69bfdac000      4K rw--- libnvidia-glsi.so.580.95.05
00007f69bfdad000     32K rw---   [ anon ]
00007f69bfdb5000      4K r---- libdl.so.2
00007f69bfdb6000      4K r-x-- libdl.so.2
00007f69bfdb7000      4K r---- libdl.so.2
00007f69bfdb8000      4K r---- libdl.so.2
00007f69bfdb9000      4K rw--- libdl.so.2
00007f69bfdba000      4K r---- librt.so.1
00007f69bfdbb000      4K r-x-- librt.so.1
00007f69bfdbc000      4K r---- librt.so.1
00007f69bfdbd000      4K r---- librt.so.1
00007f69bfdbe000      4K rw--- librt.so.1
00007f69bfdbf000      4K r---- libpthread.so.0
00007f69bfdc0000      4K r-x-- libpthread.so.0
00007f69bfdc1000      4K r---- libpthread.so.0
00007f69bfdc2000      4K r---- libpthread.so.0
00007f69bfdc3000      4K rw--- libpthread.so.0
00007f69bfdc4000    208K r---- libEGL_nvidia.so.580.95.05
00007f69bfdf8000    604K r-x-- libEGL_nvidia.so.580.95.05
00007f69bfe8f000    336K r---- libEGL_nvidia.so.580.95.05
00007f69bfee3000      4K ----- libEGL_nvidia.so.580.95.05
00007f69bfee4000     32K r---- libEGL_nvidia.so.580.95.05
00007f69bfeec000     88K rw--- libEGL_nvidia.so.580.95.05
00007f69bff02000     20K rw---   [ anon ]
00007f69bff07000      8K r---- libEGL.so.1.1.0
00007f69bff09000     40K r-x-- libEGL.so.1.1.0
00007f69bff13000     16K r---- libEGL.so.1.1.0
00007f69bff17000      4K r---- libEGL.so.1.1.0
00007f69bff18000      4K rw--- libEGL.so.1.1.0
00007f69bff19000    332K rw---   [ anon ]
00007f69bff6c000      8K r---- libXdmcp.so.6.0.0
00007f69bff6e000      8K r-x-- libXdmcp.so.6.0.0
00007f69bff70000      8K r---- libXdmcp.so.6.0.0
00007f69bff72000      4K r---- libXdmcp.so.6.0.0
00007f69bff73000      4K rw--- libXdmcp.so.6.0.0
00007f69bff74000     48K r---- libxcb.so.1.1.0
00007f69bff80000     80K r-x-- libxcb.so.1.1.0
00007f69bff94000     36K r---- libxcb.so.1.1.0
00007f69bff9d000      4K r---- libxcb.so.1.1.0
00007f69bff9e000      4K rw--- libxcb.so.1.1.0
00007f69bff9f000      4K r---- libbrotlicommon.so.1.1.0
00007f69bffa0000      4K r-x-- libbrotlicommon.so.1.1.0
00007f69bffa1000    124K r---- libbrotlicommon.so.1.1.0
00007f69bffc0000      4K r---- libbrotlicommon.so.1.1.0
00007f69bffc1000      4K rw--- libbrotlicommon.so.1.1.0
00007f69bffc2000      8K rw---   [ anon ]
00007f69bffc4000     92K r---- libX11.so.6.4.0
00007f69bffdb000    592K r-x-- libX11.so.6.4.0
00007f69c006f000    572K r---- libX11.so.6.4.0
00007f69c00fe000     12K r---- libX11.so.6.4.0
00007f69c0101000     16K rw--- libX11.so.6.4.0
00007f69c0105000     12K r---- libresolv.so.2
00007f69c0108000     36K r-x-- libresolv.so.2
00007f69c0111000     12K r---- libresolv.so.2
00007f69c0114000      4K r---- libresolv.so.2
00007f69c0115000      4K rw--- libresolv.so.2
00007f69c0116000      8K rw---   [ anon ]
00007f69c0118000      8K r---- libkeyutils.so.1.10
00007f69c011a000      8K r-x-- libkeyutils.so.1.10
00007f69c011c000      4K r---- libkeyutils.so.1.10
00007f69c011d000      4K r---- libkeyutils.so.1.10
00007f69c011e000      4K rw--- libkeyutils.so.1.10
00007f69c011f000     12K r---- libkrb5support.so.0.1
00007f69c0122000     28K r-x-- libkrb5support.so.0.1
00007f69c0129000      8K r---- libkrb5support.so.0.1
00007f69c012b000      4K r---- libkrb5support.so.0.1
00007f69c012c000      4K rw--- libkrb5support.so.0.1
00007f69c012d000      8K r---- libcom_err.so.2.1
00007f69c012f000      4K r-x-- libcom_err.so.2.1
00007f69c0130000      4K r---- libcom_err.so.2.1
00007f69c0131000      4K r---- libcom_err.so.2.1
00007f69c0132000      4K rw--- libcom_err.so.2.1
00007f69c0133000      8K rw---   [ anon ]
00007f69c0135000     12K r---- libk5crypto.so.3.1
00007f69c0138000    112K r-x-- libk5crypto.so.3.1
00007f69c0154000     44K r---- libk5crypto.so.3.1
00007f69c015f000      8K r---- libk5crypto.so.3.1
00007f69c0161000      4K rw--- libk5crypto.so.3.1
00007f69c0162000     68K r---- libkrb5.so.3.3
00007f69c0173000    428K r-x-- libkrb5.so.3.3
00007f69c01de000    232K r---- libkrb5.so.3.3
00007f69c0218000     56K r---- libkrb5.so.3.3
00007f69c0226000      8K rw--- libkrb5.so.3.3
00007f69c0228000     12K r---- libcap.so.2.76
00007f69c022b000     20K r-x-- libcap.so.2.76
00007f69c0230000      8K r---- libcap.so.2.76
00007f69c0232000      4K r---- libcap.so.2.76
00007f69c0233000      4K rw--- libcap.so.2.76
00007f69c0234000      4K r---- libbrotlidec.so.1.1.0
00007f69c0235000     36K r-x-- libbrotlidec.so.1.1.0
00007f69c023e000     12K r---- libbrotlidec.so.1.1.0
00007f69c0241000      4K r---- libbrotlidec.so.1.1.0
00007f69c0242000      4K rw--- libbrotlidec.so.1.1.0
00007f69c0243000     24K r---- libpng16.so.16.50.0
00007f69c0249000    164K r-x-- libpng16.so.16.50.0
00007f69c0272000     36K r---- libpng16.so.16.50.0
00007f69c027b000      4K r---- libpng16.so.16.50.0
00007f69c027c000      4K rw--- libpng16.so.16.50.0
00007f69c027d000      8K r---- libbz2.so.1.0.8
00007f69c027f000     52K r-x-- libbz2.so.1.0.8
00007f69c028c000      8K r---- libbz2.so.1.0.8
00007f69c028e000      4K r---- libbz2.so.1.0.8
00007f69c028f000      4K rw--- libbz2.so.1.0.8
00007f69c0290000      8K r---- libGLX.so.0.0.0
00007f69c0292000    104K r-x-- libGLX.so.0.0.0
00007f69c02ac000     12K r---- libGLX.so.0.0.0
00007f69c02af000      4K r---- libGLX.so.0.0.0
00007f69c02b0000      4K rw--- libGLX.so.0.0.0
00007f69c02b1000     64K rw---   [ anon ]
00007f69c02c1000      8K r---- libGLdispatch.so.0.0.0
00007f69c02c3000    252K r-x-- libGLdispatch.so.0.0.0
00007f69c0302000     76K r---- libGLdispatch.so.0.0.0
00007f69c0315000    112K r---- libGLdispatch.so.0.0.0
00007f69c0331000      4K rw--- libGLdispatch.so.0.0.0
00007f69c0332000     32K rw---   [ anon ]
00007f69c033a000     36K r---- libgssapi_krb5.so.2.2
00007f69c0343000    244K r-x-- libgssapi_krb5.so.2.2
00007f69c0380000     40K r---- libgssapi_krb5.so.2.2
00007f69c038a000      8K r---- libgssapi_krb5.so.2.2
00007f69c038c000      4K rw--- libgssapi_krb5.so.2.2
00007f69c038d000      8K r---- libexpat.so.1.11.1
00007f69c038f000    120K r-x-- libexpat.so.1.11.1
00007f69c03ad000     32K r---- libexpat.so.1.11.1
00007f69c03b5000      8K r---- libexpat.so.1.11.1
00007f69c03b7000      4K rw--- libexpat.so.1.11.1
00007f69c03b8000     84K r---- libsystemd.so.0.41.0
00007f69c03cd000    780K r-x-- libsystemd.so.0.41.0
00007f69c0490000    268K r---- libsystemd.so.0.41.0
00007f69c04d3000     36K r---- libsystemd.so.0.41.0
00007f69c04dc000      4K rw--- libsystemd.so.0.41.0
00007f69c04dd000      4K rw---   [ anon ]
00007f69c04de000     16K r---- libgcc_s.so.1
00007f69c04e2000    140K r-x-- libgcc_s.so.1
00007f69c0505000     16K r---- libgcc_s.so.1
00007f69c0509000      4K r---- libgcc_s.so.1
00007f69c050a000      4K rw--- libgcc_s.so.1
00007f69c050b000      8K r---- libffi.so.8.2.0
00007f69c050d000     28K r-x-- libffi.so.8.2.0
00007f69c0514000      4K r---- libffi.so.8.2.0
00007f69c0515000      4K r---- libffi.so.8.2.0
00007f69c0516000      4K rw--- libffi.so.8.2.0
00007f69c0517000     24K r---- libfreetype.so.6.20.4
00007f69c051d000    608K r-x-- libfreetype.so.6.20.4
00007f69c05b5000    164K r---- libfreetype.so.6.20.4
00007f69c05de000     32K r---- libfreetype.so.6.20.4
00007f69c05e6000      4K rw--- libfreetype.so.6.20.4
00007f69c05e7000     12K r---- libz.so.1.3.1
00007f69c05ea000     56K r-x-- libz.so.1.3.1
00007f69c05f8000     24K r---- libz.so.1.3.1
00007f69c05fe000      4K r---- libz.so.1.3.1
00007f69c05ff000      4K rw--- libz.so.1.3.1
00007f69c0600000    144K r---- libc.so.6
00007f69c0624000   1480K r-x-- libc.so.6
00007f69c0796000    444K r---- libc.so.6
00007f69c0805000     16K r---- libc.so.6
00007f69c0809000      8K rw--- libc.so.6
00007f69c080b000     32K rw---   [ anon ]
00007f69c0814000     16K rw---   [ anon ]
00007f69c0818000      4K r---- libfontenc.so.1.0.0
00007f69c0819000     12K r-x-- libfontenc.so.1.0.0
00007f69c081c000      8K r---- libfontenc.so.1.0.0
00007f69c081e000      4K r---- libfontenc.so.1.0.0
00007f69c081f000      4K rw--- libfontenc.so.1.0.0
00007f69c0820000     12K rw---   [ anon ]
00007f69c0823000    188K r---- libGL.so.1.7.0
00007f69c0852000    124K r-x-- libGL.so.1.7.0
00007f69c0871000     80K r---- libGL.so.1.7.0
00007f69c0885000     56K r---- libGL.so.1.7.0
00007f69c0893000      4K rw--- libGL.so.1.7.0
00007f69c0894000      4K rw---   [ anon ]
00007f69c0895000      4K r---- libXau.so.6.0.0
00007f69c0896000      4K r-x-- libXau.so.6.0.0
00007f69c0897000      4K r---- libXau.so.6.0.0
00007f69c0898000      4K r---- libXau.so.6.0.0
00007f69c0899000      4K rw--- libXau.so.6.0.0
00007f69c089a000     32K r---- libtirpc.so.3.0.0
00007f69c08a2000    108K r-x-- libtirpc.so.3.0.0
00007f69c08bd000     32K r---- libtirpc.so.3.0.0
00007f69c08c5000      8K r---- libtirpc.so.3.0.0
00007f69c08c7000      4K rw--- libtirpc.so.3.0.0
00007f69c08c8000     56K r---- libnettle.so.8.11
00007f69c08d6000    192K r-x-- libnettle.so.8.11
00007f69c0906000     96K r---- libnettle.so.8.11
00007f69c091e000     12K r---- libnettle.so.8.11
00007f69c0921000      4K rw--- libnettle.so.8.11
00007f69c0922000      8K rw---   [ anon ]
00007f69c0924000     60K r---- libm.so.6
00007f69c0933000    556K r-x-- libm.so.6
00007f69c09be000    456K r---- libm.so.6
00007f69c0a30000      4K r---- libm.so.6
00007f69c0a31000      4K rw--- libm.so.6
00007f69c0a32000     12K r---- libdecor-0.so.0.200.3
00007f69c0a35000     12K r-x-- libdecor-0.so.0.200.3
00007f69c0a38000      8K r---- libdecor-0.so.0.200.3
00007f69c0a3a000      4K r---- libdecor-0.so.0.200.3
00007f69c0a3b000      4K rw--- libdecor-0.so.0.200.3
00007f69c0a3c000      8K r---- libgbm.so.1.0.0
00007f69c0a3e000      4K r-x-- libgbm.so.1.0.0
00007f69c0a3f000      4K r---- libgbm.so.1.0.0
00007f69c0a40000      4K r---- libgbm.so.1.0.0
00007f69c0a41000      4K rw--- libgbm.so.1.0.0
00007f69c0a42000      8K r---- liboeffis.so.1.5.0
00007f69c0a44000     12K r-x-- liboeffis.so.1.5.0
00007f69c0a47000      8K r---- liboeffis.so.1.5.0
00007f69c0a49000      4K r---- liboeffis.so.1.5.0
00007f69c0a4a000      4K rw--- liboeffis.so.1.5.0
00007f69c0a4b000     12K r---- libei.so.1.5.0
00007f69c0a4e000     56K r-x-- libei.so.1.5.0
00007f69c0a5c000     32K r---- libei.so.1.5.0
00007f69c0a64000      8K r---- libei.so.1.5.0
00007f69c0a66000      4K rw--- libei.so.1.5.0
00007f69c0a67000    296K r---- libepoxy.so.0.0.0
00007f69c0ab1000    408K r-x-- libepoxy.so.0.0.0
00007f69c0b17000    312K r---- libepoxy.so.0.0.0
00007f69c0b65000     32K r---- libepoxy.so.0.0.0
00007f69c0b6d000     28K rw--- libepoxy.so.0.0.0
00007f69c0b74000      8K rw---   [ anon ]
00007f69c0b76000     20K r---- libdrm.so.2.126.0
00007f69c0b7b000     48K r-x-- libdrm.so.2.126.0
00007f69c0b87000     16K r---- libdrm.so.2.126.0
00007f69c0b8b000      4K r---- libdrm.so.2.126.0
00007f69c0b8c000      4K rw--- libdrm.so.2.126.0
00007f69c0b8d000      4K r---- libxshmfence.so.1.0.0
00007f69c0b8e000      4K r-x-- libxshmfence.so.1.0.0
00007f69c0b8f000      4K r---- libxshmfence.so.1.0.0
00007f69c0b90000      4K r---- libxshmfence.so.1.0.0
00007f69c0b91000      4K rw--- libxshmfence.so.1.0.0
00007f69c0b92000      4K r---- libxcvt.so.0.1.3
00007f69c0b93000      4K r-x-- libxcvt.so.0.1.3
00007f69c0b94000      4K r---- libxcvt.so.0.1.3
00007f69c0b95000      4K r---- libxcvt.so.0.1.3
00007f69c0b96000      4K rw--- libxcvt.so.0.1.3
00007f69c0b97000     12K r---- libwayland-client.so.0.24.0
00007f69c0b9a000     28K r-x-- libwayland-client.so.0.24.0
00007f69c0ba1000     12K r---- libwayland-client.so.0.24.0
00007f69c0ba4000      8K r---- libwayland-client.so.0.24.0
00007f69c0ba6000      4K rw--- libwayland-client.so.0.24.0
00007f69c0ba7000     12K r---- libXfont2.so.2.0.0
00007f69c0baa000    160K r-x-- libXfont2.so.2.0.0
00007f69c0bd2000     32K r---- libXfont2.so.2.0.0
00007f69c0bda000      4K r---- libXfont2.so.2.0.0
00007f69c0bdb000      4K rw--- libXfont2.so.2.0.0
00007f69c0bdc000      4K rw---   [ anon ]
00007f69c0bdd000     20K r---- libpixman-1.so.0.46.4
00007f69c0be2000    580K r-x-- libpixman-1.so.0.46.4
00007f69c0c73000     64K r---- libpixman-1.so.0.46.4
00007f69c0c83000     32K r---- libpixman-1.so.0.46.4
00007f69c0c8b000      4K rw--- libpixman-1.so.0.46.4
00007f69c0c8c000      8K rw---   [ anon ]
00007f69c0c8e000      8K rw-s- .glXXXXXX (deleted)
00007f69c0c90000      4K rw-s- nvidiactl
00007f69c0c92000     12K r---- b5c1b2f6-93b3-40ff-98c3-fa93baaaf652 (deleted)
00007f69c0c95000      4K rw-s- nvidia0
00007f69c0c96000      8K rw-s- nvidiactl
00007f69c0c98000     16K rw-s- nvidiactl
00007f69c0c9c000      4K rw-s- nvidiactl
00007f69c0c9d000      4K rw-s- nvidiactl
00007f69c0c9e000      4K r--s- nvidiactl
00007f69c0c9f000     64K rw-s- nvidia0
00007f69c0caf000     12K r---- b5c1b2f6-93b3-40ff-98c3-fa93baaaf652 (deleted)
00007f69c0cb2000     16K r----   [ anon ]
00007f69c0cb6000      8K r----   [ anon ]
00007f69c0cb8000      8K r-x--   [ anon ]
00007f69c0cba000      4K r---- ld-linux-x86-64.so.2
00007f69c0cbb000    168K r-x-- ld-linux-x86-64.so.2
00007f69c0ce5000     56K r---- ld-linux-x86-64.so.2
00007f69c0cf3000      8K r---- ld-linux-x86-64.so.2
00007f69c0cf5000      4K rw--- ld-linux-x86-64.so.2
00007f69c0cf6000      4K rw---   [ anon ]
00007ffd094fc000    132K rw---   [ stack ]
ffffffffff600000      4K --x--   [ anon ]
 total           400260K
```

