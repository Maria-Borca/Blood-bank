#include <bits/stdc++.h>
#include "structs.h"
#include "functii.h"

using namespace std;

fstream fileDonatori("donatori.txt",std::fstream::in | std::fstream::out | std::fstream::app);
fstream filePacienti ("pacienti.txt", std::fstream::in | std::fstream::out | std::fstream::app);

void citireDonator(Donator &donator)
{
    fileDonatori >> donator.nume >> donator.prenume >> donator.cnp >> donator.grupaSanguina;
    if (verificareCNP(donator.cnp))
    {
        donator.varsta = aflareVarsta(donator.cnp);
        donator.gen = aflareGen(donator.cnp);
    }
}

void citirePacient(Pacient &pacient)
{
    filePacienti >> pacient.nume >> pacient.prenume >> pacient.cnp >> pacient.grupaSanguina;
    if (verificareCNP(pacient.cnp))
    {
        pacient.varsta = aflareVarsta(pacient.cnp);
        pacient.gen = aflareGen(pacient.cnp);
    }
}

void citireSpital(Spital &spital)
{
    while (!fileDonatori.eof())
    {
        spital.numarDonatori ++;
        citireDonator (spital.donatori[spital.numarDonatori]);
    }
    fileDonatori.close();
    while (!filePacienti.eof())
    {
        spital.numarPacienti ++;
        citirePacient(spital.pacienti[spital.numarPacienti]);
    }
    filePacienti.close();
    spital.numarDonatori --;
    spital.numarPacienti --;
    calcularePosibilitati(spital);
}

void afisareDonatoriInDonatoriTxt(Donator donatori[], int numarDonatori)
{
    fstream fileDonatori("donatori.txt",std::fstream::in | std::fstream::out | std::fstream::app);
    fileDonatori.close();
    fileDonatori.open("donatori.txt");
    for (int i = 1; i <= numarDonatori; i ++)
    {
        fileDonatori << donatori[i].nume << ' ';
        fileDonatori << donatori[i].prenume << ' ';
        fileDonatori << donatori[i].cnp << ' ' << donatori[i].grupaSanguina << '\n';
    }
    fileDonatori.close();
}

void afisarePacientiInPacientiTxt(Pacient pacienti[], int numarPacienti)
{
    fstream filePacienti ("pacienti.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    filePacienti.close();
    filePacienti.open("pacienti.txt");
    for (int i = 1; i <= numarPacienti; i ++)
    {
        filePacienti << pacienti[i].nume << ' ';
        filePacienti << pacienti[i].prenume << ' ';
        filePacienti << pacienti[i].cnp << ' ' << pacienti[i].grupaSanguina << '\n';
    }
    filePacienti.close();
}
