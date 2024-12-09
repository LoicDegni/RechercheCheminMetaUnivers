/*  Position d'une cellule dans le metavers
    TP3 - Coordonnees.h
    Kaikou Loic Degni
*/

#if !defined(_COORDONNEEs__H_)
#define _COORDONNEEs__H_
#include <iostream>
using namespace std;

class Coordonnees {
  int x;
  int y;

  public:
    Coordonnees(int _x, int _y): x(_x), y(_y){};
    ~Coordonnees(){};

  friend bool operator==(const Coordonnees&, const Coordonnees&);
  friend bool operator <(const Coordonnees&, const Coordonnees&);
};


#endif


