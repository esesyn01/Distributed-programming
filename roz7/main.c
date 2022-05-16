#include <unistd.h>
#include <stdio.h>
#define ODCZYT 0
#define ZAPIS 1
int main ()
{
    int potok[2];
    int potok2[2];
    int x;
    char message[80];
    char message_upper[80];
    char recv[80];
    puts (" Program pipes startuje ");
    puts (" Tworze potok ");
    pipe (potok);
    pipe (potok2);
    puts (" fork ");
    if (fork())
    {
        puts (" Proces macierzysty ");
        close (potok2[ZAPIS]);
        puts (" Czekam na proces potomny ");
        read (potok2[ODCZYT],recv,sizeof(recv));
        printf(" Proces macierzysty otrzymal: %s \n ",recv);
        close(potok2[ODCZYT]);
    }
    else
    {
        if(fork())
        {
            puts(" Proces potomny ");
            read(potok[ODCZYT], &message_upper, sizeof(message_upper));
            int it=0;
            while(message_upper[it]!='\0')
            {
                if (message_upper[it]>96 && message_upper[it]<123)
                {
                    message_upper[it]-=32;
                }
                it++;
            }
            close(potok[ODCZYT]);
            write(potok2[ZAPIS],message_upper,sizeof(message_upper));
            puts(" Proces potomny wyslal ");
            close(potok2[ZAPIS]);
        }
        else
        {
            puts(" Proces potomno potomny ");
            close(potok[ODCZYT]);
            scanf("%s", message);
            close(potok[ODCZYT]);
            write(potok[ZAPIS],&message,sizeof(message));
            puts(" Proces potomno potomny wyslal ");
            close(potok[ZAPIS]);
        }
    }
    puts(" Program pipes konczy ");
}