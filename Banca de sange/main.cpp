#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "fisiere.h"
#include "functii.h"
#include "ui.h"


using namespace std;


int main()
{
    Spital spital;
    citireSpital(spital);
    meniu(spital);
    return 0;
}
