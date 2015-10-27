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
#define PREPORT "1202"
#define HOST "nunki.usc.edu"
#define MAXDATASIZE 100 
int get_my_addr1(void);
int get_my_addr2(void);

typedef struct seller_data
{
   char type[2];
   char name[50];
   char password[50];
   char account[50];
} seller1_data_t, seller2_data_t;


typedef struct item_data
{
   char name[50];
   char stuff[10][50];
   int price[50];
} item1_data_t, item2_data_t;


item1_data_t item1;
item2_data_t item2;
seller1_data_t seller1;
seller2_data_t seller2;
int sockfd1, sockfd2, sockfd3, sockfd4;
char hostIP1[INET6_ADDRSTRLEN]; 
char hostPort1[20];
char hostIP2[INET6_ADDRSTRLEN]; 
char hostPort2[20];
char serv1IP[20], serv2IP[20];


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
	int bytes_send1, bytes_send2, bytes_send3, bytes_send4, len1, len2, len3, len4;
	int n1, n2, m1, m2;
	char mess1[100];
	char mess2[100];
	char bbuf1[MAXDATASIZE];
	char bbuf2[MAXDATASIZE];
	struct addrinfo hints1, *servinfo1, *p1;
	struct addrinfo hints2, *servinfo2, *p2;
	struct addrinfo hints3, *servinfo3, *p3;
	struct addrinfo hints4, *servinfo4, *p4;
	int rv1, rv2, rv3, rv4;
	/*char s1[INET6_ADDRSTRLEN];
	char s2[INET6_ADDRSTRLEN];*/
   
   
   /* loadfile initial*/
	FILE *fp1, *fp2, *fp3, *fp4;
	char itembuf1[100], itembuf2[100];
	char *pp1, *pp2;
	char *token1 = NULL;
	char *token2 = NULL;
	char current_line1[512];
	char current_line2[512];
	pid_t pid;

    /*fork*/
	pid=fork();
	if(pid<0)
	{
		printf("error in fork!\n");
	}
	else
	{ 
/*//////////////////////////////////////////////////////// child process seller2*///////////////////////////////////////////// 
		if(pid==0)
		{
		/*gethostbyname*/
			/*struct hostent* he = gethostbyname(HOST);
			printf("host name is %s\n", he->h_name);*/
			
			
/*////////////////Phase 1/////////////*/
			sleep(2);
			memset(&hints2, 0, sizeof hints2);
			hints2.ai_family = AF_UNSPEC;
			hints2.ai_socktype = SOCK_STREAM;
			if ((rv2 = getaddrinfo(HOST, PORT, &hints2, &servinfo2)) != 0) 
			{
				/*fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv2));*/
				return 1;
			}
			
			for(p2 = servinfo2; p2 != NULL; p2 = p2->ai_next) 
			{
				if ((sockfd2 = socket(p2->ai_family, p2->ai_socktype,p2->ai_protocol)) == -1) 
				{
					perror("seller2: socket");
					continue;
				}
				if (connect(sockfd2, p2->ai_addr, p2->ai_addrlen) == -1) 
				{
					close(sockfd2);
					perror("seller2: connect");
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
			/*inet_ntop(p2->ai_family, get_in_addr((struct sockaddr *)p2->ai_addr),s2, sizeof s2);
			printf("seller2: connecting to %s\n", s2);
			freeaddrinfo(servinfo2); */
		
        
			/* load file */
			fp2=fopen("test/sellerPass2.txt","r");
			if(fp2==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			while(fgets(current_line2, 512, fp2)!=NULL)
			{
				token2=strtok(current_line2, " ");
				strcpy(seller2.type, token2);
				token2=strtok(NULL, " ");
				strcpy(seller2.name, token2);
				token2=strtok(NULL, " ");
				strcpy(seller2.password, token2);
				token2=strtok(NULL, " ");
				strcpy(seller2.account, token2);
                printf("Phase 1: Login request. User: %s. Password: %s. Bank account: %s\n", seller2.name, seller2.password, seller2.account);
				/*fprintf(stdout, "name=%s\n", seller2.name);
				fprintf(stdout, "password=%s\n", seller2.password);
				fprintf(stdout, "account=%s\n", seller2.account);*/

                /*begin to send*/
				sprintf(bbuf2, "%s@%s@%s@%s", seller2.type, seller2.name, seller2.password, seller2.account);
				len2 = sizeof(bbuf2);
				bytes_send2 = send(sockfd2, bbuf2, len2, 0);
				if (bytes_send2 == -1)
				{
					perror("seller2 send");
					exit(1);
				}

				/* receive the reply */
				n2 = recv(sockfd2, mess2, 100, 0);
				mess2[n2] = '\0';
				if (n2 == -1) 
				{
					perror("seller2 recv");
					exit(1);
				}
				printf("Phase 1: Login request reply: %s\n", mess2);
				m2 = recv(sockfd2, serv2IP, 20, 0);
				serv2IP[m2] = '\0';
				if (n2 == -1) 
				{
					perror("seller1 recv serv2IP");
					exit(1);
				}
			}
			printf("End of Phase 1 for <Seller2>.\n\n\n\n");
			close(sockfd2);
			
			
			
/*/////////////////////Seller2 Phase 2////////////////////////////*/
            sleep(15);
			printf("Phase 2: Auction Server IP Address: %s PreAuction Port Number: %s.\n\n", serv2IP, PREPORT);
			
			memset(&hints4, 0, sizeof hints4);
			hints4.ai_family = AF_UNSPEC;
			hints4.ai_socktype = SOCK_STREAM;
			if ((rv4 = getaddrinfo(HOST, PREPORT, &hints4, &servinfo4)) != 0) 
			{
				/*fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv4));*/
				return 1;
			}
			
			for(p4 = servinfo4; p4 != NULL; p4 = p4->ai_next) 
			{
				if ((sockfd4 = socket(p4->ai_family, p4->ai_socktype,p4->ai_protocol)) == -1) 
				{
					perror("seller2: socket4");
					continue;
				}
				if (connect(sockfd4, p4->ai_addr, p4->ai_addrlen) == -1) 
				{
					
					perror("seller2: connect4");
					continue;
				}
				break;
			}
			if (p4 == NULL) 
			{
				fprintf(stderr, "client: failed to connect\n");
				return 2;
			}
			
			fp4=fopen("test/itemList2.txt","r");
			if(fp4==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			pp2 = itembuf2;
			fread(pp2, 100, 1, fp4);
			len4 = sizeof(itembuf2);
			bytes_send4 = send(sockfd4, itembuf2, len4, 0);
			if (bytes_send4 == -1)
			{
				perror("seller2 send4");
				exit(1);
			}
			printf("Phase 2: <Seller2> send items lists\n");
			fprintf(stdout, "%s\n", itembuf2);
			printf("End of Phase 2 for <Seller2>.\n\n\n");
			return(0);
			close(sockfd4);
		}
      
/*////////////////////////////////////////////////////////// father process//////////////////////////////////////////*/ 
		else
		{ 
			/*gethostbyname
			struct hostent* he = gethostbyname(HOST);
			printf("host name is %s\n", he->h_name);*/
			
			
/*///////////////////////Seller1 Phase 1/////////////////////////*/
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
					perror("seller1: socket");
					continue;
				}
				if (connect(sockfd1, p1->ai_addr, p1->ai_addrlen) == -1) 
				{
                  
					perror("seller1: connect");
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
			freeaddrinfo(servinfo1); 
			printf("seller1 connecting to %s\n", s1);*/
			
            /*load file*/
			fp1=fopen("test/sellerPass1.txt","r");
			if(fp1==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			while(fgets(current_line1, 512, fp1)!=NULL)
			{
				token1=strtok(current_line1, " ");
				strcpy(seller1.type, token1);
				token1=strtok(NULL, " ");
				strcpy(seller1.name, token1);
				token1=strtok(NULL, " ");
				strcpy(seller1.password, token1);
				token1=strtok(NULL, " ");
				strcpy(seller1.account, token1);
				printf("Phase 1: Login request. User: %s. Password: %s. Bank account: %s\n", seller1.name, seller1.password, seller1.account);

				/*fprintf(stdout, "\nname=%s\n", seller1.name);
				fprintf(stdout, "password=%s\n", seller1.password);
				fprintf(stdout, "account=%s\n", seller1.account);*/

				/* begin to send*/ 
				sprintf(bbuf1, "%s@%s@%s@%s", seller1.type, seller1.name, seller1.password, seller1.account);
				len1 = sizeof(bbuf1);
				bytes_send1 = send(sockfd1, bbuf1, len1, 0);
				if (bytes_send1 == -1)
				{
					
					perror("seller1 send");
					exit(1);
				}

				/* receive the  reply*/ 
				n1 = recv(sockfd1, mess1, 100, 0);
				mess1[n1] = '\0';
				if (n1 == -1) 
				{
					perror("seller1 recv mess1");
					exit(1);
				}
				printf("Phase 1: Login request reply: %s\n", mess1);
				m1 = recv(sockfd1, serv1IP, 20, 0);
				serv1IP[m1] = '\0';
				if (n1 == -1) 
				{
					perror("seller1 recv serv1IP");
					exit(1);
				}
			}
			printf("End of Phase 1 for <Seller1>.\n\n\n\n");
			close(sockfd1);
			
			
			/*/////////////////////Seller1 Phase 2////////////////////////////*/
            sleep(10);
			printf("Phase 2: Auction Server IP Address: %s PreAuction Port Number: %s.\n\n", serv1IP, PREPORT);
			memset(&hints3, 0, sizeof hints3);
			hints3.ai_family = AF_UNSPEC;
			hints3.ai_socktype = SOCK_STREAM;
			if ((rv3 = getaddrinfo(HOST, PREPORT, &hints3, &servinfo3)) != 0) 
			{
				/*fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv3));*/
				return 1;
			}
			
			for(p3 = servinfo3; p3 != NULL; p3 = p3->ai_next) 
			{
				if ((sockfd3 = socket(p3->ai_family, p3->ai_socktype,p3->ai_protocol)) == -1) 
				{
					perror("seller1: socket3");
					
				}
				/*printf(" socket success!!!!!!!");*/
				if (connect(sockfd3, p3->ai_addr, p3->ai_addrlen) == -1) 
				{
					
					perror("seller1: connect3\n\n");
					continue;
				}
				break;
			}
			
			if (p3 == NULL) 
			{
				fprintf(stderr, "client: failed to connect\n");
				return 2;
			}
			
			fp3=fopen("test/itemList1.txt","r");
			if(fp3==NULL)
			{
				printf("Cannot open file strike any key exit!\n");
			}
			pp1 = itembuf1;
			fread(pp1, 100, 1, fp3);
			len3 = sizeof(itembuf1);
			bytes_send3 = send(sockfd3, itembuf1, len3, 0);
			if (bytes_send3 == -1)
			{
				perror("seller1 send3");
				exit(1);
			}
			printf("Phase 2: <Seller1> send items lists\n");
			fprintf(stdout, "%s\n", itembuf1);
			printf("End of Phase 2 for <Seller1>.\n\n\n");
			return(0);
			close(sockfd3);
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
	printf("Phase 1: <Seller1> has the TCP port: %s and IP address: %s\n\n", hostPort1, hostIP1);
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
	sprintf(hostPort2, "%u", ntohs(my_addr.sin_port));
	printf("Phase 1: <Seller2> has the TCP port: %s and IP address: %s\n\n", hostPort2, hostIP2);
	return(1);
} 
   
   


   
   
  
