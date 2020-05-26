// Team members-Harshitha Inti and Pujitha Indukuri
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<string.h>
int main(int argc, char *argv[]){
        char message[100];
        int server, portNumber;
        socklen_t len;
        struct sockaddr_in servAdd;
        int dice;
        int32_t converted_dice;
        int size=sizeof(converted_dice);
        if(argc != 3){
                printf("Call model:%s <IP> <Port#>\n",argv[0]);
                exit(0);
        }
        if ((server=socket(AF_INET,SOCK_STREAM,0))<0){
                fprintf(stderr, "Cannot create socket\n");
                exit(1);
        }
        servAdd.sin_family = AF_INET;
        sscanf(argv[2], "%d", &portNumber);
        servAdd.sin_port = htons((uint16_t)portNumber);
        if(inet_pton(AF_INET, argv[1],
                &servAdd.sin_addr) < 0){
                fprintf(stderr, " inet_pton() has failed\n");
                exit(2);
        }
        if(connect(server, (struct sockaddr *) &servAdd,
                sizeof(servAdd))<0){
                fprintf(stderr, "connect() failed, exiting\n");
                exit(3);
        }
        while(1){
                if (read(server, message, 100)<0){
                        fprintf(stderr, "read() error\n");
                }
                printf("%s\n",message);
                if(!strcmp(message,"You can now play")){
			srand(time(0));
                        dice = rand()%6+1 ;
                        printf("Dice Value : %d\n",dice);
                        converted_dice=htonl(dice);
                        write(server,&converted_dice,size);
                }
                else if(!strcmp(message,"Game over: You won the game")){
                printf("\nI won the game\n");
                exit(0);
                }

                else if(!strcmp(message,"Game over: You lost the game")){
                printf("\nI lost the game\n");
                exit(0);
                }
        }
        exit(0);
}
