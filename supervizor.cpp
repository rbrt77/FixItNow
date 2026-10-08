#include "supervizor.h"


Supervizor::Supervizor(string n, string p, string c, Data da, string oras) : Angajat(n, p, c, da, oras) 
{
}


Supervizor::~Supervizor() {
/*se ocupa angajat*/ }


double Supervizor::calculeazaSalariu() const {
    double salariuTotal = getSalariuComun();
    double sporConducere = SALARIU_BAZA_FIX * PROCENT_SPOR_CONDUCERE;

    return salariuTotal + sporConducere;
}


void Supervizor::afisare(ostream& os) const {
    os << "----------------------------------------" << endl;
    os << "ID: " << idAngajat << " | Functie: SUPERVIZOR" << endl;
    os << "Nume: " << getNumeComplet() << endl;
    os << "CNP: " << cnp << endl;
    os << "Data Angajare: " << dataAngajare.zi << "/" << dataAngajare.luna << "/" << dataAngajare.an << endl;
    os << "Domiciliu: " << orasDomiciliu << endl;
    os << "Salariu curent: " << calculeazaSalariu() << " RON" << endl;
    os << "----------------------------------------" << endl;
}