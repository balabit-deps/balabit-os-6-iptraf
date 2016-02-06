/* copied from Linux ISDN subsystem for inclusion in iptraf */

/* Linux ISDN subsystem, main header
 *
 * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)
 * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg
 * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)
 * Copyright 2000-2002  by Kai Germaschewski (kai@germaschewski.name)
 * 
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

/* Packet encapsulations for net-interfaces */
#define ISDN_NET_ENCAP_ETHER      0
#define ISDN_NET_ENCAP_RAWIP      1
#define ISDN_NET_ENCAP_IPTYP      2
#define ISDN_NET_ENCAP_CISCOHDLC  3 /* Without SLARP and keepalive */
#define ISDN_NET_ENCAP_SYNCPPP    4
#define ISDN_NET_ENCAP_UIHDLC     5
#define ISDN_NET_ENCAP_CISCOHDLCK 6 /* With SLARP and keepalive    */
#define ISDN_NET_ENCAP_X25IFACE   7 /* Documentation/networking/x25-iface.txt*/
#define ISDN_NET_ENCAP_NR         8

/* New ioctl-codes */
#define IIOCNETAIF  _IO('I',1)
#define IIOCNETDIF  _IO('I',2)
#define IIOCNETSCF  _IO('I',3)
#define IIOCNETGCF  _IO('I',4)
#define IIOCNETANM  _IO('I',5)
#define IIOCNETDNM  _IO('I',6)
#define IIOCNETGNM  _IO('I',7)
#define IIOCGETSET  _IO('I',8) /* no longer supported */
#define IIOCSETSET  _IO('I',9) /* no longer supported */
#define IIOCSETVER  _IO('I',10)
#define IIOCNETHUP  _IO('I',11)
#define IIOCSETGST  _IO('I',12)
#define IIOCSETBRJ  _IO('I',13)
#define IIOCSIGPRF  _IO('I',14)
#define IIOCGETPRF  _IO('I',15)
#define IIOCSETPRF  _IO('I',16)
#define IIOCGETMAP  _IO('I',17)
#define IIOCSETMAP  _IO('I',18)
#define IIOCNETASL  _IO('I',19)
#define IIOCNETDIL  _IO('I',20)
#define IIOCGETCPS  _IO('I',21)
#define IIOCGETDVR  _IO('I',22)


typedef struct {
	char	name[10];	/* Name of interface                     */
	char	master[10];	/* Name of Master for Bundling           */
	char	slave[10];	/* Name of Slave for Bundling            */
	char	eaz[256];	/* EAZ/MSN                               */
	char	drvid[25];	/* DriverId for Bindings                 */
	int	onhtime;	/* Hangup-Timeout                        */
	int	charge;		/* Charge-Units                          */
	int	l2_proto;	/* Layer-2 protocol                      */
	int	l3_proto;	/* Layer-3 protocol                      */
	int	p_encap;	/* Encapsulation                         */
	int	exclusive;	/* Channel, if bound exclusive           */
	int	dialmax;	/* Dial Retry-Counter                    */
	int	slavedelay;	/* Delay until slave starts up           */
	int	cbdelay;	/* Delay before Callback                 */
	int	chargehup;	/* Flag: Charge-Hangup                   */
	int	ihup;		/* Flag: Hangup-Timeout on incoming line */
	int	secure;		/* Flag: Secure                          */
	int	callback;	/* Flag: Callback                        */
	int	cbhup;		/* Flag: Reject Call before Callback     */
	int	pppbind;	/* ippp device for bindings              */
	int	chargeint;	/* Use fixed charge interval length      */
	int	triggercps;	/* BogoCPS needed for triggering slave   */
	int	dialtimeout;	/* Dial-Timeout                          */
	int	dialwait;	/* Time to wait after failed dial        */
	int	dialmode;	/* Flag: off / on / auto                 */
} isdn_net_ioctl_cfg;




/* end of copied part */


struct isdntabent {
    char ifname[10];
    unsigned int encap;
    struct isdntabent *next_entry;
};

struct isdntab {
    struct isdntabent *head;
    struct isdntabent *tail;
};

void add_isdn_entry(struct isdntab *list, char *ifname, int isdn_fd);
struct isdntabent *isdn_table_lookup(struct isdntab *list, char *ifname,
                                     int isdn_fd);
void destroy_isdn_table(struct isdntab *list);
