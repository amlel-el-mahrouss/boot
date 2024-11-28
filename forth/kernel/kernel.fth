( *	mp-boot )
( * Copyright Amlal El Mahrouss, all rights reserved. )

0 0 ." mp-boot firmware, (c) Amlal El Mahrouss" . cr draw-text-pos

( * load MP Boot Sector partition )
0 1024 load-from-any-drive

( * goto interpreter if epm not found. )
load-boot-interpreter

( * reboot if exit )
reboot-machine