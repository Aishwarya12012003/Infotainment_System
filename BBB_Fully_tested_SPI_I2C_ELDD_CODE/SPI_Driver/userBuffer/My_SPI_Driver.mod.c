#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3726c6aa, "module_layout" },
	{ 0x77abe509, "cdev_del" },
	{ 0x2f31c9f4, "cdev_init" },
	{ 0xd39fa6ab, "__kfifo_alloc" },
	{ 0x98171fcf, "device_destroy" },
	{ 0xd0ed61a3, "__spi_register_driver" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x5f754e5a, "memset" },
	{ 0x4578f528, "__kfifo_to_user" },
	{ 0xc5850110, "printk" },
	{ 0x84be1006, "driver_unregister" },
	{ 0x8781d48, "device_create" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0xd8d9e769, "spi_sync" },
	{ 0x83c50091, "cdev_add" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xdb760f52, "__kfifo_free" },
	{ 0x5abf8d2b, "class_destroy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xf23fcb99, "__kfifo_in" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x7e2e8c4d, "spi_unregister_device" },
	{ 0xbf451cca, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("spi:SPI_LCD");
MODULE_ALIAS("of:N*T*CSPI_LCD");
MODULE_ALIAS("of:N*T*CSPI_LCDC*");
