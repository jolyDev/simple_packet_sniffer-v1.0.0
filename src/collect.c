#include <collect.h>

void collect(unsigned char* Buffer) {
	unsigned short iphdrlen;
		
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen =iph->ihl*4;
	
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph->daddr;
	

	struct IP_entry * el = get_IP_entry(inet_ntoa(source.sin_addr));
    
    if(el != NULL)	el->entry++;
    else 			add_IP_entry(createNewIP_entry( inet_ntoa(source.sin_addr), 0));
}