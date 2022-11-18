First added system call at the end of system call table in the common section so our system call is same for both architectures (64 bit and 32 bit).
The number assigned to the syscall is 448 and it's name is kernel_2d_memcpy.
Then we defined the system call (what it will do) in sys.c file in kernel/ which is where miscellaneous system calls are stored. 
For the sytem call's definition we use SYSCALL_DEFINEN family of macros where N stands for no. of arguements,
We have N = 4 as our system call takes 4 arguements. The first arguement for the macro is the system call name and the rest 4 arguements
are float * pointing to 2D array we are copying from, float * pointing to 2D array we are copying to , no. of rows (int) and no. of colums (int).
As kernel must never blindly follow a pointer into user-space because it can lead to the process tricking the kernel into reading someone 
else's data or reading data in kernel-space on it's behalf therefore we use __copy_to_user() and __copy_from_user() which are provided by the kernel 
for performing the requisite checks on pointers and the desired copy to and from user-space. 
We pass the appropriate arguements to them and the third arguement for both of them which is no. of bytes to copy, we pass 
(no. of rows)*(no. of colums)*sizeof(float). In case of sucess they return 0 and in case of an error
they return no. of bytes they failed to copy which we use in our code for error checking errors and returning -EFAULT as it is standard for 
system calls to return -EFAULT in case of an error. In case of success our system calls returns 0 and 2D array is copied.
After this we compile our kernel using appropriate make commands and finally we test our code using test.c file ehich has the two 2D matrices
hard-wired and copies one to another using our system call and prints them and the value returned by our system call.
The GNU C library provides the syscall() function for us which can call any system call by number (448) which we use for our testing code.