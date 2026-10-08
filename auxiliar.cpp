#include "auxiliar.h"

// O FAC FUNCTOE GLOBALA!!!! DEFINIEREA E AICI!!!!

ostream& operator<<(ostream& os, const Data& d) {
    os << d.zi << "." << d.luna << "." << d.an;
    return os;
}


int Data::diferentaAni(int anCurent) const {
    return anCurent - an;
}


bool Data::operator<(const Data& other) const {
    if (an != other.an) 
        return (an < other.an);

    if (luna != other.luna) 
        return (luna < other.luna);
    
    return (zi < other.zi);
}