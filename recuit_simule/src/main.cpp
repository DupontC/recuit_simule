#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "graph_complet.h"

using namespace std;
int main(int argc, char** argv) {
    std::string int_file;
    std::string param_file;
    std::string out_file;
    int nb_sommet;
    int Tmax;
    int Tmin;
    int iteration;
    int i;
    double tx;
    int cout;
    std:string bestChemin;

    if(argc<5){
        int_file = argv[1];
        param_file = argv[2];
        out_file = argv[3];
        
        int **matrice = chargement(int_file, nb_sommet);
        int **matriceBis = copyMatrice(matrice,nb_sommet);

        chargementParams(param_file,Tmax,Tmin,tx,iteration);
        std::string chemin = cheminEtCout(matriceBis, out_file, nb_sommet);
        bestChemin=chemin;
        std::cout <<"Chemin avec les voisins les plus proches --> "<< bestChemin <<endl;
        while(i<iteration && Tmax>Tmin){
            //cout << chemin<<endl;
            permutationSegment(chemin);
            acceptationRecuit(bestChemin,chemin,Tmax,Tmin , tx, matrice);
            i++;
        }
        cout=coutChemin(bestChemin,matrice);
        std::cout <<"chemin avec recuit simule " <<bestChemin<<endl;
        sav_res(out_file,Tmax,Tmin,tx,iteration,cout,bestChemin);
        
    }else{
        std::cout << "pas assez d'argument" <<endl;
    }
    return 1;
}