#include "graph_complet.h"
using namespace std;

void sav_graph(std::string out_file, int nb_sommet, int** matrice){
    std::string monFichier="./resultats/"+out_file;
    ofstream fichier(monFichier.c_str(), ios::out|ios::trunc);  // ouverture en écriture
    cout << "sav in " << out_file<< endl;
    if(fichier)
    {
        fichier << nb_sommet <<endl;
        for(int i=0; i<nb_sommet; ++i){
            for(int j=0; j<nb_sommet; ++j){
                fichier << matrice[i][j]<<" ";
            }
            fichier << endl;
        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

int ** gene_graph(int nb_sommet,int min, int max){
    int** matrice = NULL ;
    
    //on declare la matrice
    matrice = new int * [nb_sommet];
    for (int i=0; i<nb_sommet; ++i) {
        matrice [i] = new int [nb_sommet];
    }
    
    //on ajout les couts des distances entre le villes
    for(int i=0; i<nb_sommet; ++i){
        for(int j=0; j<nb_sommet; ++j){
            if(i!=j){
                matrice[i][j]=rand()%((max+1)-min) +min;
            }else{
                matrice[i][j]=0;
            }
        }
    }
    return matrice;
}