
all: p1_msg p2_msg p1_fifo p2_fifo p1_socket p2_socket
 
p1_msg: msg_p1.c
    gcc -o msg_p1 msg_p1.c
 
p2_msg: msg_p2.c
    gcc -o msg_p2 msg_p2.c
 
p1_fifo: fifo_p1.c
    gcc -o fifo_p1 fifo_p1.c
 
p2_fifo: fifo_p2.c
    gcc -o fifo_p2 fifo_p2.c
 
p1_socket: sock_p1.c
    gcc -o sock_p1 sock_p1.c
 
p2_socket: sock_p2.c
    gcc -o sock_p2 sock_p2.c
 
clean:
    rm -r echo_socket
