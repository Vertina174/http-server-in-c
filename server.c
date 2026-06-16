#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<string.h>
// void two_second_wait(){
//     for(int i=0; i<3; i++){
//         printf(".");
//         Sleep(1000);
//     }
// printf("\n");
// }
int main(){
WSADATA wsa;
int wsa_result = WSAStartup(MAKEWORD(2,2),&wsa); // returns 0 for successful calling
 if(wsa_result!=0){
         printf("WSAStartup failed with error Code: %d\n", wsa_result);
         return 1;
     }
    printf("WSA Started Successfully\n");
// two_second_wait();

SOCKET sock = socket(AF_INET,SOCK_STREAM,0); // returns 0 for successful calling
 if(sock==INVALID_SOCKET){// -1 or INVALIND_SOCKET for error
        printf("Socket Error: %d\n",WSAGetLastError());
        WSACleanup();
            exit(-1);
     }  
    printf("Communication End-Point Estaiblished\n");
    // two_second_wait();

    // Defining Server Addresses
    struct sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_addr.S_un.S_addr = INADDR_ANY;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8080);

// Binding Start to Ports
int bind_Result =  bind(sock,(struct sockaddr *)&server_address,sizeof(server_address )); // 0 if successfully called

if(bind_Result!=0){// -ve values for error code respectively
   printf("Bind Failed: %d\n", WSAGetLastError()); 
closesocket(sock);
WSACleanup();
exit(-1);}
printf("SuccessFull Binding to Port and IP Address\n");
// two_second_wait();

// Listening to Incoming Traffic
int listen_result = listen(sock,5); // 0 for Successful calling
if(listen_result!=0){
    printf("Listen Failed: %d\n",listen_result);
closesocket(sock);
WSACleanup();
exit(-1);
}
printf("SuccessFully Listened to a Client");
// two_second_wait();

struct sockaddr_in client_addr;
int len = sizeof(client_addr);
printf("Waiting For Request:\n");
SOCKET client = accept(sock,(struct sockaddr*)& client_addr, &len);
// or accept(sock, NULL, NULL) optional to get cilent addr  info or not 
if(client == INVALID_SOCKET){
    printf("Unable to Accept Client Request, Socket Error: %d\n",WSAGetLastError());
     closesocket(sock);
     WSACleanup();
     exit(-1);
}
printf("SuccessFully Accepted New Cilent Request\n");
// two_second_wait();
// This is Optional for server side!!!
char request_buffer[1024];
 memset(request_buffer,0,1024);
int recv_result = recv(client,request_buffer,1024,0); // return 1 upon successfull calling
if(recv_result<0){ // return -ve value for error 
    printf("Unable to Receive Request from Client Side: %d",WSAGetLastError());
         closesocket(sock);
         closesocket(client);
     WSACleanup();
     exit(-1);
}
if(recv_result==0){// return zero for termination of Client connection
    printf("\nRemote Client Closed the Connectoin.\n");
     closesocket(sock);
         closesocket(client);
     WSACleanup();
exit(-1);
}

 printf("Bytes Received: %d\n",recv_result);// data from client side
 for(int i=0; i<recv_result; i++){
     printf("%c",request_buffer[i]);
 }
 char *http_protocol="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
send(client,http_protocol,strlen(http_protocol),0);

FILE *file = fopen("hi1.html","r");
if(file == NULL){// If file could not be loaded to the file container
    printf("Failed to Open the File,\n");
closesocket(sock);
closesocket(client);
WSACleanup();
exit(-1);
}
  char c;  
  while((c=getc(file))!=EOF){
    send(client,&c,1,0); 
  }
fclose(file);

// two_second_wait();
closesocket(client);
closesocket(sock);

WSACleanup();
}