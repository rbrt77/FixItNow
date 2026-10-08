#include "receptioner.h"


Receptioner::Receptioner(string n, string p, string c, Data da, string oras) : Angajat(n, p, c, da, oras)
{
    //vector de iduri e gol
}


Receptioner::~Receptioner() {
/*se ocupa angajat*/ }


double Receptioner::calculeazaSalariu() const {
    return getSalariuComun();   //normal fara nmc
}


void Receptioner::adaugaCerere(int idCerere) {
    cereriInregistrate.push_back(idCerere); //la final cerere curenta
}


void Receptioner::afisare(ostream& os) const {
    os << "----------------------------------------" << endl;
    os << "ID: " << idAngajat << " | Functie: RECEPTIONER" << endl;
    os << "Nume: " << getNumeComplet() << endl;
    os << "CNP: " << cnp << endl;
    os << "Data Angajare: " << dataAngajare.zi << "/" << dataAngajare.luna << "/" << dataAngajare.an << endl;
    os << "Domiciliu: " << orasDomiciliu << endl;
    
    // lista d cereri
    os << "Cereri inregistrate (ID-uri): [ ";
    if (cereriInregistrate.empty()) {  //e == bool
        os << "- ";
    } else {
        for (int id : cereriInregistrate) {
            os << id << " "; //aifsam spatiu gol sa vad ca a intrat in el
        }
    }
    os << "]" << endl;

    os << "Salariu curent: " << calculeazaSalariu() << " RON" << endl;
    os << "----------------------------------------" << endl;
}