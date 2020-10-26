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
#define EPHEMERAL_PORT 53


/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
 
void print_list(){
	 
 }

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
    
    /* Bind */
    if(bind(fdsocket, (struct sockaddr *)&remote_client_addr, sizeof(remote_client_addr)) < 0 )
        perror("Bind failed");
    
    bzero(&remote_server_addr, sizeof(remote_server_addr));
    remote_server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
    remote_server_addr.sin_port = htons(server_port);
    //    printf("hehe");
    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0){
//        perror("Connect failed");
//        printf("dede");
        cse4589_print_and_log("[%s:ERROR]\n", "LOGIN");
        cse4589_print_and_log("[%s:END]\n", "LOGIN");
    }
    else {
        cse4589_print_and_log("[%s:SUCCESS]\n", "LOGIN");
        cse4589_print_and_log("[%s:END]\n", "LOGIN");
        
    }
    return fdsocket;
}

 typedef struct Node{
	 char *hostname;
	 char *ip;
	 int port_no;
	 int num_msg_recv;
     int num_msg_sent;
     struct Node *next;
 };

//https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/ 
void append(struct Node** head_ref, char *hostname, char *ip, int port_no){
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	new_node->hostname = hostname;
	new_node->ip = ip;
	new_node->port_no = port_no;
	new_node->next = NULL;
	if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }
	while (last->next != NULL) 
        last = last->next; 
	last->next = new_node;
	return;
}

void printList(struct Node *node) 
{ 
  while (node != NULL) 
  { 
	int list_id = 1;
     //printf(" %s ", node->hostname); 
	 //printf(" %s ", node->ip);
	 //printf(" %d ", node->port_no);
	 cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", list_id, node->hostname, node->ip, node->port_no);
     node = node->next; 
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
//    printf("%d",PORT);
    struct Node *head_ref = NULL;    //making the list null
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
				perror("select failed.");
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
								printf("I, %s, %s have read and understood the course academic integrity policy.\n", "spampatt","kavithac");
                                cse4589_print_and_log("[%s:END]\n", cmd);
							}
				
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
							
							//LIST COMMAND
							else if (strcmp(cmd, "LIST\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                printList(head_ref);
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
                        caddr_len = sizeof(client_addr);
                        fdaccept = accept(server_socket, (struct sockaddr *)&client_addr, &caddr_len);
                        if(fdaccept < 0)
                            perror("Accept failed.");
                        
                        /* Add to watched socket list */
                        FD_SET(fdaccept, &master_list);
                        if(fdaccept > head_socket) head_socket = fdaccept;
                        
                        //get ip address, client port and hostname
                        inet_ntop(AF_INET, &(client_addr.sin_addr), ip_address, INET_ADDRSTRLEN);
                        inet_pton(AF_INET,ip_address, &addr_ip);
//                        ip_address = inet_ntoa(client_addr.sin_addr);
                        client_port = (int)ntohs(client_addr.sin_port);
//                        inet_aton(ip_address, &client_addr);
                        hn = gethostbyaddr(&addr_ip, sizeof(addr_ip), AF_INET);
                        char* host_name = hn->h_name;
                        append(&head_ref,host_name,ip_address, client_port);
//                        printList(head_ref);
//                        printf("%s %d %s",ip_address,client_port,host_name);
                        //imply linked list
                        
						printf("\nRemote Host connected!\n");                        

                        
                    }
                    /* Read from existing clients */
                    else{
                        /* Initialize buffer to receieve response */
                        char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
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
                            
                            //send that message to the client if loggined or else store it in buffer
                            
                            
                        	printf("\nClient sent me: %s\n", buffer);
							printf("ECHOing it back to the remote host ... ");
							if(send(fdaccept, buffer, strlen(buffer), 0) == strlen(buffer))
								printf("Done!\n");
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
        struct sockaddr_in server_addr;
        int server;
//        int server_fd, client_max = 0;
//        fd_set masterlist, watchlist;
//
//
//
//        FD_ZERO(&masterlist);
//        FD_ZERO(&watchlist);
//        FD_SET(0,&masterlist);
//
//        //client_max =0;
//        //int server;
//        //server = listening_fd;
//
        while (TRUE)
        {
//            watchlist = masterlist;
////            printf("\n[PA1-Client@CSE489/589]$ ");
//            //flush(stdout);
//            int selret = select(client_max+1, &watchlist, NULL, NULL, NULL);
//            if( selret == -1)
//            {
//                perror("select");
//            }
//            //char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);
//
//            if(selret > 0)
//            {
//                // Loop through socket descriptors to check which ones are ready
//
//                for(int sock_index=0; sock_index<=client_max; sock_index+=1)
//                {
//                    if(FD_ISSET(sock_index, &watchlist))
//                    {
//                        // Check if new command on STDIN
//                        if (sock_index == STDIN)
//                        {
                            char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);
                            char *command= (char*) malloc(sizeof(char)*CMD_SIZE);
                            memset(cmd, '\0', CMD_SIZE);
                            if(fgets(cmd, CMD_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to cmd
                                exit(-1);
                            strcpy(command,cmd);
                            char* input = strtok(command, " ");
                            printf("\nI got: %s\n", cmd);
                            
                            //AUTHOR COMMAND
                            if (strcmp(cmd, "AUTHOR\n") == 0)
                            {
                                //cse4589_print_and_log("[%s:SUCCESS]\n", command);
                                cse4589_print_and_log("I, %s, %s have read and understood the course academic integrity policy.\n", "spampatt","kavithac");
                                //cse4589_print_and_log("[%s:END]\n", command);
                            }
                            else if (strcmp(cmd, "LIST\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                printList(head_ref);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            else
                            {
                                cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            
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

                            
                            
                            //EXIT COMMAND
                            else if (strcmp(cmd, "EXIT\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                exit(0);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            
                            //PORT COMMAND
                            else if (strcmp(cmd, "PORT\n") == 0)
                            {
                                cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
                                cse4589_print_and_log("%d",PORT);
                                cse4589_print_and_log("[%s:END]\n", cmd);
                            }
                            
                            
                            else if (strstr(cmd,"BROADCAST")){
                                
                            }
                            else if (strstr(cmd,"BLOCK")){
                                
                            }
                            else if (strstr(cmd,"UNBLOCK")){
                                
                            }
                            
                            //LOGIN COMMAND
                            else if (strcmp(input, "LOGIN") == 0)
                            {
                            	char delim[] = " ";
   								int count = 1;
								char *ptr = strtok(cmd, delim);
								char* ser_port;
								char *ser_ip;
                                
								while (ptr != NULL)
								{   
        						if (count==1){
									ptr = strtok(NULL, delim);
       								count += 1;
        							}
        						else if (count==2){
        							
        							ser_ip = ptr;
									ptr = strtok(NULL, delim);
        							count += 1;
        							}
       							else if (count==3){
        							
        							ser_port = ptr;
									ptr = strtok(NULL, delim);
        							count += 1;
        							}
								}
                                int server_port = atoi(ser_port);
//                                printf("%d",server_port);
//                                printf("%s",ser_ip);
                                connect_to_host(ser_ip,server_port,PORT);
//                                server_fd = socket(AF_INET, SOCK_STREAM, 0);
//                                   if(server_fd < 0){
//                                printf("Client Socket creation failed\n");
//                                exit(EXIT_FAILURE);
//                                    }
//                                else {
//                                FD_SET(server_fd, &masterlist);
//                                if(server_fd > client_max){
//                                    client_max = server_fd;
//                                    }
//                                server_addr.sin_family = AF_INET;
//                                unsigned int port_temp = atoi(cli_port);
//                                server_addr.sin_port = htons(port_temp);
//                                inet_pton(AF_INET, ser_ip, &(server_addr.sin_addr));
//                                    printf("hi");
//                                if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0){
//                                    cse4589_print_and_log("[%s:ERROR]\n", "LOGIN");
//                                    cse4589_print_and_log("[%s:END]\n", "LOGIN");
//                                }
//
//                                else{
//                                    // printf("\n Sending port");
//                                    cse4589_print_and_log("[%s:SUCCESS]\n","LOGIN");
//                                    cse4589_print_and_log("[%s:END]\n","LOGIN");
//                                    exit(0);
//                                    close(server_fd);
////                                     send_port(port_no, server_fd);
//                                       }

//                                }
								
                            }
                            
                            else
                            {
                                printf("Hey");
                                cse4589_print_and_log("[%s:ERROR]\n", cmd);
                                cse4589_print_and_log("[%s:END]\n", cmd);
//                                exit(0);
//                                close(server_fd);
                            }
                            
                            
                        }
//                    }
//                }
////
//            }
//        }
    
    }
    return 0;
}

