/*
 * hpreadymsg -- a JetDirect Display Hack
 *   Original:  (c) 1997 Silicosis of L0pht <sili@l0pht.com>.
 *   This port: (c) 2022 Colin Cogle <colin@colincogle.name>.
 *
 * From https://www.irongeek.com/i.php?page=security/jetdirecthack:
 * "Back in 1997 Silicosis of L0pht (sili@l0pht.com) wrote a bit of exploit
 *  code for *nix systems that allows you to set the text that displays on
 *  the little LCD panel of an HP printer.  It accomplished this over the
 *  network by sending packets to the JetDirect box hooked to the printer
 *  (or built into it)."
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, visit: https://gnu.org/licenses/gpl-3.0.html
 */

#include <stdio.h>	/* printf(), fprintf() */
#include <string.h>	/* strcpy(), strcat(), strncat(), strlen() */
#include <sys/types.h>	/* size_t */
#include "hpreadymsg.h"	/* PACKAGE, VERSION, if not defined by automake */
#ifdef WIN32
	#include <winsock.h>	/* send(), close(), socket stuff */
	#include <WS2tcpip.h>	/* getaddrinfo(), inet_ntop() */
#else
	#include <unistd.h> /* send(), close(), EAI_SYSTEM */
	#include <sys/socket.h>	/* socket functions */
	#include <netdb.h>	/* getaddrinfo(), gai_strerror() */
	#include <netinet/in.h>	/* sockaddr types */
	#include <arpa/inet.h>	/* inet_ntop() */
#endif


int
main (const int argc, const char* const argv[])
{
	struct addrinfo*	result = NULL;
	struct addrinfo*	results;
	char				line[91];	/* the data we send will be 91 characters at most */
	int					error = 0;
	char				foundValidServerIP = 0;
	#ifndef WIN32
		int socket_desc = -1;
	#else
		SOCKET socket_desc = INVALID_SOCKET;
		WSADATA wsaData;
	#endif

	/* Say hello and validate input. */
	credits();
	if (argc != 3)
	{
		help(argv[0]);
		return 1;
	}

	#ifdef WIN32
	/* Start up our sockets (Windows). */
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
	{
		fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	#endif

	/* Look up IP addresses associated with the provided hostname.*/
	error = getaddrinfo(argv[1], NULL, NULL, &results);
	if (error != 0)
	{
		if (error == EAI_SYSTEM)
		{
			perror("getaddrinfo");
		}
		else
		{
			fprintf(stderr, "error in getaddrinfo: %s: %s\n", argv[1], gai_strerror(error));
		}
		#ifdef WIN32
			WSACleanup();
		#endif
		return 1;
	}

	/* Connect to the first functioning IP address. */
	printf("Hostname: %s\nMessage:  %s\n", argv[1], argv[2]);
	for (result = results; result != NULL && !foundValidServerIP; result = result->ai_next)
	{
		struct sockaddr* const addressinfo = result->ai_addr;
		char buffer[50];	/* Maximum size of an IPv6 address, plus room for %ifname. */
		
		socket_desc = socket(addressinfo->sa_family, SOCK_STREAM, IPPROTO_TCP);
		if (socket_desc < 0)
		{
			perror("error in socket()\n");
			continue;
		}

		if (addressinfo->sa_family == AF_INET6) /* IPv6 */
		{
				((struct sockaddr_in6*)addressinfo)->sin6_port = htons(9100);
				inet_ntop(
					AF_INET6,
					&((struct sockaddr_in6*)addressinfo)->sin6_addr,
					buffer,
					INET6_ADDRSTRLEN
				);
				printf("Connecting to [%s]:9100…\n", buffer);
		}
		else /* we're connecting via IPv4 */
		{
				((struct sockaddr_in*)addressinfo)->sin_port = htons(9100);
				inet_ntop(
					AF_INET,
					&((struct sockaddr_in*)addressinfo)->sin_addr,
					buffer,
					INET_ADDRSTRLEN
				);
				printf("Connecting to %s:9100…\n", buffer);
		}

		if (connect(socket_desc, addressinfo, (size_t)(result->ai_addrlen)) >= 0)
		{
			foundValidServerIP = 1;
		}
		else
		{
			perror("error in connect()");
			shutdown(socket_desc, 2);
		}
	}
	freeaddrinfo(results);
	if (!foundValidServerIP)
	{
		fprintf(stderr, "Could not connect to the printer!\n");
		#ifdef WIN32
			WSACleanup();
		#endif
		return 1;
	}

	/* Preparing PJL Command */
	strcpy(line,  "\033%-12345X@PJL RDYMSG DISPLAY = \"");
	strncat(line, argv[2], 44);
	strcat(line,  "\"\r\n\033%-12345X\r\n");

	/* Sending data! */
	#ifdef DEBUG
		printf("Sending Data...%ld\n", strlen(line));
		printf("Line: %s\n", line);
	#endif
	printf("Sent %ld bytes to the printer.\n", send(socket_desc,line,strlen(line),0));
	
	#ifdef WIN32
		closesocket(socket_desc);
		WSACleanup();
	#else
		close(socket_desc);
	#endif
	return 0;
}

inline void
credits ()
{
	printf("HP Display Hack\n--sili@l0pht.com 12/8/97\n--Port by Colin Cogle, 2022\n\n");
	return;
}

inline void
help (const char* const appName)
{
	fprintf(stderr, "Usage: %s printer \"message\"\n", appName);
	fprintf(stderr, "\tMessage can be up to 16 characters long (44 on 5si's)\n");
	return;
}