# PID_Controller

Here you will find a Vivado project for a PID controller as well as associated C code that is used to set the parameters.

To compile the Verilog code, you will need:
  Xilinx [Vivado 2016.2](http://www.xilinx.com/support/download.html) FPGA development tools. The SDK (bare metal toolchain) must also be installed, be careful during the install process to select it. Preferably use the default install location.

The C code can be compiled in Linux using the following command:
```
arm-linux-gnueabihf-gcc -g -std=gnu99 -Wall -Werror -lm    pidctrl.c  -o pidctrl
```
  (`arm-linux_gnueabihf-gcc` came with the installation of Vivado)
  (I haven't tried compiling the C code under Windows yet, but there should be some easy ways to do so.)

# How to Operate the PID Controller on Red Pitaya (RP)
0. Generate and copy a bitstream file to the Linux system running on RP.
Connect to the same network as the RP (so that your computer and RP are going through the same router). Note the IP address of RP. (In the lab we have ``192.168.1.7``)

1. Load the bitstream file to the FPGA
2. 
