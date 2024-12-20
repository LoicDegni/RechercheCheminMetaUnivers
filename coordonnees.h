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
  int id;  //Identifiant
  int x;   //position x
  int y;   //position y
  int c;   //couleur

  friend bool operator==(const Coordonnees&, const Coordonnees&);
  friend bool operator <(const Coordonnees&, const Coordonnees&);
  friend ostream& operator <<(ostream&,const Coordonnees&);

  public:
    Coordonnees(){}
    Coordonnees(int _id, int _x, int _y, int _c): id(_id), x(_x), y(_y), c(_c){};
    ~Coordonnees(){};

    friend class Univers;
};


#endif


