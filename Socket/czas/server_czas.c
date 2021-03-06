#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

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
    //while(1){
    //odczyt wiadomosci klienta
    bzero(wiadomosc,200);
    recv(gniazdo_klienta,wiadomosc,200,0);
    printf("klient pyta: %s\n", wiadomosc);

    bzero(wiadomosc,200);
   // int a = rand()%100;
    //char tab[10];
    //sprintf(tab, "%d", a);
    time_t now;
    time(&now);
    printf("%s", ctime(&now));
    strcpy(wiadomosc, ctime(&now));
    send(gniazdo_klienta,wiadomosc,strlen(wiadomosc),0);

    }
    close(gniazdo);
    close(gniazdo_klienta);
    
return 0;    
}
