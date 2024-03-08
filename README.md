# LKS32MC07x_CMake_Template
A template project for LKS32MC07x with CMake  

This project contains the Standard library for LKS32MC07x from Linko Semiconductor (or LKSMCU), and a simple blinky/UART printing example.

I know nothing about Assembly, so I transplanted the startup file and the link script file with the reference of those for STM32, so there might be some bug which I haven't found yet.  

You can flash and debug the chip using pyOCD.

* Make sure pyOCD is installed, which can be done by `pip install pyocd`.
* Copy everything *under* [Pack](./Pack) folder to the pack folder of pyOCD, which is `%appdata%\..\Local\cmsis-pack-manager\cmsis-pack-manager\` in Windows.
* Merge the target config from [index_lks32mc07x.json](./index_lks32mc07x.json) into the target index file of pyOCD, which is `%appdata%\..\Local\cmsis-pack-manager\cmsis-pack-manager\index.json` in Windows.
* Run `pyocd pack install lks32mc07x` to update the pack index.
* Connect the board and run `pyocd erase --chip --target lks32mc074dof8q8` in the project folder to see if it works properly.