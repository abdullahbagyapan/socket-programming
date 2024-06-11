#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main() {


	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify remote socket
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(8080);
	remote_address.sin_addr.s_addr = INADDR_ANY;

	// connect remote socket
	int conn_status = connect(network_socket, (struct sockaddr*) &remote_address, sizeof(remote_address));

	if (conn_status == -1) { // error handling
		printf("error while connecting to the remote socket");
	}

	char network_buffer[256]; // buffer for received data

	// receive data from connection
	recv(network_socket, network_buffer, sizeof(network_buffer), 0);
 
	// print received data
	printf("%s", network_buffer);

	// close socket conn
	close(network_socket);

	return 0;
}
