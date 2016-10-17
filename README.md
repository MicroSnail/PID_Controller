# PID_Controller

## Current Stage:
You can use set $K_{p,i,d}$

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
0. Some preparations
Connect to the same network as the RP (so that your computer and RP are going through the same router). Note the IP address of RP. (In the lab we have ``192.168.1.7``)

Under Windows, one can transfer files to RP with [WinScp](https://winscp.net/eng/download.php) and login the Linux on RP with [PuTTY](http://www.putty.org/).

Under Linux, one can transfer files by `scp <local_filename> root@192.168.1.7:~/tmp/` (Assuming `~/tmp/` exists)
and login the Linux on RP with `ssh root@192.168.1.7`. (password is written on the ethernet socket sticker)

1. Generate and copy a bitstream file to the Linux system running on RP.
Use Vivado to open `PID_controller.xpr`. Click the **Generate Bitstream** button on the **Flow Navigator** panel or goto **Flow-->Generate Bitstream**. The resulting bit file will be available at `<project_dir>/PID_controller.runs/impl_1/*.bit`

2. Load the bitstream file to the FPGA
3. 
