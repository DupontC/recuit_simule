#include "graph_complet.h"
using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

/*
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
*/

void cheminEtCout(int** matrice, std::string out_file, int &nb_sommet){
    
}

int ** chargement(std::string int_file,int &nb_sommet){
    std::ifstream text;
    text.open(int_file.c_str());
    int indice_i=0;
    int indice_j=0;
    int cout;
    int** matrice = NULL ;
    
    if(text.is_open())
    {
        while(text.good())
        {
            std::string line = "";
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                //on recupere les arguments de la ligne
                //cout << line << endl;
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                //on parcour les différents elements
                if(line.length()>1){
                    indice_j=0;
                    for (it = x.begin() ; it < x.end(); it++)
                    {
                        std::stringstream ss;
                        ss << *it;
                        ss >> cout;
                        matrice[indice_i][indice_j] = cout;
                        indice_j++;
                    }
                    indice_j=0;
                    indice_i++;
                }else{
                    std::stringstream ss;
                    it = x.begin() ;
                    ss << *it;
                    ss >> nb_sommet;
                    //on declare la matrice
                    matrice = new int * [nb_sommet];
                    for (int i=0; i<nb_sommet; ++i) {
                        matrice [i] = new int [nb_sommet];
                    }
                }
            }
        }
        text.close();
    }else{
        //cout << "can't open the file" <<endl;
    }
    return matrice;
}
