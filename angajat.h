#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "auxiliar.h" 
using namespace std;

class Angajat {
protected:
    const int idAngajat;       
    string nume;
    string prenume;
    string cnp;                // de valid in constr
    Data dataAngajare;
    string orasDomiciliu;      

    static int numarTotalAngajati; // e dat la toti global
    static int generatorId; //sa mearga si daca stergem angajat(fara conflict id)

    // pt salarii
    const double SALARIU_BAZA_FIX = 4000.0;      
    const double BONUS_FIDELITATE_PROCENT = 0.05; 
    const int ANI_FIDELITATE = 3;                 // pt ca la 3 ani e binus
    const double PRIMA_TRANSPORT = 400.0;        

    // e de baza: 4000 + ce o mai fi
    double getSalariuComun() const;


public:
    // aici sunt validarile
    Angajat(string nume, string prenume, string cnp, Data dataAngajare, string oras);

    virtual ~Angajat();
    virtual double calculeazaSalariu() const = 0; 
    virtual void afisare(ostream& os) const = 0;

    static int getNumarAngajati(); // statica ca sa fie si pt 0 angajati

    int getId() const;
    string getNumeComplet() const;
    string getCnp() const;
    string getOras() const;
    Data getDataAngajare() const;
};