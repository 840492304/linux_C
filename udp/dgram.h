//
// Created by Wen on 2018/3/15.
//

#ifndef LINUX_C_DGRAM_H
#define LINUX_C_DGRAM_H


int make_server_addr(int port, struct sockaddr_sin * saddr);
int make_server_udp(int port);
int make_client_udp(int port);
int get_internet_address(char * host, int len, int * prot_p, struct sockaddr_in * saddr_in);
void print_client(struct sockaddr_in  * saddr);



#endif //LINUX_C_DGRAM_H
