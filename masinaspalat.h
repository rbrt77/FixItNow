#pragma once
#include "electrocasnic.h"

class MasinaSpalat : public Electrocasnic {
private:
    double capacitate; //kg doar

public:

    MasinaSpalat(string marca, string model, int an, double pret, double cap);

    void afisare(ostream& os) const override;
    string getDetaliiSpecifice() const override; //mu e nev dest
};