cmd_/home/debian/userBuffer/modules.order := {   echo /home/debian/userBuffer/My_SPI_Driver.ko; :; } | awk '!x[$$0]++' - > /home/debian/userBuffer/modules.order
