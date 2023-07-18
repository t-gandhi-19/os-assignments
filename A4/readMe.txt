We statically created the semaphores empty and full and mutex using DEFINE_MUTEX() and also globally
define a long pointer representing the queue and two integers both initialised to zero.
Then in initialK system call we allocate memory using kmalloc() and GFP_KERNEL flag then 
we initialise semaphores using sema_init() with full start value as zero and empty
start value as size of buffer(queue) and mutex using mutex_init(). 
We will use mutex to create critical section when we enqueue and dequeue from the queue
and other two semaphores to keep track of full and empty slots in queue.
Then in writer system call we down empty and aquire mutex lock() and after enqueing
we unlock mutex and up full. We first down empty to show that number of empty slots is decreased
and then after enqueing we do up full to keep track that no. of full slots increased by one.
In reader system call we down full then aquire mutex , read from queue and copy it to user
and then unlock mutex and up empty. This all is done in kernel/sys.c 
The kernel data sructure used are mutex and counting semaphore which keep track of no. of
empty and full slots and also a long pointer for queue.