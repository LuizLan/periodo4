#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

/*
Implemente um servidor TCP em C que atenda a múltiplos clientes. O servidor deve receber strings dos clientes e remover todas as vogais dessas strings. 
A requisição e o resultado da remoção das vogais devem ser registrados em um arquivo de log (usando monitores) e enviados de volta para os clientes. 
O cliente deve enviar primeiro uma mensagem para o servidor com a string. 
Se o cliente enviar a string "EXIT", sua conexão deve ser fechada.
Se três ou mais clientes enviarem a string "SHUTDOWN" para o servidor, o servidor deve ser finalizado.
*/

#define MAX_CLIENTS 10 //numero maximo de clientes
#define BUFFER_SIZE 1024 // tamanho do buffer de entrada do socket
#define MSG_SIZE 2048 // tamanho para mensagem que sera enviada ao cliente
#define SERVER_PORT 9999 // port do servidor

typedef struct {
	FILE* file;
	pthread_mutex_t mutex;

} t_log_monitor; // monitor para o arquivo de log, certificando que nao se sobresreva ou perca informaçao

int shutdown_counter = 0; // contador para verificar se o servidor deve ser finalizado, devido aos pedidos de SHUTDOWN dos clientes
pthread_mutex_t shutdown_mutex; //mutex para manipular a variavel shutdown_counter
t_log_monitor server_log; // monitor para o arquivo de log

void write_log(t_log_monitor* log, char* msg) { // recebe uma mensagem que deve ser escrita no log do servidor
	pthread_mutex_lock(&log->mutex); // mutex para garantir segurança da zona critica 
	//escreve no arquivo de log
	printf("[log] %s\n", msg); // zona critica, escrita no log
	pthread_mutex_unlock(&log->mutex); // sai da zona critica
}

void remove_vogais(char* str) { // funcao que o servidor rodara em cima dos buffers recebidos dos clientes
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) { //checa se é  vogal, se for remove da string
        char ch = str[i];
        if (!isalpha(ch) || !strchr("AEIOUaeiou", ch)) { 
            str[j] = ch;
            j++;
        }
    }
    str[j] = '\0';
}

void limpar_buffer(char* str) { //funcao simples para tirar tudo que nao é alphanumerico da mensagem recebida do cliente, usada pois o telnet tem algum caracter especial na mensagem que estava interferindo na comparaçao com EXIT e SHUTDOWN
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) { // remove tudo que nao é alphanumerico da string
        if (isalnum(str[i])) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

void* handle_client(void* p) { // funcao que sera executada por cada thread, recebe o socket do cliente como parametro
	long int client_socket = (long int)p;
	
	while(1) {
		char recv_buffer[BUFFER_SIZE] = {0}; // string enviada pelo cliente
        char removed_buffer[BUFFER_SIZE] = {0}; // string sem as vogais para ser enviada de volta para o cliente e escrita no log
        char msg[MSG_SIZE] = {0}; // mensagem que sera enviada para o cliente
		char msg_log[MSG_SIZE] = {0};  // mensagem que sera escrita no log, usada como apoio
		char msg_exit[MSG_SIZE] = {0}; // string que sera comparada com EXIT e SHUTDOWN para saber se o cliente quer desconectar ou se o servidor deve ser finalizado, usada como apoio pois o telnet envia as string com caracteres especiais

		write(client_socket, "Digite uma string(EXIT para desconectar, SHUTDOWN para pedir encerramento): ", strlen("Digite uma string(EXIT para desconectar, SHUTDOWN para pedir encerramento): "));
		read(client_socket, recv_buffer, BUFFER_SIZE); // prompt para o cliente inserir sua string e lida da string escrita pelo cliente
		recv_buffer[strlen(recv_buffer)-1] = '\0'; // removendo o quebra linha que o telnet insere na string

		strcpy(msg_exit, recv_buffer);
		limpar_buffer(msg_exit); // mantendo somente valores alphanumericos na string de apoio para comparar com EXIT e SHUTDOWN

		if (strcasecmp(msg_exit, "EXIT") == 0){ // se o cliente enviar EXIT, sua conexao sera fechada
			close(client_socket);
			break;
		}
		else if (strcasecmp(msg_exit, "SHUTDOWN") == 0){ // se o cliente enviar SHUTDOWN, o contador de pedidos de SHUTDOWN sera incrementado, se o contador for maior ou igual a 3, o servidor sera finalizado
			pthread_mutex_lock(&shutdown_mutex);
			shutdown_counter++;
			if (shutdown_counter >= 3){
				exit(0);
			}else{
				pthread_mutex_unlock(&shutdown_mutex);
				sprintf(msg_log, "shutdown_counter: %d", shutdown_counter);
				write_log(&server_log, msg_log);
				continue;
			}
		}		

        strcpy(removed_buffer, recv_buffer);
        remove_vogais(removed_buffer); // remove as vogais da string recebida do cliente

		sprintf(msg_log, "mensagem recebida: %s", recv_buffer); // escreve no log a mensagem recebida do cliente
		write_log(&server_log, msg_log);
		write(client_socket, msg_log, strlen(msg_log)); // envia a mensagem recebida do cliente de volta para ele
		sprintf(msg_log, "vogais removidas, resultado parcial: %s", removed_buffer);
		write_log(&server_log, msg_log); // escreve no log a mensagem sem as vogais


        sprintf(msg, "vogais removidas, resultado final: %s\n", removed_buffer);
        write(client_socket, msg, strlen(msg)); // envia a mensagem sem as vogais para o cliente
	} 
}

int main(void) {
	int server_socket; // socket do servidor
	long int client_socket[MAX_CLIENTS]; // socket dos clientes
	int client_counter = 0; // contador de clientes conectados
	pthread_t client_threads[MAX_CLIENTS]; // threads dos clientes
 	struct sockaddr_in server_params; // parametros do socket do servidor
	struct sockaddr_in client_params[MAX_CLIENTS]; // parametros dos sockets dos clientes
	int client_params_size[MAX_CLIENTS]; // tamanho dos parametros dos sockets dos clientes

	server_params.sin_family = AF_INET; // configurando o socket do servidor
	server_params.sin_addr.s_addr = INADDR_ANY; // aceitando conexoes de qualquer endereco
	server_params.sin_port = htons(SERVER_PORT); // configurando a porta do servidor
	


	server_socket = socket(AF_INET, SOCK_STREAM, 0); // criando o socket do servidor

	if (server_socket < 0) { // verificando se o socket foi criado corretamente
		perror("socket() error! ");
		write_log(&server_log, "socket() error!");
		exit(EXIT_FAILURE);
	}

	int bind_ret = bind(server_socket, (struct sockaddr*)&server_params, sizeof(server_params)); // associando o socket do servidor a porta 8080

	if (bind_ret < 0) { // verificando se o bind foi feito corretamente
		perror("bind() error! ");
		write_log(&server_log, "bind() error!");
		exit(EXIT_FAILURE);
	}

	int listen_ret = listen(server_socket, MAX_CLIENTS); // colocando o socket do servidor em modo de escuta

	if (listen_ret < 0) { // verificando se o listen foi feito corretamente
		perror("listen() error! ");
		write_log(&server_log, "listen() error!");
		exit(EXIT_FAILURE);
	}

	char banner[MSG_SIZE]; // string que sera escrita no log
	sprintf(banner, "[server] waiting for connections on: %d\n", SERVER_PORT); // escrevendo a string banner
	write_log(&server_log, banner); 

	while(1) { // loop infinito para aceitar novas conexoes
		client_socket[client_counter] = accept(server_socket, 
						(struct sockaddr*)&client_params[client_counter],
						(socklen_t*) &client_params_size[client_counter]);

		if (client_socket[client_counter] < 0) { // verificando se a conexao foi aceita corretamente
			perror("accept() error! ");
			write_log(&server_log, "accept() error!");
			exit(EXIT_FAILURE);
		}
		char msg[MSG_SIZE];
		sprintf(msg, "[server] new connection: %d", client_params[client_counter].sin_addr.s_addr); // escrevendo no log o ip do cliente que se conectou
		write_log(&server_log, msg);
		
		pthread_create(&client_threads[client_counter], NULL, handle_client, 
							(void*)client_socket[client_counter]); // criando uma thread para tratar a conexao do cliente

		client_counter = (client_counter + 1) % MAX_CLIENTS; // incrementando o contador de clientes conectados
	}


	return 0;

}