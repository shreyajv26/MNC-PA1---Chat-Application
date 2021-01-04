/**
 * @spampatt_assignment1
 * @author  Shreya Pampattiwar <spampatt@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/global.h"
#include "../include/logger.h"

#define BACKLOG 5
#define STDIN 0
#define TRUE 1
#define CMD_SIZE 100
#define BUFFER_SIZE 256
#define TRUE 1
#define MSG_SIZE 256


/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */

						

int connect_to_host(char *server_ip, int server_port, int PORT)
{
    int fdsocket, len;
    struct sockaddr_in remote_server_addr, remote_client_addr;
    
	fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdsocket < 0)
        perror("Failed to create socket");
    bzero(&remote_client_addr, sizeof(remote_client_addr));
    
    remote_client_addr.sin_family = AF_INET;
    remote_client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    remote_client_addr.sin_port = htons(PORT);
    
    /* Bind 
    if(bind(fdsocket, (struct sockaddr *)&remote_client_addr, sizeof(remote_client_addr)) < 0 )
        perror("Bind failed");
    */
    bzero(&remote_server_addr, sizeof(remote_server_addr));
    remote_server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
    remote_server_addr.sin_port = htons(server_port);
    
    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0){
//        perror("Connect failed");

        cse4589_print_and_log("[%s:ERROR]\n", "LOGIN");
        cse4589_print_and_log("[%s:END]\n", "LOGIN");
    }
    else {
        cse4589_print_and_log("[%s:SUCCESS]\n", "LOGIN");
        cse4589_print_and_log("[%s:END]\n", "LOGIN");
        
    }
    return fdsocket;
}

int isvalidIP(char *ipadr)
{
    struct sockaddr_in temp;
    int result= inet_pton(AF_INET, ipadr, &temp.sin_addr);
    if(result==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


typedef struct Block{
    char* client_ip;
    char* cli_ip1;
    char* cli_ip2;
    char* cli_ip3;
    char* cli_ip4;
    struct Block *next;
};

void fillNullBlock(struct Block** block_head_ref, char * cli_ip){
    struct Block* new_node_bl = (struct Block*) malloc(sizeof(struct Block));
    struct Block *last_bl = (struct Block*) malloc(sizeof(struct Block));
    struct Block* node_bl = (struct Block*) malloc(sizeof(struct Block));
    node_bl = *block_head_ref;
    printf("node entered");
    
    last_bl=*block_head_ref;
    new_node_bl->client_ip = (char*)malloc(sizeof(CMD_SIZE));
    new_node_bl->cli_ip1 = (char*)malloc(sizeof(CMD_SIZE));
    new_node_bl->cli_ip2 = (char*)malloc(sizeof(CMD_SIZE));
    new_node_bl->cli_ip3 = (char*)malloc(sizeof(CMD_SIZE));
    new_node_bl->cli_ip4 = (char*)malloc(sizeof(CMD_SIZE));
    
	strcpy(new_node_bl->client_ip, cli_ip);
    strcpy(new_node_bl->cli_ip1, "");
    strcpy(new_node_bl->cli_ip2, "");
    strcpy(new_node_bl->cli_ip3,"");
    strcpy(new_node_bl->cli_ip4,"");
   	
   	printf("block working");
   	
    if (*block_head_ref == NULL)
    {
        *block_head_ref = new_node_bl;
        new_node_bl->next = NULL;
        printf("first node block");
        //printf("%s,%s,%d",new_node->hostname,new_node->ip,new_node->port_no);
        return;
    }
    // int flag = 0;
//     //insert the client only if its not there
//     for (int i=0; i<4; i++){
//         if (strcmp(node_bl->client_ip,cli_ip) == 0){
//             flag = 1;
//             printf("block\n");
//             break;
//             printf("block");
//         }
//         else{
//             node_bl = node_bl->next;
//         }
//     }
    // printf("still working");
//     if (flag == 0){
//         //insert
        while (last_bl->next != NULL)
            last_bl = last_bl->next;
        printf("yes block");
        //printf("%s,%s,%d",hostname,ip,port_no);
        new_node_bl->next = last_bl->next;
        last_bl->next = new_node_bl;
        printf("Done block");
        return;
//     }
   
}

void appendBlock(struct Block **head, char* client_ip, char* block_ip){
    struct Block* node_bl = (struct Block*) malloc(sizeof(struct Block));
    node_bl = *head;
    //int list_id = 1;
    while (strcmp(node_bl->client_ip, client_ip) != 0)
    {
        if(node_bl-> next == NULL)
			break;
		node_bl = node_bl->next;
		
    }
    if (strcmp(node_bl->cli_ip1,"") == 0){
        strcat(node_bl->cli_ip1,block_ip);
    }
    else if (strcmp(node_bl->cli_ip2,"") == 0){
        strcat(node_bl->cli_ip2,block_ip);
    }
    else if (strcmp(node_bl->cli_ip3,"") == 0){
        strcat(node_bl->cli_ip3,block_ip);
    }
    else if (strcmp(node_bl->cli_ip4,"") == 0){
        strcat(node_bl->cli_ip4,block_ip);
    }
    //return;
    
}

void unBlock(struct Block **head, char* client_ip, char* block_ip){
    struct Block* node_bl = (struct Block*) malloc(sizeof(struct Block));
    node_bl = *head;
    //int list_id = 1;
    while (strcmp(node_bl->client_ip, client_ip) != 0)
    {
        node_bl = node_bl->next;
    }
    if (strcmp(node_bl->cli_ip1, block_ip)==0){
        node_bl->cli_ip1 = NULL;
    }
    else if (strcmp(node_bl->cli_ip2, block_ip) == 0){
        node_bl->cli_ip1 = NULL;
    }
    else if (strcmp(node_bl->cli_ip3, block_ip) == 0){
        node_bl->cli_ip1 = NULL;
    }
    else if (strcmp(node_bl->cli_ip4, block_ip) == 0){
        node_bl->cli_ip1 = NULL;
    }
    return;
}

int isBlocked(struct Block *head, char* client_ip, char* block_ip){
    struct Block* node=head;
    //int list_id = 1;
    while (strcmp(node->client_ip, client_ip) !=0)
    {
        node = node->next;
    }
    if (strcmp(node->cli_ip1, block_ip)==0){
        return 1;
    }
    else if (strcmp(node->cli_ip2, block_ip) == 0){
        return 1;
    }
    else if (strcmp(node->cli_ip3, block_ip) == 0){
        return 1;
    }
    else if (strcmp(node->cli_ip4, block_ip) == 0){
        return 1;
    }
    else{
        return 0;
    }
}


 typedef struct Node{
	 char *hostname;
	 char *ip;
	 int port_no;
	 int num_msg_recv;
     int num_msg_sent;
	 int fdsocket_cl;
     int status;
     char* msg;
     struct Node *next;
 };
 
 void send_list_back(struct Node** head_ref, int fdaccept){
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node = *head_ref;
	

char* hname = (char*)malloc(256);
char* ipname = (char*)malloc(16);
char* portname = (char*)malloc(16);
int count = 0;
//strcpy(hname, " ");
while (node != NULL){
	printf("while\n");
	strcat(hname, node->hostname);
	count = 1;
	strcpy(ipname, node->ip);
    snprintf(portname, sizeof(portname), "%d", node->port_no);
    strcat(hname," ");
    strcat(hname,ipname);
    strcat(hname," ");
    strcat(hname, portname);
    strcat(hname, " ");
    printf("hname is %s ",hname);
    printf("size: %d",sizeof(hname));                       
//     char* hname = (char*)malloc(256);
	node = node->next;
}

if (send(fdaccept, hname, 256, 0) < 0){
	printf("tcp error");
}
else {
	printf("[%s:SUCCESS]\n", "sent");
    printf("[%s:END]\n", "sent");
}
}

//https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/ 
void appendList(struct Node** head_ref, char *hostname, char *ip, int port_no, int fdsocket_cl){
	
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node *last = (struct Node*) malloc(sizeof(struct Node));
	
	last=*head_ref;
	new_node->hostname = (char*)malloc(sizeof(hostname));
	new_node->ip = (char*)malloc(sizeof(ip));
	strcpy(new_node->hostname,hostname);
	strcpy(new_node->ip,ip);
	new_node->port_no = port_no;
	new_node->fdsocket_cl = fdsocket_cl;
	
	if (*head_ref == NULL) 
    { 
	   *head_ref = new_node; 
	   new_node->next = NULL;
	   printf("%s,%s,%d",new_node->hostname,new_node->ip,new_node->port_no);
       return; 
    }
	
	while (last->next != NULL) 
        last = last->next; 
	
	//printf("%s,%s,%d",hostname,ip,port_no);
	new_node->next = last->next; 
	last->next = new_node;
	return;
}

//https://stackoverflow.com/questions/26352007/inserting-in-singly-linked-list-in-ascending-order
void sorted_insert(struct Node** head_ref, char *hostname, char *ip, int port_no, int fdsocket_cl, int status) {
    
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node* needle = (struct Node*) malloc(sizeof(struct Node));
	struct Node* needle_no = *head_ref;
    
    needle=*head_ref;
    new_node->hostname = (char*)malloc(sizeof(hostname));
    new_node->ip = (char*)malloc(sizeof(ip));
    strcpy(new_node->hostname,hostname);
    strcpy(new_node->ip,ip);
    new_node->port_no = port_no;
    new_node->fdsocket_cl = fdsocket_cl;
	new_node->status = status;
    
    
    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = NULL;
        return;
    }
    
	//needle_no = *head_ref;
	while(strcmp(needle_no->ip,ip) != 0){
			printf("first while\n");
			if (needle_no->next != NULL){
				needle_no = needle_no->next;
				printf("firstttt\n");
				}
			else {
			break;
			}
	}
	printf("out of while\n");
	if(strcmp(needle_no -> ip,ip) == 0){
	needle_no->port_no = port_no;
	needle_no->fdsocket_cl = fdsocket_cl;
	needle_no->status = status;
	printf("inside if\n");
	}
	
    // Should we insert at the head of the linked list
	else{
		if (new_node->port_no < (*head_ref)->port_no) {
		printf("inside else if\n");
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
		}
    
    // Otherwise, find the last element that is smaller than this node
    //struct node *needle = *head_ref;
    while (TRUE) {
        if (needle->next == NULL)
            break;
        if (new_node->port_no < needle->next->port_no)
            break;
        needle = needle->next;
        printf("inside second while\n");
    }
    printf("outside second while");
    // Insert the element
    new_node->next = needle->next;
    needle->next = new_node;
	
    
	}
	return;

}




typedef struct ClientNode{
    char *hostname;
    char *ip;
    int port_no;
    struct ClientNode *next;
};

//https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
void appendClientList(struct ClientNode** cli_head_ref, char *hostname, char *ip, int port_no){
    
    struct ClientNode* new_node = (struct ClientNode*) malloc(sizeof(struct ClientNode));
    struct ClientNode *last = (struct ClientNode*) malloc(sizeof(struct ClientNode));
    
    last=*cli_head_ref;
    new_node->hostname = (char*)malloc(sizeof(hostname));
    new_node->ip = (char*)malloc(sizeof(ip));
    strcpy(new_node->hostname,hostname);
    strcpy(new_node->ip,ip);
    new_node->port_no = port_no;
    
    if (*cli_head_ref == NULL)
    {
        *cli_head_ref = new_node;
        new_node->next = NULL;
//         printf("%s,%s,%d",new_node->hostname,new_node->ip,new_node->port_no);
        return;
    }
    
    while (last->next != NULL)
    last = last->next;
    
    //printf("%s,%s,%d",hostname,ip,port_no);
    new_node->next = last->next;
    last->next = new_node;
    return;
}

int isClientValid(struct ClientNode *head, char* ip){
    struct ClientNode* node=head;
    while (node != NULL)
    {
        if (strcmp(node->ip, ip) == 0){
            return 1;
        }
        node = node->next;
    }
    return 0;
}



void printList(struct Node *head)
{
  struct Node* node=head;
  int list_id = 1;
  while (node != NULL)
  {
	if((node -> status) == 1){

		cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", list_id, node->hostname, node->ip, node->port_no);
		list_id = list_id + 1;
	}
	node = node->next;
	printf("come out");
	}
}

void printClientList(struct ClientNode *head)
{
    struct ClientNode* node=head;
    int list_id = 1;
    while (node != NULL)
    {
        //cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", list_id, node->hostname, node->ip, node->port_no);
        cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", list_id, node->hostname, node->ip, node->port_no);
        node = node->next;
        list_id = list_id + 1;
    }
}

void deleteList(struct ClientNode** cli_head_ref)
{
    
    /* deref head_ref to get the real head */
    struct ClientNode* current = *cli_head_ref;
    struct ClientNode* next;
    
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    /* deref head_ref to affect the real head back
     in the caller. */
    *cli_head_ref = NULL;
}

void printStat(struct Node *head)
{
  struct Node* node=head;
  int list_id = 1;
  while (node != NULL)
  {

if(node->status == 0)
	//cse4589_print_and_log("%-5d%-35s%-20s%-8d%-8s\n", list_id, node->hostname, node->ip, node->port_no,"Logged-out");
	cse4589_print_and_log("%-5d%-35s%-8d%-8d%-8s\n", list_id, node-> hostname, node->num_msg_sent, node->num_msg_recv, "Logged-out");
else
	//cse4589_print_and_log("%-5d%-35s%-20s%-8d%-8s\n", list_id, node->hostname, node->ip, node->port_no,"Logged-in");
	cse4589_print_and_log("%-5d%-35s%-8d%-8d%-8s\n", list_id, node-> hostname, node->num_msg_sent, node->num_msg_recv, "Logged-in");
     node = node->next;
	 
	list_id = list_id + 1;
  }

}

void printBlock(struct Block *head)
{
    struct Block* node_bl=head;
    int list_id = 1;
    while (node_bl != NULL)
    {
        //cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", list_id, node->hostname, node->ip, node->port_no);
        cse4589_print_and_log("%-5d%-35s%-8d%-8d%-8s\n", list_id, node_bl->client_ip, node_bl->cli_ip1, node_bl->cli_ip2,node_bl->cli_ip3);
        node_bl = node_bl->next;
        list_id = list_id + 1;
    }

}


int main(int argc, char **argv)
{
	/*Init. Logger*/
	cse4589_init_log(argv[2]);

	/*Clear LOGFILE*/
	fclose(fopen(LOGFILE, "w"));

	/*Start Here*/
	if(argc != 3) {    //if 2 args are not provided. User cant go ahead without providing 2nd argment for port#
		printf("Usage:%s [port]\n", argv[0]);
		exit(-1);
	}
	
	int PORT;
	PORT = atoi(argv[2]);

    struct Node *head_ref = NULL;    //making the list null
    struct ClientNode *cli_head_ref = NULL;
    struct Block *block_head_ref = NULL;
    const char * start;
    start = argv[1];
//    printf("%s",start);
	if (strcmp(start, "s") == 0)
	{
//         printf("hi");
		int port, server_socket, head_socket, selret, sock_index, fdaccept=0, caddr_len;
		struct sockaddr_in server_addr, client_addr;
		fd_set master_list, watch_list;
        

		/* Socket */
		server_socket = socket(AF_INET, SOCK_STREAM, 0);	//domain-IPv4,type-TCP,protocol
		if(server_socket < 0)
			perror("Cannot create socket");

		/* Fill up sockaddr_in struct */
//        port = atoi(argv[1]);
		bzero(&server_addr, sizeof(server_addr));	////clear server_addr

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(PORT);

		/* Bind */
		if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 )
			perror("Bind failed");

		/* Listen */
		if(listen(server_socket, BACKLOG) < 0)
			perror("Unable to listen on port");
		
		/* Zero select FD sets */
		FD_ZERO(&master_list);
		FD_ZERO(&watch_list);
		
		/* Register the listening socket */
		FD_SET(server_socket, &master_list);
		/* Register STDIN */
		FD_SET(STDIN, &master_list);

		head_socket = server_socket;
        
		while(TRUE)
		{
//            printf("hey");
			memcpy(&watch_list, &master_list, sizeof(master_list));
			/* select() system call. This will BLOCK */
			selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);
			if(selret < 0)
				perror("select failed\n");
			/* Check if we have sockets/STDIN to process */
			if(selret > 0)
			{
				/* Loop through socket descriptors to check which ones are ready */
				for(sock_index=0; sock_index<=head_socket; sock_index+=1)
				{
					if(FD_ISSET(sock_index, &watch_list))
					{
						/* Check if new command on STDIN */
						if (sock_index == STDIN)
						{
							char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);
							memset(cmd, '\0', CMD_SIZE);
							if(fgets(cmd, CMD_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to cmd
								exit(-1);
//                            printf("cool");
							printf("\nI got: %s\n", cmd);
							
							//Process PA1 commands here ...
							//AUTHOR COMMAND
							if (strcmp(cmd, "AUTHOR\n") == 0)
							{
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
								cse4589_print_and_log("I, %s, %s have read and understood the course academic integrity policy.\n", "spampatt","kavithac");
                                cse4589_print_and_log("[%s:END]\n", cmd);
							}
							
							//IP COMMAND
                            else if (strcmp(cmd, "IP\n") == 0){
                                struct sockaddr_in ip_udp;
                                int dummy_udp =socket(AF_INET, SOCK_DGRAM, 0);
                                if(dummy_udp < 0){
                                    printf("Error while creating UDP socket\n");
                                    return -1;
                                    }
                                int length = sizeof(ip_udp);
                                char ip[INET_ADDRSTRLEN];
//                                 uint16_t gport = 53;
                                const char* googleip = "8.8.8.8";
                                memset(&ip_udp, 0, length);
                                ip_udp.sin_family = AF_INET;
                                ip_udp.sin_addr.s_addr = inet_addr(googleip);
                                ip_udp.sin_port = htons(53);
                               inet_pton(AF_INET, googleip, &ip_udp.sin_addr);
                                

                                if(connect(dummy_udp, (struct sockaddr*)&ip_udp, length) < 0){
                                    cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                    cse4589_print_and_log("[%s:END]\n", cmd);
                                    printf("[%s:ERROR]\n", cmd);
                                    
                                }

                                else{
                                    if (getsockname(dummy_udp, (struct sockaddr *)&ip_udp, (unsigned int*)&length) == -1){
                                        perror("getsockname");
                                        cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                        cse4589_print_and_log("[%s:END]\n", cmd);
                    
                                    }
                                    else{
                                        inet_ntop(AF_INET, &(ip_udp.sin_addr), ip, length);
                                        cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                        cse4589_print_and_log("IP:%s\n",ip);
                                        cse4589_print_and_log("[%s:END]\n", cmd);
                                    }
                                }
                                close(dummy_udp);
                            }

							//PORT COMMAND
							else if (strcmp(cmd, "PORT\n") == 0)
							{
								cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
								cse4589_print_and_log("%d",PORT);
								cse4589_print_and_log("[%s:END]\n", cmd);
							}
							else if (strstr(cmd, "BLOCKED"))
							{	
								struct Block *node_bl = (struct Block*) malloc(sizeof(struct Block));
								node_bl=block_head_ref;
								char delim[] = " ";
                                int count = 1;
                                char *ptr = strtok(cmd, delim);
                                char *cli_ip;
                                char* commandd;
                                char* dup_cli_ip;
                                int flag;
                                printf("Start block");
                                printf("%s\n",ptr);
                                commandd = ptr;
                                
                                while (ptr != NULL)
                                {
                                	printf("loop\n");
                                    if (count==1){
                                    	printf("if 1\n");
                                        ptr = strtok(NULL, delim);
                                        dup_cli_ip = ptr;
                                        cli_ip = ptr;
                                        // printf("%s\n",ptr);
//                                         printf("if 11\n");
                                        ptr = NULL;
                                        count += 1;
                                        
                                    }
                                    
								}
									dup_cli_ip[strlen(dup_cli_ip)-1] = '\0';
									flag =isvalidIP(dup_cli_ip);
									// printf("%d",flag);
// //                                     printf("end while\n");
//                                 	printf("mutation\n");
// 									
// 									printf("Seg1\n");
									while (strcmp(node_bl->client_ip, cli_ip)!=0)
									{	
										printf("Seg2\n");	
										if(node_bl -> next == NULL)
											break;
										node_bl = node_bl->next;
									}
									printf("before if\n");
									if (flag){
										printf("Seg3\n");
										if (strcmp(node_bl->client_ip,cli_ip)==0){
										printf("%s\n%s\n%s\n%s\n",node_bl->cli_ip1,node_bl->cli_ip2,node_bl->cli_ip3,node_bl->cli_ip4);
										printBlock(block_head_ref);
										}
										else {
										printf("Client not found\n");
										}
									}	
										
								// cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
// // 								printBlock(block_head_ref, ip);
// 								cse4589_print_and_log("[%s:END]\n", cmd);
							}
							
							//LIST COMMAND
							else if (strcmp(cmd, "LIST\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                printList(head_ref);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            else if (strcmp(cmd, "STATISTICS\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                printStat(head_ref);
                                cse4589_print_and_log("[%s:END]\n", cmd);
							}

                            else
                            {
                                cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
						free(cmd);
						}
						
						/* Check if new client is requesting connection */
					else if(sock_index == server_socket){
						struct hostent *hn;
                        struct in_addr addr_ip;
                        char ip_address[INET_ADDRSTRLEN];
                        int client_port;
						int status = 0;
						//struct sockaddr_in client_addr;
						
                        caddr_len = sizeof(client_addr);
                        fdaccept = accept(server_socket, (struct sockaddr *)&client_addr, &caddr_len);
                        if(fdaccept < 0)
                            perror("Accept failed\n");
                        
                        /* Add to watched socket list */
                        FD_SET(fdaccept, &master_list);
                        if(fdaccept > head_socket) head_socket = fdaccept;
						printf("fdaccept is: %d",fdaccept);
						int fdaccept_me = fdaccept;
                        status = 1;
                        //get ip address, client port and hostname
                        inet_ntop(AF_INET, &(client_addr.sin_addr), ip_address, INET_ADDRSTRLEN);
                        inet_pton(AF_INET,ip_address, &addr_ip);

						
                        client_port = (int)ntohs(client_addr.sin_port);

                        hn = gethostbyaddr(&addr_ip, sizeof(addr_ip), AF_INET);
                        char* host_name = hn->h_name;
                        sorted_insert(&head_ref,host_name,ip_address, client_port, fdaccept_me, status);
                        fillNullBlock(&block_head_ref,ip_address);
                        send_list_back(&head_ref,fdaccept_me);
						
						// bzero(&client_addr, sizeof(client_addr));
// 						bzero(&addr_ip,sizeof(addr_ip));

                        
						printf("\nRemote Host connected!\n");                        

                        
                    }
                    /* Read from existing clients */
                    else{
                        /* Initialize buffer to receieve response */
                        char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                        char *dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                        memset(buffer, '\0', BUFFER_SIZE);

                        if(recv(sock_index, buffer, BUFFER_SIZE, 0) <= 0){
                            close(sock_index);
                            printf("Remote Host terminated connection!\n");

                            /* Remove from watched list */
                            FD_CLR(sock_index, &master_list);
                        }
                        else {
                        	//Process incoming data from existing clients here ...
//                            char *msg;
//                            char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
//                            memset(buffer, '\0', BUFFER_SIZE);
//                            msg = recv(sock_index, buffer, BUFFER_SIZE, 0);
                            printf("%s\n",buffer);
                            //send that message to the client if loggined or else store it in buffer
                            // char delim[] = " ";
//                             int count = 1;
//                             strcpy(dup_buffer,buffer);
//                             char *ptr = strtok(buffer, delim);
//                             char* cli_cmd;
//                             char* var1;
//                             char* var2;
//                             int temp;
//                             char* temp_msg;
//                             char* dup_var1;
//                             
//                             while (ptr != NULL)
//                             {
//                                 if (count==1){
//                                     cli_cmd = ptr;
//                                     ptr = strtok(NULL, delim);
//                                     count += 1;
//                                 }
//                                 else if (count==2){
//                                     var1 = ptr;
//                                     dup_var1 = ptr;
//                                     ptr = strtok(NULL, delim);
//                                     count += 1;
//                                 }
//                                 else if (count==3){
//                                     var2 = ptr;
//                                     ptr = strtok(NULL, delim);
//                                     count += 1;
//                                 }
//                         //     }
                            if (strstr(buffer,"SEND"))
                            {
//                             	char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
//     buffer = "SEND 123.4.52.33 hello kavitha nice to meet you kavs";
    						char *dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
    						char delim[] = " ";
                            int count = 1;
                            strcat(buffer," ");
                            strcat(buffer,"kavs\n");
                            strcpy(dup_buffer,buffer);
                            //printf("seg\n");
                            char *ptr = strtok(dup_buffer, delim);
                            //printf("seg1\n");
                            char* cli_cmd;
                            char* var1;
                            char* var2;
                            int temp;
                            char* temp_msg;
                            char* dup_var1;
                            char* sam =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            char* samplemsg =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            while (ptr != NULL)
                            {
								printf("while\n");
                                if (count==1){
                                    cli_cmd = ptr;
                                    ptr = strtok(NULL, delim);
                                    var1 = ptr;
                                    printf("%s\n",var1);
                                    count += 1;
                                
                                }
                                else if (count==2){
                                    //printf("cnt2\n");
                                    
                                    ptr = strtok(NULL, delim);
                                    
                                    //printf("hey\n");
                                    var2 = ptr;
									printf("%sdddd\n",var2);
                                    if (strcmp(var2,"kavs\n")==0){
										printf("enter kavs\n");
                                        break;
									}
                                    printf("%sdddd\n",var2);
                                    strcat(sam,var2);
                                    strcat(sam," ");
                                    
                                    
                                }
                                
                            //printf("while ends\n");  
                            }	
								char* sam1 =(char*) malloc(sizeof(char)*BUFFER_SIZE);
								strcpy(sam1,sam);
								
								// strcat(var1," ");
// 								strcat(var1,sam1);
								
		
                                printf("sam1 is %s\n",sam1);
                                //printf("%s\n%s\n",cli_cmd,var1);

                            	
                                int temp1 = 0;
                                int temp2 = 0;	
								struct Node* node1 = (struct Node*) malloc(sizeof(struct Node));
								struct Node* node2 = (struct Node*) malloc(sizeof(struct Node));
								//struct Node *node1 = (struct Node*) malloc(sizeof(struct Node));
								//struct Node *node2 = (struct Node*) malloc(sizeof(struct Node));
								//printf("before head\n");
                                
								node1 = head_ref;
                                node2 = head_ref;
								
                                while (strcmp(node1->ip, var1) !=0)
                                {	
                                    node1 = node1->next;
									printf("%s\n",node1->ip);
									printf("var1%s\n",var1);
                                }
								
								printf("%s\n",node1->ip);
								printf("var1%s\n",var1);
								
                                int sock = node1->fdsocket_cl;

								
                                while (node2->fdsocket_cl != sock_index)
                                {
                                    node2 = node2->next;
									//printf("while2\n");
									printf("%d",node2->fdsocket_cl);
									printf("sock_index%d",sock_index);
                                }
								
								printf("out while2\n");
                                char * sender_ip;
                                sender_ip = node2->ip;
                                
                                int flag;
                                //flag = isBlocked(block_head_ref,var1, sender_ip);
                                //if (flag == 0)
								//{
                                    //if (node1->status > 0)
									//{
                                // if not in block list send
                                
                                strcpy(samplemsg,sender_ip);
                                strcat(samplemsg," ");
                                //strcat(samplemsg,var1);
                                //strcat(samplemsg," ");
                                strcat(samplemsg,sam1);
                                strcat(samplemsg," ");
                            	strcat(samplemsg,"kavs\n");
                            
                                        if (send(sock, samplemsg, 256, 0) < 0)
										{
                                            printf("Error Send()\n");
                                        }
                                        else{
                                            temp2 = node2->num_msg_sent;
                                            temp2 += 1;
                                            node2->num_msg_sent = temp2;
											printf("Success Send()\n");
                                            temp1 = node1->num_msg_recv;
                                            temp1 += 1;
                                            node1->num_msg_recv = temp1;
                                            //increment msg sent too
                                            }
                                   // }
//                                    else {
//                                        temp_msg = node1->msg;
//                                        strcat(temp_msg," ");
//                                        strcat(temp_msg, var2);
//                                        node1->msg = temp_msg;
//                                        }
                                    //}
                                
                            }
							
                            else if (strstr(buffer,"BLOCK"))
                            {
							cse4589_print_and_log("[%s:SUCCESS]\n", buffer);
							
                            char delim[] = " ";
                            int count = 1;
                            strcpy(dup_buffer,buffer);
                            char *ptr = strtok(dup_buffer, delim);
                            char* cli_cmd;
                            char* var1;
                            char* var2;
                            int temp;
                            char* temp_msg;
                            char* dup_var1;
                            
                            while (ptr != NULL)
                            {
                                if (count==1){
                                    cli_cmd = ptr;
                                    ptr = strtok(NULL, delim);
									var1 = ptr;
                                    dup_var1 = ptr;
                                    count += 1;
									ptr = NULL;
                                }
								/*
                                else if (count==2){
                                    var1 = ptr;
                                    dup_var1 = ptr;
                                    ptr = strtok(NULL, delim);
                                    count += 1;
                                }
                                else if (count==3){
                                    var2 = ptr;
                                    ptr = strtok(NULL, delim);
                                    count += 1;
                                }
								*/
								cse4589_print_and_log("[%s:END]\n", buffer);
                            }
                            	
                            	
                            	printf("Server side block");
//                             	char* dup_var;
                                //struct Block* blocknode = block_head_ref;
                                struct Node* node = head_ref;
                                int flag;
                                while (node->fdsocket_cl != sock_index)
                                {
                                    node = node->next;
                                    printf("casual\n");
									
                                }
                                char* temp_ip = (char*) malloc(sizeof(char)*CMD_SIZE);
                                temp_ip = node->ip;
//                                 strcpy(dup_var,var1);
								printf("before dup var\n");
                                dup_var1[strlen(dup_var1)-1] = '\0';
                                printf("after dup var\n");
                                flag = isvalidIP(dup_var1);
                                printf("flag: %d\n",flag);
                                if (flag == 1){
                                printf("Entering flag\n");
								printf("temp_ip: %s\n",temp_ip);
								printf("var1: %s\n",var1);
                                appendBlock(&block_head_ref,temp_ip,var1);
                                }
                                
                            }
                            else if (strstr(buffer,"UNBLOCK"))
                            {
								
								cse4589_print_and_log("[%s:SUCCESS]\n", buffer);
								cse4589_print_and_log("[%s:END]\n", buffer);
                             char delim[] = " ";
                            int count = 1;
                            strcpy(dup_buffer,buffer);
                            char *ptr = strtok(buffer, delim);
                            char* cli_cmd;
                            char* var1;
                            char* var2;
                            int temp;
                            char* temp_msg;
                            char* dup_var1;
                            
                            while (ptr != NULL)
                            {
                                if (count==1){
                                    cli_cmd = ptr;
                                    ptr = strtok(NULL, delim);
                                    count += 1;
                                }
                                else if (count==2){
                                    var1 = ptr;
                                    dup_var1 = ptr;
                                    ptr = strtok(NULL, delim);
                                    count += 1;
                                }
                                else if (count==3){
                                    var2 = ptr;
                                    ptr = strtok(NULL, delim);
                                    count += 1;
                                }
                            }
                            	
                            	
                            	printf("Server side block");
//                             	char* dup_var;
                                struct Block* blocknode = block_head_ref;
                                struct Node* node = head_ref;
                                int flag;
                                while (node->fdsocket_cl != sock_index)
                                {
                                    node = node->next;
                                    printf("casual\n");
                                }
                                char* temp_ip;
                                temp_ip = node->ip;
//                                 strcpy(dup_var,var1);
								printf("before dup var\n");
                                dup_var1[strlen(dup_var1)-1] = '\0';
                                printf("after dup var\n");
                                flag = isvalidIP(dup_var1);
                                printf("flag: %d\n",flag);
                                if (flag == 1){
                                unBlock(&block_head_ref,temp_ip,var1);
                                }
                            }
                            else if (strstr(buffer,"BROADCAST"))
                            {
								struct Node* node_l = head_ref;
								struct Node* node_s = head_ref;
                                int flag;
                                /*
								while (node_l->fdsocket_cl != sock_index)
                                {
                                    node_l = node_l->next;
                                    printf("casual\n");
                                }
                                char* temp_ip = = (char*) malloc(sizeof(char)*CMD_SIZE);
                                temp_ip = node_l->ip;
								*/
								
								char *dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
    						char delim[] = " ";
                            int count = 1;
                             strcat(buffer," ");
                             strcat(buffer,"kavs\n");
                            strcpy(dup_buffer,buffer);
                            //printf("seg\n");
                            char *ptr = strtok(dup_buffer, delim);
                            //printf("seg1\n");
                            char* cli_cmd;
                            char* var1 =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            char* var2;
                            int temp;
                            char* temp_msg;
                            char* dup_var1;
                            char* sam =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            char* samplemsg =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            while (ptr != NULL)
                            {
								printf("while\n");
                                if (count==1){
                                    cli_cmd = ptr;
                                    ptr = strtok(NULL, delim);
                                    var1 = ptr;
                                    printf("%s\n",var1);
                                    count += 1;
                                
                                }
                                else if (count==2){
                                    //printf("cnt2\n");
                                    
                                    ptr = strtok(NULL, delim);
                                    
                                    //printf("hey\n");
                                    var2 = ptr;
									printf("%sdddd\n",var2);
                                    if (strcmp(var2,"kavs\n")==0){
										printf("enter kavs\n");
                                        break;
									}
                                    printf("%sdddd\n",var2);
                                    strcat(sam,var2);
                                    strcat(sam," ");
                                    
                                    
                                }
                                
                            //printf("while ends\n");  
                            }	
								char* sam1 =(char*) malloc(sizeof(char)*BUFFER_SIZE);
								strcat(var1," ");
								strcat(var1,sam);
								strcpy(sam1,var1);
								
								
								while (node_s != NULL)
								{
									if (node_s->fdsocket_cl != sock_index){
										int sock = node_s->fdsocket_cl;
										if (send(sock, sam1, 256, 0) >=0 )
										{
                                            printf("Send()\n");
                                        }
									}
									node_s = node_s->next;
								}
                                cse4589_print_and_log("[%s:SUCCESS]\n", buffer);
								cse4589_print_and_log("[%s:END]\n", buffer);
                            }
                        
                            else if (strstr(buffer,"REFRESH\n"))
                            {	
								cse4589_print_and_log("[%s:SUCCESS]\n", buffer);
								printf("Client asked for refresh");
                                send_list_back(&head_ref,sock_index);
								cse4589_print_and_log("[%s:END]\n", buffer);
                            }
							
							
							
							else if (strstr(buffer,"LOGOUT\n"))
                            {	
								cse4589_print_and_log("[%s:SUCCESS]\n", buffer);
								cse4589_print_and_log("[%s:END]\n", buffer);
								printf("Client asked for logout");
                                struct Node* node_lo = head_ref;
								
								//sock_index
								while (node_lo != NULL){
									
									if(node_lo->fdsocket_cl == sock_index)
                                {
                                    printf("casual\n");
									node_lo->status = 0;
									
									close(sock_index);
									sock_index =  -1;
									break;
                                }
								
								
								printf("Node set to 0");
								
								node_lo = node_lo->next;
								
								}	
								
                            }
                            
                            
//                            struct Node* node = head_ref;
//                            while (node->ip != cli_ip)
//                            {
//                                node = node->next;
//                            }
//                            int sock = node->fdsocket_cl;
//                            // if not in block list send
//                            if (send(sock, command, sizeof(command), 0) < 0){
//                                tcperror("Send()");
//                            }
//                            else{
//                                temp = node->num_msg_recv;
//                                temp += 1;
//                                node->num_msg_recv = temp;
//                                }
                            
                            
                            
                        	printf("\nClient sent me: %s\n", buffer);
							//printf("ECHOing it back to the remote host ... \n");
							//if(send(fdaccept, buffer, strlen(buffer), 0) == strlen(buffer))
								//printf("Done!\n");
							fflush(stdout);
                        }

                        free(buffer);
                    }
                }
            }
        }
    }

    return 0;
}
	
	
    else if (strcmp(argv[1], "c") == 0)
    {

			int server;
			//char *server_ip;

			int port, head_socket, selret, sock_index, fdsocket, caddr_len;
			struct sockaddr_in server_addr, client_addr;
			fd_set master_list, watch_list;


			int PORT = (int)atoi(argv[2]);

			FD_ZERO(&master_list);
			FD_ZERO(&watch_list);

			FD_SET(STDIN, &master_list);

			head_socket = STDIN;
        
        while (TRUE)
        {	
			printf("\n[PA1-Client@CSE489/589]$ ");
			fflush(stdout);
			
        	memcpy(&watch_list, &master_list, sizeof(master_list));
			/* select() system call. This will BLOCK */
			selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);
			if(selret < 0)
				perror("select failed\n");
			/* Check if we have sockets/STDIN to process */
			if(selret > 0)
			{
				/* Loop through socket descriptors to check which ones are ready */
				for(sock_index=0; sock_index<=head_socket; sock_index+=1)
				{
					if(FD_ISSET(sock_index, &watch_list))
					{
					char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);
					//fflush(stdout);
					if (sock_index== STDIN){
							
                          	//char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);
                            char *command= (char*) malloc(sizeof(char)*CMD_SIZE);
                            char *sendmsg= (char*) malloc(sizeof(char)*CMD_SIZE);
                            memset(cmd, '\0', CMD_SIZE);
                            if(fgets(cmd, CMD_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to cmd
                                exit(-1);
                            strcpy(command,cmd);
                            strcpy(sendmsg,command);
                            char* input = strtok(command, " ");
							//strcat(input,"\n");
                            printf("\nI got: %s\n", cmd);
                            
                            //AUTHOR COMMAND
                            if (strcmp(cmd, "AUTHOR\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", command);
                                cse4589_print_and_log("I, %s, %s have read and understood the course academic integrity policy.\n", "spampatt","kavithac");
                                cse4589_print_and_log("[%s:END]\n", command);
                            }
							
							//LIST COMMAND
                            else if (strcmp(cmd, "LIST\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                printClientList(cli_head_ref);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
							
							
							//REFRESH COMMAND
                            else if (strcmp(cmd, "REFRESH\n") == 0)
                            {
								//cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
								if (send(fdsocket, cmd, strlen(cmd), 0) == strlen(cmd))
								{
								//char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
								printClientList(cli_head_ref);
								printf("REFRESH command sent!\n");
								}
								char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
								memset(buffer, '\0', BUFFER_SIZE);

								if(recv(fdsocket, buffer, BUFFER_SIZE, 0) >= 0)
								{
								printf("Server responded: %s\n", buffer);
								deleteList(&cli_head_ref);
								//char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
								//printf("%s\n",buffer);
								//memset(buffer, '\0', BUFFER_SIZE);

								char delim[] = " ";
								int count = 1;
								char* dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
								strcpy(dup_buffer,buffer);
								char *ptr = strtok(buffer, delim);
								char* lis_port;
								char* lis_ip;
								char* lis_hostname;

								while (ptr != NULL)
								{
								printf("enter while\n");
								if (count==1){
								lis_hostname = ptr;
								ptr = strtok(NULL, delim);
								count += 1;
								}
								else if (count==2){
								lis_ip = ptr;
								ptr = strtok(NULL, delim);
								count += 1;
								}
								else if (count==3){

								lis_port = ptr;
								ptr = strtok(NULL, delim);
								count += 1;
								int list_port = atoi(lis_port);

								printf("inserted\n");
								appendClientList(&cli_head_ref,lis_hostname,lis_ip, list_port);
								}
								else if (count ==4){
								int list_port = atoi(lis_port);
								count -= 3;

								}

								}
								cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
								//printClientList(cli_head_ref);
								cse4589_print_and_log("[%s:END]\n", cmd);

								}

								else{
								printf("REFRESH failed");
								cse4589_print_and_log("[%s:ERROR]\n", cmd);
								cse4589_print_and_log("[%s:END]\n", cmd);
                                            }
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
							
							
							//LOGOUT COMMAND
                            else if (strcmp(cmd, "LOGOUT\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                //printClientList(cli_head_ref);
								if (send(fdsocket, cmd, strlen(cmd), 0) == strlen(cmd)){
                                            	printf("LOGOUT command sent!\n");
												//sock_index = -1;
												close(sock_index);
												
										}
								else{
												printf("LOGOUT failed");
												cse4589_print_and_log("[%s:ERROR]\n", cmd);
												cse4589_print_and_log("[%s:END]\n", cmd);
                                            }
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            
							//IP COMMAND
                            else if (strcmp(cmd, "IP\n") == 0)
							{
                                struct sockaddr_in ip_udp;
                                int dummy_udp =socket(AF_INET, SOCK_DGRAM, 0);
                                if(dummy_udp < 0){
                                    printf("Error while creating UDP socket\n");
                                    return -1;
                                    }
                                int length = sizeof(ip_udp);
                                char ip[INET_ADDRSTRLEN];
//                                 uint16_t gport = 53;
                                const char* googleip = "8.8.8.8";
                                memset(&ip_udp, 0, length);
                                ip_udp.sin_family = AF_INET;
                                ip_udp.sin_addr.s_addr = inet_addr(googleip);
                                ip_udp.sin_port = htons(53);
                               inet_pton(AF_INET, googleip, &ip_udp.sin_addr);
                                

                                if(connect(dummy_udp, (struct sockaddr*)&ip_udp, length) < 0){
                                    cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                    cse4589_print_and_log("[%s:END]\n", cmd);
                                    printf("[%s:ERROR]\n", cmd);
                                    
                                }

                                else{
                                    if (getsockname(dummy_udp, (struct sockaddr *)&ip_udp, (unsigned int*)&length) == -1){
                                        perror("getsockname");
                                        cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                        cse4589_print_and_log("[%s:END]\n", cmd);
                    
                                    }
                                    else{
                                        inet_ntop(AF_INET, &(ip_udp.sin_addr), ip, length);
                                        cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                        cse4589_print_and_log("IP:%s\n",ip);
                                        cse4589_print_and_log("[%s:END]\n", cmd);
                                    }
                                }
                                close(dummy_udp);
                            }
							
                            
							
							//LOGIN COMMAND
							else if (strstr(cmd, "LOGIN"))
                            {
								printf("hi");
                            	char delim[] = " ";
   								int count = 1;
								char *ptr = strtok(cmd, delim);
								char* ser_port;
								char *ser_ip;
                                printf("heyy");
								while (ptr != NULL)
								{   
        						if (count==1){
									ptr = strtok(NULL, delim);
       								count += 1;
        							}
        						else if (count==2){
        							
        							ser_ip = ptr;
									ptr = strtok(NULL, delim);
									printf("%s",ser_ip);
        							count += 1;
        							}
       							else if (count==3){
        							
        							ser_port = ptr;
									ptr = strtok(NULL, delim);
									printf("%s",ser_port);
        							count += 1;
        							}
								}
								
                                int server_port = atoi(ser_port);
								fdsocket = socket(AF_INET, SOCK_STREAM, 0);
								if (fdsocket <0)
									perror("Failed to create socket");
								
								bzero(&client_addr, sizeof(client_addr));
								client_addr.sin_family = AF_INET;
								client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
								client_addr.sin_port = htons(PORT);
								
								if(bind(fdsocket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0 )
									perror("Bind failed");
								
								bzero(&server_addr, sizeof(server_addr));
								server_addr.sin_family = AF_INET;
								inet_pton(AF_INET, ser_ip, &server_addr.sin_addr);
								server_addr.sin_port = htons(server_port);
								
								if(connect(fdsocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
							//        perror("Connect failed");

									cse4589_print_and_log("[%s:ERROR]\n", "LOGIN");
									cse4589_print_and_log("[%s:END]\n", "LOGIN");
								}
								else {
									cse4589_print_and_log("[%s:SUCCESS]\n", "LOGIN");
									cse4589_print_and_log("[%s:END]\n", "LOGIN");
									
								}
								
								char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
								//printf("%s\n",buffer);
								memset(buffer, '\0', BUFFER_SIZE);
            
										
							if(recv(fdsocket, buffer, BUFFER_SIZE, 0) <= 0){
								close(sock_index);
                            printf("Remote Host terminated connection!\n");

                            /* Remove from watched list */
                            FD_CLR(sock_index, &master_list);
							}
							else{
				
									printf("Server responded: %s\n", buffer);
        
									char delim[] = " ";
									int count = 1;
									char* dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
									strcpy(dup_buffer,buffer);
									char *ptr = strtok(buffer, delim);
									char* lis_port;
									char* lis_ip;
									char* lis_hostname;
									
									while (ptr != NULL)
									{
										printf("enter while\n");
										if (count==1){
											lis_hostname = ptr;
											ptr = strtok(NULL, delim);
											count += 1;
										}
										else if (count==2){
											lis_ip = ptr;
											ptr = strtok(NULL, delim);
											count += 1;
										}
										else if (count==3){
											
											lis_port = ptr;
											ptr = strtok(NULL, delim);
											count += 1;
											int list_port = atoi(lis_port);
					//                			 deleteList(&cli_head_ref);
											printf("inserted\n");
											 appendClientList(&cli_head_ref,lis_hostname,lis_ip, list_port);
										}
										else if (count ==4){
											int list_port = atoi(lis_port);
											 count -= 3;

										}
									}
									
								}
								fflush(stdout);
								sock_index = STDIN;
			
								if (fdsocket> head_socket)
									head_socket = fdsocket;
								FD_SET(fdsocket,&master_list);
                            }
							
							//PORT COMMAND
                            else if (strcmp(cmd, "PORT\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                cse4589_print_and_log("%d",PORT);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
							
                            
                            //EXIT COMMAND
                            else if (strcmp(cmd, "EXIT\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                exit(0);
                                close(fdsocket);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            
                            
                            
                            
                            else if (strstr(cmd,"BROADCAST"))
							{
                                if (send(fdsocket, cmd, strlen(cmd), 0) == strlen(cmd)){
                                    printf("Done!\n");
									cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
									cse4589_print_and_log("[%s:END]\n", cmd);
                                }
								
                                fflush(stdout);
                            }
							
							//BLOCK COMMAND
                            else if (strstr(cmd, "BLOCK"))
							{
								struct ClientNode *node_cli = (struct ClientNode*) malloc(sizeof(struct ClientNode));
	
									node_cli=cli_head_ref;
                                char delim[] = " ";
                                int count = 1;
                                char *ptr = strtok(cmd, delim);
                                char *ser_ip;
                                char* commandd;
                                char* dup_ser_ip;
                                int flag;
                                printf("Start block");
                                printf("%s\n",ptr);
                                commandd = ptr;
                                
                                while (ptr != NULL)
                                {
                                	printf("loop\n");
                                    if (count==1){
                                    	printf("if 1\n");
                                        ptr = strtok(NULL, delim);
                                        dup_ser_ip = ptr;
                                        ser_ip = ptr;
                                        printf("%s\n",ptr);
                                        printf("if 11\n");
                                        ptr = NULL;
                                        count += 1;
                                        
                                    }
                                    
								}
									dup_ser_ip[strlen(dup_ser_ip)-1] = '\0';
									flag =isvalidIP(dup_ser_ip);
									printf("%d",flag);
//                                     printf("end while\n");
                                	printf("mutation\n");
									
									printf("Seg1\n");
									while (strcmp(node_cli->ip, ser_ip)!=0)
									{	
										printf("Seg2\n");	
										if(node_cli -> next == NULL)
											break;
										
										node_cli = node_cli->next;
										
									}
									
									printf("before if\n");
									if (flag){
										printf("Seg3\n");
										if (strcmp(node_cli->ip,ser_ip)==0){
											printf("Seg4\n");
											printf("%s\n",sendmsg);
											if (send(fdsocket, sendmsg, strlen(sendmsg), 0) == strlen(sendmsg)){
                                            printf("Block command sent!\n");
											cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
											cse4589_print_and_log("[%s:END]\n", cmd);
											
                                        }
											else{
												printf("send failed");
												cse4589_print_and_log("[%s:ERROR]\n", commandd);
												cse4589_print_and_log("[%s:END]\n", commandd);
                                            }
                                        }
                                    else{
                                        printf("IP not in list");
                                        cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                        cse4589_print_and_log("[%s:END]\n", commandd);
                                        }
                                    //fflush(stdout);
                                }
                                else {
                                    printf("IP is not valid");
                                    cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                    cse4589_print_and_log("[%s:END]\n", commandd);
									}
								
									fflush(stdout);
									sock_index = STDIN;
			
								if (fdsocket> head_socket)
									head_socket = fdsocket;
								FD_SET(fdsocket,&master_list);	
								
								}
							
							
                            else if (strstr(cmd, "UNBLOCK")){
                                //is ip valid
                               struct ClientNode *node_cli = (struct ClientNode*) malloc(sizeof(struct ClientNode));
	
									node_cli=cli_head_ref;
                                char delim[] = " ";
                                int count = 1;
                                char *ptr = strtok(cmd, delim);
                                char *ser_ip;
                                char* commandd;
                                char* dup_ser_ip;
                                int flag;
                                printf("Start block");
                                printf("%s\n",ptr);
                                commandd = ptr;
                                
                                while (ptr != NULL)
                                {
                                	printf("loop\n");
                                    if (count==1){
                                    	printf("if 1\n");
                                        ptr = strtok(NULL, delim);
                                        dup_ser_ip = ptr;
                                        ser_ip = ptr;
                                        printf("%s\n",ptr);
                                        printf("if 11\n");
                                        ptr = NULL;
                                        count += 1;
                                        
                                    }
                                    
									}
									dup_ser_ip[strlen(dup_ser_ip)-1] = '\0';
									flag =isvalidIP(dup_ser_ip);
									printf("%d",flag);
//                                     printf("end while\n");
                                	printf("mutation\n");
									
									printf("Seg1\n");
									while (strcmp(node_cli->ip, ser_ip)!=0)
									{	
										printf("Seg2\n");	
										node_cli = node_cli->next;
									}
									printf("before if\n");
									if (flag){
										printf("Seg3\n");
										if (strcmp(node_cli->ip,ser_ip)==0){
											printf("Seg4\n");
											printf("%s\n",sendmsg);
											if (send(fdsocket, sendmsg, strlen(sendmsg), 0) == strlen(sendmsg)){
                                            printf("UnBlock command sent!\n");
											cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
											cse4589_print_and_log("[%s:END]\n", cmd);
                                        }
											else{
												printf("send failed");
												cse4589_print_and_log("[%s:ERROR]\n", commandd);
												cse4589_print_and_log("[%s:END]\n", commandd);
                                            }
                                        }
                                    else{
                                        printf("IP not in list");
                                        cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                        cse4589_print_and_log("[%s:END]\n", commandd);
                                        }
                                    fflush(stdout);
                                }
                                else {
                                    printf("IP is not valid");
                                    cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                    cse4589_print_and_log("[%s:END]\n", commandd);
									}
								}
							
                            else if (strstr(cmd, "SEND")){
                                struct ClientNode *node_cli = (struct ClientNode*) malloc(sizeof(struct ClientNode));

								node_cli=cli_head_ref;
                                char delim[] = " ";
                                int count = 1;
                                char *ptr = strtok(cmd, delim);
                                char *ser_ip;
                                char* commandd;
                                char* dup_ser_ip;
                                int flag;
                                printf("Start block");
                                printf("%s\n",ptr);
                                commandd = ptr;
                               
                                while (ptr != NULL)
                                {
                                printf("loop\n");
                                    if (count==1){
                                    printf("if 1\n");
                                        ptr = strtok(NULL, delim);
                                        dup_ser_ip = ptr;
                                        ser_ip = ptr;
                                        printf("%s\n",ptr);
                                        printf("if 11\n");
                                        ptr = NULL;
                                        count += 1;
                                       
                                   	 }
                                   
								}
								//dup_ser_ip[strlen(dup_ser_ip)-1] = '\0';
								flag =isvalidIP(dup_ser_ip);
								printf("%d",flag);
//                                     printf("end while\n");
                                printf("mutation\n");

								printf("Seg1\n");
								while (strcmp(node_cli->ip, ser_ip)!=0)
								{
									printf("Seg2\n");
									printf("%s",ser_ip);
									node_cli = node_cli->next;
								}
								printf("before if\n");
								if (flag){
									printf("Seg3\n");
									if (strcmp(node_cli->ip,ser_ip)==0){
										printf("Seg4\n");
										printf("%s\n",sendmsg);
											if (send(fdsocket, sendmsg, strlen(sendmsg), 0) == strlen(sendmsg)){
                                            	printf("SEND command sent!\n");
												cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
												cse4589_print_and_log("[%s:END]\n", cmd);
                                        	}
											else{
												printf("send failed");
												cse4589_print_and_log("[%s:ERROR]\n", commandd);
												cse4589_print_and_log("[%s:END]\n", commandd);
                                            }
                                        }
                                    else{
                                        printf("IP not in list");
                                        cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                        cse4589_print_and_log("[%s:END]\n", commandd);
                                        }
                                    fflush(stdout);
                                }
                                else {
                                    printf("IP is not valid");
                                    cse4589_print_and_log("[%s:ERROR]\n", commandd);
                                    cse4589_print_and_log("[%s:END]\n", commandd);
								}
							}
                            		
                            else
                            {
                                printf("Hey");
                                cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                cse4589_print_and_log("[%s:END]\n", cmd);
//
                            }
                        }
                            
            /* Initialize buffer to receieve response */
            // char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
//             memset(buffer, '\0', BUFFER_SIZE);
//             
//             if(recv(fdsocket, buffer, BUFFER_SIZE, 0) >= 0){
//                 printf("Server responded: %s\n", buffer);
//                 fflush(stdout);
//                         }
// 				if((!strstr(cmd, "LIST")) && (!strstr(cmd, "IP")) && (!strstr(cmd, "PORT")) && (!strstr(cmd, "AUTHOR")) && (!strstr(cmd, "BLOCK")) && (!strstr(cmd, "UNBLOCK")) && (!strstr(cmd, "LOGOUT")) && (!strstr(cmd, "SEND")) && (strstr(cmd, "LOGIN"))){
				                //store the list in buffer
			
			
			else{
				
                char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                printf("%s\n",buffer);
           		memset(buffer, '\0', BUFFER_SIZE);
            
            if(recv(fdsocket, buffer, BUFFER_SIZE, 0) >= 0)
			{
				printf("Server responded: %s\n", buffer);
				
        		char *dup_buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
    						char delim[] = " ";
                            int count = 1;
                             strcat(buffer," ");
                            strcat(buffer,"kavs\n");
                            strcpy(dup_buffer,buffer);
                            //printf("seg\n");
                            char *ptr = strtok(dup_buffer, delim);
                            //printf("seg1\n");
                            char* cli_cmd;
                            char* var1;
                            char* var2;
                            int temp;
                            char* temp_msg;
                            char* dup_var1;
                            char* sam =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            char* samplemsg =(char*) malloc(sizeof(char)*BUFFER_SIZE);
                            while (ptr != NULL)
                            {
								printf("while\n");
                                if (count==1){
                                    cli_cmd = ptr;
                                    ptr = strtok(NULL, delim);
                                    //var1 = ptr;
                                    //printf("%s\n",var1);
                                    count += 1;
                                
                                }
                                else if (count==2){
                                    //printf("cnt2\n");
                                    var2 = ptr;
                                   
                                    
                                    //printf("hey\n");
                                    
									printf("%sdddd\n",var2);
                                    if (strcmp(var2,"kavs\n")==0){
										printf("enter kavs\n");
                                        break;
									}
									ptr = strtok(NULL, delim);
                                    printf("%sdddd\n",var2);
                                    strcat(sam,var2);
                                    strcat(sam," ");
                                    
                                    
                                }
                                
                            //printf("while ends\n");  
                            }	
								char* sam1 =(char*) malloc(sizeof(char)*BUFFER_SIZE);
								strcpy(sam1,sam);
								//printf("Sender ip: %s\n",cli_cmd);
								//printf("Client ip: %s\n",var1);
								//printf("msg received: %s\n",sam1);
								cse4589_print_and_log("[RECEIVED:SUCCESS]");
								cse4589_print_and_log("msg from:%s\n[msg]:%s\n", cli_cmd, sam1);
								cse4589_print_and_log("[RECEIVED:END]");
								
								
			
			
		}

          }
        }
    }  
    
    }
	
		}  //return 0;
}

}
