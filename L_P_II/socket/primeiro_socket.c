#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void) {
	int server_fd, new_socket;
	struct sockaddr_in endereco;
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	endereco.sin_family = AF_INET;
	endereco.sin_addr.s_addr = INADDR_ANY;
	endereco.sin_port = htons(8000);

	bind
	listen
	accept

}
