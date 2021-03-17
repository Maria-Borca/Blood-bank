#include "structs.h"

bool verificareCNP (char cnp[]);
int aflareVarsta(char cnp[]);
char aflareGen(char cnp[]) ;
bool cnpUnic(Donator donatori[], int numarDonatori, Pacient pacienti[], int numarPacient, char cnp[]);
void adaugareDonator(Donator donatori[], int &numarDonatori, char nume[], char prenume[], char grupaSanguina[], char cnp[], char gen, int varsta);
void adaugarePacient(Pacient pacienti[], int &numarPacienti, char nume[], char prenume[], char grupaSanguina[], char cnp[], char gen, int varsta);
int cautareCNPDonator(Donator donatori[], int numarDonatori, char cnp[]);
int cautareCNPPacient(Pacient pacienti[], int numarPacienti, char cnp[]);
void updateDonator(Donator &donator, char numeNou[], char prenumeNou[]);
void updatePacient(Pacient &pacient, char numeNou[], char prenumeNou[]);
void corectareNPG (char nume[]);
bool verificareGrupaSanguina (char grupaSanguina[]);
int numarPacientiCuDonator(Pacient pacienti[], int numarPacienti);
int procentFemeiCareDoneaza(Donator donatori[], int numarDonatori);
int procentFemeiPacient(Pacient pacienti[], int numarPacienti);
int procentBarbatiCareDoneaza(Donator donatori[], int numarDonatori);
int procentBarbatiPacient(Pacient pacienti[], int numarPacienti);
double vastaMedieDonatori(Donator donatori[], int numarDonatori) ;
double vastaMediePacienti(Pacient pacienti[], int numarPacienti) ;
int procentDonatoriIntervalVarsta(Donator donatori[], int numarDonatori, int x, int y);
int numarDonatoriGrupa (Donator donatori[], int numarDonatori, char grupaSanguina[]);
int numarPacientiGrupa (Pacient pacienti[], int numarPacienti, char grupaSanguina[]);
bool compatibil(char grupaSanguinaPacient[], char grupaSanguinaDonator[]);
void calcularePosibilitati(Spital &spital);
int cautaDonator(int pozPacient, Spital &spital);
void cautareDonatoriPentruPacienti(Spital &spital);