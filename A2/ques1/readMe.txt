First used fork() to create a child process S1 and saved it's pid in local variable ps1.
Then we registered a signal handler for SIGTERM for S1 in if(ps1 == 0) block using sigaction and set sa_flag = SA_SIGINFO and assigning 
a pointer to the handler function in sa_sigaction (instead of sa_handler) as later we will require to send data to this process using signals.
We also use the handler function which takes three arguements (void handler(int sig, siginfo_t *info, void *ucontext)). 
Then we fork two more processes SR and ST and use execvp() system call to send pid of S1 to them as an arguement 
(after converting it to string) in a null terminated args array which can be retrieved from char *argv[] in main.
We store the retrieved pid (after converting it into int) in a global variable for both e1 and e2 programs.
In both e1 nad e2 we register a signal handler for SIGALRM using sugaction and set timers at intervals of one second using setitimer()
which sets a timer that when expires sends a signal to the process and restarts the timer. First arguement passed to setitimer() is 
ITIMER_REAL as it decrements in real time, and delivers SIGALRM upon expiration and the second arguement is pointer to struct itimerval and third arguement is null.
After this in functionality of SR we use inline assembly to read a random number from CPU using RDRAND instruction, the command used is
__asm__ volatile("rdrand %0"  : "=r" (number)) which means an instruction to read random no. from cpu and store it in rax which is %0 as 
an input/output operand is designated as %N where the N is the number of operand from left to right beginning from zero and we only have one operand.
The second part of the our assembly statement is located after the : symbol and contains the definition of the output value 
where the constraint is r and the = symbol is modifier which denotes output value. We get our no. in number variable.
After this we pass the random no. to S1 along with SIGTERM signal using sigqueue and assigning the no. to sival_int field in union sigval
which is passed as third arguement to sigqueue.
Then in functionality of ST we read the CPU timestamp counter (using inline assembly to run RDTSC instruction) using 
__asm__ volatile("rdtsc\t\n" "shl $32 , %%rdx\t\n" "xor %%rdx , %0\t\n" : "=a" (nr) : : "%rdx") where rdtsc reads first 32 bits into 
edx and next 32 bits into eax so after rdtsc we shift rdx register left by 32 bits and the xor rdx and rax (given by %0) so we get the
entire 32 bits in rax(which is the destination operand and xor stores ans in destination operand) and finally we get our timestamp (no of cpu cycles sinse reboot)
in nr variable as the constraint is a which is for rax, rdx is specified as a clobber (register whose content will be modified by the assembler code).
We get our cpu frequency using $ cat /proc/cpuinfo | grep MHz command which comes out to be 2592 MHz.
We divide nr(no of cpu cycles since reboot) by cpu frequency to get number of seconds since reboot and further convert them into min, hours, dats, years.
We pass the total no. of seconds since reboot to S1 along with SIGTERM signal using sigqueue.
The main process sleeps for 7 seconds after which it sends SIGINT signal to SR and ST to terminate them.