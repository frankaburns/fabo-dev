/**********************************************************************
* file:   pktanl.c
*
* Description: 
*
*   Large amounts of this code were taken from tcpdump source
*   namely the following files..
*
*   print-ether.c
*   print-ip.c
*   ip.h
*
* Compile with:
* gcc -Wall -pedantic pktanl.c -lpcap (-o foo_err_something) 
*
* Usage:
* a.out (interface) (# of packets) "filter string"
*
**********************************************************************/

#include <pcap.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <linux/if_packet.h>
#include <linux/netdevice.h>

/* tcpdump header (ether.h) defines ETHER_HDRLEN) */
#ifndef ETHER_HDRLEN 
#define ETHER_HDRLEN 14
#endif

u_int16_t 
handle_ethernet (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet);

u_char
*handle_IP (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet);

u_int16_t 
handle_arp (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet);

u_int16_t 
handle_vlan (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet);


/*
 * Structure of an internet header, naked of options.
 *
 * Stolen from tcpdump source (thanks tcpdump people)
 *
 * We declare ip_len and ip_off to be short, rather than u_short
 * pragmatically since otherwise unsigned comparisons can result
 * against negative integers quite easily, and fail in subtle ways.
 */
struct my_ip {
	u_int8_t	ip_vhl;		/* header length, version */
#define IP_V(ip)	(((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip)	( (ip)->ip_vhl & 0x0f)
	u_int8_t	ip_tos;		/* type of service */
	u_int16_t	ip_len;		/* total length */
	u_int16_t	ip_id;		/* identification */
	u_int16_t	ip_off;		/* fragment offset field */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
#define	IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
	u_int8_t	ip_ttl;		/* time to live */
	u_int8_t	ip_p;		/* protocol */
	u_int16_t	ip_sum;		/* checksum */
	struct	in_addr ip_src,ip_dst;	/* source and dest address */
};

/* looking at ethernet headers */
void 
my_callback(u_char *args, const struct pcap_pkthdr *pkthdr,const u_char *packet)
{
    u_int16_t type = handle_ethernet(args,pkthdr,packet);
    u_char   *zeroLenPkt;

    if(type == ETHERTYPE_IP) {/* handle IP packet */
        handle_IP(args,pkthdr,packet);
    } else if(type == ETHERTYPE_ARP) {/* handle arp packet */
        handle_arp(args,pkthdr,packet);
    } else if(type == ETHERTYPE_REVARP) {/* handle reverse arp packet */
    
    } else  if (type == ETHERTYPE_VLAN) {
	zeroLenPkt = &packet[2];
        handle_IP(args,pkthdr,zeroLenPkt);
    }
}

u_char
*handle_IP (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    const struct my_ip* ip;
    u_int length = pkthdr->len;
    u_int hlen,off,version;
    int i, j, k;

    int len, tabs;

    /* jump pass the ethernet header */
    ip = (struct my_ip*)(packet + sizeof(struct ether_header));
    length -= sizeof(struct ether_header); 

    /* check to see we have a packet of valid length */
    if (length < sizeof(struct my_ip))
    {
        printf("truncated ip %d\n",length);
        return NULL;
    }

    len     = ntohs(ip->ip_len);
    hlen    = IP_HL(ip); /* header length (32 bit Words)*/
    version = IP_V(ip);/* ip version */

    /* check version */
    if(version != 4)
    {
      fprintf(stdout,"Unknown version %d\n",version);
      return NULL;
    }

    /* check header length */
    if(hlen < 5 )
    {
        fprintf(stdout,"bad-hlen %d \n",hlen);
    }

    /* see if we have as much packet as we should */
    if(length < len)
        printf("\ntruncated IP - %d bytes missing\n",len - length);

    /* Check to see if we have the first fragment */
    /* aka no 1's in first 13 bits */  
    off = ntohs(ip->ip_off);
    if((off & 0x1fff) == 0 ) { /* print SOURCE DESTINATION hlen version len offset */
        fprintf(stdout,"IP, Protocol: %d\n", ip->ip_p);
        fprintf(stdout,"Src: %s \n", inet_ntoa(ip->ip_src));
        fprintf(stdout, "Dst: %s\n", inet_ntoa(ip->ip_dst));
        fprintf(stdout, "Header Length: %d, Version: %d\nPacket Length: %d Fragment Flag: %d\n",
                hlen,version,len,off);
    }

    /* print the IP Header (HEX & Ascii)  */
    fprintf (stdout, "IP Header:");
    for (j=0, i=sizeof(struct ether_header); j<hlen*4; i++, j++) {
      if (!(j%8)) {
         if (j==0) {
           fprintf (stdout, "\n");
         } else {
           fprintf (stdout, "\t\"");
           for (k=i-8; k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
           fprintf (stdout, "\"\n");
         }
      }
      fprintf (stdout, "%02x ", packet[i]);
    }

    /* calculate the number of tabs for last line */
    if (j%8) {
       tabs = ((8 - j%8)/2)+1;
       for (k=0; k<tabs; k++) fprintf (stdout, "\t");
       fprintf (stdout, "\"");
       for (k=i-(j%8); k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
       fprintf (stdout, "\"\n\n");
    } else {
       fprintf (stdout, "\n\n");
    }

    /* print the IP Data (HEX & Ascii)  */
    fprintf (stdout, "\nIP Data:");
    for (j=0, i=sizeof(struct ether_header)+hlen*4; i<length; i++, j++) {
      if (!(j%8)) {
         if (j==0) {
           fprintf (stdout, "\n");
         } else {
           fprintf (stdout, "\t\"");
           for (k=i-8; k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
           fprintf (stdout, "\"\n");
         }
      }
      fprintf (stdout, "%02x ", packet[i]);
    }

    /* calculate the number of tabs for last line */
    if (j%8) {
       tabs = ((8 - j%8)/2)+1;
       for (k=0; k<tabs; k++) fprintf (stdout, "\t");
       fprintf (stdout, "\"");
       for (k=i-(j%8); k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
       fprintf (stdout, "\"\n\n");
    } else {
       fprintf (stdout, "\n\n");
    }
}

/* handle ethernet packets, much of this code gleaned from
 * print-ether.c from tcpdump source
 */
u_int16_t 
handle_ethernet (u_char *args, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    int   i, j, k;
    int   tabs, len;

    u_int caplen = pkthdr->caplen;
    u_int length = pkthdr->len;

    u_short ether_type;

    struct iphdr        *iphead=NULL;
    struct ether_arp    *arphead=NULL;
    struct ether_header *eptr;  /* net/ethernet.h */

    if (caplen < ETHER_HDRLEN) {
        fprintf(stdout,"Packet length less than ethernet header length\n");
        return -1;
    }

    /* lets start with the ether header... */
    eptr = (struct ether_header *) packet;
    ether_type = ntohs(eptr->ether_type);

    /* Lets print SOURCE DEST TYPE LENGTH */
    fprintf(stdout,"ETH: \n");
    fprintf(stdout,"Src: %s \n"
            ,ether_ntoa((struct ether_addr*)eptr->ether_shost));
    fprintf(stdout,"Dst: %s \n"
            ,ether_ntoa((struct ether_addr*)eptr->ether_dhost));

    /* print the IP Header (HEX & Ascii)  */
    fprintf (stdout, "\nETHER Header - Packet Length: %d\n",length);
    for (j=0, i=0; j<ETHER_HDRLEN; i++, j++) {
      if (!(j%8)) {
         if (j==0) {
           fprintf (stdout, "\n");
         } else {
           fprintf (stdout, "\t\"");
           for (k=i-8; k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
           fprintf (stdout, "\"\n");
         }
      }
      fprintf (stdout, "%02x ", packet[i]);
    }

    /* calculate the number of tabs for last line */
    if (i%8) {
       tabs = ((8 - i%8)/2)+1;
       for (k=0; k<tabs; k++) fprintf (stdout, "\t");
       fprintf (stdout, "\"");
       for (k=i-(i%8); k<i; k++) fprintf (stdout, "%c", isgraph(packet[k]) ? packet[k] : 46);
       fprintf (stdout, "\"\n\n");
    } else {
       fprintf (stdout, "\n\n");
    }



    /* check to see if we have an ip packet */
    if (ether_type == ETHERTYPE_IP) {
        fprintf(stdout,"(IP)");
    } else  if (ether_type == ETHERTYPE_ARP) {
        fprintf(stdout,"(ARP)");
    } else  if (ether_type == ETHERTYPE_REVARP) {
        fprintf(stdout,"(REVARP)");
    } else  if (eptr->ether_type == ETHERTYPE_VLAN) {
        fprintf(stdout,"(VLAN)");
    }else {
        fprintf(stdout,"(?) Ether Type: %d\n", ether_type);
        for ( i=ETHER_HDRLEN; i<length; i++) {
          if (!(i%8)) fprintf (stdout, "\n");
          fprintf (stdout, "%02x ", packet[i]);
        }
        fprintf (stdout, "\n\n");
    }


    return ether_type;
}

/* handle arp packets
 */
u_int16_t
handle_arp (u_char *args, const struct pcap_pkthdr* pkthdr, const u_char *packet) {
    int   i, len;

    u_int caplen = pkthdr->caplen;

    u_short ether_type;

    struct ether_arp    *arphead=NULL;
    struct ether_header *eptr;  /* net/ethernet.h */

    if (caplen < ETHER_HDRLEN) {
        fprintf(stdout,"Packet length less than ethernet header length\n");
        return -1;
    }

    /* lets start with the ether header... */
    eptr = (struct ether_header *) packet;
    ether_type = ntohs(eptr->ether_type);

    arphead = (struct ether_arp *)(packet+ETH_HLEN);

    printf ("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
    printf ("Hardware type       : %s\n", 
            (ntohs (arphead->ea_hdr.ar_hrd) == 1) ? "Ethernet" : "Unknown");
    printf ("Protocol type       : %s\n",
            (ntohs (arphead->ea_hdr.ar_pro) == 0x0800) ? "IPv4" : "Unknown");
    printf ("Operation           : %s\n",
            (ntohs (arphead->ea_hdr.ar_op) == ARPOP_REQUEST) ? "ARP_REQUEST" : "ARP_REPLY");


    if( (ntohs (arphead->ea_hdr.ar_hrd) == 1) && (ntohs (arphead->ea_hdr.ar_pro) == 0x0800)) {
       printf ("Source      MAC: ");
       for (i=0;i<6;i++) printf ("%02x:", arphead->arp_sha[i]);

       printf ("\nSource       IP: ");
       for (i=0;i<4;i++) printf ("%d.", arphead->arp_spa[i]);

       printf ("\nDestination MAC: ");
       for (i=0;i<6;i++) printf ("%02x:", arphead->arp_tha[i]);

       printf ("\nDestination  IP: ");
       for (i=0;i<4;i++) printf ("%d.", arphead->arp_tpa[i]);
       printf ("\n");
    }

    fprintf (stdout, "ARP Header:");
    for ( i=0; i<pkthdr->len; i++) {
      if (!(i%8)) fprintf (stdout, "\n");
      fprintf (stdout, "%02x ", packet[i]);
    }
    fprintf (stdout, "\n\n");
}
 
/* handle vlan packets
 */
u_int16_t
handle_vlan (u_char *args, const struct pcap_pkthdr* pkthdr, const u_char *packet) {
int i;

 fprintf (stdout, "VLAN:\n");

 fprintf (stdout, "ARP Header:\n");
 for ( i=0; i<pkthdr->len; i++) {
   fprintf (stdout, "%02x ", packet[i]);
   if (i && !(i%8)) fprintf (stdout, "\n");
 }
 fprintf (stdout, "\n");
}

int main(int argc,char **argv)
{ 
    int i=0,j=0;
    char *dev = "br-test1q";
    char  errbuf[PCAP_ERRBUF_SIZE];

    pcap_t    *descr;
    pcap_if_t *alldevs;
    pcap_if_t *d;

    u_char* args = NULL;

    struct sockaddr_ll *pkt;

    struct bpf_program fp;      /* hold compiled program     */

    bpf_u_int32 maskp;          /* subnet mask               */
    bpf_u_int32 netp;           /* ip                        */

    /* Options must be passed in as a string because I am lazy */
    if(argc < 3){ 
        fprintf(stdout,"Usage: %s <interface> <numpackets> \"options\"\n",argv[0]);
        return 0;
    }
    
    /* Retrieve the device list from the local machine */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }
    
    /* Print the list */
    for(d= alldevs; d != NULL; d= d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
#if 0	
        if (d->addresses) {
            if (d->addresses->addr->sa_family == AF_PACKET) {
               pkt = (struct sockaddr_ll *)d->addresses->addr;
               printf ("  protocol  = %4x\n", (unsigned short)pkt->sll_protocol);
               printf ("  int inde  = %x\n", pkt->sll_ifindex);
               printf ("  hatype    = %4x\n", (unsigned short)pkt->sll_hatype);
               printf ("  pkttype   = %2x\n", (unsigned char)pkt->sll_pkttype);
               printf ("  sa_family = (AF_PACKET) - sockaddr->sll_addr[ ");
               for (j=0; j<pkt->sll_halen; j++)
                  printf("%2x ", (unsigned char)pkt->sll_addr[j]);
               printf (" ]\n\n");
            } else {
               printf ("  sa_family = (%d) - sockaddr->sa_data[ ",d->addresses->addr->sa_family);
               for (j=0; j<14; j++)
                  printf("%2x ", (unsigned char)d->addresses->addr->sa_data[j]);
               printf (" ]\n\n");
            }
        }
#endif
    }
    
    /* We don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);

    /* ask pcap for the network address and mask of the device */
    pcap_lookupnet(argv[1],&netp,&maskp,errbuf);

    /* open device for reading. NOTE: defaulting to
     * promiscuous mode*/
    descr = pcap_open_live(argv[1],BUFSIZ,1,-1,errbuf);
    if(descr == NULL)
    { printf("pcap_open_live(): %s\n",errbuf); exit(1); }


    if(argc > 2)
    {
        /* Lets try and compile the program.. non-optimized */
        if(pcap_compile(descr,&fp,argv[3],0,netp) == -1)
        { fprintf(stderr,"Error calling pcap_compile\n"); exit(1); }

        /* set the compiled program as the filter */
        if(pcap_setfilter(descr,&fp) == -1)
        { fprintf(stderr,"Error setting filter\n"); exit(1); }
    }

    /* ... and loop */
    pcap_loop(descr,atoi(argv[2]),my_callback,args);

    fprintf(stdout,"\nfinished\n");
    exit (0);
}
