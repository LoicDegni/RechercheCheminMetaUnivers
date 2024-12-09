#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include "graphe.h"
#include "coordonnees.h"
using namespace std;


class Univers
{
	unsigned int N; 	// Nombre de ligne et nombre de colonnes
	unsigned int C; 	// Nombre de couleur

    map< int, Graphe<Coordonnees> > cellules;
	// TODO : Complétez avec les attributs nécessaires pour représenter l'univers

public:
	Univers()  {}
	~Univers() {}

    void ajouterCellule(const int, const Coordonnees&);
	void plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination);
	friend istream& operator >> (istream& is, Univers& univers);
    friend ostream& operator << (ostream& os, Univers& univers);
};

