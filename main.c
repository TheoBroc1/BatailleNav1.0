//Théo Brocard
//bataille navale v1
//07.03.2022


#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//
int regle = 2;
int Colonne = -1, Ligne = -1;
char RepCol[] = "A";
char pseudo[20];
int nbBateau;
int nbRandom;
int score=3;
int tire;


int tab[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
//affiche le fichier du score
void afficheFichier(char nomFichier[]){
    //Cette fonction affiche le fichier texte
    //dont le nom est passé par la variable "nomFichier"
    char chaine[50]="";//pour lire une ligne, longueur max 50
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "r");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        //lecture de la ligne suivante
        printf("\n******** début de fichier ***********\n");
        while (fgets(chaine,50,fichier) ){
            printf("%s",chaine);//affichage ligne (y compris fin de ligne)
        }
        printf("\n********* fin de fichier ************\n");
        fclose(fichier); // fermeture du fichier
    }
}
// ajoute un fichier pour le score
void ajouteFichier(char nomFichier[], char ligne[]){
    //Cette fonction ouvre le fichier nomFichier
    // et ajoute une ligne avec la chaine ligne[]
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "a");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        //Ecrire un saut de ligne puis la ligne
        fputs("\n",fichier);
        fputs( ligne, fichier );
        fclose(fichier); // fermeture du fichier
    }
}

//pour que dans le score, il y ai la date et l'heure que quand il y a eu une partie
void dateHeure(char chaine[]){
    //Cette fonction va chercher la date et l'heure et l'écrit dans la variable qu'on lui donne
    time_t now;
    int h,min,s,day,month,year;//pour récupérer chaque détail

    time(&now);// Renvoie l'heure actuelle
    struct tm *local = localtime(&now);//structure qui contient chaque détail de l'heure
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    // Ecrire dans la chaine les détails du genre 28/03/2022 11:52:05
    sprintf(chaine,"%02d/%02d/%04d %02d:%02d:%02d",day,month,year,h,min,s);

}
// ajoute le fichier pour la date et l'heure du score
void ajouteFichierAvecHeure(char nomFichier[], char ligne[]){
    char dateheure[20]="";//chaine pour écrire l'heure
    char saisie2[50]="";

    //récupération de l'heure
    dateHeure(dateheure);
    //Concaténation heure + saisie
    sprintf(saisie2,"%s %s",dateheure, ligne);
    //Ecriture dans le fichier
    ajouteFichier("../score.txt",saisie2);

}
//pour pouvoir inserer plusieurs fichier dans le code, pour avoir plusieurs tableaux différents
int lectureFichierVersTableau(char nomFichier[]) {
    //Cette procédure lit le fichier nomFichier (ex: ../BN1.txt dans le répertoire du main.c)
    //on s'attend à un fichier du genre:
    // 0011111000
    // 0000033000... etc
    //et le transforme en fichier BN[10][10]
    char chaine[20];
    FILE *fichier = NULL; // pointeur sur le fichier
    //ouverture du fichier en mode lecture seule
    fichier = fopen(nomFichier, "r");
    // teste si le fichier existe
    if (fichier == NULL) {
        printf("Le fichier n'existe pas!\n");
    } else {
        int ligne=0;
        //lecture de la ligne suivante (de 0 à 9 max)
        while (fgets(chaine,20,fichier) && ligne<10){
            int co=0;
            //la boucle s'arrête soit quand on est à 9, soit quand ce n'est pas un chiffre
            while (co<10 && chaine[co]>=48 && chaine[co]<=57){
                tab[ligne][co]=chaine[co]-48;
                co++;
            }
            ligne++;
        }
        fclose(fichier); // fermeture du fichier
    }
}


    int main() {
        //declaration des variables
        SetConsoleOutputCP(65001); //pour les accents





        //Menu principal

        printf("   \n Bataille Navale 1.0");
        printf("    \n    Théo Brocard");
        printf("\n---------------------");
        printf("\n\nbienvenue.\nveuillez choisir un pseudo (20 caracteres max et pas d'espaces) :");
        scanf(" %s", &pseudo); // pour pouvoir choisir un pseudo
        ajouteFichierAvecHeure("../score.txt",pseudo); //pour que sa affiche le pseudo dans le score

        //boucle du jeu principal pour qu'il ne dur pas qu'une seul manche
        do {

            printf("\nBonjour %s, veuillez choisir ce que vous voulez faire :");
            printf("\n1: Apprendre à jouer :");
            printf("\n2: Jouer contre l'ordinateur :");
            printf("\n3: Score :", score);
            printf("\n   écrivez votre réponse ici :");
            scanf("%d", &regle);


            //Faire que le menu fonctionne en 2 partie (1 apprendre a jouer)(2 jouer)

            switch (regle) {
                case 1:

                    printf("\nRaté = 0");    //explique les logos
                    printf("\nTouché = X");  //explique les logos
                    printf("\nCoulé = /\n"); //expplique les logos

                    printf("\nLe but du jeu est de couler tous les bateaux de l'adversaire. Pour cela, chacun votre tour,vous devez essayer de  tirer  sur ses navires en devinant leurs positions.\n\n Pour tirer, il faut citer les coordonnées d'un emplacement comprenant un chiffre et une lettre. Par exemple : H5. Si le bateau de votre opposant se trouve a cette position alors il est touché et vous pouvez rejouer Pour couler le navire,il faut le toucher entierement.C est a dire qu un bateau prenant 5 cases doit être atteint en ses 5 cases pour être coulé. Le premier a faire chavirer tous les navires de l autre a gagné. \n\n ");
                    break;


                case 2:
                    printf("\n-----------------"); // rajoute une ligne pour le style
                    printf("\nRaté = 0");      // explique les logos
                    printf("\nouché = X");     // explique les logos
                    printf("\nCoulé = /\n");   // explique les logos



                    // faire que le programme choisissent un tableau aléatoire
                    srand(time(NULL));
                    nbRandom = rand() % 5 + 1;
                    char nomfichier[15] = "../tableau%d.txt";
                    sprintf(nomfichier, "../tableau%d.txt", nbRandom);
                    lectureFichierVersTableau(nomfichier);
                    printf(" \n%s\n", nomfichier);



                    //printf("\n   Bataille Navale 1.0");
                    //printf("\n  ----------------------");
                    printf("\n   A  B  C  D  E  F  G  H  I  J ");
                    for (int ligne = 0; ligne < 10; ligne++) {
                        printf("\n");
                        printf("%2d", ligne + 1);
                        for (int col = 0; col < 10; col++) {
                            if (tab[ligne][col] < 10) {
                                printf(" _|"); //tableau de base
                            }
                            if (tab[ligne][col] == 10) {
                                printf(" O|"); // ajoute un <0> si je rate le bateau
                            }
                            if (tab[ligne][col] > 10) {
                                printf(" X|"); // ajoute un <X> si je touche le bateau
                            }
                            if (tab[ligne][col] > 20) {
                                printf(" /|"); // ajoute des </> quand le bateau est coulé
                            }
                        }
                    }
                    //boucle do pour que le tableau se réaffiche
                    do {
                        printf("\nColonne ?(A-J)"); //demande quel colonne on veut toucher
                        scanf("%s", &RepCol);
                        RepCol[0] = RepCol[0] & (0xFF - 0x20);
                        Colonne = RepCol[0] - 65;
                        printf("\nLigne ?(1-10)"); //demande la ligne qu on veut toucher
                        scanf("%d", &Ligne);
                        Ligne -= 1;


                        //mettre à jour le tableau
                        if (tab[Ligne][Colonne] < 10) {
                            tab[Ligne][Colonne] += 10;
                        }





                        //afficher le tableau apres choix
                        printf("\n   A  B  C  D  E  F  G  H  I  J ");
                        for (int ligne = 0; ligne < 10; ligne++) {
                            printf("\n");
                            printf("%2d", ligne + 1);
                            for (int col = 0; col < 10; col++) {
                                if (tab[ligne][col] < 10) {
                                    printf(" _|");
                                }
                                if (tab[ligne][col] == 10) {
                                    printf(" O|");
                                }
                                if (tab[ligne][col] > 10) {
                                    printf(" X|");
                                }
                                if (tab[ligne][col] > 20) {
                                    printf(" /|");
                                }
                            }
                        }


                        //pour que quand il n'y à plus de bateau, la bataille s'arrête
                        nbBateau = 0;
                        for (int ligne = 0; ligne < 10; ligne++) {
                            for (int col = 0; col < 10; col++) {
                                if ((tab[ligne][col] >= 1) && (tab[ligne][col] <= 5)) {
                                    nbBateau++;
                                }
                            }
                        }


                        printf("\n\nil vous reste %d  case contenant une partie de bateaux",
                               nbBateau);// affiche le nombre de <case de bateau> restant



                    } while (nbBateau > 0);// quand il reste 0 bateaux, le joueur a gagné
                    printf("\nBien joué, tu as touché tous les bateaux, tu as gagné !.\n");// message quand le joueur a gagné

                    ajouteFichierAvecHeure("../score.txt",pseudo); //pour afficher le pseudo dans le score
                    return 0;



                    case 3:
                    afficheFichier("../score.txt"); //pour que le fichier soient dans le code
                    break;

            }
        } while (regle > 0);// suite de la boucle pour que le menu continue apres avoir demander le tuto

    }