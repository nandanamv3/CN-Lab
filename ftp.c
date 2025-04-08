//Server Code
//The server listens for incoming connections, receives a file request, reads the file, and sends its content to the client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
char buffer[BUFFER_SIZE] = {0};
char filename[BUFFER_SIZE] = {0};

// Receive filename from client

int bytes_received = recv(client_socket, filename, BUFFER_SIZE, 0);
if (bytes_received < 0) {
perror("Error receiving filename");
close(client_socket);
return;
}

// Open the requested file

FILE *file = fopen(filename, "r");
if (file == NULL) {
char *error_message = "File not found";
send(client_socket, error_message, strlen(error_message), 0);
perror("File not found");
} else {

// Read file and send its content

while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
send(client_socket, buffer, strlen(buffer), 0);
memset(buffer, 0, BUFFER_SIZE);
}

printf("File Send to client\n");
fclose(file);
}
close(client_socket);
}

int main() {

int server_socket, client_socket;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_len = sizeof(client_addr);

// Create server socket

server_socket = socket(AF_INET, SOCK_STREAM, 0);
if (server_socket == 0) {
perror("Socket failed");
exit(EXIT_FAILURE);
}

// Configure server address
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);

// Bind socket to address
if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("Bind failed");
exit(EXIT_FAILURE);
}

// Start listening
if (listen(server_socket, 3) < 0) {
perror("Listen failed");
exit(EXIT_FAILURE);
}

printf("Server is listening on port %d\n", PORT);
while (1) {
// Accept client connection
client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
if (client_socket < 0) {
perror("Accept failed");
exit(EXIT_FAILURE);
}

printf("Client connected\n");
// Handle client

handle_client(client_socket);
}

close(server_socket);
return 0;
}
//Client Code

//The client connects to the server, sends the file name, and displays the received file content.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
int client_socket;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE] = {0};
char filename[BUFFER_SIZE] = {0};

// Create client socket

client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
    }

// Configure server address

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

// Connect to server
if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("Connection failed");
exit(EXIT_FAILURE);

}
// Get filename from user
printf("Enter the filename to request: ");
scanf("%s", filename);

// Send filename to server
send(client_socket, filename, strlen(filename), 0);

// Receive and print file content

printf("File content received:\n");
while (recv(client_socket, buffer, BUFFER_SIZE, 0) > 0) {
printf("%s", buffer);
memset(buffer, 0, BUFFER_SIZE);
}

printf("\n");
close(client_socket);

return 0;
}
