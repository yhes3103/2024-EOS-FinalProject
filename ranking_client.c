# include <stdio.h>
# include <unistd.h> // for sleep() fork() exec() read() close() lseek() dup() ...
# include <stdlib.h>
# include <netinet/in.h>  // sockaddr_in, htons, INADDR_ANY
# include <arpa/inet.h>   // htons, inet_ntoa
# include <sys/socket.h> // for socket
# include <string.h>
# include <errno.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>

# define NAME_SIZE 10
# define BUFFERSIZE 1024
# define GAMETIME 300

void countdown_timer(int seconds) {
    while (seconds > 0) {
        system("clear");

        printf("GAME TIME LEFT：%02d:%02d\n", seconds / 60, seconds % 60);

        sleep(1); 
        seconds--; 
    }

    system("clear");
    printf("GAME OVER！\n");
}

int main(int argc, char* argv[]){
    char send_buf[50] = {0};
    char recv_buf[BUFFERSIZE] = {0};

    if (argc != 3){
        printf("Usage: ./ranking_client <ip> <port>\n");
        exit(EXIT_FAILURE);
    }

    int server_fd = 0;
    server_fd =  socket(AF_INET , SOCK_STREAM , 0);
    if(server_fd == -1){
        perror("Connect to server failed");
    }

    int port = atoi(argv[2]);
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(port);

    if(connect(server_fd,(struct sockaddr *)&address, addrlen) < 0){
        printf("Connection error\n");
    }

    while(1){
        printf("==== MENU ====\n");
        printf("1. User Login and Start game\n");
        printf("2. Ranking Board\n");
        printf("3. exit\n");
        printf("Enter Your Choice: ");
        int choice;
        char user_name[NAME_SIZE];
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Please enter your name:");
            scanf("%10s", user_name);
            sprintf(send_buf, "%s %s %s", "first", user_name, "10");
            send(server_fd, send_buf, 50, 0);
            countdown_timer(GAMETIME);
            memset(send_buf, 0, sizeof(send_buf));

        } else if (choice == 2) {
            send(server_fd, "second", 7, 0);
            sleep(1);
            if (recv(server_fd, recv_buf, BUFFERSIZE, 0) > 0){
                printf("%s", recv_buf);
            }
        } else if(choice == 3){
            close(server_fd);
            break;

        }
    }

    return 0;


}