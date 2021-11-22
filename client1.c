#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Function to compare two strings
int compare_strings(char x[], char y[])
{
    int z = 0;
    while (x[z] == y[z]) 
    {

        if (x[z] == '\0' || y[z] == '\0')
        break;
        z++;
    }

    if (x[z] == '\0' && y[z] == '\0')

    return 0;

    else

    return -1;
}

int main() {
    //Declare variables
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAdd;
    socklen_t addr_size;
    

    //Server settings
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(8888);
    serverAdd.sin_addr.s_addr = inet_addr("192.168.56.104");
    memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
    addr_size = sizeof serverAdd;

    //Connect to Server
    if (connect(clientSocket, (struct sockaddr *) &serverAdd, addr_size) <0 )
    {
        puts("CONNECTION ERROR!!");
    }
    else{
         puts("#### WELCOME TO AF CHATROOM ####\n");
    
    }
   


    //Input msg from Client1
    printf("Client 1 : ");
    scanf(" %[^\n]s", buffer);
    send(clientSocket,buffer,sizeof buffer - 1,0);      

    //The msg will send & received untill clients type "exit"
    int exit = 0;
    while (exit == 0)
    {
        
        if (compare_strings(buffer, "exit")==-1)
        {
            //Empty the buffer
            memset(&buffer[0], 0, sizeof(buffer));
            
            //Receive func
            int receive = recv(clientSocket, buffer, sizeof buffer - 1, 0);
            //If recv != 1, the message has been received
            if (receive != 1)
            {
                //If input not "exit"
                if (compare_strings(buffer, "exit")==-1)
                {
                    //Input msg from Client2
                    printf("Client 2 : ");
                    printf("%s\n", buffer);

                    //Empty the buffer
                    memset(&buffer[0], 0, sizeof(buffer));
                }
                //If Client2 type "exit"
                else exit=1;
            }
            //If rcv = 1, no message will be received
            else
            {
                //Input msg from Client1
                printf("Client 1 : ");
                scanf(" %[^\n]s", buffer);

                //Send msg to Server
                send(clientSocket,buffer,sizeof buffer - 1,0);
            }
        }
        //Exit the looping when Client type "exit"
        else exit = 1;
    }

    return 0;
}


