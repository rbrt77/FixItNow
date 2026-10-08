#include "tehnician.h"


Tehnician::Tehnician(string n, string p, string c, Data da, string oras) : Angajat(n, p, c, da, oras)
{
    valoareTotalaReparatii = 0.0;
    durataTotalaMunca = 0; 
    //la inc nu are nmc
    esteOcupat = false;
    timpRamasExecutie = 0;
    idCerereCurenta = -1; // INSEAMNA CA NU ARE CERERE!!!!!!!!!!!!!!!!!!
}


Tehnician::~Tehnician() {
/*se ocupa angajat, vector competente se duce singur*/}


double Tehnician::calculeazaSalariu() const {

    double salariuDeBaza = getSalariuComun(); //ca la rest
    double bonusReparatii = valoareTotalaReparatii * 0.02; //reparat
    return salariuDeBaza + bonusReparatii;
}

void Tehnician::adaugaCompetenta(string tip, string marca) {
    Competenta c;
    c.tipApp = tip;
    c.marcaApp = marca;
    listaCompetente.push_back(c); //bag componenta toata
}


bool Tehnician::verificaCompetenta(string tip, string marca) const {
    for (int i = 0; i < listaCompetente.size(); i++) 
        if (listaCompetente[i].tipApp == tip && listaCompetente[i].marcaApp == marca) 
            return true; 
    return false;
}


void Tehnician::adaugaReparatieLaSalariu(double valoareReparatie) {
    valoareTotalaReparatii += valoareReparatie;
}


long Tehnician::getDurataMunca() const {
    return durataTotalaMunca;
}


bool Tehnician::eDisponibil() const {
    return !esteOcupat; // != cu !=
}

void Tehnician::asigneazaCerere(int idCerere, int durataEstimata) {
    this->idCerereCurenta = idCerere;
    this->timpRamasExecutie = durataEstimata;
    this->esteOcupat = true;
    this->durataTotalaMunca += durataEstimata;
}


void Tehnician::executaTic() {
    if (esteOcupat) {
        timpRamasExecutie--; // trece 1

        if (timpRamasExecutie <= 0) 
            esteOcupat = false;
    }
}

int Tehnician::getIdCerereCurenta() const {
    return idCerereCurenta;
}


void Tehnician::afisare(ostream& os) const {
    os << "----------------------------------------" << endl;
    os << "ID: " << idAngajat << " | Functie: TEHNICIAN" << endl;
    os << "Nume: " << getNumeComplet() << endl;
    os << "CNP: " << cnp << endl;
    os << "Data Angajare: " << dataAngajare.zi << "/" << dataAngajare.luna << "/" << dataAngajare.an << endl;
    os << "Domiciliu: " << orasDomiciliu << endl;
    

    os << "Competente: ";
    if (listaCompetente.empty()) {
        os << "(Fara specializare)";
    } 
    else {
        for (int i = 0; i < listaCompetente.size(); i++) {
            os << "[" << listaCompetente[i].tipApp << " " << listaCompetente[i].marcaApp << "] ";
        }
    }
    os << endl;

    os << "Valoare reparatii efectuate: " << valoareTotalaReparatii << " RON" << endl;
    os << "Salariu curent (cu bonus 2%): " << calculeazaSalariu() << " RON" << endl;

 
    os << "Status: ";
    if (esteOcupat) 
        os << "OCUPAT";
    else 
        os << "LIBER";
    
        
    if (esteOcupat) {
        os << " (Cerere " << idCerereCurenta << ", Timp ramas: " << timpRamasExecutie << "s)";
    }
    os << endl;
    os << "----------------------------------------" << endl;
}