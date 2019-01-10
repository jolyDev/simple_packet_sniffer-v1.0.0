#pragma once

#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<unistd.h>	//memset

#include<string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <stdbool.h>

//own headers
#include <printPacketInfo.h>
#include <collect.h>

const int log_to_console = true;

int start_sniffing(bool procced);

#define SIZE_ETHERNET 14

#define BUFF_SIZE 30000

#define PROCESS_PACKET(buffer,size) {											\
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
	collect(buffer);															\
	log_IP_call_history();														\
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
	loadStat();		
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

	int sock_len = 4;
	int sock_raw[sock_len];

	// @TODO create own thread for each

	sock_raw[0] = socket(AF_INET , SOCK_RAW , IPPROTO_UDP);
	sock_raw[1] = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
	sock_raw[2] = socket(AF_INET , SOCK_RAW , IPPROTO_ICMP); // some minor inconsistencys was detected
	sock_raw[3] = socket(AF_INET , SOCK_RAW , IPPROTO_IGMP); // so for now freezed


	if(sock_raw[0] < 0 || sock_raw[1] < 0)
	{
		printf("Socket Error\n");
		return 1;
	}

	for(; procced ;)
	{
        saddr_size = sizeof saddr;
		//Receive a packet
		data_size = recvfrom(sock_raw[1] , buffer , BUFF_SIZE , 0 , &saddr , &saddr_size);
		
		if(data_size <0 ) continue;
		
		PROCESS_PACKET(buffer , data_size);
	}
	close(sock_raw);
	printf("Finished");
}