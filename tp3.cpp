#include "univers.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc != 7) {
		std::cerr << "Utilisation : " << argv[0] << " x_depart y_depart couleur_depart x_destination y_destination" << std::endl;
		return -1;
	}

	std::ifstream entree = std::ifstream(argv[1]);

	Univers univers;
	entree >> univers;

    cout << univers;


	unsigned int x_depart = atoi(argv[2]);
	unsigned int y_depart = atoi(argv[3]);
	unsigned int couleur_depart = atoi(argv[4]);
	unsigned int x_destination = atoi(argv[5]);
	unsigned int y_destination = atoi(argv[6]);

	//univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
