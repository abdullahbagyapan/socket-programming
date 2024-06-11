#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main() {

    // define server message
    char server_message[256] = "Greeting from Server";

    // create a socket
    int server_connection;
    server_connection = socket(AF_INET, SOCK_STREAM, 0);

    // define a server address
    struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

    // bind together the socket with IP and port number
    bind(server_connection, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen specified address and port
    int listen_status = listen(server_connection, 5);

    if (listen_status == -1) { // error handling
		printf("error while listening to the socket");
	}

    // accept remote connection
    int client_conn;
    client_conn = accept(server_connection, NULL, NULL);

    // send a message to remote connection
    send(client_conn, server_message, sizeof(server_message), 0);

    // close socket conn
    close(server_connection);

    return 0;
}