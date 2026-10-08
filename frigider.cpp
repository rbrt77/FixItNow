#include "frigider.h"


Frigider::Frigider(string m, string mod, int an, double pret, bool cong) : Electrocasnic(TipElectrocasnic::Frigider, m, mod, an, pret), areCongelator(cong) 
{
}


void Frigider::afisare(ostream& os) const {
    os << "[Frigider] " << marca << " " << model << " | An: " << anFabricatie << " | Pret: " << pretCatalog << " | Congelator: " << (areCongelator ? "Da" : "Nu");
       // NU are endl
}


string Frigider::getDetaliiSpecifice() const {
    return (areCongelator ? "Cu Congelator" : "Fara Congelator");
}