#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <stdio.h>
#include "functii.h"
#include "fisiere.h"

using namespace std;

void afisareDonatorConsola(Donator donator)
{
    cout << donator.nume << ' ';
    cout << donator.prenume << ' ';
    cout << donator.cnp << ' ';
    cout << donator.grupaSanguina;
}

void afisarePacientConsola(Pacient pacient)
{
    cout << pacient.nume << ' ';
    cout << pacient.prenume << ' ';
    cout << pacient.cnp << ' ';
    cout << pacient.grupaSanguina;
}

void afisareSpitalConsola(Spital spital)
{
    cout << "Donatorii: \n";
    for (int i = 1; i <= spital.numarDonatori; i ++)
    {
        afisareDonatorConsola(spital.donatori[i]);
        cout << '\n';
    }
    cout << '\n';
    cout << "Pacienti: \n";
    for (int i = 1; i <= spital.numarPacienti; i ++)
    {
        afisarePacientConsola(spital.pacienti[i]);
        cout << '\n';
    }
}

void afisareIstoricConsola(Spital spital)
{
    cout << "Numarul Pacientilor cu donatori este:" << spital.istoric.contor << '\n';
    for (int i = 1; i <= spital.istoric.contor; i ++)
    {
        int pozPacient = cautareCNPPacient(spital.pacienti, spital.numarPacienti, spital.istoric.legaturi[i].cnpPacient);
        int pozDonator = cautareCNPDonator(spital.donatori, spital.numarDonatori, spital.istoric.legaturi[i].cnpDonator);
        afisarePacientConsola(spital.pacienti[pozPacient]);
        cout << " -----> ";
        afisareDonatorConsola(spital.donatori[pozDonator]);
        cout << '\n';
    }
}


void adaugaDonator(Donator donatori[], int &numarDonatori, Pacient pacienti[], int numarPacienti)
{
    char nume[105];
    char prenume[105];
    char cnp[15], cnp2[15];
    char grupaSanguina[5];
    char gen;
    int varsta;
    cout << "Scrieti numele:\n";
    cin >> nume;
    corectareNPG(nume);
    cout << "\nScrieti prenumele:\n";
    cin >> prenume;
    corectareNPG(prenume);
    cout << '\n';
    do
    {
        cout << "Scrieti grupa Sanguina:\n";
        cin >> grupaSanguina;
        corectareNPG(grupaSanguina);
        if (verificareGrupaSanguina(grupaSanguina) == 0)
        {
            cout << "Aceasta grupa sanguina nu exista!\n";
            cout << "Apasa orice tasta pentru a reintroduce grupa sanguina!";
            getch();
            system("CLS");
        }
    }
    while (verificareGrupaSanguina(grupaSanguina) == 0);
    cout << '\n';
    do
    {
        do
        {
            cout << "Scrieti CNP-ul:\n";
            cin >> cnp;
            usleep(5);
            system("CLS");
            if (verificareCNP(cnp) && cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp))
            {
                gen = aflareGen(cnp);
                varsta = aflareVarsta(cnp);
            }
            else
            {
                cout << "CNP incorect!\n";
                cout << "Apasa orice tasta pentru a reintroduce CNP-ul!";
                getch();
                system("CLS");
            }

        }
        while(verificareCNP(cnp) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp) == 0);
        do
        {
            cout << "Confirmati CNP-ul:\n";
            cin >> cnp2;
            usleep(5);
            system("CLS");
            if (verificareCNP(cnp2) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp2) == 0)
            {
                cout << "Confirmare CNP incorecta!\n";
                cout << "Apasa orice tasta pentru a reintroduce CNP-ul!";
                getch();
                system("CLS");
            }
        }
        while(verificareCNP(cnp2) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp2) == 0);
        if (strcmp(cnp,cnp2) != 0)
        {
            cout << "CNP-urile nu corespund!\n";
            cout << "Apasati orice tasta pentru a le reintroduce!";
            getch();
            system("CLS");
        }
    }
    while(strcmp(cnp,cnp2) != 0);
    adaugareDonator(donatori, numarDonatori, nume, prenume, grupaSanguina, cnp, gen, varsta);
    cout << "Donatorul a fost adaugat cu succes!\n";
    cout << "Apasati orice tasta pentru a continua!\n";
    getch();
    system("CLS");
    afisareDonatoriInDonatoriTxt(donatori, numarDonatori);
}

void adaugaPacient(Pacient pacienti[], int &numarPacienti, Donator donatori[], int numarDonatori)
{
    char nume[105];
    char prenume[105];
    char cnp[15], cnp2[15];
    char grupaSanguina[5];
    char gen;
    int varsta;
    cout << "Scrieti numele:\n";
    cin >> nume;
    corectareNPG(nume);
    cout << "\nScrieti prenumele:\n";
    cin >> prenume;
    corectareNPG(prenume);
    do
    {
        cout << "\nScrieti grupa Sanguina:\n";
        cin >> grupaSanguina;
        corectareNPG(grupaSanguina);
        if (verificareGrupaSanguina(grupaSanguina) == 0)
        {
            cout << "Aceasta grupa sanguina nu exista!\n";
            cout << "Apasa orice tasta pentru a reintroduce grupa sanguina!";
            getch();
            system("CLS");
        }
    }
    while (verificareGrupaSanguina(grupaSanguina) == 0);
    cout << '\n';
    do
    {
        do
        {
            cout << "Scrieti CNP-ul:\n";
            cin >> cnp;
            usleep(5);
            system("CLS");
            if (verificareCNP(cnp) && cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp))
            {
                gen = aflareGen(cnp);
                varsta = aflareVarsta(cnp);
            }
            else
            {
                cout << "CNP incorect!\n";
                cout << "Apasa orice tasta pentru a reintroduce CNP-ul!";
                getch();
                system("CLS");
            }
        }
        while(verificareCNP(cnp) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp) == 0);

        do
        {
            cout << "Confirmati CNP-ul:\n";
            cin >> cnp2;
            usleep(5);
            system("CLS");
            if (verificareCNP(cnp2) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp2) == 0)
            {
                cout << "Confirmare CNP incorecta!\n";
                cout << "Apasa orice tasta pentru a reintroduce CNP-ul!";
                getch();
                system("CLS");
            }
        }
        while(verificareCNP(cnp2) == 0 || cnpUnic(donatori, numarDonatori, pacienti, numarPacienti, cnp2) == 0);
        if (strcmp(cnp,cnp2) != 0)
        {
            cout << "CNP-urile nu corespund!\n";
            cout << "Apasati orice tasta pentru a le reintroduce!";
            getch();
            system("CLS");
        }
    }
    while(strcmp(cnp,cnp2)!=0);
    adaugarePacient(pacienti, numarPacienti, nume, prenume, grupaSanguina, cnp, gen, varsta);
    cout << "Pacientul a fost adaugat cu succes!\n";
    cout << "Apasati orice tasta pentru a va reitoarce la meniu!\n";
    getch();
    system("CLS");
    afisarePacientiInPacientiTxt(pacienti, numarPacienti);
}

void updateazaDonator (Donator donatori[], int numarDonatori)
{
    char cnp[15];
    do
    {
        cout << "Scrie-ti CNP-ul: \n";
        cin >> cnp;
        usleep(5);
        system("CLS");
        if (cautareCNPDonator(donatori, numarDonatori, cnp) == 0)
        {
            cout << "CNP-ul nu se afla in baza de date!\n";
            cout << "Apasati orice tasta pentru a-l reintroduce!\n";
            getch();
            system("CLS");
        }
    }
    while (cautareCNPDonator(donatori, numarDonatori, cnp) == 0);
    system("CLS");
    int pozitieDonator = cautareCNPDonator(donatori, numarDonatori, cnp);
    char numeNou[105], prenumeNou[105], grupaSanguinaNoua[5];
    cout << "Scrie numele: \n";
    cin >> numeNou;
    corectareNPG(numeNou);
    cout << "\nScrie prenumele: \n";
    cin >> prenumeNou;
    corectareNPG(prenumeNou);
    updateDonator(donatori[pozitieDonator], numeNou, prenumeNou);
    cout << '\n';
    cout << "Modificarile au fost facute!\n";
    cout << "Apasati orice tasta pentru a reveni la meniu!\n";
    getch();
    system("CLS");
    afisareDonatoriInDonatoriTxt(donatori, numarDonatori);
}

void updateazaPacient (Pacient pacienti[], int numarPacienti)
{
    char cnp[15];
    do
    {
        cout << "Scrie-ti CNP-ul pacientului: \n";
        cin >> cnp;
        usleep(5);
        system("CLS");
        if (cautareCNPPacient(pacienti, numarPacienti, cnp) == 0)
        {
            cout << "CNP-ul nu se afla in baza de date!\n";
            cout << "Apasati orice tasta pentru a-l reintroduce!\n";
            getch();
            system("CLS");
        }
    }
    while (cautareCNPPacient(pacienti, numarPacienti, cnp) == 0);
    system("CLS");
    int pozitiePacient = cautareCNPPacient(pacienti, numarPacienti, cnp);
    char numeNou[105], prenumeNou[105], grupaSanguinaNoua[5];
    cout << "Scrie numele pacientului: \n";
    cin >> numeNou;
    corectareNPG(numeNou);
    cout << "\nScrie prenumele pacientului: \n";
    cin >> prenumeNou;
    corectareNPG(prenumeNou);
    updatePacient(pacienti[pozitiePacient], numeNou, prenumeNou);
    Sleep(500);
    system("CLS");
    cout << "Modificarile au fost facute!\n";
    cout << "Apasati orice tasta pentru a reveni la meniu!\n";
    getch();
    system("CLS");
    afisarePacientiInPacientiTxt(pacienti, numarPacienti);
}

void nevoiBanca(Donator donatori[], int numarDonatori, Pacient pacienti[], int numarPacienti)
{
    int donatoriCuGrupa0 = numarDonatoriGrupa(donatori, numarDonatori, "0");
    int donatoriCuGrupaA = numarDonatoriGrupa(donatori, numarDonatori, "A");
    int donatoriCuGrupaB = numarDonatoriGrupa(donatori, numarDonatori, "B");
    int donatoriCuGrupaAB = numarDonatoriGrupa(donatori, numarDonatori, "AB");
    int pacientiCuGrupa0 = numarPacientiGrupa(pacienti, numarPacienti, "0");
    int pacientiCuGrupaA = numarPacientiGrupa(pacienti, numarPacienti, "A");
    int pacientiCuGrupaB = numarPacientiGrupa(pacienti, numarPacienti, "B");
    int pacientiCuGrupaAB = numarPacientiGrupa(pacienti, numarPacienti, "AB");
    int ok = 1;
    if (donatoriCuGrupa0 - pacientiCuGrupa0 < 0)
    {
        cout << "Banca mai are nevoie de inca " << pacientiCuGrupa0 - donatoriCuGrupa0 << " donator";
        if(pacientiCuGrupa0 - donatoriCuGrupa0 > 1)
            cout << "i";
        cout << " cu grupa 0.\n";
        ok = 0;
    }
    if (donatoriCuGrupaA - pacientiCuGrupaA < 0)
    {
        cout << "Banca mai are nevoie de inca " << pacientiCuGrupaA - donatoriCuGrupaA << " donator";
        if(pacientiCuGrupaA - donatoriCuGrupaA > 1)
            cout << "i";
        cout << " cu grupa A.\n";
        ok = 0;
    }
    if (donatoriCuGrupaB - pacientiCuGrupaB < 0)
    {
        cout << "Banca mai are nevoie de inca " << pacientiCuGrupaB - donatoriCuGrupaB << " donator";
        if(pacientiCuGrupaB - donatoriCuGrupaB > 1)
            cout << "i";
        cout << " cu grupa B.\n";
        ok = 0;
    }
    if (donatoriCuGrupaAB - pacientiCuGrupaAB < 0)
    {
        cout << "Banca mai are nevoie de inca " << pacientiCuGrupaAB - donatoriCuGrupaAB << " donator";
        if(pacientiCuGrupaAB - donatoriCuGrupaAB > 1)
            cout << "i";
        cout << " cu grupa AB.\n";
        ok = 0;
    }
    if (ok == 1)
        cout << "Toti pacientii au donator!\n";
}



bool intrebari ()
{
    ifstream fin("intrebari.in");
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 11);
    int n;
    fin>>n;
    int ok=1;
    fin.get();
    char intrebare[305], raspuns[105], raspunsCorect[5];
    for(int i = 1; i <= n and ok == 1; i ++)
    {
        fin.getline(intrebare, 305);
        cout << intrebare << '\n';
        fin >> raspunsCorect;
        fin.get();
        do
        {
            cin >> raspuns;
            usleep(5);
            system("CLS");
            raspuns[0] = toupper(raspuns[0]);
            raspuns[1] = toupper(raspuns[1]);
            if (strcmp(raspuns, "DA") != 0 && strcmp(raspuns, "NU") != 0)
            {
                cout << "Raspunsul trebuie sa fie DA sau NU!\n";
                getch();
                system("CLS");
                cout << intrebare << '\n';
            }
        }
        while (strcmp(raspuns, "DA") != 0 && strcmp(raspuns, "NU") != 0);
        if(strcmp(raspuns,raspunsCorect) != 0)
        {

            cout << "Nu indepliniti toate conditiile pentru a dona sange!\n";
            ok = 0;
            getch();
            system("CLS");
        }
    }

    if(ok == 1)
    {
        cout<< "Sunteti compatibil pentru donare!\n" << endl;
        getch();
        system("CLS");
        return 1;
    }
    return 0;
}

void cautareDonator(Spital &spital)
{
    char cnp[20];
    cout << "Introduceti CNP-ul pacientului:\n";
    cin >> cnp;
    int poz = cautareCNPPacient(spital.pacienti, spital.numarPacienti, cnp);
    if (poz)
    {
        int pozDonator = cautaDonator(poz, spital);
        if (pozDonator != -1)
        {
            afisarePacientConsola(spital.pacienti[poz]);
            cout << " ------> ";
            afisareDonatorConsola(spital.donatori[pozDonator]);
        }
        else cout << "Nu s-a gasit niciun donator compatibil!";
    }
    else cout << "Nu exista niciun pacient cu acest CNP!\n";
}

void meniu(Spital &spital)
{
    int raspuns;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 64);
    cout << "            ~ BANCA DE SANGE ~            \n\n";
    do
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "Daca vreti sa donati sange apasati tasta 1\n";
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Daca sunteti medic apasati tasta 2\n";
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "Daca vreti sa iesiti apasati tasta 0\n";
        cin >> raspuns;
        Sleep(100);
        system("CLS");
        if (raspuns != 1 && raspuns != 2 && raspuns != 0)
        {
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "Tasta incorecta!\nApasati orice tasta pentru a va reintoarce la meniu!";
            getch();
            system("CLS");
        }

    }
    while (raspuns != 1 && raspuns != 2 && raspuns != 0);
    if (raspuns == 2)
    {
        char parola[100];
        do
        {
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "Introduceti parola!\n";
            cin >> parola;
            system("CLS");
            if (strcmp(parola, spital.parola) != 0)
            {
                cout << "Daca sunteti donator apasati tasta 1, altfel apasati tasta 2 pentru a reintroduce parola!\n";
                cin >> raspuns;
                system("CLS");
            }
        }
        while (strcmp(parola, spital.parola) != 0 && raspuns == 2);
    }
    switch(raspuns)
    {
    case 1:
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 11);
        if (intrebari() == 0)
            break;
        adaugaDonator(spital.donatori, spital.numarDonatori, spital.pacienti, spital.numarPacienti);
        char optiune;
        cout << "Donatorul: \n";
        afisareDonatorConsola(spital.donatori[spital.numarDonatori]);
        cout << '\n';
        cout << "Apasati tasta 1 daca ati gresit numele sau prenumele sau orice tasta daca e totul corect!\n";
        cin >> optiune;
        while (optiune == '1')
        {
            system("CLS");
            updateazaDonator(spital.donatori, spital.numarDonatori);
            afisareDonatorConsola(spital.donatori[spital.numarDonatori]);
            cout << '\n';
            cout << "Apasati tasta 1 daca ati gresit numele sau prenumele sau orice tasta daca e totul corect!\n";
            cin >> optiune;
        }
        getch();
        system("CLS");
        cout << "Multumim ca v-ati inregistrat!\nAti salvat o viata!\n";
        getch();
        system("CLS");
        break;
    }
    case 2:
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 14);
        int optiuneDoctor;
        do
        {
            system("CLS");
            cout << "Daca vreti sa iesiti din aplicatie apasati tasta 0\n";
            cout << "Daca vreti sa introduceti un pacient apasati tasta 1\n";
            cout << "Daca vreti sa modificati un pacient apasati tasta 2\n";
            cout << "Daca vreti sa cautati un donator pentru un pacient apasati tasta 3\n";
            cout << "Daca vreti sa afisati donatorii si pacientii compatibili si numarul lor apasati tasta 4\n";
            cout << "Daca vreti sa afisati toti donatorii si pacientii apasati tasta 5\n";
            cout << "Daca vreti sa aflati diferite statistici apasati tasta 6\n\n";
            cout << "Optiunea ta este: ";
            cin >> optiuneDoctor;
            Sleep(100);
            system("CLS");
            if (optiuneDoctor == 1)
            {
                adaugaPacient(spital.pacienti, spital.numarPacienti, spital.donatori, spital.numarDonatori);
                calcularePosibilitati(spital);
            }

            if (optiuneDoctor == 2)
                updateazaPacient(spital.pacienti, spital.numarPacienti);
            if (optiuneDoctor == 3)
            {
                cautareDonator(spital);

            }
            if (optiuneDoctor == 4)
            {
                cautareDonatoriPentruPacienti(spital);
                afisareIstoricConsola(spital);
            }
            if (optiuneDoctor == 5)
                afisareSpitalConsola(spital);
            if (optiuneDoctor == 6)
            {
                int numarStatistica;
                do
                {
                    system("CLS");
                    cout << "Daca vreti sa iesiti apasati tasta 0\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor de gen feminin care vor sa doneze apasati tasta 1\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor de gen masculin care vor sa doneze apasati tasta 2\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor de gen feminin care au nevoie de sange apasati tasta 3\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor de gen masculin care au nevoie de sange apasati tasta 4\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor intre 18 si 30 de ani care vor sa doneze sange 5\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor intre 30 si 50 de ani care vor sa doneze sange 6\n";
                    cout << "Daca vreti sa vedeti procentul persoanelor intre 50 si 60 de ani care vor sa doneze sange 7\n";
                    cout << "Daca vreti sa vedeti varsta medie a donatorilor apasati tasta 8\n";
                    cout << "Daca vreti sa vedeti varsta medie a pacientilor apasati tasta 9\n";
                    cout << "Daca vreti sa vedeti de ce grupe de sange mai are nevoie banca 10\n";
                    cout << "Optiunea ta este: ";
                    cin >> numarStatistica;

                    if (numarStatistica == 1)
                    {
                        cout << "Procentul persoanelor de gen feminin care vor sa doneze este: ";
                        cout << procentFemeiCareDoneaza(spital.donatori, spital.numarDonatori) << "%\n";
                    }

                    if (numarStatistica == 2)
                    {
                        cout << "Procentul persoanelor de gen masculin care vor sa doneze este: ";
                        cout << procentBarbatiCareDoneaza(spital.donatori, spital.numarDonatori) << "%\n";
                    }

                    if (numarStatistica == 3)
                    {
                        cout << "Procentul persoanelor de gen feminin care au nevoie de sange este: ";
                        cout << procentFemeiPacient(spital.pacienti, spital.numarPacienti) << "%\n";
                    }
                    if (numarStatistica == 4)
                    {
                        cout << "Procentul persoanelor de gen masculin care au nevoie de sange este: ";
                        cout << procentBarbatiPacient(spital.pacienti, spital.numarPacienti) << "%\n";
                    }
                    if (numarStatistica == 5)
                    {
                        cout << "Procentul donatorilor cu varsta intre 18 si 30 de ani este: ";
                        cout << procentDonatoriIntervalVarsta(spital.donatori, spital.numarDonatori, 18, 30) << "%\n";
                    }
                    if (numarStatistica == 6)
                    {
                        cout << "Procentul donatorilor cu varsta intre 30 si 50 de ani este: ";
                        cout << procentDonatoriIntervalVarsta(spital.donatori, spital.numarDonatori, 30, 50) << "%\n";
                    }
                    if (numarStatistica == 7)
                    {
                        cout << "Procentul donatorilor cu varsta intre 50 si 60 de ani este: ";
                        cout << procentDonatoriIntervalVarsta(spital.donatori, spital.numarDonatori, 50, 60) << "%\n";
                    }
                    if (numarStatistica == 8)
                    {
                        cout << "Varsta medie a donatorilor este: ";
                        cout << vastaMedieDonatori(spital.donatori, spital.numarDonatori) << '\n';
                    }
                    if (numarStatistica == 9)
                    {
                        cout << "Varsta medie a pacientilor este: ";
                        cout << vastaMediePacienti(spital.pacienti, spital.numarPacienti) << '\n';
                    }
                    if (numarStatistica == 10)
                        nevoiBanca(spital.donatori, spital.numarDonatori, spital.pacienti, spital.numarPacienti);
                    getch();
                }
                while (numarStatistica != 0);
            }
            getch();
        }
        while (optiuneDoctor != 0);
        break;
    }
    case 0:
        break;

    }

}
