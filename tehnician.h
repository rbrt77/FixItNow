#pragma once
#include "angajat.h"
#include <vector>


struct Competenta {
    string tipApp;   // (tip d reparat)
    string marcaApp; // (marca tipului)
};

class Tehnician : public Angajat {
private:
   
    vector<Competenta> listaCompetente; //lista poate repara

    double valoareTotalaReparatii; //pt bonus reparat

    bool esteOcupat;       
    int timpRamasExecutie;  
    int idCerereCurenta;  
    long durataTotalaMunca;

public:
 
    Tehnician(string n, string p, string c, Data da, string oras);
    ~Tehnician();

    double calculeazaSalariu() const override;
    void afisare(ostream& os) const override;
    
    void adaugaCompetenta(string tip, string marca);
    bool verificaCompetenta(string tip, string marca) const; //daca stie sa repare

    void adaugaReparatieLaSalariu(double valoareReparatie); //modic direct valoareTotalaReparatii

    bool eDisponibil() const;         
    void asigneazaCerere(int idCerere, int durataEstimata);
    void executaTic();                 // +1 sec(vede singur daca poate)
    int getIdCerereCurenta() const;  
    long getDurataMunca() const;
};