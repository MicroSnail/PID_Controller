# PID_Controller

Here you will find a Vivado project for a PID controller as well as associated C code that is used to set the parameters.

To compile the Verilog code, you will need:
  Xilinx [Vivado 2016.2](http://www.xilinx.com/support/download.html) FPGA development tools. The SDK (bare metal toolchain) must also be installed, be careful during the install process to select it. Preferably use the default install location.



The C code can be compiled in Linux using the following command:
```
arm-linux-gnueabihf-gcc -g -std=gnu99 -Wall -Werror -lm    pidctrl.c  -o pidctrl
```
  (`arm-linux_gnueabihf-gcc` came with the installation of Vivado)
  (I am not sure yet)
