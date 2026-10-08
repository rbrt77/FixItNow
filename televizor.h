#pragma once
#include "electrocasnic.h"

class Televizor : public Electrocasnic {
private:
    double diagonala; //cm doar

public:

    Televizor(string marca, string model, int an, double pret, double diag);

    void afisare(ostream& os) const override;
    string getDetaliiSpecifice() const override; //mu e nev dest
};