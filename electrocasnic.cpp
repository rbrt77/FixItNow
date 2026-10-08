#include "electrocasnic.h"


Electrocasnic::Electrocasnic(TipElectrocasnic t, string m, string mod, int an, double pret) : tip(t), marca(m), model(mod), anFabricatie(an), pretCatalog(pret) 
{}


TipElectrocasnic Electrocasnic::getTip() const { 
    return tip; 
}

string Electrocasnic::getMarca() const { 
    return marca; 
}

string Electrocasnic::getModel() const { 
    return model; 
}

int Electrocasnic::getAn() const { 
    return anFabricatie; 
}

double Electrocasnic::getPret() const { 
    return pretCatalog; 
}