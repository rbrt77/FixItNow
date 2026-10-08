#include "masinaspalat.h"
#include <string> //tostring

MasinaSpalat::MasinaSpalat(string m, string mod, int an, double pret, double cap) : Electrocasnic(TipElectrocasnic::MasinaSpalat, m, mod, an, pret), capacitate(cap)
{
}


void MasinaSpalat::afisare(ostream& os) const {
    os << "[Masina Spalat] " << marca << " " << model << " | An: " << anFabricatie << " | Pret: " << pretCatalog << " | Capacitate: " << capacitate << " kg";
       // NU are endl!!
}


string MasinaSpalat::getDetaliiSpecifice() const {
    return ("Capacitate: " + to_string(capacitate) + " kg"); //scrie in caractere numar dat(zerouri dupa virgula)
}