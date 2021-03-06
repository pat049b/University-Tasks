#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    
   int gniazdo,gniazdo_klienta,dl_adresu,odczyt;
   struct sockaddr_in adres_servera, adres_clienta;
   char wiadomosc[200];
   
   bzero(wiadomosc,200);
   
   gniazdo = socket(AF_INET,SOCK_STREAM,0);
   if(gniazdo<0){
       printf("gniazdko nam nie powstalo\n");
       exit(1);
   }
    
    memset(&adres_servera, 0, sizeof(adres_servera));
    adres_servera.sin_family = AF_INET;
    adres_servera.sin_port = htons(8888);
    adres_servera.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(gniazdo, (struct sockaddr*)&adres_servera, sizeof(adres_servera))<0){
        printf("nie zbindowalo sie\n");
        exit(1);
    }
    
    listen(gniazdo,5);
    
    dl_adresu = sizeof(adres_clienta);
    gniazdo_klienta = accept(gniazdo, (struct sockaddr*)&adres_clienta, &dl_adresu);
    if(gniazdo_klienta<0){
        printf("nie ma akceptacji");
        exit(1);
    }
    
    for(;;){
    //odczyt wiadomosci klienta
    bzero(wiadomosc,200);
    recv(gniazdo_klienta,wiadomosc,200,0);
    printf("klient pyta: %s\n", wiadomosc);

    int a,dl,b,wynik,i;
    char tab[10],tab3[10],znak;

    a=atoi(wiadomosc);
    sprintf(tab, "%d", a);
    dl=strlen(tab);
    znak=wiadomosc[dl];
    for(i=0;i<10;i++){
        tab3[i]=wiadomosc[i+dl+1];
    }

    b=atoi(tab3);
    switch(znak){
        case '+':
            wynik = a+b;
            break;
        case '-':
            wynik = a-b;
            break;
        case '*':
            wynik = a*b;
            break;
        case '/':
            wynik = a/b;
            break;
    }

    sprintf(tab, "%d", wynik);
    strcpy(wiadomosc, tab);
    send(gniazdo_klienta,wiadomosc,strlen(wiadomosc),0);

    }
    close(gniazdo);
    close(gniazdo_klienta);

return 0;    
}
