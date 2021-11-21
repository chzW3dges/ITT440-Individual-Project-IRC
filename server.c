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
    int socket_desc, Client1, Client2;
    char buffer[1024];
    struct sockaddr_in serverAdd;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size; 
    

    //Server settings
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(8888);
    serverAdd.sin_addr.s_addr = inet_addr("192.168.56.104");
    memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
    bind(socket_desc, (struct sockaddr *) &serverAdd, sizeof(serverAdd));

    //Server listen
    if (listen(socket_desc,5)==0)
        {
        puts("\n#################### WELCOME TO SERVER AF CHATROOM ####################");
        puts("                         Server is Listening...\n"); //puts letak string into new line terus
        }
     else
        puts("Error"); //kalau printf kene ada \n baru new line

    //Bind - 1 server, 2 clients
    addr_size = sizeof serverStorage;
    Client1 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);
    Client2 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);

    int exit = 0;
    //Function where disconnect when client type "exit"
    while (exit == 0)
    {
        
        recv(Client1, buffer, 1024, 0); //receive msg from Client1
        printf ("%s\n   --Send to Client2--\n", buffer); //send msg to Client2
        send(Client2,buffer,1024,0);

        //Exit the looping if Client1 type "exit"
        if (compare_strings(buffer, "exit")==0)
            {   
            exit = 1;
            }
        
        else 
            {
            //Empty the buffer
            memset(&buffer[0], 0, sizeof(buffer));

            recv(Client2, buffer, 1024, 0); //receive msg from Client2
            printf ("%s\n   --Send to Client1--\n", buffer); //send msg to Client1
            send(Client1,buffer,1024,0);

            //Exit the looping if Client2 type "exit"
            if (compare_strings(buffer, "exit")==0)
                {
                exit = 1;
                }
            }
    }

    return 0;
}

