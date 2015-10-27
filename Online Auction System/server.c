/*
** server.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT "1102" 
#define BACKLOG 10 
#define HOST "nunki.usc.edu"
#define PREPORT "1202"

int file_load(void);
int check(void);
int get_my_addr(void);
int get_my_addragain(void);
int phase2(void);

typedef struct cust_data
{
	char type[2];
	char name[50];
	char password[50];
	char account[50];
} cust_data_t;

typedef struct user_data
{
	char type[2];
	char name[50];
	char password[50];
	char account[50];
} user_data_t;

user_data_t user[10];
cust_data_t cust[10];
char sbuf[10][128];
char mess[10][100];
char itembuf[10][100];
char hostIP[INET6_ADDRSTRLEN]; 
char peerIP[INET6_ADDRSTRLEN];
char hostPort[20];
int n[20], m[20];
int a[20], b[20], c[20], d[20];
int new_fd[20], renew_fd[20];
int sockfd, sockfd1;
int numbytes[4];
socklen_t sin_size;
struct sockaddr_storage user_addr;

char s[INET6_ADDRSTRLEN];
struct addrinfo hints1, *servinfo1, *p1;



void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) 
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(void)
{
	int yes=1;  
	struct addrinfo hints, *servinfo, *p;
	int rv;
/*/////////////////Phase 1////////////////////////////////*/
    memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP
	if ((rv = getaddrinfo(HOST, PORT, &hints, &servinfo)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
  
   /* find error */
	for(p = servinfo; p != NULL; p = p->ai_next) 
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) 
		{
			printf("server: socket error!\n");
			continue;
		}
		/*else
		{
			printf("server: socket success!\n");
		}*/
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) 
		{
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
		{
			close(sockfd);
			perror("server: bind error!\n");
			continue;
		}
		
		/*else
		{
			printf("server: bind success!\n");
		}*/
		break;
	}
	if (p == NULL) 
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	freeaddrinfo(servinfo); 

   
	/*begin to listen */
	if (listen(sockfd, BACKLOG) == -1) 
	{
		printf("server: listen error!\n");
		exit(1);
	}
	
	get_my_addr();
	/*printf("server: waiting for connections...\n");*/
    file_load();
    check();
	/*printf("server: check finish\n");*/
	printf("End of Phase 1 for Auction Server.\n\n\n");
    close(sockfd);
	
/*/////////////////phase 2////////////////////////////////*/
    
	printf("Phase 2: Auction Server IP Address: %s PreAuction TCP Port Number: %s.\n", hostIP, PREPORT);
	phase2();
	return(0);
	
}



/*load*/
int file_load(void)
{
   
	FILE *fp;
	fp = fopen("test/Registration.txt","r");
	char current_line[512];
	char *token = NULL;
	int i = 0;
	if((fp)==NULL)
	{
		printf("\nCannot open file strike any key exit!");
	}
	while(fgets(current_line, 512, fp)!=NULL)
	{
        token=strtok(current_line, " ");
            
        strcpy(cust[i].name, token);
        token=strtok(NULL, " ");
        strcpy(cust[i].password, token);
        token=strtok(NULL, " ");
        strcpy(cust[i].account, token);
            
        /*fprintf(stdout, "name=%s\n", cust[i].name);
        fprintf(stdout, "password=%s\n", cust[i].password);
        fprintf(stdout, "account=%s\n", cust[i].account);*/

        i=i+1;
	}
    return(1);
}
 

int check(void)
{
   char *token = NULL;
   char t[1]= "2";
   struct sockaddr_in peer_addr;
   socklen_t len = sizeof(peer_addr);
   int i, j, k, rev, llen, gg;
   for(i=0;i<4;i++)
   {
        /*int count=0;*/
		sin_size = sizeof user_addr;
		new_fd[i] = accept(sockfd, (struct sockaddr *)&user_addr, &sin_size);
		if (new_fd[i] == -1) 
		{
			perror("accept");
            exit(1);
		}
		/*inet_ntop(user_addr.ss_family,get_in_addr((struct sockaddr *)&user_addr),s, sizeof s);*/
		/*printf("server: got connection from %s\n", s);*/
        numbytes[i] = recv(new_fd[i], sbuf[i], 127, 0);
		sbuf[i][numbytes[i]]= '\0';
		if (numbytes[i] == -1)
		{
			perror("error");
			exit(1);
		}
		
		/* check */
		token = strtok(sbuf[i], "@");
		strcpy(user[i].type, token);
		token = strtok(NULL, "@");
		strcpy(user[i].name, token);
		token = strtok(NULL, "@");
		strcpy(user[i].password, token);
		token = strtok(NULL, " ");
		strcpy(user[i].account, token);
	   
		/*printf("server: bidder%d begin to check!\n", i);*/
		for(j=0;j<6;j++)
		{
			a[i]=strcmp(user[i].name, cust[j].name);
			b[i]=strcmp(user[i].password, cust[j].password);
			c[i]=strcmp(user[i].account, cust[j].account);
			d[i]=strcmp(user[i].type, t);
			if((a[i]==0)&&(b[i]==0)&&(c[i]==0))
			{
				/*printf("server: %d check Accepted\n", i);*/
				sprintf(mess[i], "Accepted\n");
				n[i]=send(new_fd[i], mess[i], 100, 0);// send a reply
				if(n[i] == -1)
				{
					perror("send");
				}
				rev = getpeername(new_fd[i], (struct sockaddr *)&peer_addr, &len);
				if(rev == -1)
				{
					perror("getpeername");
				}
				inet_ntop(AF_INET, &peer_addr.sin_addr, peerIP, sizeof(peerIP));
				k=i+1;
				printf("Phase 1: Authentication request. User%d: Username: %s Password: %s Bank Account: %s User IP Addr: %s Authorized: %s\n", k, user[i].name, user[i].password, user[i].account, peerIP, mess[i]);
				if(d[i]==0)
				{
					printf("Phase 1: Auction Server IP Address: %s PreAuction Port Number: %s sent to the <Seller%d>\n\n", hostIP, PREPORT, i);
					llen = sizeof(hostIP);
					gg = send(new_fd[i], hostIP, llen, 0);
					if (gg == -1)
					{
					
						perror("server send to seller");
						
					}
				}
				
			}
			
		}
		
		close(new_fd[i]);
		
	}
	return(1);
}


int get_my_addr(void)
{
	struct sockaddr_in my_addr;
	int getsock_check;
	socklen_t addrlen = sizeof(my_addr);
	getsock_check = getsockname(sockfd, (struct sockaddr *)&my_addr, &addrlen);
	if(getsock_check==-1)
	{
		perror("getsockname");
		exit(1);
	}
	inet_ntop(AF_INET, &my_addr.sin_addr, hostIP, sizeof(hostIP));
	sprintf(hostPort, "%u", ntohs(my_addr.sin_port));
	printf("Phase1: Auction server has TCP port number %s and IP address %s\n\n", hostPort, hostIP);
	return(1);
}         


int phase2(void)
{
	int i;
	int yes1=1;
	int rv1;
	memset(&hints1, 0, sizeof hints1);
	hints1.ai_family = AF_UNSPEC;
	hints1.ai_socktype = SOCK_STREAM;
	hints1.ai_flags = AI_PASSIVE; // use my IP
	if ((rv1 = getaddrinfo(HOST, PREPORT, &hints1, &servinfo1)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv1));
		return 1;
	}
	for(p1 = servinfo1; p1 != NULL; p1 = p1->ai_next) 
	{
		if ((sockfd1 = socket(p1->ai_family, p1->ai_socktype,p1->ai_protocol)) == -1) 
		{
			printf("server: socket error!\n");
			continue;
		}
		/*else
		{
			printf("server: socket success!\n");
		}*/
		if (setsockopt(sockfd1, SOL_SOCKET, SO_REUSEADDR, &yes1,sizeof(int)) == -1) 
		{
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd1, p1->ai_addr, p1->ai_addrlen) == -1) 
		{
			close(sockfd1);
			perror("server: bind error!\n");
			continue;
		}
		/*else
		{
			printf("server: bind success!\n");
		}*/
		break;
	}
	if (p1 == NULL) 
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	freeaddrinfo(servinfo1); 
    if (listen(sockfd1, BACKLOG) == -1) 
	{
		printf("server: listen error!\n");
		exit(1);
	}
	/*else
	{ 
		printf("server: listen success!\n");
	}*/
	get_my_addragain();
	for(i=0;i<2;i++)
	{
		sin_size = sizeof user_addr;
		/*printf("begin to accept!!!!\n");*/
		renew_fd[i] = accept(sockfd1, (struct sockaddr *)&user_addr, &sin_size);
		
		if (renew_fd[i] == -1) 
		{
			perror("phase2 accept");
            
		}
		m[i] = recv(renew_fd[i], itembuf[i], 99, 0);
		itembuf[i][m[i]]= '\0';
		if (m[i] == -1)
		{
			perror("phase recv");
			
		}
		i=i+1;
		printf("Phase 2: <Seller%d> send item Lists.\n", i);
		i=i-1;
		fprintf(stdout, "%s\n", itembuf[i]);
	}
	printf("End of Phase 2 for Auction Server\n");
	close(sockfd1);
	return(1);
}


int get_my_addragain(void)
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
	/*inet_ntop(AF_INET, &my_addr.sin_addr, hostIP, sizeof(hostIP));
	sprintf(hostPort, "%u", ntohs(my_addr.sin_port));
	printf("Phase1: Auction server has TCP port number %s and IP address %s\n", hostPort, hostIP);*/
	return(1);

}
         
