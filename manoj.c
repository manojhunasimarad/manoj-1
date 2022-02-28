#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024



void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) 
    {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}
 
 void write_file(int sockfd){
  int n;
  FILE *fp;
  // char *filename = "recv.txt";

char receiver[500];
   printf("enter the file name along with extension to be received");
 scanf("%s",receiver);
  char *filename = receiver;
  char buffer[SIZE];
 
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}
 
int main()
{
     
  char input;
  printf("pleaser input server as s or client as c\n");
  scanf("%c",&input);



if(input=='s')
{

    // char *ip = "192.168.60.79";
    char rip[200];
    printf("enter  ip address of the server which is reciving {your system}");
    scanf("%s",rip);
     char *ip = rip;
     int port = 8080;
     int e;
     int sockfd, new_sock;
     struct sockaddr_in server_addr, new_addr;
     FILE *fp;
     socklen_t addr_size;

     char buffer[SIZE];

    
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

    
     
  if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 }else
 {
 perror("[-]Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("[+]Data written in the file successfully.\n");
 return 0;
}

else if(input=='c')
{
 
 
//   char *ip = "192.168.60.41";
char sip[200];
  printf("Enter ip address of the client which is sending file system {other system }");
 scanf("%s",sip);
 char *ip = sip;

  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
 char stringer[500];
 printf("enter the file name along with extension to be sent");
 scanf("%s",stringer);
  char *filename = stringer;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
 
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
 
  printf("[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}



}
