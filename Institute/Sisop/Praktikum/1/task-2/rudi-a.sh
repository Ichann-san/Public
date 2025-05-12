#!/bin/bash

# ip address
awk '
/192.168.1.1/ { ++x }
/192.168.1.2/ { ++y }
/192.168.1.3/ { ++z }
END { print "Total request yang dibuat oleh pengguna dengan IP Address\n192.168.1.1 :", x, "kali\n192.168.1.2 :", y, "kali\n192.168.1.3 :", z, "kali" }' access.log

# status codes
awk '
/200/ { ++a }
/302/ { ++b }
/404/ { ++c }
/500/ { ++d }
END { print "Jumlah Status Code\n200 :", a, "\n302 :", b, "\n404 :", c, "\n500 :", d}' access.log

# path access.log dapat diubah tergantung dengan tempat disimpannya file
