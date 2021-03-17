#pragma once

struct Donator
{
    char nume[105];
    char prenume[105];
    char cnp[20];
    char gen;
    char grupaSanguina[5];
    int varsta;
};

struct Pacient
{
    char nume[105];
    char prenume[105];
    char cnp[20];
    char gen;
    char grupaSanguina[5];
    int varsta;
};

struct Legatura
{
    char cnpDonator[50];
    char cnpPacient[50];
};

struct Istoric
{
    Legatura legaturi[100];
    int contor = 0;
};

struct Spital
{
    char parola[105] = "BancaDeSange_2021";
    Donator donatori[105];
    Pacient pacienti[105];
    int posibilitati[105][105];
    Istoric istoric;
    int numarDonatori = 0;
    int numarPacienti = 0;
};
