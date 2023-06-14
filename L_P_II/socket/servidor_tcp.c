#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

#define SERVER_PORT 9990
#define BUFFER_SIZE 1024
#define BACKLOG_SIZE 5
#define CLIENTS_QTD 10

void* client_handling(void* p) {
	int my_cli_fd = (int)p;

        char buffer_in[BUFFER_SIZE] = {0};
        char buffer_out[BUFFER_SIZE] = {0};

        strcpy(buffer_out, "BEM VINDO AO SERVIDOR\n");

        write(my_cli_fd, buffer_out, strlen(buffer_out));
        printf("Enviei ao cliente (fd: %d): %s\n", my_cli_fd,
                                                buffer_out);

        int ret_read = read(my_cli_fd, buffer_in, BUFFER_SIZE);
        if (ret_read < 0) {
                perror("read() error!");
                exit(EXIT_FAILURE);
        }

        printf("Recebi do cliente (fd: %d): %s\n", my_cli_fd,
						buffer_in);

	if (strstr(buffer_in, "RAND") != NULL) {
		int rnd = rand() % 1000;
		sprintf(buffer_out, "RANDOM: %d\n", rnd);
	} else {
	        strcpy(buffer_out, "TCHAU\n");
	}

        write(my_cli_fd, buffer_out, strlen(buffer_out));
        printf("Enviei ao cliente (fd: %d): %s\n", my_cli_fd,
						buffer_out);

	close(my_cli_fd);

	return 0;
}

int main(void) {
	int server_fd;
	int client_fd[CLIENTS_QTD];

	struct sockaddr_in server_params;
	struct sockaddr_in client_addr[CLIENTS_QTD];

	pthread_t cli_threads[CLIENTS_QTD];

	int cli_count = 0;

	time_t t;

	srand(time(&t));

	server_fd = socket(AF_INET, SOCK_STREAM, 0); //TCP
	
	if (server_fd < 0) {
		perror("socket() error!");
		exit(EXIT_FAILURE);
	}

	server_params.sin_family = AF_INET; //TCP-IP
	server_params.sin_addr.s_addr = INADDR_ANY; //SERVIDOR
	server_params.sin_port = htons(SERVER_PORT); //PORT

	int ret_bind = bind(server_fd, 
			    (struct sockaddr*)&server_params,
			     sizeof(server_params));

	if (ret_bind < 0) {
		perror("bind() error!");
		exit(EXIT_FAILURE);
	}

	int ret_list = listen(server_fd, BACKLOG_SIZE);
	if (ret_list < 0) {
		perror("listen() error!");
		exit(EXIT_FAILURE);
	}

	printf("Servidor aguardando conexoes na porta %d...\n",
			SERVER_PORT);

	int client_addr_size = sizeof(client_addr);
	while (1) {
		client_fd[cli_count] = accept(server_fd, 
		   (struct sockaddr*) &client_addr[cli_count],
		   (socklen_t *)&client_addr_size);

		if (client_fd[cli_count] < 0) {
			perror("accept() error!");
			exit(EXIT_FAILURE);
		}

		printf("Novo cliente conectado %d - fd: %d\n", 
			client_addr[cli_count].sin_addr.s_addr,
			client_fd[cli_count]);

		pthread_create(&cli_threads[cli_count],
				0, client_handling, 
				(void*) client_fd[cli_count]);
		cli_count = ((cli_count + 1) % 10);
	}

	return 0;
}
