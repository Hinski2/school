# zad 1 

---

* `identyfikator procesu` - (PID) unikalny numer nadawany każdemu procesowi przez os, służy do identyfikacji procesu
* `identyfikator grupy procesów` - (PGID) numer wspólny dla grupy powiązanych procesów, używany np do wspólnego zarządzania sygnałami
* `identyfikator rodzica procesu` - (PPID) pid procesu procesu który utworzył dany proces
* `identyfikator właściciela procesu` - (UID/EUID) numer użytkownika, do ktorego należy proces, np root = 0
* `wątek jądra` - proces działający w trybie jadra, może wykonywać zadania systemowe np. I/O
* `hierarchia procesów` - drzewo relacji między procesami, proces init (odpowiada za rozruch całego systemu) ma pid=1

`TID` - thread id
`PRI` - priority - niższa liczba -> wyższy priorytet
`STAT` - STATE - aktualny stan procesu:
* R - running
* S - sleep
* I - idle (bazczynny)
* < - high priority
* N - low priority
* s - session leader (leader grupy procesów)
* \+ - foreground proces (proces znajduje się na pierwszym planei)

`WCHAN` (waiting channel) - nazwa funkcji jadra na która czeka proces

---

### kto jest rodzicem init:

``` bash
USER         PID    PPID    PGID     TID PRI STAT WCHAN  CMD
root           1       0       1       1  19 Ss   -      /sbin/init splash
```

init nie ma rodzica

### ktore to procesy jądra 

procesy jądra są oznaczone `[*]`

### hierarchia procesów
``` bash
systemd─┬─NetworkManager───3*[{NetworkManager}]
        ├─blueman-applet───5*[{blueman-applet}]
        ├─blueman-tray───5*[{blueman-tray}]
        ├─bluetoothd
        ├─brave─┬─brave───brave─┬─brave
        │       │               └─10*[{brave}]
        │       ├─brave───brave─┬─2*[brave───8*[{brave}]]
        │       │               ├─brave───26*[{brave}]
        │       │               ├─brave───23*[{brave}]
        │       │               ├─brave───21*[{brave}]
        │       │               ├─3*[brave───22*[{brave}]]
        │       │               ├─brave───25*[{brave}]
        │       │               ├─2*[brave───18*[{brave}]]
        │       │               ├─brave───24*[{brave}]
        │       │               ├─3*[brave───17*[{brave}]]
        │       │               ├─brave───19*[{brave}]
        │       │               └─brave───15*[{brave}]
        │       ├─brave───18*[{brave}]
        │       ├─brave───8*[{brave}]
        │       └─37*[{brave}]
        ├─2*[chrome_crashpad───2*[{chrome_crashpad}]]
        ├─chrome_crashpad───{chrome_crashpad}
        ├─code─┬─code───code─┬─code
        │      │             └─9*[{code}]
        │      ├─code───code─┬─code───24*[{code}]
        │      │             └─code───21*[{code}]
        │      ├─code───10*[{code}]
        │      ├─code───15*[{code}]
        │      ├─code───17*[{code}]
        │      ├─code─┬─2*[code───7*[{code}]]
        │      │      └─15*[{code}]
        │      ├─code─┬─cpuUsage.sh───sleep
        │      │      ├─zsh───pstree
        │      │      └─16*[{code}]
        │      └─39*[{code}]
        ├─dbus-broker-lau───dbus-broker
        ├─dunst───6*[{dunst}]
        ├─login───zsh───hyprland─┬─Xwayland
        │                        └─5*[{hyprland}]
        ├─polkit-gnome-au───5*[{polkit-gnome-au}]
        ├─polkitd───3*[{polkitd}]
        ├─rtkit-daemon───2*[{rtkit-daemon}]
        ├─ssh-agent
        ├─supergfxd───16*[{supergfxd}]
        ├─swaybg───2*[{swaybg}]
        ├─systemd─┬─(sd-pam)
        │         ├─at-spi-bus-laun─┬─dbus-broker-lau───dbus-broker
        │         │                 └─4*[{at-spi-bus-laun}]
        │         ├─at-spi2-registr───3*[{at-spi2-registr}]
        │         ├─dbus-broker-lau───dbus-broker
        │         ├─dconf-service───3*[{dconf-service}]
        │         ├─pipewire───2*[{pipewire}]
        │         ├─pipewire-pulse───2*[{pipewire-pulse}]
        │         ├─wireplumber───5*[{wireplumber}]
        │         ├─xdg-desktop-por───5*[{xdg-desktop-por}]
        │         ├─xdg-desktop-por───7*[{xdg-desktop-por}]
        │         ├─xdg-desktop-por───3*[{xdg-desktop-por}]
        │         ├─xdg-document-po─┬─fusermount3
        │         │                 └─6*[{xdg-document-po}]
        │         └─xdg-permission-───3*[{xdg-permission-}]
        ├─systemd-journal
        ├─systemd-logind
        ├─systemd-udevd
        ├─systemd-userdbd───3*[systemd-userwor]
        ├─tmux: server─┬─tmux-session-di
        │              └─2*[zsh]
        ├─upowerd───3*[{upowerd}]
        ├─waybar───31*[{waybar}]
        └─wpa_supplicant
```

---

``` bash
ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd
USER         PID    PPID    PGID     TID PRI STAT WCHAN  CMD
root           1       0       1       1  19 Ss   -      /sbin/init splash
root           2       0       0       2  19 S    -      [kthreadd]
root           3       2       0       3  19 S    -      [pool_workqueue_release]
root           4       2       0       4  39 I<   -      [kworker/R-rcu_gp]
root           5       2       0       5  39 I<   -      [kworker/R-sync_wq]
root           6       2       0       6  39 I<   -      [kworker/R-kvfree_rcu_reclaim]
root           7       2       0       7  39 I<   -      [kworker/R-slub_flushwq]
root           8       2       0       8  39 I<   -      [kworker/R-netns]
root          10       2       0      10  39 I<   -      [kworker/0:0H-kblockd]
root          11       2       0      11  19 I    -      [kworker/0:1-events]
root          13       2       0      13  39 I<   -      [kworker/R-mm_percpu_wq]
root          15       2       0      15  19 S    -      [ksoftirqd/0]
root          16       2       0      16  41 I    -      [rcu_preempt]
root          17       2       0      17  41 S    -      [rcub/0]
root          18       2       0      18  19 S    -      [rcu_exp_par_gp_kthread_worker/0]
root          19       2       0      19  19 S    -      [rcu_exp_gp_kthread_worker]
root          20       2       0      20 139 S    -      [migration/0]
root          21       2       0      21  90 S    -      [idle_inject/0]
root          22       2       0      22  19 S    -      [cpuhp/0]
root          23       2       0      23  19 S    -      [cpuhp/1]
root          24       2       0      24  90 S    -      [idle_inject/1]
root          25       2       0      25 139 S    -      [migration/1]
root          26       2       0      26  19 S    -      [ksoftirqd/1]
root          28       2       0      28  39 I<   -      [kworker/1:0H-events_highpri]
root          29       2       0      29  19 S    -      [cpuhp/2]
root          30       2       0      30  90 S    -      [idle_inject/2]
root          31       2       0      31 139 S    -      [migration/2]
root          32       2       0      32  19 S    -      [ksoftirqd/2]
root          33       2       0      33  19 I    -      [kworker/2:0-cgroup_free]
root          34       2       0      34  39 I<   -      [kworker/2:0H-events_highpri]
root          35       2       0      35  19 S    -      [cpuhp/3]
root          36       2       0      36  90 S    -      [idle_inject/3]
root          37       2       0      37 139 S    -      [migration/3]
root          38       2       0      38  19 S    -      [ksoftirqd/3]
root          39       2       0      39  19 I    -      [kworker/3:0-events]
root          40       2       0      40  39 I<   -      [kworker/3:0H-events_highpri]
root          41       2       0      41  19 S    -      [cpuhp/4]
root          42       2       0      42  90 S    -      [idle_inject/4]
root          43       2       0      43 139 S    -      [migration/4]
root          44       2       0      44  19 S    -      [ksoftirqd/4]
root          46       2       0      46  39 I<   -      [kworker/4:0H-events_highpri]
root          47       2       0      47  19 S    -      [cpuhp/5]
root          48       2       0      48  90 S    -      [idle_inject/5]
root          49       2       0      49 139 S    -      [migration/5]
root          50       2       0      50  19 S    -      [ksoftirqd/5]
root          51       2       0      51  19 I    -      [kworker/5:0-mm_percpu_wq]
root          52       2       0      52  39 I<   -      [kworker/5:0H-events_highpri]
root          53       2       0      53  19 S    -      [cpuhp/6]
root          54       2       0      54  90 S    -      [idle_inject/6]
root          55       2       0      55 139 S    -      [migration/6]
root          56       2       0      56  19 S    -      [ksoftirqd/6]
root          58       2       0      58  39 I<   -      [kworker/6:0H-events_highpri]
root          59       2       0      59  19 S    -      [cpuhp/7]
root          60       2       0      60  90 S    -      [idle_inject/7]
root          61       2       0      61 139 S    -      [migration/7]
root          62       2       0      62  19 S    -      [ksoftirqd/7]
root          64       2       0      64  39 I<   -      [kworker/7:0H-events_highpri]
root          65       2       0      65  19 S    -      [cpuhp/8]
root          66       2       0      66  90 S    -      [idle_inject/8]
root          67       2       0      67 139 S    -      [migration/8]
root          68       2       0      68  19 S    -      [ksoftirqd/8]
root          70       2       0      70  39 I<   -      [kworker/8:0H-events_highpri]
root          71       2       0      71  19 S    -      [cpuhp/9]
root          72       2       0      72  90 S    -      [idle_inject/9]
root          73       2       0      73 139 S    -      [migration/9]
root          74       2       0      74  19 S    -      [ksoftirqd/9]
root          75       2       0      75  19 I    -      [kworker/9:0-mm_percpu_wq]
root          76       2       0      76  39 I<   -      [kworker/9:0H-events_highpri]
root          77       2       0      77  19 S    -      [cpuhp/10]
root          78       2       0      78  90 S    -      [idle_inject/10]
root          79       2       0      79 139 S    -      [migration/10]
root          80       2       0      80  19 S    -      [ksoftirqd/10]
root          82       2       0      82  39 I<   -      [kworker/10:0H-events_highpri]
root          83       2       0      83  19 S    -      [cpuhp/11]
root          84       2       0      84  90 S    -      [idle_inject/11]
root          85       2       0      85 139 S    -      [migration/11]
root          86       2       0      86  19 S    -      [ksoftirqd/11]
root          87       2       0      87  19 I    -      [kworker/11:0-cgroup_free]
root          88       2       0      88  39 I<   -      [kworker/11:0H-events_highpri]
root          89       2       0      89  19 S    -      [cpuhp/12]
root          90       2       0      90  90 S    -      [idle_inject/12]
root          91       2       0      91 139 S    -      [migration/12]
root          92       2       0      92  19 S    -      [ksoftirqd/12]
root          94       2       0      94  39 I<   -      [kworker/12:0H-events_highpri]
root          95       2       0      95  19 S    -      [cpuhp/13]
root          96       2       0      96  90 S    -      [idle_inject/13]
root          97       2       0      97 139 S    -      [migration/13]
root          98       2       0      98  19 S    -      [ksoftirqd/13]
root         100       2       0     100  39 I<   -      [kworker/13:0H-events_highpri]
root         101       2       0     101  19 S    -      [cpuhp/14]
root         102       2       0     102  90 S    -      [idle_inject/14]
root         103       2       0     103 139 S    -      [migration/14]
root         104       2       0     104  19 S    -      [ksoftirqd/14]
root         106       2       0     106  39 I<   -      [kworker/14:0H-kblockd]
root         107       2       0     107  19 S    -      [cpuhp/15]
root         108       2       0     108  90 S    -      [idle_inject/15]
root         109       2       0     109 139 S    -      [migration/15]
root         110       2       0     110  19 S    -      [ksoftirqd/15]
root         112       2       0     112  39 I<   -      [kworker/15:0H-events_highpri]
root         113       2       0     113  19 S    -      [kdevtmpfs]
root         114       2       0     114  39 I<   -      [kworker/R-inet_frag_wq]
root         115       2       0     115  19 I    -      [rcu_tasks_kthread]
root         116       2       0     116  19 I    -      [rcu_tasks_rude_kthread]
root         117       2       0     117  19 I    -      [rcu_tasks_trace_kthread]
root         118       2       0     118  19 S    -      [kauditd]
root         119       2       0     119  19 S    -      [khungtaskd]
root         120       2       0     120  19 S    -      [oom_reaper]
root         122       2       0     122  39 I<   -      [kworker/R-writeback]
root         123       2       0     123  19 S    -      [kcompactd0]
root         124       2       0     124  14 SN   -      [ksmd]
root         125       2       0     125   0 SN   -      [khugepaged]
root         127       2       0     127  39 I<   -      [kworker/R-kblockd]
root         128       2       0     128  39 I<   -      [kworker/R-blkcg_punt_bio]
root         129       2       0     129  39 I<   -      [kworker/R-kintegrityd]
root         130       2       0     130  90 S    -      [irq/9-acpi]
root         131       2       0     131  19 I    -      [kworker/8:1-mm_percpu_wq]
root         132       2       0     132  39 I<   -      [kworker/R-tpm_dev_wq]
root         133       2       0     133  39 I<   -      [kworker/R-ata_sff]
root         134       2       0     134  39 I<   -      [kworker/R-edac-poller]
root         135       2       0     135  39 I<   -      [kworker/R-devfreq_wq]
root         136       2       0     136  90 S    -      [watchdogd]
root         138       2       0     138  39 I<   -      [kworker/3:1H-kblockd]
root         139       2       0     139  19 S    -      [kswapd0]
root         140       2       0     140  39 I<   -      [kworker/R-kthrotld]
root         141       2       0     141  90 S    -      [irq/125-pciehp]
root         142       2       0     142  90 S    -      [irq/126-pciehp]
root         143       2       0     143  39 I<   -      [kworker/R-acpi_thermal_pm]
root         144       2       0     144  19 I    -      [kworker/10:1-events]
root         147       2       0     147  19 S    -      [hwrng]
root         148       2       0     148  19 S    -      [scsi_eh_0]
root         149       2       0     149  39 I<   -      [kworker/R-scsi_tmf_0]
root         150       2       0     150  19 I    -      [kworker/7:1-mm_percpu_wq]
root         152       2       0     152  39 I<   -      [kworker/R-mld]
root         153       2       0     153  39 I<   -      [kworker/8:1H-kblockd]
root         154       2       0     154  39 I<   -      [kworker/R-ipv6_addrconf]
root         155       2       0     155  39 I<   -      [kworker/R-kstrp]
root         156       2       0     156  19 I    -      [kworker/1:1-mm_percpu_wq]
root         157       2       0     157  19 I    -      [kworker/6:2-mm_percpu_wq]
root         158       2       0     158  19 I    -      [kworker/13:1-events]
root         159       2       0     159  19 I    -      [kworker/4:1-events]
root         166       2       0     166  39 I<   -      [kworker/R-zswap-shrink]
root         167       2       0     167  39 I<   -      [kworker/u65:0-hci0]
root         169       2       0     169  19 I    -      [kworker/11:2-mm_percpu_wq]
root         172       2       0     172  39 I<   -      [kworker/0:1H-events_highpri]
root         198       2       0     198  19 I    -      [kworker/12:1-mm_percpu_wq]
root         201       2       0     201  39 I<   -      [kworker/10:1H-kblockd]
root         203       2       0     203  39 I<   -      [kworker/7:1H-kblockd]
root         206       2       0     206  39 I<   -      [kworker/13:1H-kblockd]
root         207       2       0     207  39 I<   -      [kworker/11:1H-kblockd]
root         211       2       0     211  39 I<   -      [kworker/9:1H-kblockd]
root         212       2       0     212  39 I<   -      [kworker/6:1H-kblockd]
root         213       2       0     213  19 S    -      [nv_queue]
root         214       2       0     214  19 S    -      [nv_queue]
root         215       2       0     215  19 S    -      [nv_open_q]
root         216       2       0     216  19 I    -      [kworker/7:2-events]
root         260       2       0     260  39 I<   -      [kworker/12:1H-kblockd]
root         261       2       0     261  39 I<   -      [kworker/14:1H-events_highpri]
root         262       2       0     262  39 I<   -      [kworker/1:1H-kblockd]
root         263       2       0     263  39 I<   -      [kworker/4:1H-kblockd]
root         264       2       0     264  39 I<   -      [kworker/2:1H-kblockd]
root         265       2       0     265  39 I<   -      [kworker/5:1H-kblockd]
root         266       2       0     266  39 I<   -      [kworker/15:1H-kblockd]
root         267       2       0     267  19 S    -      [nvidia-modeset/kthread_q]
root         268       2       0     268  19 S    -      [nvidia-modeset/deferred_close_kthread_q]
root         269       2       0     269  19 S    -      [UVM global queue]
root         270       2       0     270  19 S    -      [UVM deferred release queue]
root         271       2       0     271  19 S    -      [UVM Tools Event Queue]
root         272       2       0     272  90 S    -      [irq/146-nvidia]
root         273       2       0     273  19 S    -      [nvidia]
root         274       2       0     274  19 S    -      [nv_queue]
root         275       2       0     275  19 I    -      [kworker/14:1-mm_percpu_wq]
root         276       2       0     276  19 I    -      [kworker/15:1-events]
root         277       2       0     277  19 I    -      [kworker/5:1-mm_percpu_wq]
root         278       2       0     278  39 I<   -      [kworker/R-nvme-wq]
root         279       2       0     279  39 I<   -      [kworker/R-nvme-reset-wq]
root         280       2       0     280  39 I<   -      [kworker/R-nvme-delete-wq]
root         281       2       0     281  39 I<   -      [kworker/R-nvme-auth-wq]
root         293       2       0     293  19 I    -      [kworker/9:2-events]
root         368       2       0     368  19 S    -      [jbd2/nvme1n1p3-8]
root         369       2       0     369  39 I<   -      [kworker/R-ext4-rsv-conversion]
root         411       1     411     411  19 Ss   -      /usr/lib/systemd/systemd-journald
root         425       1     425     425  19 Ss   -      /usr/lib/systemd/systemd-userdbd
root         429       2       0     429  41 S    -      [psimon]
root         449       1     449     449  19 Ss   -      /usr/lib/systemd/systemd-udevd
root         452       2       0     452  41 S    -      [psimon]
root         510       2       0     510  19 I    -      [kworker/14:2-cgroup_free]
root         511       2       0     511  19 I    -      [kworker/12:2-pm]
root         568       2       0     568  90 S    -      [irq/193-mei_me]
root         578       2       0     578  19 I    -      [kworker/u64:6-events_unbound]
root         581       2       0     581  39 I<   -      [kworker/R-cfg80211]
root         583       2       0     583  19 I    -      [kworker/10:2-events]
root         586       2       0     586  90 S    -      [irq/194-ELAN06FA:00]
root         591       2       0     591  19 I    -      [kworker/8:2-mm_percpu_wq]
root         602       2       0     602  19 I    -      [kworker/0:2-events]
root         612       2       0     612  90 S    -      [irq/196-iwlwifi:default_queue]
root         613       2       0     613  90 S    -      [irq/197-iwlwifi:queue_1]
root         614       2       0     614  90 S    -      [irq/198-iwlwifi:queue_2]
root         615       2       0     615  90 S    -      [irq/199-iwlwifi:queue_3]
root         616       2       0     616  90 S    -      [irq/200-iwlwifi:queue_4]
root         617       2       0     617  90 S    -      [irq/201-iwlwifi:queue_5]
root         618       2       0     618  90 S    -      [irq/202-iwlwifi:queue_6]
root         619       2       0     619  90 S    -      [irq/203-iwlwifi:queue_7]
root         620       2       0     620  90 S    -      [irq/204-iwlwifi:queue_8]
root         621       2       0     621  90 S    -      [irq/205-iwlwifi:queue_9]
root         622       2       0     622  90 S    -      [irq/206-iwlwifi:queue_10]
root         623       2       0     623  90 S    -      [irq/207-iwlwifi:queue_11]
root         624       2       0     624  90 S    -      [irq/208-iwlwifi:queue_12]
root         625       2       0     625  90 S    -      [irq/209-iwlwifi:queue_13]
root         626       2       0     626  90 S    -      [irq/210-iwlwifi:queue_14]
root         627       2       0     627  90 S    -      [irq/211-iwlwifi:exception]
root         804       2       0     804  19 I    -      [kworker/13:2-mm_percpu_wq]
dbus         895       1     895     895  19 Ss   -      /usr/bin/dbus-broker-launch --scope system --audit
root         909       2       0     909  19 I    -      [kworker/2:2-mm_percpu_wq]
dbus         919     895     895     919  19 S    -      dbus-broker --log 10 --controller 9 --machine-id 01548ae482744d2c85df33abd2507
root         924       1     924     924  19 Ssl  -      /usr/bin/NetworkManager --no-daemon
root         925       1     925     925  19 Ssl  -      /usr/bin/supergfxd
root         926       1     926     926  19 Ss   -      /usr/lib/systemd/systemd-logind
root        1045       1    1045    1045  19 Ss   -      /usr/lib/bluetooth/bluetoothd
root        1050       2       0    1050  39 I<   -      [kworker/u65:3-hci0]
root        1051       1    1051    1051  19 Ss   -      /usr/bin/wpa_supplicant -u -s -O /run/wpa_supplicant
root        1054       1    1054    1054  19 Ss   -      login -- hinski2
root        1208       2       0    1208  19 I    -      [kworker/15:2-mm_percpu_wq]
root        1254       2       0    1254  41 S    -      [psimon]
hinski2     1256       1    1256    1256  19 Ss   -      /usr/lib/systemd/systemd --user
hinski2     1258    1256    1256    1258  19 S    -      (sd-pam)
hinski2     1265    1256    1265    1265  19 Ss   do_epo /usr/bin/dbus-broker-launch --scope user
hinski2     1266    1265    1265    1266  19 S    do_epo dbus-broker --log 11 --controller 10 --machine-id 01548ae482744d2c85df33abd250
hinski2     1267    1256    1267    1267  30 S<sl do_epo /usr/bin/pipewire
hinski2     1269    1256    1269    1269  30 S<sl poll_s /usr/bin/wireplumber
hinski2     1270    1054    1270    1270  19 Ss   sigsus -zsh
hinski2     1271    1256    1271    1271  30 S<sl do_epo /usr/bin/pipewire-pulse
rtkit       1286       1    1286    1286  18 SNsl -      /usr/lib/rtkit-daemon
polkitd     1295       1    1295    1295  19 Ssl  -      /usr/lib/polkit-1/polkitd --no-debug --log-level=notice
hinski2     1340       1    1340    1340  19 Ss   -      ssh-agent -s
root        1357       2       0    1357  29 S<   -      [krfcommd]
hinski2     1364    1256    1364    1364  19 Ssl  poll_s /usr/lib/xdg-permission-store
hinski2     1378    1270    1378    1378  19 Sl+  do_epo hyprland
root        1395       2       0    1395  19 S    -      [nvidia-drm/timeline-7]
hinski2     1401    1256    1401    1401  19 Ssl  poll_s /usr/lib/dconf-service
hinski2     1411       1    1378    1411  19 Sl+  poll_s waybar
hinski2     1413       1    1378    1413  19 Sl+  poll_s swaybg -m fill -i /home/hinski2/Pictures/cat.jpg
hinski2     1415       1    1378    1415  19 Sl+  poll_s /usr/bin/python /usr/bin/blueman-applet
hinski2     1417       1    1378    1417  19 Sl+  poll_s dunst
hinski2     1423       1    1378    1423  19 Sl+  poll_s /usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1
hinski2     1444    1378    1378    1444  19 S+   do_epo Xwayland :0 -rootless -core -listenfd 76 -listenfd 77 -displayfd 115 -wm 112
hinski2     1490    1256    1490    1490  19 Ssl  poll_s /usr/lib/at-spi-bus-launcher
hinski2     1529    1490    1490    1529  19 S    do_epo /usr/bin/dbus-broker-launch --config-file=/usr/share/defaults/at-spi2/accessib
hinski2     1532    1529    1490    1532  19 S    do_epo dbus-broker --log 10 --controller 9 --machine-id 01548ae482744d2c85df33abd2507
root        1536       2       0    1536  19 S    -      [nvidia-drm/timeline-8]
hinski2     1538    1256    1538    1538  19 Ssl  poll_s /usr/lib/xdg-desktop-portal
hinski2     1539    1256    1539    1539  19 Ssl  poll_s /usr/lib/at-spi2-registryd --use-gnome-session
hinski2     1552    1256    1552    1552  19 Ssl  poll_s /usr/lib/xdg-document-portal
root        1558    1552    1558    1558  19 Ss   -      fusermount3 -o rw,nosuid,nodev,fsname=portal,auto_unmount,subtype=portal -- /r
hinski2     1563    1256    1563    1563  19 Ssl  poll_s /usr/lib/xdg-desktop-portal-gtk
hinski2     1575    1256    1575    1575  19 Ssl  futex_ /usr/lib/xdg-desktop-portal-hyprland
hinski2     1603       1    1378    1603  19 Sl+  poll_s /usr/bin/python /usr/bin/blueman-tray
root        2105       2       0    2105  19 I    -      [kworker/6:1]
root        2157       2       0    2157  19 I    -      [kworker/u64:0-kvfree_rcu_reclaim]
root        2407       1    2407    2407  19 Ssl  -      /usr/lib/upowerd
root        2817       2       0    2817  19 I    -      [kworker/u64:1-events_unbound]
root        3246       2       0    3246  19 I    -      [kworker/4:0]
root        3440       2       0    3440  19 I    -      [kworker/3:2-events]
hinski2     3635       1    1378    3635  19 Sl+  poll_s /opt/brave-bin/brave
hinski2     3637       1    3636    3637  19 Sl   do_epo /opt/brave-bin/chrome_crashpad_handler --monitor-self --monitor-self-annotatio
hinski2     3639       1    3638    3639  19 Sl   do_epo /opt/brave-bin/chrome_crashpad_handler --no-periodic-tasks --monitor-self-anno
hinski2     3645    3635    1378    3645  19 S+   poll_s /opt/brave-bin/brave --type=zygote --no-zygote-sandbox --crashpad-handler-pid=
hinski2     3646    3635    1378    3646  19 S+   do_wai /opt/brave-bin/brave --type=zygote --crashpad-handler-pid=3637 --enable-crash-
hinski2     3648    3646    1378    3648  19 S+   poll_s /opt/brave-bin/brave --type=zygote --crashpad-handler-pid=3637 --enable-crash-
hinski2     3675    3645    1378    3675  19 Sl+  futex_ /opt/brave-bin/brave --type=gpu-process --ozone-platform=wayland --render-node
hinski2     3676    3635    1378    3676  19 Sl+  futex_ /opt/brave-bin/brave --type=utility --utility-sub-type=network.mojom.NetworkSe
hinski2     3680    3648    1378    3680  19 Sl+  futex_ /opt/brave-bin/brave --type=utility --utility-sub-type=storage.mojom.StorageSe
root        3722       2       0    3722  19 S    -      [nvidia-drm/timeline-3f]
hinski2     3723    3675    1378    3723  19 S+   skb_wa /opt/brave-bin/brave --type=broker
hinski2     3753    3648    1378    3753  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     3785    3648    1378    3785  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     3971    3648    1378    3971  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     3981    3648    1378    3981  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4008    3648    1378    4008  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4019    3648    1378    4019  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4035    3648    1378    4035  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4044    3648    1378    4044  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4094    3635    1378    4094  19 Sl+  futex_ /opt/brave-bin/brave --type=utility --utility-sub-type=audio.mojom.AudioServic
hinski2     4109    3648    1378    4109  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4119    3648    1378    4119  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
root        4136       2       0    4136  19 I    -      [kworker/1:0]
hinski2     4186    3648    1378    4186  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4210    3648    1378    4210  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4219    3648    1378    4219  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4240    3648    1378    4240  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4249    3648    1378    4249  19 Sl+  futex_ /opt/brave-bin/brave --type=renderer --crashpad-handler-pid=3637 --enable-cras
hinski2     4768       1    4768    4768  19 Ss   poll_s tmux
hinski2     4769    4768    4769    4769  19 Ss+  poll_s -zsh
hinski2     4820    4768    4820    4820  19 Zs   -      [tmux-session-di] <defunct>
hinski2     4941    4768    4941    4941  19 Ss+  poll_s -zsh
hinski2     5265       1    5265    5265  19 Ssl  poll_s /opt/visual-studio-code/code .
hinski2     5299    5265    5265    5299  19 S    poll_s /opt/visual-studio-code/code --type=zygote --no-zygote-sandbox
hinski2     5300    5265    5265    5300  19 S    do_wai /opt/visual-studio-code/code --type=zygote
hinski2     5302    5300    5265    5302  19 S    poll_s /opt/visual-studio-code/code --type=zygote
hinski2     5321       1    5320    5321  19 Sl   do_epo /opt/visual-studio-code/chrome_crashpad_handler --monitor-self-annotation=ptyp
hinski2     5332    5299    5265    5332  19 Sl   poll_s /opt/visual-studio-code/code --type=gpu-process --crashpad-handler-pid=5321 --
hinski2     5337    5265    5265    5337  19 Sl   futex_ /opt/visual-studio-code/code --type=utility --utility-sub-type=network.mojom.N
root        5353       2       0    5353  19 S    -      [nvidia-drm/timeline-5e]
hinski2     5354    5332    5265    5354  19 S    skb_wa /opt/visual-studio-code/code --type=broker
hinski2     5363    5302    5265    5363  19 Sl   futex_ /opt/visual-studio-code/code --type=renderer --crashpad-handler-pid=5321 --ena
hinski2     5406    5265    5265    5406  19 Sl   futex_ /opt/visual-studio-code/code --type=utility --utility-sub-type=node.mojom.Node
hinski2     5407    5265    5265    5407  19 Sl   futex_ /opt/visual-studio-code/code --type=utility --utility-sub-type=node.mojom.Node
hinski2     5436    5265    5265    5436  19 Sl   futex_ /opt/visual-studio-code/code --type=utility --utility-sub-type=node.mojom.Node
hinski2     5624    5436    5265    5624  19 Sl   do_epo /opt/visual-studio-code/code /opt/visual-studio-code/resources/app/extensions/
hinski2     5772    5436    5265    5772  19 Sl   do_epo /opt/visual-studio-code/code /opt/visual-studio-code/resources/app/extensions/
root        5829     425     425    5829  19 S    -      systemd-userwork: waiting...
root        5830     425     425    5830  19 S    -      systemd-userwork: waiting...
root        5831     425     425    5831  19 S    -      systemd-userwork: waiting...
hinski2     5871       1    1378    5871  19 Sl+  do_epo foot
hinski2     5873    5871    5873    5873  19 Ss   sigsus /usr/bin/zsh
hinski2     5934    5873    5934    5934  19 R+   -      ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd
```