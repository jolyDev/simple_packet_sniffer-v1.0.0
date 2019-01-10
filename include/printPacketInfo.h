#pragma once

#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc

/*secondary*/
#include<string.h>	//memset
//#include <pcap.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <stdbool.h>

#include<netinet/ip_icmp.h>	//Provides declarations for icmp header
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/tcp.h>	//Provides declarations for tcp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>

// typedef unsigned char unsigned char

struct sockaddr_in source,dest;

/* IP header */
struct sniff_ip {
	unsigned char  ip_vhl;                 /* version << 4 | header length >> 2 */
	unsigned char  ip_tos;                 /* type of service */
	unsigned short ip_len;                 /* total length */
	unsigned short ip_id;                  /* identification */
	unsigned short ip_off;                 /* fragment offset field */
	#define IP_RF 0x8000            /* reserved fragment flag */
	#define IP_DF 0x4000            /* dont fragment flag */
	#define IP_MF 0x2000            /* more fragments flag */
	#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
	unsigned char  ip_ttl;                 /* time to live */
	unsigned char  ip_p;                   /* protocol */
	unsigned short ip_sum;                 /* checksum */
	struct  in_addr ip_src,ip_dst;  /* source and dest address */
};

void print_ip_header(unsigned char* , int);
void print_tcp_packet(unsigned char* , int);
void print_udp_packet(unsigned char * , int);
void print_icmp_packet(unsigned char* , int);
void PrintData (unsigned char* , int);