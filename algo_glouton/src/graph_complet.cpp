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
    int num_ville=0;
    int indice_j;
    int sumCout=0;
    int cout=0;
    int coutTmp=-1;
    int nb_ville_res=nb_sommet;
    int i=0;
    
    std::cout << "calcul du chemin"<<endl;
    //on boucle afin de marquer toutes les villes
    while (nb_ville_res>0) {
        std::stringstream ss;
        std::string ville;
        ss << i;
        ss >> ville;
        
        //on ecrie dans le fichier txt la ville etape
        displayChemin(out_file,"ville_"+ville);//  /!\a modifier avec le nom de la ville en string/!\
        
        for(int j=0;j<nb_sommet;j++){
            //on regarde les villes accesible
            if(i!=j && i!=-1 && j!= -1){
                //si le cout est minimale
                if(coutTmp==-1 || (coutTmp > matrice[i][j] && matrice[i][j]!=-1)){
                    coutTmp=matrice[i][j];
                    indice_j=j;
                }
            }
        }
        
        //on marque la ville comme deja passé
        for(int j=0;j<nb_sommet;j++){
            matrice[i][j]=-1;
        }
        for(int k=0;k<nb_sommet;k++){
            matrice[k][i]=-1;
        }
        //std::cout << "indice "<<indice_j <<" cout "<<coutTmp<<endl;
        i=indice_j;
        //maj du cout du chemin minimal
        cout=cout+coutTmp;
        coutTmp=-1;
        
        //on decremente le nombre de ville restantes a parcourir
        nb_ville_res--;
    }
    //on ecrie le cout minimal du trajet
    displayCout(out_file,cout);
}

void displayChemin(std::string out_file, std::string ville){
    std::string monFichier="./resultats/"+out_file;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
    
    if(fichier)
    {
        fichier << ville << " - " ;
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void displayCout(std::string out_file, int cout){
    std::string monFichier="./resultats/"+out_file;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
           
    if(fichier)
    {
        fichier << endl <<" Cout du trajet "<<cout <<endl;
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

int ** chargement(std::string int_file,int &nb_sommet){
    //ouverture du fichier en lecture
    std::ifstream text;
    text.open(int_file.c_str());
    
    //declaration des variables
    int indice_i=0;
    int indice_j=0;
    int cout;
    int** matrice = NULL ;
    
    std::cout << "chargement du graph complet" <<endl;
    //si le fichier est ouvert ..
    if(text.is_open())
    {
        //tant qu'il y a des lignes
        while(text.good())
        {
            std::string line = "";
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                //on recupere les arguments de la ligne
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                //on parcour les différents elements
                if(x.size()>1){
                    indice_j=0;
                    for (it = x.begin() ; it < x.end(); it++)
                    {
                        // on caste les arguemnts :  string to int
                        std::stringstream ss;
                        ss << *it;
                        ss >> cout;
                        //on remplie la matrice
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
                    //on initialise la matrice
                    matrice = new int * [nb_sommet];
                    for (int i=0; i<nb_sommet; ++i) {
                        matrice [i] = new int [nb_sommet];
                    }
                }
            }
        }
        //on ferme le fichier
        text.close();
    }else{
        std::cout << "can't open the file" <<endl;
    }
    return matrice;
}
