#include <stdio.h>
#include <stdlib.h>

/*
Voyageur de commerce
Author : Axel MACZKOWIAK
Date : 11/11/2017
*/

/*int tabVilles[5][5] = {
        {0,120,45,84,67},
        {120,0,234,56,87},
        {45,234,0,156,41},
        {84,56,156,0,100},
        {67,87,41,100,0}
    };*/

//Fonctions statiques

//Tableau stockant les distances entre les villes
int tabVilles[5][5] = {0};
int *tab;

//Fonction prenant en param�tre le num�ro de la ville � v�rifier ainsi que le tableau de �tapes d�j� effectu�es. Renvoie 1 si la ville � d�j� �t� visit�e, 0 sinon.
int isVisited(int ville, int etapes[5]){
    int i;
    int res = 0;
    for (i = 0; i < 5; i++){
        if (etapes[i]==ville) {
            res = 1;
        }
    }
    return res;
}


//Fonction principale de l'exercice en statique, prenant en argument un tableau de distance entre les villes de 5x5
void commerce_statique(int villes[5][5]){

    //On r�cup�re le num�ro de la ville de d�part
    int villeDepart;
    printf("Saisir le numero de la ville de depart : ");
    scanf("%d",&villeDepart);
    villeDepart--;

    //On initialise le tableau des �tapes
    int etapes[5] = {-1,-1,-1,-1,-1};
    etapes[0] = villeDepart;

    printf("Depart de V%d",etapes[0]+1);
    int distance = 0;
    int k;

    for (k = 1; k < 5; k++){

        int i = 0;

        //On r�cup�re la ville pr�c�dente
        int VillePrec = etapes[k-1];
        int VilleProche = 0;

        //On initialise le min � une valeur diff�rente de 0 et dont la ville n'a pas d�j� �t� visit�e
        int min = villes[VillePrec][i];
        while (min == 0 || isVisited(i,etapes) == 1){
            i++;
            min = villes[VillePrec][i];
            VilleProche = i;
        }

        //On initialise la future distance � rejouter
        int distTemp = min;

        int j;

        for (j = 0; j < 5; j++){
            //Si la distance entre le ville pr�c�dente et la ville j est plus petite que min, qu'elle est diff�rente de 0 et que la ville n'a pas encore �t� visit�e...
            if ((villes[VillePrec][j] < min) && (villes[VillePrec][j] != 0) && isVisited(j,etapes) == 0){
                //... elle devient candidate � �tre la prochaine �tape
                min = villes[VillePrec][j];
                distTemp = min;
                VilleProche = j;
            }
        }

        //La nouvelle �tape a �t� trouv�e, on ajoute la distance � la distance totale et on ajoute une �tape dans le tableau des �tapes
        distance += distTemp;
        etapes[k] = VilleProche;

        //On affiche la nouvelle �tape � l'utilisateur
        printf("\nEtape %d : V%d",k,etapes[k]+1);
    }

    //On affiche la distance totale parcourue
    printf("\nDistance totale : %d\n",distance);

}

//Fonction de saisie du tableau des distances en statique
int saisieDistance(){

    int i,j;

    //On initialise le tableau des distances (dans le cas o� l'on peut r�ex�cuter le programme sans le fermer
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            tabVilles[i][j] = 0;
        }
    }

    //On parcourt le tableau
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            //On v�rifie qu'on ne demande pas de saisir la distance Vi-Vi qui reste � 0 et que la distance Vi-Vj n'a pas �t� saisie
            if ((i != j) && (tabVilles[i][j] == 0)){

                //L'utilisateur saisit la distance
                printf("\nSaisir la distance V%d - V%d : ",i+1,j+1);
                scanf("%d",&tabVilles[i][j]);

                //On enregistre la distance Vj-Vi qui est la m�me que Vi-Vj
                tabVilles[j][i] = tabVilles[i][j];
            }
        }
    }
     printf("\nSaisie terminee ! \n");
}

//Fonctions Dynamiques

//Fonction de saisie du tableau des distances en dynamique
int saisieDyn(){
    int nbVilles;
    printf("Nombre de villes a traiter : ");
    scanf("%d",&nbVilles);

    tab = (int *) malloc(sizeof(int)*nbVilles*nbVilles);
    int i;
    int j;
    for (i = 0; i < nbVilles; i++){
        for (j = 0; j < nbVilles; j++){
           *(tab + (i*nbVilles) + j) = 0;
        }
    }
    for (i = 0; i < nbVilles; i++){
        for (j = 0; j < nbVilles; j++){
           if ((i != j) && (*(tab + (i*nbVilles) + j) == 0)){
                printf("\nSaisir la distance V%d - V%d : ",i+1,j+1);
                scanf("%d",tab + (i*nbVilles) + j);
                *(tab + (j*nbVilles) + i) = *(tab + (i*nbVilles) + j);
           }
        }
    }

    /*
    for (i = 0; i < nbVilles*nbVilles; i++){
            printf("%d, ",*(tab+i));
    }
    */
    return nbVilles;
}

//Fonction prenant en param�tre le num�ro de la ville � v�rifier, le nombre total de villes ainsi que le tableau de �tapes d�j� effectu�es. Renvoie 1 si la ville � d�j� �t� visit�e, 0 sinon.
int isVisitedDyn(int ville, int nbVilles, int *etapes){
    int i;
    int res = 0;
    for (i = 0; i < nbVilles; i++){
        if (*(etapes+i)==ville) {
            res = 1;
        }
    }
    return res;
}

//Fonction principale de l'exercice en dynamique, prenant en argument le nombre de villes n

int commerce_dyn(int n){
    //On r�cup�re le num�ro de la ville de d�part
    int villeDepart;
    printf("Saisir le numero de la ville de depart : ");
    scanf("%d",&villeDepart);
    villeDepart--;

    //On initialise le tableau des �tapes
    int *etapes = (int *) malloc(sizeof(int)*n);
    *(etapes) = villeDepart;

    printf("Depart de V%d",*(etapes)+1);
    int distance = 0;
    int k;

    for (k = 1; k < n; k++){

        int i = 0;

        //On r�cup�re la ville pr�c�dente
        int VillePrec = *(etapes+k-1);
        int VilleProche = 0;

        //On initialise le min � une valeur diff�rente de 0 et dont la ville n'a pas d�j� �t� visit�e
        int min = *(tab+VillePrec*n+i);
        while (min == 0 || isVisitedDyn(i,n,etapes) == 1){
            i++;
            min = *(tab+VillePrec*n+i);
            VilleProche = i;
        }

        //On initialise la future distance � rejouter
        int distTemp = min;

        int j;

        for (j = 0; j < n; j++){
            //Si la distance entre le ville pr�c�dente et la ville j est plus petite que min, qu'elle est diff�rente de 0 et que la ville n'a pas encore �t� visit�e...
            if ((*(tab+VillePrec*n+j) < min) && (*(tab+VillePrec*n+j) != 0) && isVisitedDyn(j,n,etapes) == 0){
                //... elle devient candidate � �tre la prochaine �tape
                min = *(tab+VillePrec*n+j);
                distTemp = min;
                VilleProche = j;
            }
        }

        //La nouvelle �tape a �t� trouv�e, on ajoute la distance � la distance totale et on ajoute une �tape dans le tableau des �tapes
        distance += distTemp;
        etapes[k] = VilleProche;

        //On affiche la nouvelle �tape � l'utilisateur
        printf("\nEtape %d : V%d",k,*(etapes+k)+1);
    }

    //On affiche la distance totale parcourue
    printf("\nDistance totale : %d\n",distance);
}

//Programme principal

int main()
{
    int choix;
    printf("--- Voyageur de commerce ---\n");
    printf("1 : Statique\n");
    printf("2 : Dynamique\n");
    scanf("%d",&choix);
    switch (choix){
    case 1:
        saisieDistance();
        commerce_statique(tabVilles);
        break;
    case 2:
        commerce_dyn(saisieDyn());
        break;
    }
    return 0;
}
