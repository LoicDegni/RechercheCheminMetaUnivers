
#include "univers.h"


void Univers::ajouterCellule(int couleur, const Coordonnees& c) {
    cellules[couleur].ajouterSommet(c);
}

void Univers::plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination) {
}

bool Univers::estAccessible(int couleurUnivers, const Coordonnees& c)
{
    return couleurUnivers != c.c;
}


istream& operator >> (istream& is, Univers& univers) {
	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);

    unsigned int couleur, id;
    unordered_map<int, Coordonnees> entree;
	for(unsigned int y = 0; y<univers.N; y++) {
		for(unsigned int x = 0; x<univers.N; x++) {
			is >> couleur;
            id = (x + y*univers.N);
            Coordonnees cellule(x,y, couleur, id);
            entree[id] = cellule;
            univers.ajouterCellule(couleur,cellule);
		}
	}
    unsigned int nbElements = univers.N * univers.N;

    for(unsigned int a = 0; a < univers.C; a++){
        for(unsigned int i = 0; i < nbElements; i++){
            //Verifie si on est pas sur derniere ligne
            if(nbElements - i > univers.N){
                //cout << entree.at(i) << endl;
                if(univers.estAccessible(a, entree.at(i + univers.N) ) ){
                    univers[a].ajouterAreteOrientee(entree.at(i), entree.at(i+ univers.N));
                }
            }
            //Verifie si on est pas sur premiere ligne
            if(i > univers.N){
                if(univers.estAccessible(a, entree.at(i - univers.N) )){
                    univers[a].ajouterAreteOrientee(entree.at(i), entree.at(i - univers.N));
                }
            }
            //Verifie on est pas a la premiere case d'une ligne
            if(i % univers.N > 0){
                if(univers.estAccessible(a, entree.at(i-1))){
                    univers[a].ajouterAreteOrientee(entree.at(i), entree.at(i -1));
                }
            }
            //verifie si on est pas a la derniere case d'une ligne
            if((i + 1)% univers.N > 0){
                if(univers.estAccessible(a, entree.at(i + 1))){
                    univers[a].ajouterAreteOrientee(entree.at(i), entree.at(i+1));
                }
            }
        }
    }
	return is;
}


ostream& operator <<(ostream& os, Univers& univers) { 
    for(const auto& [couleur,cellulec]: univers.cellules){
        cout << "couleur: " << couleur << " ";
        cellulec.afficherCellules();
    }
    return os;
}

