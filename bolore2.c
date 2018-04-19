#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 1337

void BasicArrays() {
    // declaring an array with a literal
    int litArray[10];
    
    // declaring an array with a variable
    int ArraySize = 10;
    int varArray[ArraySize];

    // declaring an array with pre-defined objects
    int objArray[10] = {0,1,2,3,4,5,6,7,8,9};

    // setting an index in an array to an object
    litArray[0] = 1337;

    // retrieving an item from an array
    int leet = litArray[0];

    // creating a matrix with a literal
    int litMatrix[13][37];

    // creating a matrix with variables
    int rows = 13;
    int cols = 37;

    int varMatrix[rows][cols];

    // inputting to a matrix
    varMatrix[4][20] = 1337;

    // retrieving from a matrix
    int MatrixLeet = varMatrix[4][20];
}

void Pointers() {
    int num = 10;

    // pointer to an int type
    // holds the address of an int type variable
    int *pointer;

    // &<variable> retrieves the memory address of the object
    pointer = &num;

    printf("num: %d\n", num);
    printf("*pointer: %d\n", *pointer);
    printf("Address of num: %p\n", &num);
    printf("Address of num using pointer: %p\n", pointer);
    printf("Address of pointer: %p\n", &pointer);
}

void malloc_ex() {
    char *mem_alloc;

    // allocate memory for 11 characters
    mem_alloc = malloc(11 * sizeof(char));

    // move the string "Hello World" into memory
    strcpy(mem_alloc,"Hello World");

    printf("malloc-mem_alloc: %s\n", mem_alloc);

    // free allocated memory
    free(mem_alloc);
}

void calloc_ex() {
    char *mem_alloc;

    // allocate memory for 11 characters
    mem_alloc = calloc(11, sizeof(char));

    // move "Hello World" into mem_alloc
    strcpy(mem_alloc, "Hello World");

    printf("calloc-mem_alloc: %s\n", mem_alloc);

    // free allocated memory
    free(mem_alloc);
}

void realloc_free() {
    char *mem_alloc;

    // allocate memory for 11 characters
    mem_alloc = malloc(11 * sizeof(char));

    // move "Hello World" onto mem_alloc
    strcpy(mem_alloc, "Hello World");

    printf("realloc-free-mem_alloc malloc: %s\n", mem_alloc);

    // reallocate memory for 21 characters
    mem_alloc = realloc(mem_alloc, 21 * sizeof(char));

    // move "1337 h4x0r @nonymoose" into mem_alloc
    strcpy(mem_alloc, "1337 h4x0r @nonymoose");

    printf("realloc-free-mem_alloc realloc: %s\n", mem_alloc);

    // free allocated memory
    free(mem_alloc);
}

void DynMalloc() {
    malloc_ex();
    calloc_ex();
    realloc_free();
}

void Server() {

    // set up initial server variables
    int server, sock, value;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *serverhello = "Server Hello";
    
    // create socket
    server = socket(AF_INET, SOCK_STREAM, 0);

    // attach socket to port 1337
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind socket to server
    bind(server, (struct sockaddr *)&address, sizeof(address));

    // listen for client
    listen(server, 3);

    // accept connection
    sock = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // read from socket connection
    value = read(sock, buffer, 1024);

    printf("%s\n", buffer);

    // send message on socket connection
    send(sock, serverhello, strlen(serverhello), 0);
}

void Client() {
    struct sockaddr_in address;
    int sock = 0, value;
    struct sockaddr_in server_addr;
    char *helloclient = "Client Hello";
    char buffer[1024] = {0};

    // create socket 
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // set up socket object
    memset(&server_addr , '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // convert IP address to binary format
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // connect to server
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // send "Client Hello" message to server
    send(sock, helloclient, strlen(helloclient), 0);

    // read message from server over socket connection
    value = read(sock, buffer, 1024);

    printf("%s\n", buffer);
}

void SocketProgramming() {
    Server();
    Client();
}

void *mythread(void *vargp) {
    // pause for 1 second
    sleep(1);

    printf("Hello from mythread\n");
}

void Threading() {
    pthread_t tid;

    printf("This is before the thread\n");

    // create a new thread using the mythread function
    pthread_create(&tid, NULL, mythread, NULL);

    // join the thread with the main thread
    pthread_join(tid, NULL);

    printf("This is after the thread\n");
}

int main()
{
    // 1. Basic Arrays
    // 2. Pointers
    // 3. dynamic memory allocation
    // 4. socket programming
    // 5. threading

    BasicArrays();
    Pointers();
    DynMalloc();
    SocketProgramming();
    Threading();

    return 0;
}
