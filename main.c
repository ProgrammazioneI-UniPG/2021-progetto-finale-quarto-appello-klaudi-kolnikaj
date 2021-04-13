#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

//MENU
void menu();
int main(void){
int scelta;

do {
  printf("\nSELEZIONARE UN'OPZIONE\n");
  printf("\n*1) IMPOSTA GIOCO *\n");
  printf("\n*2) GIOCA         *\n");
  printf("\n*3) TERMIINA GIOCO*\n");
  scanf("%d", &scelta);
  


  switch(scelta){
    case 1:
    printf("HAI SELEZIONATO IMPOSTA GIOCO");
    imposta_gioco();
        break;
    case 2:
    printf("HAI SELEZIONATO GIOCA");
    gioca();
        break;
    case 3:
    printf("HAI SELEZIONATO TERMINA GIOCO");
    termina_gioco();
        break;
    default:
        printf("Il comando è sbagliato\n");
        break;
}
}while(scelta > 4);
return 0;
}
