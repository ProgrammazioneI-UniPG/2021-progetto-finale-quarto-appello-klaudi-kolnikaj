#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

//MENU
void menu();
int main(void){
int scelta;

do {
  printf("SELEZIONARE UN'OPZIONE");
  printf("*********MENU******");
  printf("*1) IMPOSTA GIOCO *");
  printf("*2) GIOCA         *");
  printf("*3) TERMIINA GIOCO*");
  printf("*******************");
  scanf("%d", &scelta);
  while(getchar()=='\n');


  switch(scelta){
    case 1:
        printf("HAI SELEZIONATO IMPOSTA GIOCO\n");
        break;
    case 2:
        printf("HAI SELEZIONATO GIOCA\n");
        break;
    case 3:
        printf("HAI SELEZIONATO TERMINA GIOCO\n");
        break;
    default:
        printf("Il comando è sbagliato\n");
        break;
}
}
while(scelta < 4);
}



