#pragma once
#include "angajat.h"
#include <vector> 

class Receptioner : public Angajat {
private:
  
    vector <int>  cereriInregistrate; //iduri meorate

public:
   
    Receptioner(string n, string p, string c, Data da, string oras);
    ~Receptioner();

    double calculeazaSalariu() const override;
    void afisare(ostream& os) const override;

    void adaugaCerere(int idCerere); //fara stergere pt ca vr sa vedem istoric- direct in receptioner
};