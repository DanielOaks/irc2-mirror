/************************************************************************
 *   IRC - Internet Relay Chat, include/config.h
 *   Copyright (C) 1990 Jarkko Oikarinen
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: config.h,v 6.1 1991/07/04 21:04:27 gruner stable gruner $
 *
 * $Log: config.h,v $
 * Revision 6.1  1991/07/04  21:04:27  gruner
 * Revision 2.6.1 [released]
 *
 * Revision 6.0  1991/07/04  18:05:00  gruner
 * frozen beta revision 2.6.1
 *
 */

/* Type of host */

#define BSD		1	/* 4.2 BSD, 4.3 BSD, SunOS 3.x, 4.x, Apollo */
#define HPUX		0	/* HP-UX */
#define ULTRIX		0	/* Vax Ultrix. */
#define AIX             0       /* IBM ugly so-called Unix, AIX */
#define MIPS            0       /* MIPS Unix */

/* Do these work? I dunno... */

#define SYSV		0	/* Does not work yet. Under construction */
#define VMS		0	/* Should work for IRC client, not server */
#define MAIL50		0	/* If you're running VMS 5.0 */
#define RSUMMON		0	/* Remote summon feature --does not work */

/*
 * The following are additional symbols to define. If you are not
 * sure about them, leave them all defined as they are.
 */

/*
 * If you get loader errors about unreferenced function calls, you must
 * define the following accordingly:
 */
#if NEXT || HPUX
#define NEED_STRERROR   0
#else
#define NEED_STRERROR	1	/* Your libc.a not ANSI-compatible and has */
				/* no strerror() */
#endif
#define NEED_STRTOKEN	1	/* Your libc.a does not have strtoken(3) */
#define NEED_INET_ADDR  0	/* You need inet_addr(3)	*/
#define NEED_INET_NTOA  0	/* You need inet_ntoa(3)	*/
#define NEED_INET_NETOF 0	/* You need inet_netof(3)	*/


#define HAVE_RELIABLE_SIGNALS	0

#ifdef APOLLO
#define	RESTARTING_SYSTEMCALLS	1 
#endif 				  /* read/write are restarted after signals
				     defining this 1, gets siginterrupt call
				     compiled, which attempts to remove this
				     behaviour (apollo sr10.1/bsd4.3 needs
				     this) */

#define DEBUGMODE	1	/* define DEBUGMODE to enable debugging mode.*/

/*
 * If you have curses, and wish to use it, then define HAVECURSES. This is the
 * default mode. If you do not have termcap, then undefine HAVETERMCAP. This is
 * the default mode. You can use both HAVECURSES and HAVETERMCAP, but you must
 * define one of the two at least. Remember to check LIBFLAGS in the Makefiles.
 *
 * NOTICE: HAVECURSES and HAVETERMCAP are still under testing. Currently, use
 *  only HAVECURSES and not HAVETERMCAP. This is a temporary condition only.
 *
 * NOTE: These *ONLY* apply to the irc client in this package
 */

#define HAVECURSES      1       /* If you have curses, and want to use it.  */
#define HAVETERMCAP     0       /* If you have termcap, and want to use it. */

/*
 * Full pathnames and defaults of irc system's support files. Please note that
 * these are only the recommened names and paths. Change as needed.
 * You must define these to something, even if you don't really want them.
 */

#define SPATH "/usr/local/src/ircd/bin/ircd" /* Where the server lives.  */
#define CPATH "/usr/local/src/ircd/ircd.conf" /* IRC configuration file.  */
#define MPATH "/usr/local/src/ircd/ircd.motd" /* message of the day file. */
#define LPATH "/tmp/ircd7.log" /* Where the debug file lives, if DEBUGMODE */
#define PPATH "/usr/local/src/ircd/ircd.pid" /* where the server's pid is */

/* ENABLE_SUMMON
 *
 * The SUMMON command requires the ircd to be run as group tty in order
 * to work properly in many cases.  If you are on a machine where it
 * won't work, or simply don't want local users to be summoned, undefine
 * this.
 */

/* #define ENABLE_SUMMON /* local summon */
 
/* MAXIMUM LINKS
 *
 * This define is useful for leaf nodes and gateways. It keeps you from
 * connecting to too many places. It works by keeping you from
 * connecting to more than "n" nodes which you have C:blah::blah:6667
 * lines for.
 *
 * Note that any number of nodes can still connect to you. This only
 * limits the number that you actively reach out to connect to.
 *
 * Leaf nodes are nodes which are on the edge of the tree. If you want
 * to have a backup link, then sometimes you end up connected to both
 * your primary and backup, routing traffic between them. To prevent
 * this, #define MAXIMUM_LINKS 1 and set up both primary and
 * secondary with C:blah::blah:6667 lines. THEY SHOULD NOT TRY TO
 * CONNECT TO YOU, YOU SHOULD CONNECT TO THEM.
 *
 * Gateways such as the server which connects Australia to the US can
 * do a similar thing. Put the American nodes you want to connect to
 * in with C:blah::blah:6667 lines, and the Australian nodes with
 * C:blah::blah lines. Have the Americans put you in with C:blah::blah
 * lines. Then you will only connect to one of the Americans.
 *
 * This value is only used if you don't have server classes defined, and
 * a server is in class 0 (the default class if none is set).
 *
 */

#define MAXIMUM_LINKS 1

#define WALLOPS_REMOTES    /* Notify all opers of remote SQUITS/CONNECTS */

#define WALLOPS_QUARANTINE /* Notify all opers of closing undesirable links */

/* R_LINES:  The conf file now allows the existence of R lines, or
 * restrict lines.  These allow more freedom in the ability to restrict
 * who is to sign on and when.  What the R line does is call an outside
 * program which returns a reply indicating whether to let the person on.
 * Because there is another program involved, Delays and overhead could
 * result. It is for this reason that there is a line in config.h to
 * decide whether it is something you want or need. -Hoppie
 *
 * The default is no R_LINES as most people probably don't need it. --Jto
 */

/* #define R_LINES /* */

#ifdef R_LINES
/* Also, even if you have R lines defined, you might not want them to be 
   checked everywhere, since it could cost lots of time and delay.  Therefore, 
   The following two options are also offered:  R_LINES_REHASH rechecks for 
   R lines after a rehash, and R_LINES_OFTEN, which rechecks it as often
   as it does K lines.  Note that R_LINES_OFTEN is *very* likely to cause 
   a resource drain, use at your own risk.  R_LINES_REHASH shouldn't be too
   bad, assuming the programs are fairly short. */
#define R_LINES_REHASH /* */
#define R_LINES_OFTEN  /* */
#endif

/*
 * NOTE: defining CMDLINE_CONFIG and installing ircd SUID or SGID is a MAJOR
 *       security problem - they can use the "-f" option to read any files
 *       that the 'new' access lets them. Note also that defining this is
 *       a major security hole if your ircd goes down and some other user
 *       starts up the server with a new conf file that has some extra
 *       O-lines. So don't use this unless you're debugging.
 */
/* #define CMDLINE_CONFIG /* allow conf-file to be specified on command line */

/*
 * Define this filename to maintain a list of persons who log
 * into this server. Logging will stop when the file does not exist.
 * Logging will be disable also if you do not define this.
 */

#define FNAME_USERLOG "/usr/local/src/ircd/userlog" /* */

/*
 * define this if you want to use crypted passwords for operators in your
 * ircd.conf file. See ircd/crypt/README for more details on this.
 */
#undef CRYPT_OPER_PASSWORD

#undef WALL /* Define this if you want walls */

/*
 * define this if you enable summon and if you want summon to look for the
 * least idle tty a user is logged in on.
 */
#define LEAST_IDLE

/*
 * Max amount of internal send buffering when socket is stuck (bytes)
 */
#define MAXSENDQLENGTH 200000    /* Recommended value: 100000 for leaves */
                                 /*                    200000 for backbones */

/*
 * Use our "ctype.h" defines (islower(),isupper(),tolower(),toupper(), etc).
 * These are all table referencing macros and are 'quicker' than on some
 * systems, and they provide consistant ANSI behavior for the Finnish character
 * set no mater how broken the host OS is or what language things are.
 * IRC expects []{}\| and A-Za-z to behave properly as upper/lower case,
 * and if this isn't true bad things can happen.
 *
 * THE CODE ASSUMES THAT tolower AND toupper DO NOT DESTROY CHARACTERS
 * THEY ARE NOT CHANGING. This is ANSI, but not old-style K&R. In particular,
 * you cannot just use the standard SunOS 4.1.1 ctype macros and have
 * the server work.
 *
 * Our code assumes EOF is -1. If that isn't true on your system, don't
 * use our ctype, but make sure yours understands { is lower case [, and
 * so on for }] and |\.
 */

#define USE_OUR_CTYPE

/*   STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP  */

/* You shouldn't change anything below this line, unless absolutely needed. */

/*
 * Port where ircd resides. NOTE: This *MUST* be greater than 1024 if you
 * plan to run ircd under any other uid than root.
 */
#define PORTNUM 6667		/* Recommended values: 6667 or 6666 */

/*
 * Maximum number of network connections your server will allow.  This should
 * never exceed max. number of open file descrpitors and wont increase this.
 * Should remain LOW as possible. Most sites will usually have under 30 or so
 * connections. A busy hub or server may need this to be as high as 50 or 60.
 * Making it over 100 decreases any performance boost gained from it being low.
 * if you have a lot of server connections, it may be worth splitting the load
 * over 2 or more servers.
 * 1 server = 1 connection, 1 user = 1 connection.
 */
#define MAXCONNECTIONS	50

/*
 * this defines the length of the nickname history.  each time a user changes
 * nickname or signs off, their old nickname is added to the top of the list.
 * The following sizes are recommended:
 * 8MB or less  core memory : 200
 * 8MB-16MB     core memory : 200-300
 * 16MB-32MB    core memory : 300-500
 * 32MB or more core memory : 500+
 * (100 nicks/users ~ 75K)
 * NOTE: this is directly related to the amount of memory ircd will use whilst
 *	 resident and running - it hardly ever gets swapped to disk! You can
 *	 ignore these recommendations- they only are meant to serve as a guide
 */
#define NICKNAMEHISTORYLENGTH 350

/*
 * WALLOPS : When enabled this will send a broadcast message out to anybody
 *           who is listening. Generally this is operators and eager users.
 *           Disabling (undefining WALLOPS) prevents users from annoying
 *           operators and other users who wish to listen for them. This is
 *           the prefered action.
 */
#undef WALLOPS	 		 /* Define this if you want wallops */

/*
 * Time interval to wait and if no messages have been received, then check for
 * PINGFREQUENCY and CONNECTFREQUENCY 
 */
#define TIMESEC  60		/* Recommended value: 60 */

/*
 * If daemon doesn't receive anything from any of its links within
 * PINGFREQUENCY seconds, then the server will attempt to check for
 * an active link with a PING message. If no reply is received within
 * (PINGFREQUENCY * 2) seconds, then the connection will be closed.
 */
#define PINGFREQUENCY    120	/* Recommended value: 120 */

/*
 * If the connection to to uphost is down, then attempt to reconnect every 
 * CONNECTFREQUENCY  seconds.
 */
#define CONNECTFREQUENCY 600	/* Recommended value: 600 */

/*
 * Often net breaks for a short time and it's useful to try to
 * establishing the same connection again faster than CONNECTFREQUENCY
 * would allow. But, to keep trying on bad connection, we require
 * that connection has been open for certain minimum time
 * (HANGONGOODLINK) and we give the net few seconds to steady
 * (HANGONRETRYDELAY). This latter has to be long enough that the
 * other end of the connection has time to notice it broke too.
 */
#define HANGONRETRYDELAY 10	/* Recommended value: 10 seconds */
#define HANGONGOODLINK 300	/* Recommended value: 10 minutes */

/*
 * Number of seconds to wait for write to complete if stuck.
 */
#define WRITEWAITDELAY     15	/* Recommended value: 15 */

/*
 * Max time from the nickname change that still causes KILL
 * automaticly to switch for the current nick of that user. (seconds)
 */
#define KILLCHASETIMELIMIT 90   /* Recommended value: 90 */

/*
 * Max number of channels a user is allowed to join.
 */
#define MAXCHANNELSPERUSER  10

/*
 * Double buffering has been designed to increase the packet size of
 * individual packets sent out by the server. This is done by putting all
 * outbound messages (as many as will fit - if any) into an outbound
 * buffer before either adding to sendQ or writing. This also reduces the
 * number of write() calls the server makes. The outbound buffer is flushed
 * by the server regularly either onto the sendQ or down the connection.
 * Whether or not this idea is worth doing is yet to be seen but there is
 * no harm in trying it out.
 * It is not fully tested and may cause problems. Define it only for testing
 * or if you are sure you know what you are doing. -avalon
 */
#undef DOUBLE_BUFFER

#define MOTD MPATH
#define MYNAME SPATH
#define CONFIGFILE CPATH
#define IRCD_PIDFILE PPATH

#if DEBUGMODE
# define LOGFILE LPATH
#else
# if VMS
#	define LOGFILE "NLA0:"
# else
#	define LOGFILE "/dev/null"
# endif
#endif

#ifndef ENABLE_SUMMON
#  undef LEAST_IDLE
#endif


#ifdef mips
#undef SYSV
#endif

#if MIPS
#undef BSD
#define BSD             1       /* mips only works in bsd43 environment */
#endif

#ifdef sequent                   /* Dynix (sequent OS) */
#define SEQ_NOFILE    128        /* set to your current kernel impl, */
#endif                           /* max number of socket connections */

#if HAVECURSES
# define DOCURSES
#else
# undef DOCURSES
#endif

#if HAVETERMCAP
# define DOTERMCAP
#else
# undef DOTERMCAP
#endif

#define Reg1 register
#define Reg2 register
#define Reg3 register
#define Reg4 register
#define Reg5 register
#define Reg6 register
#define Reg7 register
#define Reg8 register
#define Reg9 register
#define Reg10 register
#define Reg11 
#define Reg12 
#define Reg13 
#define Reg14 
#define Reg15 
#define Reg16 