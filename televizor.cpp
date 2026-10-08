#include "televizor.h"
#include <string>   //tostring

Televizor::Televizor(string m, string mod, int an, double pret, double diag) : Electrocasnic(TipElectrocasnic::Televizor, m, mod, an, pret), diagonala(diag)
{
}


void Televizor::afisare(ostream& os) const {
    os << "[TV] " << marca << " " << model << " | An: " << anFabricatie << " | Pret: " << pretCatalog << " | Diagonala: " << diagonala << " cm";
       // NU are endl!!
}


string Televizor::getDetaliiSpecifice() const {
    return ("Diagonala: " + to_string(diagonala) + " cm"); //scrie in caractere numar dat(zerouri dupa virgula)
}