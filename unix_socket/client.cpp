#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "server.hpp"
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "JSON.h"

/*
If you want to communicate with a remote host, then you will probably need an INET socket.

The difference is that an INET socket is bound to an IP address-port tuple, while a UNIX socket is "bound" to a special file on your filesystem. Generally, only processes running on the same machine can communicate through the latter.

So, why would one use a UNIX socket? Exactly for the reason above: communication between processes on the same host, being a lightweight alternative to an INET socket via loopback.

In fact, INET sockets sit at the top of a full TCP/IP stack, with traffic congestion algorithms, backoffs and the like to handle. A UNIX socket doesn't have to deal with any of those problems, since everything is designed to be local to the machine, so its code is much simpler and the communication is faster. Granted, you will probably notice the difference only under heavy load, e.g. when reverse proxying an application server (Node.js, Tornado...) behind Nginx etc.

*/

// g++ -I./json client.cpp json/JSON.cpp json/JSONValue.cpp -o client && ./client

std::string jsontype_str(JSONType jsonType)
{
	std::string jsonTypeStr[JSONType_Object + 1] = { "JSONType_Null", "JSONType_String", "JSONType_Bool", "JSONType_Number", "JSONType_Array", "JSONType_Object" };
}

int main()
{
	int sockfd_;
	struct sockaddr_un addr;
	int ret;
	char buffer[8192];
	struct sockaddr_un from;
	
	int status = 1;

	
	int len;
	if ((sockfd_ = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) { 
	  // The PF_UNIX (also called PF_LOCAL) socket family  is  used
      // to communicate between processes on the same machine efficiently.
      	perror("socket () error");
		status = 0;
	}
	
	if (status) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX; // The sun_family field always contains AF_UNIX. 
		strcpy(addr.sun_path, CLIENT_SOCKET_FILE);
		unlink(CLIENT_SOCKET_FILE);
		
		if (bind(sockfd_, (struct sockaddr *)&addr,sizeof(addr)) < 0) {
			perror("bind");
			status = 0;
		}	
	}
	
	if (status) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX; 
		strcpy(addr.sun_path, SERVER_SOCKET_FILE);
		if (connect(sockfd_, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
			perror("connect");
			status = 0;
		}
	}
	
	
	int requestNumber = 1;
	
	while (true)
	{    

		printf("Request number before break %d", requestNumber);
		if (requestNumber > 10)
			break;
				
		if (status) {
			//const wchar_t* jsonSample = L"{ \"event\": \"calc\", \"function\":\"fact\",  \"data\": 7 }";
			memset(&buffer, '\0', 8192);
			std::string message = "{ \"event\": \"calc\", \"function\":\"fact\",  \"data\":" +  std::to_string(requestNumber) + " }\0";
			strcpy(buffer, message.c_str());	
			
			printf("Message is: %s\n", message.c_str());
			
				     							
			
			if (send(sockfd_, buffer, strlen(buffer) + 1, 0) == -1) {
				perror("send");
				status = 0;
			}
			printf("Request number after send %d", requestNumber);
			
			requestNumber++;
		
			printf("sent message\n");
		}
		
		if (status) {
			if ((len = recv(sockfd_, buffer, 8192, 0)) < 0) {
				perror("recv");
				status = 0;
			}
			printf("receive %d %s\n", len, buffer);
		}	
	}
	
	if (sockfd_ >= 0) {
		close(sockfd_);
	}
	
	unlink (CLIENT_SOCKET_FILE);
	return 0;	
}

