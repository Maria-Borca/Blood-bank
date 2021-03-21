#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "structs.h"

using namespace std;

bool verificareGrupaSanguina (char grupaSanguina[])
{
    if (strcmp(grupaSanguina, "0") == 0)
        return 1;
    if (strcmp(grupaSanguina, "A") == 0)
        return 1;
    if (strcmp(grupaSanguina, "B") == 0)
        return 1;
    if (strcmp(grupaSanguina, "AB") == 0)
        return 1;
    return 0;
}

bool verificareCNP (char cnp[])
{
    char constanta[13] = "279146358279";
    int sum = 0, cc;
    if (strlen(cnp) != 13)
        return 0;
    for (int i = 0; i < strlen(cnp); i ++)
        if (!isdigit(cnp[i]))
            return 0;
    int gen = cnp[0] - 48;
    int luna = (cnp[3] - 48) * 10 + (cnp[4] - 48);
    int ziua = (cnp[5] - 48) * 10 + (cnp[6] - 48);
    int jud = (cnp[7] - 48) * 10 + (cnp[8] - 48);
    if (gen < 1 || gen > 8)
        return 0;
    if (luna < 1 || luna > 12)
        return 0;
    if (ziua < 1 || ziua > 31)
        return 0;
    if (jud < 1 || jud > 48)
        return 0;
    for (int i = 0; i <= 11; i ++)
        sum += (constanta[i] - 48) * (cnp[i] - 48);
    cc = sum % 11;
    if (cc == 10)
        cc = 1;
    if (cc != cnp[12] - 48)
        return 0;
    return 1;
}

int aflareVarsta(char cnp[])
{
    int gen = cnp[0] - 48;
    int an = (cnp[1] - 48) * 10 + (cnp[2] - 48);
    if (gen == 1 || gen == 2)
        return 2021 - (1900 + an);
    if (gen == 3 || gen == 4)
        return 2021 - (1800 + an);
    if (gen == 5 || gen == 6)
        return 2021 - (2000 + an);
}

char aflareGen(char cnp[])
{
    int gen = cnp[0] - 48;
    if (gen % 2 == 0)
        return 'F';
    return 'M';
}

bool compatibil(char grupaSanguinaPacient[], char grupaSanguinaDonator[])
{
    if (strcmp(grupaSanguinaPacient, "0") == 0)
        if (strcmp(grupaSanguinaDonator, "0") == 0)
            return 1;
    if (strcmp(grupaSanguinaPacient, "A") == 0)
    {
        if (strcmp(grupaSanguinaDonator, "A") == 0 || strcmp(grupaSanguinaDonator, "0") == 0)
            return 1;
    }
    if (strcmp(grupaSanguinaPacient, "B") == 0)
    {
        if (strcmp(grupaSanguinaDonator, "B") == 0 || strcmp(grupaSanguinaDonator, "0") == 0)
            return 1;
    }
    if (strcmp(grupaSanguinaPacient, "AB") == 0)
        return 1;
    return 0;
}

int sumaPeColoane(int mat[][105], int c, int numarLinii)
{
    int suma = 0;
    for (int i = 1; i <= numarLinii; i ++)
        suma += mat[i][c];
    return suma;
}

void calcularePosibilitati(Spital &spital)
{
    for (int i = 1; i <= spital.numarPacienti; i ++)
    {
        for (int j = 1; j <= spital.numarDonatori; j ++)
            spital.posibilitati[i][j] = compatibil(spital.pacienti[i].grupaSanguina, spital.donatori[j].grupaSanguina);
    }
    for (int j = 1; j <= spital.numarDonatori; j ++)
        spital.posibilitati[spital.numarPacienti + 1][j] = sumaPeColoane(spital.posibilitati, j, spital.numarPacienti);
}

int pacientulSeAflaInIstoric(char cnp[], Istoric istoric)
{
    for (int i = 1; i <= istoric.contor; i ++)
        if (strcmp(cnp, istoric.legaturi[i].cnpPacient) == 0)
            return i;
    return 0;
}

int donatorulSeAflaInIstoric(char cnp[], Istoric istoric)
{
    for (int i = 1; i <= istoric.contor; i ++)
        if (strcmp(cnp, istoric.legaturi[i].cnpDonator) == 0)
            return i;
    return 0;
}

int cautaDonator(int pozPacient, Spital &spital)
{
    int minn = INT_MAX, coloana = -1, i = pozPacient;
    for (int j = 1; j <= spital.numarDonatori; j ++)
        if (spital.posibilitati[i][j] == 1
                && spital.posibilitati[spital.numarPacienti + 1][j] < minn
                && donatorulSeAflaInIstoric(spital.donatori[j].cnp, spital.istoric) == 0)
        {
            minn = spital.posibilitati[spital.numarPacienti + 1][j];
            coloana = j;
        }
    if (coloana != -1)
    {
        spital.istoric.contor ++;
        strcpy(spital.istoric.legaturi[spital.istoric.contor].cnpDonator, spital.donatori[coloana].cnp);
        strcpy(spital.istoric.legaturi[spital.istoric.contor].cnpPacient, spital.pacienti[i].cnp);
        for (int j = 1; j <= spital.numarDonatori; j ++)
            spital.posibilitati[i][j] = 0;
        for (int l = 1; l <= spital.numarPacienti + 1; l ++)
            spital.posibilitati[l][coloana] = 0;
    }
    return coloana;
}

bool cnpUnic(Donator donatori[], int numarDonatori, Pacient pacienti[], int numarPacienti, char cnp[])
{
    for (int i = 1; i <= numarDonatori; i ++)
        if (strcmp(donatori[i].cnp, cnp) == 0)
            return 0;
    for (int i = 1; i <= numarPacienti; i ++)
        if (strcmp(pacienti[i].cnp, cnp) == 0)
            return 0;
    return 1;
}

int cautareCNPDonator(Donator donatori[], int numarDonatori, char cnp[])
{
    for (int i = 1; i <= numarDonatori; i ++)
        if (strcmp(donatori[i].cnp, cnp) == 0)
            return i;
    return 0;
}

int cautareCNPPacient(Pacient pacienti[], int numarPacienti, char cnp[])
{
    for (int i = 1; i <= numarPacienti; i ++)
        if (strcmp(pacienti[i].cnp, cnp) == 0)
            return i;
    return 0;
}

void adaugareDonator(Donator donatori[], int &numarDonatori, char nume[], char prenume[], char grupaSanguina[], char cnp[], char gen, int varsta)
{
    numarDonatori ++;
    strcpy(donatori[numarDonatori].nume, nume);
    strcpy(donatori[numarDonatori].prenume, prenume);
    strcpy(donatori[numarDonatori].grupaSanguina, grupaSanguina);
    strcpy(donatori[numarDonatori].cnp, cnp);
    donatori[numarDonatori].gen = gen;
    donatori[numarDonatori].varsta = varsta;
}

void adaugarePacient(Pacient pacienti[], int &numarPacienti, char nume[], char prenume[], char grupaSanguina[], char cnp[], char gen, int varsta)
{
    numarPacienti ++;
    strcpy(pacienti[numarPacienti].nume, nume);
    strcpy(pacienti[numarPacienti].prenume, prenume);
    strcpy(pacienti[numarPacienti].grupaSanguina, grupaSanguina);
    strcpy(pacienti[numarPacienti].cnp, cnp);
    pacienti[numarPacienti].gen = gen;
    pacienti[numarPacienti].varsta = varsta;
}

void updateDonator(Donator &donator, char numeNou[], char prenumeNou[])
{
    strcpy(donator.nume, numeNou);
    strcpy(donator.prenume, prenumeNou);
}

void updatePacient(Pacient &pacient, char numeNou[], char prenumeNou[])
{
    strcpy(pacient.nume, numeNou);
    strcpy(pacient.prenume, prenumeNou);
}

void corectareNPG (char nume[])
{
    for (int i = 0; i < strlen(nume); i ++)
        nume[i] = toupper(nume[i]);
}



float procentFemeiCareDoneaza(Donator donatori[], int numarDonatori)
{
    int cont = 0;
    for (int i = 1; i <= numarDonatori; i ++)
        if (donatori[i].gen == 'F')
            cont ++;
    return (float)cont * 100 / numarDonatori;
}

float procentFemeiPacient(Pacient pacienti[], int numarPacienti)
{
    int cont = 0;
    for (int i = 1; i <= numarPacienti; i ++)
        if (pacienti[i].gen == 'F')
            cont ++;
    return (float)cont * 100 / numarPacienti;
}

float procentBarbatiCareDoneaza(Donator donatori[], int numarDonatori)
{
    int cont = 0;
    for (int i = 1; i <= numarDonatori; i ++)
        if (donatori[i].gen == 'M')
            cont ++;
    return (float)cont * 100 / numarDonatori;
}

float procentBarbatiPacient(Pacient pacienti[], int numarPacienti)
{
    int cont = 0;
    for (int i = 1; i <= numarPacienti; i ++)
        if (pacienti[i].gen == 'M')
            cont ++;
    return (float)cont * 100 / numarPacienti;
}

double vastaMedieDonatori(Donator donatori[], int numarDonatori)
{
    double medie = 0;
    for (int i = 1; i <= numarDonatori; i ++)
        medie += donatori[i].varsta;
    return medie / numarDonatori;
}

double vastaMediePacienti(Pacient pacienti[], int numarPacienti)
{
    double medie = 0;
    for (int i = 1; i <= numarPacienti; i ++)
        medie += pacienti[i].varsta;
    return medie / numarPacienti;
}

float procentDonatoriIntervalVarsta(Donator donatori[], int numarDonatori, int x, int y)
{
    int nrInterval = 0;
    for (int i = 1; i <= numarDonatori; i ++)
        if (donatori[i].varsta >= x && donatori[i].varsta <= y)
            nrInterval ++;
    return (float) nrInterval * 100 / numarDonatori;
}

int numarDonatoriGrupa (Donator donatori[], int numarDonatori, char grupaSanguina[])
{
    int cont = 0;
    for (int i = 1; i <= numarDonatori; i ++)
        if (strcmp(donatori[i].grupaSanguina, grupaSanguina) == 0)
            cont ++;
    return cont;
}

int numarPacientiGrupa (Pacient pacienti[], int numarPacienti, char grupaSanguina[])
{
    int cont = 0;
    for (int i = 1; i <= numarPacienti; i ++)
        if (strcmp(pacienti[i].grupaSanguina, grupaSanguina) == 0)
            cont ++;
    return cont;
}

void cautareDonatoriPentruPacienti(Spital &spital)
{
    for (int i = 1; i <= spital.numarPacienti; i ++)
        cautaDonator(i, spital);
}
