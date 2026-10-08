#pragma once
#include "angajat.h"

class Supervizor : public Angajat {
private:
    const double PROCENT_SPOR_CONDUCERE = 0.20; 

public:
    Supervizor(string n, string p, string c, Data da, string oras);
    ~Supervizor();

    double calculeazaSalariu() const override;
    void afisare(ostream& os) const override;
};