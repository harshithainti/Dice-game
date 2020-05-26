// Team members-Project by Harshitha Inti and Pujitha Indukuri
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
void servicePlayers(int TOTO,int TITI);
int main(int argc, char *argv[]){
        int sd, TOTO,TITI, portNumber;
        socklen_t len;
        struct sockaddr_in servAdd;
        int dice_value;
        int32_t converted_dice_value;
        int size = sizeof(converted_dice_value);
        if(argc != 2){
                fprintf(stderr,"Call model: %s <Port#>\n",argv[0]);
                exit(0);
        }
        if((sd = socket(AF_INET, SOCK_STREAM, 0))<0){
                fprintf(stderr, "Could not create socket\n");
                exit(1);
        }
        servAdd.sin_family = AF_INET;
        servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
        sscanf(argv[1], "%d", &portNumber);
        servAdd.sin_port = htons((uint16_t)portNumber);
        bind(sd, (struct sockaddr *) &servAdd,sizeof(servAdd));
        listen(sd, 6);
        while(1){
                TOTO=accept(sd,(struct sockaddr*)NULL,NULL);
                TITI=accept(sd,(struct sockaddr*)NULL,NULL);
                printf("WELCOME TOTO AND TITI! LET'S START THE GAME \n");
                if(fork()==0)
                        servicePlayers(TOTO,TITI);

	}
}

void servicePlayers(int TOTO,int TITI){
        int p1_total_score=0,p2_total_score=0,size=sizeof(int32_t);
        int32_t p1_converted_dice_value,p2_converted_dice_value;
        while(1){
                sleep(1);
                write(TOTO,"You can now play",100);
                if(read(TOTO,&p1_converted_dice_value,size)<0)
                        printf("Read Error from Player p1");
                p1_total_score+=ntohl(p1_converted_dice_value);
                if(p1_total_score>=100){
                        write(TOTO,"Game over: You won the game",100);
                        write(TITI,"Game over: You lost the game",100);
                        break;
			 
                }
                sleep(2);
                write(TITI,"You can now play",100);
                if(read(TITI,&p2_converted_dice_value,size)<0)
                        printf("Read Error from Player p2");
                p2_total_score+=ntohl(p2_converted_dice_value);
                if(p2_total_score>=100){
                        write(TITI,"Game over: You won the game",100);
                        write(TOTO,"Game over: You lost the game",100);
                        break;
                }
                
        }
       close(TOTO);
       close(TITI);
       exit(0);

}