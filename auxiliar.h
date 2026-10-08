#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum class TipElectrocasnic {
    Frigider,
    Televizor,
    MasinaSpalat,
    Necunoscut
};

enum class StatusCerere {
    InAsteptare,
    Asignata,
    Finalizata,
    Imposibila
};


struct Data {
    int zi, luna, an;

    friend ostream& operator<<(ostream& os, const Data& d);
    int diferentaAni(int anCurent) const;
    bool operator<(const Data& other) const;
};