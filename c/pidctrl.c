#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int map_registers(int *fd, void **hk, int hk_addr, int hk_size) 
{
   if ((*fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
      fprintf(stderr, "Error: could not open /dev/mem!\n");
      return -1;
   }

   if ((*hk = mmap(NULL, hk_size, PROT_READ | PROT_WRITE, 
      MAP_SHARED, *fd, hk_addr)) == (void *) -1) {
      
      fprintf(stderr, "Error: could not map memory to file!\n");
      return -1;
   }

   return 0;
}

int clean_up(int fd) 
{
   if (close(fd) < 0) {
      fprintf(stderr, "Error: could not close map file!\n");
      return -1;
   }
   return 0;
}

void printBin(unsigned n)
{
   unsigned i;
   for (i = 1 << (8-1); i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
   printf("\n");
}


int bin2dec(char* binNum) 
{
   char *a = binNum;
   int num = 0;
   do {
       int b = *a=='1'?1:0;
       num = (num<<1)|b;
       a++;
   } while (*a);
   return num;
}


int main(int argc, char** argv) 
{
   
   // const int housekeeping_base_addr = 0x40000000;
   // const int housekeeping_size      = 0x00100000;

   const int pid_base_addr = 0x40300000;
   const int pid_size = 0x00100000;


   /*static volatile struct housekeeping_control_s {
      uint32_t id;
      uint32_t dna_lo;
      uint32_t dna_hi;
      uint32_t digital_loop;
      uint32_t ex_cd_p;
      uint32_t ex_cd_n;
      uint32_t ex_co_p;
      uint32_t ex_co_n;
      uint32_t ex_ci_p;
      uint32_t ex_ci_n;
      uint32_t reserved_2;
      uint32_t reserved_3;
      uint32_t led_control;
   } *hk;*/

   // uint32_t volatile *hk = NULL;
   uint32_t volatile *pid = NULL;
   // int map_file_hk = 0;
   int map_file_pid = 0;

   // char * testNum = "";
   int setpoint = 0;
   int kp = 0;
   int ki = 0;
   int kd = 0;
   int useManualSp;

   if (argc >= 6) {
      // testNum = argv[1];
      kp = atoi(argv[1]);
      ki = atoi(argv[2]);
      kd = atoi(argv[3]);
      useManualSp = atoi(argv[4]);
      setpoint = atoi(argv[5]);

      printf("kp = %d\n", kp);
      printf("ki = %d\n", ki);
      printf("kd = %d\n", kd);
      printf("setpoint = %d\n", setpoint);
   }

   // map_registers(&map_file_hk, (void **) &hk, housekeeping_base_addr, housekeeping_size);

   map_registers(&map_file_pid, (void **) &pid, pid_base_addr, pid_size);

   //PID11 integrator reset active low?
   *(pid + 0x00) = 0;

   // PID11 set point
   *(pid + 0x04) = setpoint;
   // PID11 Kp   
   *(pid + 0x05) = kp;
   // PID11 Ki
   *(pid + 0x06) = ki;
   // PID11 Kd
   *(pid + 0x07) = kd;
   // sp_manual 
   *(pid + 0x14) = useManualSp;

   getchar();
 

   /* Set PID parameters back to all 0 */
   // PID11 set point
   *(pid + 0x04) = 0;
   // PID11 Kp   
   *(pid + 0x05) = 0;
   // PID11 Ki
   *(pid + 0x06) = 0;
   // PID11 Kd
   *(pid + 0x07) = 0;
   //PID11 integrator reset active low?
   *(pid + 0x00) = 1;

   // clean_up(map_file_hk);
   clean_up(map_file_pid);

   return 0;
}