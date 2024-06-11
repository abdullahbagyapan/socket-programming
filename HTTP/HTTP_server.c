#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>


int main() {


    FILE *HTML_data_fp; // HTML file for response

    HTML_data_fp = fopen("index.html", "r"); // open HTML file as "read-only" mode

    if (HTML_data_fp == NULL) {

        printf("error while opening the file: index.html");
        return 1;
    }


    char response_body[1024]; // HTTP response body
    char response_header[2048] = "HTTP/1.1 200 OK\r\n\n"; // set response header (HTTP status - 200 OK)

    // embed the HTML_Data into HTTP response body
    // fixes: reading only one line at once problem
    int bytes_read = fread(response_body, 1, sizeof(response_body), HTML_data_fp);
    response_body[bytes_read] = '\0'; // // null-terminate the string

    strcat(response_header, response_body); // concat both response (header and body) into only one response


    // create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) { // error handling
		printf("error while opening the socket");
        return 1;
	}

    // define server address
    struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

    // bind together the socket with IP and port number
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen socket
    int listen_status = listen(server_socket, 5);

    if (listen_status == -1) { // error handling
		printf("error while listening to the socket");
        return 1;
	}


    int client_conn;

    while(1) {

        // accept remote connection
        client_conn = accept(server_socket, NULL, NULL);

        if (client_conn == -1) { // error handling
            printf("error while accepting the client connection");
            continue; // if error occurred go wait new client connection
        }

        printf("info: new client connection has been established"); // info logger

        // send a HTTP response to the client
        send(client_conn, response_header, sizeof(response_header), 0);

        // close connection with acknowledge
        // fixes: "Recv failure: Connection reset by peer"
        int shutdown_status = shutdown(client_conn, SHUT_WR);

        if (shutdown_status == -1) { // error handling
            printf("error while ending transmission");
        }

        // close client connection
        close(client_conn);

    };

    return 0; // Ok
}