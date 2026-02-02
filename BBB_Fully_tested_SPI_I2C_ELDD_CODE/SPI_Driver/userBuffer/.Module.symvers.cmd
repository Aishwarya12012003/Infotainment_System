cmd_/home/debian/userBuffer/Module.symvers := sed 's/ko$$/o/' /home/debian/userBuffer/modules.order | scripts/mod/modpost -m    -o /home/debian/userBuffer/Module.symvers -e -i Module.symvers   -T -
