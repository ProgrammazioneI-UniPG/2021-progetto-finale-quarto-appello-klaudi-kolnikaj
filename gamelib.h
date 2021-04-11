#include <stdbool.h>

enum Tipo_stanza {vuota, quest_semplice, quest_complicata, botola};

struct Stanza {
    struct Stanza * avanti;
    struct Stanza * sinistra;
    struct Stanza * destra;
    struct Stanza * precedente;
    enum Tipo_stanza tipo;
    bool emergenza;
  };

  enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};
  enum Nome_giocatore {rosso, arancione, giallo, rosa, nero, celeste, marrone,blu, bianco, verde};

  struct Giocatore {
     enum Nome_giocatore nome;
     enum Stato_giocatore stato;
     struct Stanza * posizione;
  };

    void imposta_gioco();
    void gioca();
    void termina_gioco();



