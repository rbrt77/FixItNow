#pragma once
#include "electrocasnic.h" 

class Frigider : public Electrocasnic {
private:
    bool areCongelator;

public:
 
    Frigider(string marca, string model, int an, double pret, bool congelator);

    void afisare(ostream& os) const override;
    string getDetaliiSpecifice() const override; //mu e nev dest
};