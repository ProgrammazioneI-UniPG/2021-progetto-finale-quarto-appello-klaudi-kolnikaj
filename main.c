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
  printf("*********MENU******\n");
  printf("*1) IMPOSTA GIOCO *\n");
  printf("*2) GIOCA         *\n");
  printf("*3) TERMIINA GIOCO*\n");
  printf("*******************\n");
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


