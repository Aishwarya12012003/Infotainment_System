cmd_/home/debian/lcd_driver2/Driver_code/modules.order := {   echo /home/debian/lcd_driver2/Driver_code/main.ko; :; } | awk '!x[$$0]++' - > /home/debian/lcd_driver2/Driver_code/modules.order
