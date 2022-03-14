//Théo Brocard
//bataille navale v1
//07.03.2022

//TO DO; faire que les bateaux soient "coulés"
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

int main() {
    //declaration des variables
    int regle = 2;
    int Colonne = -1, Ligne = -1;
    char RepCol[] = "A";
    char pseudo[20];
    int nbBateau;
    int score;

    int tab[10][10] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 5, 5, 0},
            {4, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {4, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {4, 0, 0, 0, 0, 0, 0, 0, 3, 0},
            {0, 0, 0, 0, 2, 2, 0, 0, 3, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
            {0, 0, 0, 0, 0, 3, 3, 0, 3, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    //Menu principal
    printf("    Bataille Navale 1.0");
    printf("\n   ---------------------");
    printf("\n\nbienvenue.\nveuillez choisir un pseudo (20 caracteres max et pas d'espaces) :");
    scanf("%s", &pseudo);

    //boucle pour que le menu se repete apres avoir choisi le tuto
    do {


        printf("\nBonjour %s, veuillez choisir ce que vous voulez faire :");
        printf("\n1: Apprendre a jouer :");
        printf("\n2: Jouer contre l'ordinateur :");
        printf("\n   ecrivez votre reponse ici :");
        scanf("%d", &regle);

        //Faire que le menu fonctionne en 2 partie (1 apprendre a jouer)(2 jouer)

        switch (regle) {
            case 1:

                printf("\nLe but du jeu est de couler tous les bateaux de l adversaire. Pour cela, chacun votre tour,vous devez essayer de  tirer  sur ses navires en devinant leurs positions.\n\n Pour tirer, il faut citer les coordonnees d un emplacement comprenant un chiffre et une lettre. Par exemple : H5. Si le bateau de votre opposant se trouve a cette position alors il est touche et vous pouvez rejouer Pour couler le navire,il faut le toucher entierement.C est a dire qu un bateau prenant 5 cases doit etre atteint en ses 5 cases pour etre coule. Le premier a faire chavirer tous les navires de l autre a gagne. \n\n ");
                break;


            case 2:

                //afficher le tableau avant de demander quel colonne choisir

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

                do {
                    printf("\nColonne ?(A-J)"); //demande quel colonne on veut toucher
                    scanf("%s", &RepCol);
                    RepCol[0] = RepCol[0] & (0xFF - 0x20);
                    Colonne = RepCol[0] - 65;
                    printf("\nLigne ?(1-10)"); //demande la ligne qu on veut toucher
                    scanf("%d", &Ligne);
                    Ligne -= 1;

                    //mettre à jour le tableau
                    if (tab[Ligne][Colonne] < 10)
                        tab[Ligne][Colonne] += 10;




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


                    printf("\n\nil vous reste %d  case de bateaux", nbBateau);// affiche le nombre de <case de bateau> restant


                } while (nbBateau > 5);
                return 0;
        }
    } while (regle > 0);// suite de la boucle pour que le menu continue apres avoir demander le tuto
}