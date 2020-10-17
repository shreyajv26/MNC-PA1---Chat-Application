/* Function Declaration */
void print();
void add();
void delete();

int main() {
	
	if(argc != 3) {
		printf("3 arguments expected");
		exit(-1);
	}
	
    struct Clients {
		char * hostname;
		uint32_t ip_addr;
		uint32_t port_num;
		
		LIST_ENTRY(Clients) next_client;
	};
				
		LIST_HEAD(__client_list, Clients) client_list;
		LIST_INIT(&client_list);
		
}

/* PRINT FUNCTION */
void print(){
		struct Clients * tmp;
		puts("/***********************************************************/\n");
		int count = 1;
		LIST_FOREACH(tmp, &client_list, next_author) {
		printf("%d\t\t%s\t\t%d\t\t%d\n", (int)tmp ->count,tmp ->hostname,(int)tmp -> ip_addr, (int)tmp -> port_num);
		count = count + 1;
        puts("/***********************************************************/\n");
			
    }   
	
/* ADD to a LINKEDLIST */

void push(char * hostname,uint32_t ip_addr,uint32_t port_num){
	
	struct Clients c1 = {hostname,ip_addr,port_num};
	LIST_INSERT_HEAD(&client_list, &c1, next_client);
	
}

void delete(Struct Clients **head_ref, int key){
	struct Clients * tmp = *head_ref;
	if(tmp != NULL && (int)tmp-> port_num == key){
		*head_ref = head_ref -> next_client;
		free(tmp);
		return;
	}
	while(tmp != NULL && (int)tmp-> port_num != key){
		traverse = tmp;
		tmp = tmp -> next_client;
	}
	if(tmp == NULL) return;
	traverse -> next_client = tmp -> next_client;
	free(tmp);
}