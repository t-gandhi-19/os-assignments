FIFO
Created 2D char array to store random strings generated using rand() func to give values between 0 and 25 
which were added to 'A' to generate random chars. Then created a structure (data) for storing and int and a char * to 
store random string and it's index.
Created two fifos using mkfifo() with read,write and execute permission for all(0777) and 
for p1 opened one with write only and other with read only permission and for p2 did the opposite.
Then from p1 write 5 string and their indexes using sprintf and write() system call which are read from p2
using read() system call and using strtok_r() and delimiter as " " we iterate over the buffer read and find
the last index and send it to p2 using write() and p1 reads it using read() and increments the counter(the read index)
and send the next five string again.
Finally we close and remove the fifos using close() and remove().

Message Queue
Created 2D char array to store random strings generated using rand() func to give values between 0 and 25 
which were added to 'A' to generate random chars. Then created a structure (data) for storing and int and a char * to 
store random string and it's index.
Then created another structure pirate_msgbuf and instance of it (message). This structure stores a long type and 5 data struct types.
We get a key using ftok() and then we create a messgage queue using msgget(). Then we assign a positive number to message struct long mytpe
and also assign random strings and index from 2d array. Then we send the message from p1 using msgsnd() and p2 receives the message in 
it's message struct which was previously null using msgrcv() and the fourth arguement same as that of the mtype. Then p2 sends back the last index 
recieved using struct index_back sendBack and msgsnd() which is recieved by p2 using msgrcv() and the next five strings are send.
Lastly we delete the message queue using msgctl()send.

Socket 
Created 2D char array to store random strings generated using rand() func to give values between 0 and 25 
which were added to 'A' to generate random chars. Then created a structure (data) for storing and int and a char * to 
store random string and it's index.
Then we call socket() system call with the second argument as SOCK_STREAM to create a stream socketuse and unlink() to remove the socket if it already exists.
Then we bind the socket descriptor from socket() system call to an address in the Unix domain using bind() and use listen() to listen for incoming connections.
The second argument to listen() is 1 is the number of incoming connections that can be queued. Then we call accept() to accept a connection 
from a client and return another socket descriptor s2. Then we send the five strings with their indexes using sprintf() and send() system call.
In p2 we call socket() to get a Unix domain socket and use connect() to connect to with second arguement as struct sockaddr_un with the remote address. 
Once connected we use recv() to recieve the string and iterate through them using strtok_r() with delimiter as " " and get the last index and send it to
p1 using send() and p1 recieves it using recv().
Finally we close the socket using close() system call.

The data structures used is struct which is like a union to hold variables of different data types together.
other data structure used in 2d char array which is like an array of strings.