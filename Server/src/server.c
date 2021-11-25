//Compile:
//gcc -o server server.c -lconsole -L/home/kevin/Documents/PDIC/Driver/os-second-project/lib -I/home/kevin/Documents/PDIC/Driver/os-second-project/include



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <stdlib.h>
#include <time.h>

#include <libconsole.h>

char html_web_error[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><br><br><br><br><title>WebService</title>\r\n"
        "<style>body { background-color: #008080 }</style></head>\r\n"
        "<body><center><h1>Error 404 Not Found</h1><br>\r\n"
        "</center></body></html>\r\n";

char html_web_image[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: image/png\r\n\r\n";

char html_web_text[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: text/plain\r\n\r\n";

char html_web_file[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: image/*\r\n\r\n";

struct sockaddr_in get_direction(int port){
    struct sockaddr_in direction;
    direction.sin_family = AF_INET;
    direction.sin_port = htons(port);
    direction.sin_addr.s_addr = INADDR_ANY;
    return direction;
}

void bindSocket(int server_socket_descriptor, struct sockaddr_in direction){
    if (bind(server_socket_descriptor, (struct sockaddr*)& direction, sizeof(direction)) == -1) {
        close(server_socket_descriptor);
        printf("%s\n", "Error at binding");
        exit(1);
    }
}

void serverListen(int server_socket_descriptor){
    if (listen(server_socket_descriptor, 1) == -1) {
        close(server_socket_descriptor);
        printf("%s\n", "Error at listening");
        exit(1);
    }
}

char* parseQuery(char* buffer){
    int i = 0;
    int s = 0;
    int in_query=0;
    while(buffer[i]!='\0'){
        if(in_query==0&&buffer[i]=='/'){
            s=i;
            in_query=1;
        }
        if(in_query==1&&buffer[i]==' '){
            buffer[i]='\0';
            break;
        }
        ++i;
    }
    return buffer+s;
}

int parseAction(int client_socket_descriptor, struct sockaddr client, char* client_buffer){
    char* query = parseQuery(client_buffer);
    printf("%s\n", query);

    if(strncmp(query, "/right", 6)==0){
        moveRight();
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "right", 5);
        close(client_socket_descriptor);
    } else if(strncmp(query, "/left", 5)==0){
        moveLeft();
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "left", 4);
        close(client_socket_descriptor);
    } else if(strncmp(query, "/up", 2)==0){
        moveUp();
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "up", 2);
        close(client_socket_descriptor);
    } else if(strncmp(query, "/down", 5)==0){
        moveDown();
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "down", 4);
        close(client_socket_descriptor);
    } else if(strncmp(query, "/verify", 5)==0){
        verifyDevice();
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "connected", 9);
        close(client_socket_descriptor);
    } else{
        write(client_socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
        write(client_socket_descriptor, "unknown", 7);
        close(client_socket_descriptor);
    }

    return 0;
}

int main(int argc, char *argv[]) {

    int server_socket_descriptor, client_socket_descriptor, file_found, port;
    struct sockaddr_in direction;
    struct sockaddr client;
    socklen_t client_length = sizeof(client);
    char client_buffer[2048];
    char *extension, *residue;

    // Creates the server socket descriptor
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor == -1) {
        printf("%s\n", "Error creating socket");
        exit(1);
    }

    // Sets the port
    port = 8888;
    printf("Port set to %d\n", port);
    
    // Sets the sockaddr
    direction = get_direction(port);

    // Binds the server socket
    bindSocket(server_socket_descriptor, direction);

    // Sets the server socket to listen
    serverListen(server_socket_descriptor);
    
    printf("%s\n", "Server initiated");

    srand(time(NULL));

    initComm();

    while (1) {
        client_socket_descriptor = accept(server_socket_descriptor, &client, &client_length);

        if (client_socket_descriptor == -1) {
            close(server_socket_descriptor);
            printf("%s\n", "Error at accepting");
            exit(1);
        }
        printf("%s\n", "Request Received");

        // Clean read buffer
        memset(client_buffer, 0, 2048);
        read(client_socket_descriptor, client_buffer, 2048);

        if(parseAction(client_socket_descriptor, client, client_buffer)==-1){
            close(server_socket_descriptor);
            exit(1);
        }

        //close(client_socket_descriptor);
    }

    printf("%s\n", "Server stopped");

    close(server_socket_descriptor);
}
