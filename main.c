#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<unistd.h>	//memset

#include<string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>

//own headers
#include <printPacketInfo.h>
#include <collect.h>
#include <storage.h>

const int log_to_console = true;

int start_sniffing(bool procced);

void find_available_connection();

#define SIZE_ETHERNET 14

#define BUFF_SIZE 30000

#define PROCESS_PACKET(buffer,size, self) {											\
																				\
	struct iphdr *iph = (struct iphdr*)buffer;									\
																				\
	if (iph->protocol == 1) { 													\
			++icmp; 															\
			if(log_to_console)													\
				print_icmp_packet(buffer , size);								\
	}																			\
	else if (iph->protocol == 2)												\
			++igmp;																\
	else if (iph->protocol == 6) {												\
			++tcp;																\
			if(log_to_console)													\
				print_tcp_packet(buffer , size);								\
	} else if (iph->protocol == 17) { 											\
			++udp;																\
			if (log_to_console)													\
				print_udp_packet(buffer , size);								\
	} else ++others;															\
																				\
	++total;																	\
																				\
	printf("TCP : %i   UDP : %i   ICMP : %i   IGMP : %i   Others : %i   Total : %i\r\n",tcp,udp,icmp,igmp,others,total);	\
	collect(buffer, self);														\
	log_IP_call_history(self);													\
}																				\

int main(int argc, char** argv)
{
	bool procced = true;
	
	/*
	if(argc == 3 && strcmp(argv[2], "run_menu_mode") == 0 && fork() != 0) {
		loadStat();		
		start_sniffing(procced);
		return 0;
	} else menu(&procced, start_sniffing);
	*/	
	if (true)
		find_available_connection();
	start_sniffing(procced);

}

int start_sniffing(bool procced) {

	if(!procced)
		return 1;

	int tcp, udp, icmp, others, igmp, total;
	tcp = udp = icmp = others = igmp = total = 0;

	int saddr_size , data_size;
	struct sockaddr saddr;
	struct in_addr in;
	
	unsigned char *buffer = (unsigned char *)malloc(BUFF_SIZE); //Its Big!

	printf("\nStarting...\n");
	storage * self = loadStat();	
	
	int sock_len = 12;
	int sock_raw[sock_len];


	sock_raw[0] = socket(AF_INET , SOCK_RAW , IPPROTO_UDP);
	sock_raw[1] = socket(AF_INET, SOCK_RAW , IPPROTO_TCP);
	sock_raw[2] = socket(AF_INET , SOCK_RAW , IPPROTO_ICMP); // some minor inconsistencys was detected
	sock_raw[3] = socket(AF_INET , SOCK_RAW , IPPROTO_IGMP); // so for now freezed



	if(sock_raw[1] < 0 )
	{
		printf("\nSocket Error\n");
		return 1;
	}

	for(; procced ;)
	{
        saddr_size = sizeof saddr;
		//Receive a packet
		data_size = recvfrom(sock_raw[1] , buffer , BUFF_SIZE , 0 , &saddr , &saddr_size);
		
		if(data_size <0 ) continue;
		
		PROCESS_PACKET(buffer , data_size, self);
	}
	close(*sock_raw);
	printf("Finished");
}


void find_available_connection() {
	int sock_len = 12;
	int domain[12] = {

				AF_UNIX, AF_LOCAL,  //  Local communication              unix(7)
					AF_INET,        //    IPv4 Internet protocols          ip(7)
					AF_INET6,       //     IPv6 Internet protocols          ipv6(7)
					AF_IPX,         //     IPX - Novell protocols
					AF_NETLINK,     //     Kernel user interface device     netlink(7)
					AF_X25,         //     ITU-T X.25 / ISO-8208 protocol   x25(7)
					AF_AX25,        //     Amateur radio AX.25 protocol
					AF_ATMPVC,      //     Access to raw ATM PVCs
					AF_APPLETALK,   //     AppleTalk                        ddp(7)
					AF_PACKET,      //     Low level packet interface       packet(7)
					AF_ALG,         //	  Interface to kernel crypto API
	};

	for(int i = 0; i < 12; i++)
		if(socket(domain[i]  , SOCK_RAW , IPPROTO_UDP) != -1 )
			printf("Here: i = %i\n", i);
}