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
  int id;
  int x;
  int y;
  int c;
  friend bool operator==(const Coordonnees&, const Coordonnees&);
  friend bool operator <(const Coordonnees&, const Coordonnees&);
  friend ostream& operator <<(ostream&,const Coordonnees&);

  public:
    Coordonnees(){}
    Coordonnees(int _x, int _y, int _c, int _id): id(_id),  x(_x), y(_y), c(_c){};
    ~Coordonnees(){};
    
    friend class Univers;
};


#endif


