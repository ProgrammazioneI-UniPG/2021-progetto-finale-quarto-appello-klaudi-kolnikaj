#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"


struct Giocatore * giocatori;
struct Stanza * stanzai;//stanza iniziale
struct Stanza * stanzap;//stanza precedente
struct Stanza * lista;//lista stanze
unsigned short quest_da_finire, ngiocatori;

static void aggNellaLista(struct Stanza * );
static int tipostanza();
static void stampa_giocatori(int);
const char * stampa_colori(int);
const char * tipo_gioc(int);
static void avanza(int);
static void creazioneStanza(int i);
static void chiamata_emergenza(int);
static void uccidi(int);
static void sabotaggio(int);
static void usa_botola(int);
void termina_gioco();
static void esegui_quest(int);
unsigned short quest_da_finire;





static void aggNellaLista(struct Stanza * stanzanuova){

  struct Stanza * sn = malloc(sizeof(struct Stanza)); // alloco la stanza nuova
  sn = stanzanuova; // gli passo la stanza che viene creata
  sn -> avanti = NULL;

  if (lista == NULL)// guardo se la lista è nulla
    lista = sn;

  else {// altrimenti trovo l'ultimo nodo e aggiungo la nuova

    struct Stanza * ultimo = lista; //punto alla lista

    while (ultimo -> avanti != NULL) {//cerco  l'avanti null dell'ultimo nodo.
      ultimo = ultimo -> avanti;
    }

    ultimo -> avanti = sn;//aggiungo la nuova stanza alla fine
  }
}




void imposta_gioco() {

  // 10 numeri random per colore
  int ct = 0, n = 0;
  int colori[10];
  for (size_t f = 0; f < 10; f++) {
    ct = 0;
    n = rand() % 10;
    for (size_t c = 0; c < 10; c++) {
      if (colori[c] == n) ct = 1;
    }
    if (ct == 0) colori[f] = n;
  }

  do {
    printf("\nQuanti giocatori vuoi? min4 - MAX 10\n");
    scanf("%hd", &ngiocatori);
  } while (ngiocatori < 4 || ngiocatori > 10);
  printf("Quante quest vuoi finire?\n");
  scanf("%hu", & quest_da_finire);
  giocatori = (struct Giocatore * ) malloc(ngiocatori * sizeof(struct Giocatore)); // alloco l'array
  stanzai = (struct Stanza *) malloc(sizeof(struct Stanza)); // alloco stanza d'inizio

  // creazione della stanza iniziale
  stanzai -> tipo = tipostanza();
  stanzai-> avanti = NULL;
  stanzai -> sinistra = NULL;
  stanzai -> destra = NULL;
  stanzai ->  precedente = NULL;
  stanzai -> emergenza = false;
  aggNellaLista(stanzai);  // passo la stanza per aggiungerla alla lista
  int cImpostori = 0;        // tengo il conto dei impostori
  int tipo = 0;

  // creo i giocatori
  for (int i = 0; i < ngiocatori; i++) {

    giocatori[i].posizione = (struct Stanza * ) malloc(sizeof(struct Stanza));
    giocatori[i].posizione = stanzai;
    giocatori[i].nome = colori[i];
    tipo = rand() % (i + 1 + cImpostori);     // all'aumentare di i aumentano gli impostori
    if (cImpostori < 3 && tipo < 2) { // % impostori, non piu di 3 ma non meno di 1
      giocatori[i].stato = 1;
      cImpostori++;
    } else giocatori[i].stato = 0;
  }

  int a = 0;
  do {
    printf("1) STAMPA GIOCATORI\n 2) INIZIA GIOCO\n");
    scanf("%d", &a);
  } while (a < 1 || a > 2);
  if (a == 1) {
    for (int a = 0; a < ngiocatori; a++) {
      stampa_giocatori(a);// chiama il metodo stampa giocatori, che stampa un giocatore alla volta
    }
    do {
      printf("PREMI 1 PER INIZIARE");
      scanf("%d", &a);
    } while (a != 1);
    gioca();
  }
  if(a == 2) gioca();
}




static int tipostanza() {//Assegno il tipo ad una stanza (fa ritornare un intero)

  int tipostanza = rand() % 100;
  if (tipostanza < 15) tipostanza = 2;
  if (tipostanza < 45 && tipostanza > 15) tipostanza = 1;
  if (tipostanza < 75 && tipostanza > 45) tipostanza = 0;
  if (tipostanza < 100 && tipostanza > 75) tipostanza = 3;
  return tipostanza;
}



//avanzamento
static void avanza(int i){

  int a = 0;
  do {
    printf("Dove vuoi andare ?");
    printf("1-Avanti\n 2-Sinistra\n 3-Destra\n");
    scanf("%d", &a);
  }while (a > 3);

  if (a == 1) {
    if (giocatori[i].posizione -> avanti != NULL) { // creo la stanza se è gia creata cambio posizione
      giocatori[i].posizione = giocatori[i].posizione -> avanti; // mi sposto nella stanza avanti
    } else {
      giocatori[i].posizione -> avanti = (struct Stanza * ) malloc(sizeof(struct Stanza)); //alloco la stanza avanti
      giocatori[i].posizione -> avanti -> precedente = giocatori[i].posizione; // gli assegno la posizione attuale alla stanza precedente
      giocatori[i].posizione = giocatori[i].posizione -> avanti; // spostamento stanza avanti
      int sg = i;
      creazioneStanza(sg);
    }
  }

  if (a == 2) {
    if (giocatori[i].posizione -> sinistra != NULL) {
      giocatori[i].posizione = giocatori[i].posizione -> sinistra; // mi sposto nella stanza di sinistra
    } else {
      giocatori[i].posizione -> sinistra = (struct Stanza * ) malloc(sizeof(struct Stanza)); //alloco la stanza di sinistra
      giocatori[i].posizione -> sinistra -> precedente = giocatori[i].posizione; // gli assegno la posizione attuale alla stanza precedente
      giocatori[i].posizione = giocatori[i].posizione -> sinistra; // spostamento nella stanza di sinistra
      int sg = i;
      creazioneStanza(sg);
    }
  }

  if (a == 3) {
    if (giocatori[i].posizione -> destra != NULL) { //
      giocatori[i].posizione = giocatori[i].posizione -> destra; // spostamento nella stanza di destra
    } else {
      giocatori[i].posizione -> destra = (struct Stanza * ) malloc(sizeof(struct Stanza)); //alloco la stanza di destra
      giocatori[i].posizione -> destra -> precedente = giocatori[i].posizione; // gli assegno la posizione attuale alla stanza precedente
      giocatori[i].posizione = giocatori[i].posizione -> destra; // spostamento nella stanza di destra
      int sg = i;
      creazioneStanza(sg);
    }
  }
}




//creo una nuova stanza
static void creazioneStanza(int i) {
    giocatori[i].posizione -> tipo = tipostanza();
    giocatori[i].posizione -> avanti = NULL;
    giocatori[i].posizione -> sinistra = NULL;
    giocatori[i].posizione -> destra = NULL;
    giocatori[i].posizione -> precedente = NULL;
    giocatori[i].posizione -> emergenza = false;
    aggNellaLista(giocatori[i].posizione);  // la aggiungo alla lista
  }


// metodo principale
void gioca(){
      int a = 0;
      int gioc = 0;
      int ngioc = 0; // quanti giocatori ci sono nella stanza
      int emerg = 0; // controllo se ci sono morti in stanza per la possibilita di emergenza
      int giocvivi = 0;
      int impostori = 0;

      if (giocatori == NULL) {//in caso i giocatori fossero null significa che il gioco non è stato impostato
        printf("IMPOSTA ORA IL GIOCO\n");
        imposta_gioco();//chiamo quindi automaticamente il metodo imposta_gioco();
      }
      
       // conto quanti giocatori  vivi e quanti impostori
      for (size_t i = 0; i < ngiocatori; i++) {
        if (giocatori[i].stato == 0) giocvivi++;
        if (giocatori[i].stato == 1) impostori++;
      }


      //in caso ci fossero quest da fare e astronauti vivi il gioco può svolgersi
      if (quest_da_finire > 0 && giocvivi != 0) {  

        do {
          gioc = rand() % ngiocatori; //chiedo un giocatore casuale
        } while (giocatori[gioc].stato == 2 || giocatori[gioc].stato == 3); //fino a che il giocatore uscito non sarà un impostore o astronauta
        stampa_giocatori(gioc); // stampa giocatore selezionato
        printf("*******************************\n");
        printf("\n*I GIOCATORI VIVI NELLA STANZA*\n");
        printf("*******************************\n");
        for (size_t i = 0; i < ngiocatori; i++) {
          if (giocatori[gioc].posizione == giocatori[i].posizione) {
            if (giocatori[i].stato == 2 || giocatori[i].stato == 3) { //faccio vedere SOLO chi e' morto e defenestrato
              printf("\t%s\t%s\n", stampa_colori(giocatori[i].nome), tipo_gioc(giocatori[i].stato));
            } else printf("\t%s\n", stampa_colori(giocatori[i].nome));
          }
          if ((giocatori[i].stato == 2) && (giocatori[i].posizione == giocatori[gioc].posizione) && (giocatori[gioc].posizione -> emergenza)) { //per vedere se morti e emergenza
            emerg = emerg + 1;
          }
        }
        if (emerg == 0) {
          printf("NON CI SONO MORTI OPPURE EMERGENZA GIA' CHIAMATA\n");
        }

        if (giocatori[gioc].stato == 0) {//in caso si giochi con un astronauta
          do {
            printf("1) Avanza\n2) Esegui Quest\n3)Chiama Emesrgenza\n");
            scanf("%d", &a);
          } while (a < 1 || a > 3 || (a == 3 && emerg > 0) || (a == 2 && giocatori[gioc].posizione -> tipo == 0) || (a == 2 && giocatori[gioc].posizione -> tipo == 3));  //condizioni (fa ripetere il menù se certe scelte non si possono fare, come ad esempio chiama emergenza se gia chiamata)

          switch (a) {
          case 1:
            avanza(gioc);
            break;
          case 2:
            esegui_quest(gioc);
            break;
          case 3:
            chiamata_emergenza(gioc);
            break;
          default:
            printf("SCELTA NON CORRETTA, ENTRA DI NUOVO\n");
            break;
          }
        }
        if (giocatori[gioc].stato == 1) {// in caso si giochi con un impostore

          do {
            printf("1) Avanza\n2) Sabotaggio\n3) Chiama Emesrgenza\n4) Uccidi Giocatore\n5) Usa Botola\n");
            scanf("%d", & a);
          } while (a < 1 || a > 5 || (a == 3 && emerg > 0) || (a == 5 && giocatori[gioc].posizione -> tipo != 3) || (a == 2 && (giocatori[gioc].posizione -> tipo != 1 && giocatori[gioc].posizione -> tipo != 2)) || (a == 4 && ngioc == 0));

          switch (a) {
          case 1:
            avanza(gioc);
            break;
          case 2:
            sabotaggio(gioc);
            break;
          case 3:
            chiamata_emergenza(gioc);
            break;
          case 4:
            uccidi(gioc);
            break;
          case 5:
            usa_botola(gioc);
            break;

          default:
            printf("ENTRARE DI NUOVO\n");
            break;
          }
        }
      }
      if (giocvivi == 0) {     //ogni volta che si chiama il metodo gioca conta i astronauti vivi (in caso non ce ne dovessero essere si perde)
        printf("\n PERSO \n");
        termina_gioco();
      }
      if (quest_da_finire == 0 || impostori == 0) {  // se le quest finiscono o tutti gli impostori sono stati defenestrati quindi non piu impostori si vince
        printf("\n VITTORIA\n");
        termina_gioco();
      }
}


// dealloco tutto
void termina_gioco(){


      struct Stanza * plist = lista;    //uso un puntatore list per la lista delle stanze
      struct Stanza * pross;                  //una stanza d'appoggio che puntera alla successiva di plist

      while (plist != NULL) {
        pross = plist -> avanti;
        free(plist);
        plist = pross;
      }               //dealloco ogni stanza della lista
      lista = NULL;

      quest_da_finire = 0;
      ngiocatori = 0;
      free(giocatori);       //dealloco l'array di giocatori
      giocatori = NULL;
    }



// chiamata emergenza con defenestrazione
static void chiamata_emergenza(int i){

   int p = 0;
    int p1 = 0;
    int p2 = 0;
    int flag = 0;
    if (!giocatori[i].posizione -> emergenza) { // se non è mai stata chiamata

      for (size_t a = 0; p < ngiocatori; a++) {
        for (size_t b = 0; p < ngiocatori; b++) { // controllo se defenestrato
          if (giocatori[b].stato == 3 && giocatori[i].posizione == giocatori[a].posizione) flag = 1;
           }
            while (flag == 0) {
                if (giocatori[i].posizione == giocatori[a].posizione && giocatori[a].stato == 1) { // controllo se fa parte della stanza
                p1 = 30;
                for (size_t c = 0; c < ngiocatori; c++) { //vedo tutti
                  if (giocatori[a].posizione == giocatori[c].posizione && giocatori[c].stato == 1) {
                    p1 = p1 - 30;
                  } // controllo quanti altri impostori ci sono nella stanz
                  if (giocatori[a].posizione == giocatori[c].posizione && giocatori[c].stato == 0) {
                    p1 = p1 + 20;
                  } // controllo quanti altri astronauti ci sono nella stanz
                  if (p < p1) {
                    giocatori[a].stato = 3;
                    flag = 1;
                  }
                }
              }

        if (giocatori[i].posizione == giocatori[a].posizione && giocatori[a].stato == 0) { // controllo se fa parte della stanza
           p2 = 30;
              for (size_t c = 0; c < ngiocatori; c++) { //vedo tutti
                if (giocatori[a].posizione == giocatori[c].posizione && giocatori[c].stato == 1) {
                  p2 = p2 + 30;
                } // controllo quanti altri astronauti ci sono nella stanz
                if (giocatori[a].posizione == giocatori[c].posizione && giocatori[c].stato == 0) {
                  p2 = p2 + 20;
                } // controllo quanti altri impostori ci sono nella stanz
                if (p < p2) {
                  giocatori[a].stato = 3;
                  flag = 1;
                }
              }
            }

          }
        }
        giocatori[i].posizione -> emergenza = true;
      }
    }




static void uccidi(int i) {
    int probabilita = rand() % 100 + 1;
    int ugioc = 0; //per vedere se già ucciso...
    for (size_t a = 0; a < ngiocatori; a++) {
      if (giocatori[a].posizione == giocatori[a].posizione && giocatori[a].stato == 0) { // che non commetta suicidio
        if (probabilita < 100 && ugioc != 1) {
          printf("LO HAI UCCISO :%s", stampa_colori(giocatori[a].nome));
          giocatori[a].stato = 2; // muore
          giocatori[a].posizione -> emergenza = true; // per correttezza tolgo anche l'emergenza visto che ci sara una votazione a prescindere da esito +/-
          ugioc = 1; // flag per non uccidere piu di uno a volta (altrimenti farebbe una strage XD, ucciderebbe tutti)
        }
      }
    }
    if (ugioc != 0) {
      int prob_as = 0;
      for (size_t d = 0; d < ngiocatori;d++) {
        if (giocatori[i].posizione == giocatori[d].posizione) {
          prob_as = prob_as + 50;
        }
        if (giocatori[d].posizione -> precedente == giocatori[i].posizione) {
          prob_as = prob_as + 20;
        }
      }
      if (probabilita < prob_as) {
        printf("GIOCATORE DEFENESTRATO: %s", stampa_colori(giocatori[i].nome));
        giocatori[i].stato = 3; // defenestrato
      }
    }
  }



static void usa_botola(int i) {

        struct Stanza * stanzat = lista;  //puntatore alla lista
        int flag = 1;  // flag spostamento

        if (giocatori[i].posizione -> tipo == 3) {   //solo se stanze botola(condizione già vera nelle dell'impostore, tuttavia per un metodo piu corretto la rifaccio)
          while (stanzat != NULL && flag == 1) {  // scorro la lista
            if (stanzat -> tipo == 3) {
              giocatori[i].posizione = stanzat;        // sposto l'impostore
              flag = 0;   // imposto il flag a 0
            }
            stanzat = stanzat -> avanti;
          }
          if (flag == 1) {
            giocatori[i].posizione = (stanzat + rand() % sizeof stanzat);//in caso non dovessero esserci altre stanze botola lo si sposta in una casuale..
          } printf("STANZA CAMBIATA\n");
        }
      }

  static void sabotaggio(int i) {
        if (giocatori[i].posizione -> tipo == 1) {
          giocatori[i].posizione -> tipo = 0;
        }
  }


// esegue le quest e decrementa il numero
void esegui_quest(int i){
          int a = quest_da_finire;    // serve un intero in caso le quest andassero a -1 (rimane una e si fa una quest complicata...)
          if (giocatori[i].posizione -> tipo == 1) {
            giocatori[i].posizione -> tipo = 0;
            a = a - 1;
          }
          if (giocatori[i].posizione -> tipo == 2) {
            giocatori[i].posizione -> tipo = 0;
            a = a - 2;
          }
          if (a < 0 || a == 0) {
            quest_da_finire = 0;
          } else quest_da_finire = a;
          printf("QUEST RIMASTE: %hu\n", quest_da_finire);
        }

static void stampa_giocatori(int i){ // stampa un giocatore
          printf("Nome: %s\n Tipo: %s\n Stanza: %d\n", stampa_colori(giocatori[i].nome), tipo_gioc(giocatori[i].stato), tipostanza(giocatori[i].posizione -> tipo));
        }


//stampa un nome
const char * stampa_colori(int i){ //stampa un nome


     const char * r = NULL;


          switch(i){
            case 0:
              r= "rosso";
            break;

            case 1:
                r= "arancione";
            break;

            case 2:
                r= "giallo";
            break;

            case 3:
                r="rosa";
            break;

            case 4:
                r= "nero";
            break;

            case 5:
                r= "celeste";
            break;

            case 6:
               r= "marrone";
            break;

            case 7:
                r= "blu";
            break;

            case 8:
                printf("bianco");
            break;

            case 9:
                r = "verde";
            break;
          }

            return r;
        }


// stampa un tipo di giocatore
  const char * tipo_gioc(int i){

  const char * r = NULL;

          switch(i){
            case 0:
                r= "astronauta";
            break;
            case 1:
                r= "impostore";
            break;
            case 2:
                r="assasinato";
            break;
            case 3:
                r= "defenestrato";
            break;

        }
        return r;
  }



// stampa un tipo di stanza
const char * tipo_stanza(int i){

const char * r = NULL;

          switch(i){
            case 0:
                r= "vuota";
            break;
            case 1:
                r= "quest_semplice";
            break;
            case 2:
                r="quest_complicata";
            break;
            case 3:
                r= "botola";
            break;

        }
        return r;

  }


