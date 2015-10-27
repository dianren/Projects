/*
** client.c -- a stream socket client demo
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT "1102"
#define HOST "nunki.usc.edu"// the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
int get_my_addr1(void);
int get_my_addr2(void);


typedef struct bidder_data
{
   char type[2];
   char name[50];
   char password[50];
   char account[50];
} bidder1_data_t, bidder2_data_t;


bidder1_data_t bidder1;
bidder2_data_t bidder2;
int sockfd1, sockfd2;
char hostIP1[INET6_ADDRSTRLEN]; 
char hostPort1[20];
char hostIP2[INET6_ADDRSTRLEN]; 
char hostPort2[20];

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) 
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char *argv[])
{
	/* main function initial*/
	int bytes_send1, bytes_send2, len1, len2;
	int n1, n2;
	char mess1[100];
	char mess2[100];
	char bbuf1[MAXDATASIZE];
	char bbuf2[MAXDATASIZE];
	struct addrinfo hints1, *servinfo1, *p1;
	struct addrinfo hints2, *servinfo2, *p2;
	int rv1, rv2;
   /*char s1[INET6_ADDRSTRLEN];
   char s2[INET6_ADDRSTRLEN];*/
   
   /* loadfile initial*/
	FILE *fp1, *fp2;
	char *token1 = NULL;
	char *token2 = NULL;
	char current_line1[512];
	char current_line2[512];
	pid_t pid;
   
   
  
   /* send*/
	pid=fork();
	if(pid<0)
	{
		printf("error in fork!\n");
	}
	else
	{ 
      /* child process bidder2*/ 
        if(pid==0)
        {  
            
			sleep(1);
			/*struct hostent* he2 = gethostbyname(HOST);
			printf("\nhost name is %s\n", he2->h_name);*/
			memset(&hints2, 0, sizeof hints2);
			hints2.ai_family = AF_UNSPEC;
			hints2.ai_socktype = SOCK_STREAM;
			if ((rv2 = getaddrinfo(HOST, PORT, &hints2, &servinfo2)) != 0) 
			{
				/*fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv2));*/
				return 1;
			}
			/*create a socket*/
			for(p2 = servinfo2; p2 != NULL; p2 = p2->ai_next) 
			{
				if ((sockfd2 = socket(p2->ai_family, p2->ai_socktype,p2->ai_protocol)) == -1) 
				{
					perror("bidder2: socket");
					continue;
				}
               
				if (connect(sockfd2, p2->ai_addr, p2->ai_addrlen) == -1) 
				{
					close(sockfd2);
					perror("bidder2: connect");
					continue;
				}
				break;
			}
			if (p2 == NULL) 
			{
				/*fprintf(stderr, "client: failed to connect\n");*/
				return 2;
			}
			get_my_addr2();
			/*inet_ntop(p2->ai_family, get_in_addr((struct sockaddr *)p2->ai_addr),s2, sizeof s2);*/
			/*freeaddrinfo(servinfo2);*/ 
			/*printf("bidder2: connecting to %s\n", s2);*/

        
         
			/* load file */
         
			fp2=fopen("test/bidderPass2.txt","r");
			if(fp2==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			while(fgets(current_line2, 512, fp2)!=NULL)
			{
				token2=strtok(current_line2, " ");
				strcpy(bidder2.type, token2);
				token2=strtok(NULL, " ");
				strcpy(bidder2.name, token2);
				token2=strtok(NULL, " ");
				strcpy(bidder2.password, token2);
				token2=strtok(NULL, " ");
				strcpy(bidder2.account, token2);
				printf("Phase 1: Login request. User: %s. Password: %s. Bank account: %s\n", bidder2.name, bidder2.password, bidder2.account);
            
				/*fprintf(stdout, "name=%s\n", bidder2.name);
				fprintf(stdout, "password=%s\n", bidder2.password);
				fprintf(stdout, "account=%s\n", bidder2.account);*/

            
				/*begin to send*/
				
				sprintf(bbuf2, "%s@%s@%s@%s", bidder2.type, bidder2.name, bidder2.password, bidder2.account);
				len2 = sizeof(bbuf2);
				bytes_send2 = send(sockfd2, bbuf2, len2, 0);
				if (bytes_send2 == -1)
				{
					
					perror("bidder2 send");
					exit(1);
				}

				/* receive the reply */
				n2 = recv(sockfd2, mess2, 100, 0);
				mess2[n2] = '\0';
				if (n2 == -1) 
				{
					perror("bidder2 recv");
					exit(1);
				}
				printf("Phase 1: Login request reply: %s\n", mess2);
			}
			printf("End of Phase 1 for <Bidder2>.\n\n\n\n");
			return(0);
			close(sockfd2);
		}
      
      /* father process*/ 
		else
		{ 
         /*gethostbyname*/
			/*struct hostent* he1 = gethostbyname(HOST);
			printf("host name is %s\n", he1->h_name);*/
			memset(&hints1, 0, sizeof hints1);
			hints1.ai_family = AF_UNSPEC;
			hints1.ai_socktype = SOCK_STREAM;
			if ((rv1 = getaddrinfo(HOST, PORT, &hints1, &servinfo1)) != 0) 
			{
				/*fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv1));*/
				return 1;
			}
         /*create a socket*/
            for(p1 = servinfo1; p1 != NULL; p1 = p1->ai_next) 
            {
                if ((sockfd1 = socket(p1->ai_family, p1->ai_socktype,p1->ai_protocol)) == -1) 
                {
                   perror("bidder1: socket");
                   continue;
                }
                if (connect(sockfd1, p1->ai_addr, p1->ai_addrlen) == -1) 
                {
                  
                   perror("bidder1: connect");
                   continue;
                }
                break;
            }
            if (p1 == NULL) 
            {
                /*fprintf(stderr, "client: failed to connect\n");*/
                return 2;
            }
            get_my_addr1();
            /*inet_ntop(p1->ai_family, get_in_addr((struct sockaddr *)p1->ai_addr),s1, sizeof s1);
            freeaddrinfo(servinfo1);*/
            /*printf("bidder1 connecting to %s\n", s1);*/


          /*load file*/
         
            fp1=fopen("test/bidderPass1.txt","r");
            if(fp1==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			while(fgets(current_line1, 512, fp1)!=NULL)
			{
				token1=strtok(current_line1, " ");
				strcpy(bidder1.type, token1);
				token1=strtok(NULL, " ");
				strcpy(bidder1.name, token1);
				token1=strtok(NULL, " ");
				strcpy(bidder1.password, token1);
				token1=strtok(NULL, " ");
				strcpy(bidder1.account, token1);
                printf("Phase 1: Login request. User: %s. Password: %s. Bank account: %s\n", bidder1.name, bidder1.password, bidder1.account);
				/*fprintf(stdout, "name=%s\n", bidder1.name);
				fprintf(stdout, "password=%s\n", bidder1.password);
				fprintf(stdout, "account=%s\n", bidder1.account);*/

            /* begin to send*/ 
				sprintf(bbuf1, "%s@%s@%s@%s", bidder1.type, bidder1.name, bidder1.password, bidder1.account);
				len1 = sizeof(bbuf1);
                bytes_send1 = send(sockfd1, bbuf1, len1, 0);
				if (bytes_send1 == -1)
				{
					
					perror("bidder1 send");
					exit(1);
				}

			/* receive the  reply*/ 
				n1 = recv(sockfd1, mess1, 100, 0);
				mess1[n1] = '\0';
				if (n1 == -1) 
				{
					perror("bidder1 recv");
					exit(1);
				}
				printf("Phase 1: Login request reply: %s\n", mess1);
			}
			printf("End of Phase 1 for <Bidder1>.\n\n\n\n");
			return(0);
			close(sockfd1);
		}
	}
	return(0);
}



int get_my_addr1(void)
{
	struct sockaddr_in my_addr;
	int getsock_check;
	socklen_t addrlen = sizeof(my_addr);
	getsock_check = getsockname(sockfd1, (struct sockaddr *)&my_addr, &addrlen);
	if(getsock_check==-1)
	{
		perror("getsockname");
		exit(1);
	}
	inet_ntop(AF_INET, &my_addr.sin_addr, hostIP1, sizeof(hostIP1));
	/*printf("my ip: %s\n", hostIP1);*/
	sprintf(hostPort1, "%u", ntohs(my_addr.sin_port));
	printf("Phase 1: <Bidder1> has TCP port: %s and IP address: %s\n\n", hostPort1, hostIP1);
	return(1);
}
   

int get_my_addr2(void)
{
	struct sockaddr_in my_addr;
	int getsock_check;
	socklen_t addrlen = sizeof(my_addr);
	getsock_check = getsockname(sockfd2, (struct sockaddr *)&my_addr, &addrlen);
	if(getsock_check==-1)
	{
		perror("getsockname");
		exit(1);
	}
	inet_ntop(AF_INET, &my_addr.sin_addr, hostIP2, sizeof(hostIP2));
	/*printf("my ip: %s\n", hostIP2);*/
	sprintf(hostPort2, "%u", ntohs(my_addr.sin_port));
	printf("Phase 1: <Bidder2> has TCP port: %s and IP address: %s\n\n", hostPort2, hostIP2);
	return(1);
} 
   
  
   
   
  
