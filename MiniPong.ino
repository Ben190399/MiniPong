#include <SoftwareSerial.h>
#include <Minitel.h>

Minitel m;
int x = 0;      //Sert à l'affichage des bordure en heut et en bas (pour ne pas à avoir à dessiner tout les pixels un par un)
int Y = 0;      //Emplacement de la raquette du joueur 1
int Z = 0;      //Emplacement de la raquette du joueur 1
int ballx = 0;  //Position horizontale de la balle
int bally = 0;  //Position vertical de la balle
int d = 1;      //Dirrection de la balle
int pa = 0;     //Points du joueur 1
int pb = 0;     //Points du joueur 2
int menu = 1;   //Emplacement du curseur sur le menu
int set = 2;    //Taille de la hotbox des raquettes
int start = 0;  //Initialisation du jeu
int best = 0;   //Meilleur score en mode 1 joueur

void setup() {

  //Affichage des éléments fixes du menu
  m.clearScreen();
  m.textMode();
  m.charSize(SIZE_DOUBLE);
  m.text("PONG", 18, 3);
  m.text("1JOUEUR  2JOUEURS", 4, 10);
  m.charSize(SIZE_NORMAL);
  m.text("Hitbox des raquettes :", 4, 16);
  m.text("  1case    3cases    5cases", 4, 18);
  m.graphicMode();
  m.graphic("110000", 15, 19);

  //Apparition aléatoire de la balle
  ballx = random(2, 20);  //
  bally = random(2, 24);  //La balle n'apparait que dans la partie gauche de l'écran
  d = random(1, 3);       //La balle partira toujours vers la droite
}

void loop() {

  if(start == 0){ //Lit les données renvoyées par le potentiomètre pour donner l'emplacement du curseur dans le menu
    menu = map(analogRead(A1), 0, 1023, 1, 6);
    m.graphicMode();
  }
  if(menu == 1 && start == 0){  //Emplacement du curseur sur joueur 1
    m.graphic("110000", 4, 11);
    m.graphic("000000", 4, 11);
  }
  if(menu == 2 && start == 0){  //Emplacement du curseur sur joueur 2
    m.graphic("110000", 22, 11);
    m.graphic("000000", 22, 11);
  }
  if(menu == 3 && start == 0){  //etc.
    m.graphic("001011", 5, 18);
    m.graphic("000000", 5, 18);
  }
  if(menu == 4 && start == 0){
    m.graphic("001011", 14, 18);
    m.graphic("000000", 14, 18);
  }
  if(menu == 5 && start == 0){
    m.graphic("001011", 24, 18);
    m.graphic("000000", 24, 18);
  }

  if(menu == 3 && start == 0 && digitalRead(2) == 1){ //Sélection de la taille de la hitbox des raquettes
    set = 1;
    m.graphic("110000", 6, 19);
    m.graphic("000000", 15, 19);
    m.graphic("000000", 25, 19);
  }
  if(menu == 4 && start == 0 && digitalRead(2) == 1){
    set = 2;
    m.graphic("110000", 15, 19);
    m.graphic("000000", 6, 19);
    m.graphic("000000", 25, 19);
  }
  if(menu == 5 && start == 0 && digitalRead(2) == 1){
    set = 3;
    m.graphic("110000", 25, 19);
    m.graphic("000000", 6, 19);
    m.graphic("000000", 15, 19);
  }

  if(menu == 1 && start == 0 && digitalRead(2) == 1){ //Initialisation et affichage de l'interface du mode 1 joueur
  
  m.graphicMode();
  m.clearScreen();
  m.moveCursorTo(1, 1);
  while(x < 40){
    m.graphic("111111");
    x++;
    }
  x = 0;
  
  m.moveCursorTo(1, 24);
  while(x < 40){
    m.graphic("111111");
    x++;
    }
  x = 1;
  
  while(x < 24){
    m.graphic("111111", 40, x);
    x++;
  }
  
  m.textMode();
  m.moveCursorTo(5, 1);
  m.text("0");
  m.moveCursorTo(20, 1);
  m.text("Best:0");
  start = 1;
  }
  
  if(menu == 2 && start == 0 && digitalRead(2) == 1){ //Initialisation et affichage de l'interface du mode 2 joueurs
  
  m.graphicMode();
  m.clearScreen();
  m.moveCursorTo(1, 1);
  while(x < 40){
    m.graphic("111111");
    x++;
    }
  x = 0;
  
  m.moveCursorTo(1, 24);
  while(x < 40){
    m.graphic("111111");
    x++;
    }
  
  m.textMode();
  m.moveCursorTo(5, 1);
  m.text("0");
  m.moveCursorTo(36, 1);
  m.text("0");
  start = 1;
  
  }

  if(menu == 1 && start == 1){  //Boucle indéfiniment sur le mode 1 joueur une fois le jeu initialisé
    solo();
  }
  
  if(menu == 2 && start == 1){  //Boucle indéfiniment sur le mode 2 joueurs une fois le jeu initialisé
    multi();
  }
}

void solo() {
  Y = map(analogRead(A1), 0, 1023, 2, 24);  //Lit les données renvoyées par le potentiomètre pour donner l'emplacement de la raquette

  m.graphicMode();
  m.moveCursorTo(1, Y);
  m.graphic("111111");
  m.moveCursorTo(ballx, bally);
  m.graphic("111111");
  m.moveCursorTo(1, Y);
  m.graphic("000000");
  m.moveCursorTo(ballx, bally);
  m.graphic("000000");            //Affichage de la balle et de la raquette

  if(d == 1){
    hd();
  }
  if(d == 2){
    bd();
  }
  if(d == 3){
    bg();
  }
  if(d == 4){
    hg();       //Dirrection de la balle
  }

  if(bally == 2){
    if(d == 1){
      d = 2; 
    }
    if(d == 4){
      d = 3;
    }
    m.bip(200);   //Changement de dirrection lorsque la balle touche le mur du haut + bip
  }

  if(bally == 23){
    if(d == 3){
      d = 4; 
    }
    if(d == 2){
      d = 1;
    }
    m.bip(200);   //Changement de dirrection lorsque la balle touche le mur du bas + bip
  }

  if(set == 1){
    if(ballx == 2 || ballx == 1){ //Vérifier si la balle est dans la colonne de la raquette
      if(bally == Y){             //Vérifier si la balle touche la raquette (hitbox)
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }                           //Changement de dirrection lorsque la balle touche la raquette 
      pb++;
      String A = String(pb);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);                  //Incrémentation d'un point
      m.bip(200);                 //bip
    }
    else{                         //Sinon
      if(pb > best){              //Si le score courant est supérieur au meilleur score
        best = pb;                
        String C = String(best);
        m.textMode();
        m.moveCursorTo(25, 1);
        m.text(C);                //Actualiser le meilleur score
      }
      pb = 0;
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text("0");            //Remise à 0 du score courant
      m.graphicMode();
      m.moveCursorTo(6, 1);
      m.graphic("111111");
      m.graphic("111111");    //Efface le score de plus de 2 chiffres
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);       // Replace la balle aléatoirement
    }
  }
  }
  
  if(set == 2){                                     //Idem que pour set == 1
    if(ballx == 2 || ballx == 1){
  if(bally == Y || bally == Y+1 || bally == Y-1){   //Hitbox +1 et -1 autour du curseur
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }
      pb++;
      String A = String(pb);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);
      m.bip(200);
    }
    else{
      if(pb > best){
        best = pb;
        String C = String(best);
        m.textMode();
        m.moveCursorTo(25, 1);
        m.text(C);
      }
      pb = 0;
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text("0");
      m.graphicMode();
      m.moveCursorTo(6, 1);
      m.graphic("111111");
      m.graphic("111111");
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  }

  if(set == 3){                                     //Idem que pour set == 1
    if(ballx == 2 || ballx == 1){
  if(bally == Y || bally == Y+1 || bally == Y-1 || bally == Y+2 || bally == Y-2){ //Hitbox +1, -1, +2, -2 autour du curseur
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }
      pb++;
      String A = String(pb);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);
      m.bip(200);
    }
    else{
      if(pb > best){
        best = pb;
        String C = String(best);
        m.textMode();
        m.moveCursorTo(25, 1);
        m.text(C);
      }
      pb = 0;
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text("0");
      m.graphicMode();
      m.moveCursorTo(6, 1);
      m.graphic("111111");
      m.graphic("111111");
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  }

  if(ballx == 39 || ballx == 38){
    if(d == 2){
        d = 3;
      }
      if(d == 1){
        d = 4;
      }
      m.bip(200);                   //Fait rebondir la balle contre le mur d'en face + bip
    }

}

void multi() {
  Y = map(analogRead(A1), 0, 1023, 2, 24);  //Lit l'emplacement de la raquette du joueur 1 sur le potentiomètre
  Z = map(analogRead(A2), 0, 1023, 2, 24);  //Lit l'emplacement de la raquette du joueur 2 sur le potentiomètre

  m.graphicMode();
  m.moveCursorTo(1, Y);
  m.graphic("111111");
  m.moveCursorTo(40, Z);
  m.graphic("111111");
  m.moveCursorTo(ballx, bally);
  m.graphic("111111");
  m.moveCursorTo(1, Y);
  m.graphic("000000");
  m.moveCursorTo(40, Z);
  m.graphic("000000");
  m.moveCursorTo(ballx, bally);
  m.graphic("000000");                //Affichage des raquettes et de la balle

  if(d == 1){
    hd();
  }
  if(d == 2){
    bd();
  }
  if(d == 3){
    bg();
  }
  if(d == 4){
    hg();
  }             //Dirrection de la balle

  if(bally == 2){
    if(d == 1){
      d = 2; 
    }
    if(d == 4){
      d = 3;
    }
    m.bip(200);
  }

  if(bally == 23){
    if(d == 3){
      d = 4; 
    }
    if(d == 2){
      d = 1;
    }
    m.bip(200);
  }                 //Rebond de la balle contre les murs

  if(set == 1){                       //Idem que pour le mode 1 joueur + vérification de contact entre la balle et la raquette du joueur 2
    if(ballx == 39 || ballx == 38){
    if(bally == Z){
      if(d == 2){
        d = 3;
      }
      if(d == 1){
        d = 4;
      }
      m.bip(200);
    }
    else{
      pa = pa + 1;
      String A = String(pa);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  
  if(ballx == 2 || ballx == 1){
  if(bally == Y){
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }
      m.bip(200);
    }
    else{
      pb = pb + 1;
      String B = String(pb);
      m.textMode();
      m.moveCursorTo(36, 1);
      m.text(B);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  }

  if(set == 2){
  if(ballx == 39 || ballx == 38){
    if(bally == Z || bally == Z+1 || bally == Z-1){
      if(d == 2){
        d = 3;
      }
      if(d == 1){
        d = 4;
      }
      m.bip(200);
    }
    else{
      pa = pa + 1;
      String A = String(pa);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  
  if(ballx == 2 || ballx == 1){
  if(bally == Y || bally == Y+1 || bally == Y-1){
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }
      m.bip(200);
  }
    else{
      pb = pb + 1;
      String B = String(pb);
      m.textMode();
      m.moveCursorTo(36, 1);
      m.text(B);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  }

  if(set == 3){
  if(ballx == 39 || ballx == 38){
    if(bally == Z || bally == Z+1 || bally == Z-1 || bally == Z+2 || bally == Z-2){
      if(d == 2){
        d = 3;
      }
      if(d == 1){
        d = 4;
      }
      m.bip(200);
    }
    else{
      pa = pa + 1;
      String A = String(pa);
      m.textMode();
      m.moveCursorTo(5, 1);
      m.text(A);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  
  if(ballx == 2 || ballx == 1){
  if(bally == Y || bally == Y+1 || bally == Y-1 || bally == Y+2 || bally == Y-2){
      if(d == 4){
        d = 1;
      }
      if(d == 3){
        d = 2;
      }
      m.bip(200);
    }
    else{
      pb = pb + 1;
      String B = String(pb);
      m.textMode();
      m.moveCursorTo(36, 1);
      m.text(B);
      ballx = random(2, 20);
      bally = random(2, 24);
      d = random(1, 3);
    }
  }
  }
}

void hd() {           //Dirrection de la balle Haut Droite
  ballx = ballx + 2;
  bally--;
}

void bd() {           //Dirrection de la balle Bas Droite
  ballx = ballx + 2;
  bally++;
}

void bg() {           //Dirrection de la balle Bas Gauche
  ballx = ballx - 2;
  bally++;
}

void hg() {           //Dirrection de la balle Haut Gauche
  ballx = ballx - 2;
  bally--;
}


