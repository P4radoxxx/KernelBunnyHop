# KernelR4ptor
IOCTL Windows kernel driver

This is a Kernel driver using IOCTL codes to wich communicate with a usermode client.

Main purpose was to modify memory directly from kernel space to avoid populars anti-cheat detection.
It could serve as a base for a more complex hack, as for now it was tested on CSGO and was working fine,
there's only one hack that disable the flash effect, but the offsets are most likely oudated by now, so
they need to be updated.

it's unsigned of course, but you can still use GDRV Loader to test it, or write your own loader if you wanna stay undetected.

Have fun.
