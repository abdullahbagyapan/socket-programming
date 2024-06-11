# Socket in C

Sockets are low level endpoint used for processing information across a network.Common networking protocols like HTTP and FTP rely on the sockets underneath to make connection.

## Client Socket Workflow

**socket()
|
connect()
|
recv()**

* The client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

* The client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

## Server Socket Workflow

**socket()
|
bind()
|
listen()
|
accept()**

* On the "server" end of the socket,we need to also create a socket with a socket() call, but we need to bind() that socket to an IP and port where it can then listen() for connections, finally accept() a connection and then send() or recv() data to the other sockets it has connected to.


### Understanding Client Side Code

```C
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
```

### Understanding Server Side Code

```C
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
```