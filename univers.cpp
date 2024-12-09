
#include "univers.h"


void Univers::ajouterCellule(int couleur, const Coordonnees& c) {
    cellules[couleur].ajouterSommet(c);
}

void Univers::plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination) {
    cerr << "TODO : calculer le plus court chemin depuis (" << x_depart << ", " << y_depart << ") avec la couleur " << couleur_depart << " vers (" << x_destination << ", " << y_destination << ")" << std::endl;
		// TODO...
}


istream& operator >> (istream& is, Univers& univers) {
	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);

	for(unsigned int y = 0; y<univers.N; y++) {
		for(unsigned int x = 0; x<univers.N; x++) {
			unsigned int couleur;
            Coordonnees cellule(x,y);
			is >> couleur;
            univers.ajouterCellule(couleur,cellule);
			//cerr << "TODO : considérer la cellule (" << x << ", " << y << ") est de couleur " << couleur << endl;
			// TODO : enregistrer dans une structure de donnée.
		}
	}
	return is;
}

ostream& operator <<(ostream& os, Univers& univers) {
    for(const auto& [couleur,cellulec]: univers.cellules){
        cout << "couleur: " << couleur << " ";
        cellulec.afficherCellules();
    }
}
