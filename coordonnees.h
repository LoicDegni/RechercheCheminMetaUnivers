/*  Position d'une cellule dans le metavers
    TP3 - Coordonnees.h
    Kaikou Loic Degni
*/

#if !defined(_COORDONNEEs__H_)
#define _COORDONNEEs__H_
#include <iostream>
using namespace std;

class Coordonnees {
  private:
  unsigned int id;  //Identifiant
  unsigned int x;   //position x
  unsigned int y;   //position y
  unsigned int c;   //couleur
  unsigned int u;   //Univers

  friend bool operator==(const Coordonnees&, const Coordonnees&);
  friend bool operator <(const Coordonnees&, const Coordonnees&);
  friend ostream& operator <<(ostream&,const Coordonnees&);

  public:
    Coordonnees(){}
    Coordonnees(const Coordonnees& autre): id(autre.id), x(autre.x), y(autre.y), c(autre.c), u(autre.u) {
        //cout << "Constructeur par copie appelé" << endl;
    }
    Coordonnees(int _id, int _x, int _y, int _c, int _u=0): id(_id), x(_x), y(_y), c(_c), u(_u){};
    ~Coordonnees(){};

    Coordonnees& operator =(const Coordonnees&);
    friend class Univers;
};

#endif


