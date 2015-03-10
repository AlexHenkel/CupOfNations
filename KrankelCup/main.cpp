//
//  main.cpp
//  KrankelCup
//
//  Created by Alejandro Henkel on 3/8/15.
//  Copyright (c) 2015 Alejandro Henkel. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

class Partido{
public:
    Partido(){iLocal = 0; iVisitante = 0; sLocal = ""; sVisitante = ""; iClave = 0; bJugado = false;};
    void setMLocal(int iLocal){this->iLocal = iLocal;};
    void setMVisitante(int iVisitante){this->iVisitante = iVisitante;};
    void setLocal(string sLocal){this->sLocal = sLocal;};
    void setVisitante(string sVisitante){this->sVisitante = sVisitante;};
    void setClave(int iClave){this->iClave = iClave;};
    void setJugado(){bJugado = true;}
    int getMLocal(){return iLocal;};
    int getMVisitante(){return iVisitante;};
    bool getJugado(){return bJugado;};
    string getLocal(){return sLocal;};
    string getVisitante(){return sVisitante;};
    int getClave(){return iClave;};
    string ganador(){if(iLocal > iVisitante) return sLocal; else if (iVisitante > iLocal) return sVisitante; else return "Empate";};
    void resultado(){cout << iLocal << " " << sLocal << " vs " << iVisitante << " " << sVisitante;};
private:
    int iLocal, iVisitante, iClave;
    string sLocal, sVisitante;
    bool bJugado;
};

class Jugador{
public:
    Jugador(){sNombre = ""; iPuntos = 0; iGolesF = 0; iGolesC = 0; iDif = 0; iPJ = 0; dPorcentaje = 0.0;};
    Jugador(string sNombre){this->sNombre = sNombre; iPuntos = 0; iGolesF = 0; iGolesC = 0; iDif = 0; iPJ = 0; dPorcentaje = 0.0;};
    void setNombre(string sNombre){this->sNombre = sNombre;};
    void setGolesF(int iGolesF){this->iGolesF = iGolesF; iDif = this->iGolesF - iGolesC;};
    void setGolesC(int iGolesC){this->iGolesC = iGolesC; iDif = iGolesF - this->iGolesC;};
    void setPuntos(int iPuntos){this->iPuntos = iPuntos; dPorcentaje = this->iPuntos / iPJ;};
    void setPJ(int iPJ){this->iPJ = iPJ; dPorcentaje = iPuntos / this->iPJ;};
    string getNombre(){return sNombre;};
    int getPuntos(){return iPuntos;};
    int getGolesF(){return iGolesF;};
    int getGolesC(){return iGolesC;};
    int getDif(){return iDif;};
    int getPorcentaje(){return dPorcentaje;};
    int getPJ(){return iPJ;};
    void sumarPuntos(int iPuntos){this->iPuntos += iPuntos;};
    void sumarGolesF(int iGolesF){this->iGolesF += iGolesF; iDif = this->iGolesF - iGolesC;};
    void sumarGolesC(int iGolesC){this->iGolesC += iGolesC; iDif = iGolesF - this->iGolesC;};
    void sumarPartido(){iPJ++; dPorcentaje = iPuntos / iPJ;};
    void resetPuntos(){iPuntos = 0; iGolesF = 0; iGolesC = 0; iDif = 0;};
private:
    string sNombre;
    int iPuntos, iGolesF, iGolesC, iDif, iPJ;
    double dPorcentaje;
};

vector<Jugador> jugJugadores;
vector<Jugador> jugJugadoresF;
vector<Jugador> jugJugadoresTabla;
vector<Partido> parPartidos;
vector<Partido> parPartidosF;

// random generator function:
int myrandom (int i) { return std::rand()%i;}

void ingresaJugadores(int iN) {
    string sAux;
    Partido parAux;
    for (int i = 0; i < iN; i++) {
        cout << "Ingresa nombre: " << i + 1 << endl;
        cin >> sAux;
        jugJugadores.push_back(sAux);
    }
    random_shuffle(jugJugadores.begin(), jugJugadores.end());
    random_shuffle(jugJugadores.begin(), jugJugadores.end(), myrandom);
    for (int i = 0; i < iN / 2; i++) {
        for (int j = 0; j < iN / 2; j++) {
            if (i != j) {
                parAux.setLocal(jugJugadores[i].getNombre());
                parAux.setVisitante(jugJugadores[j].getNombre());
                parAux.setClave((i * 10) + j);
                parPartidos.push_back(parAux);
            }
        }
    }
    
    for (int i = iN / 2; i < iN ; i++) {
        for (int j = iN / 2; j < iN; j++) {
            if (i != j) {
                parAux.setLocal(jugJugadores[i].getNombre());
                parAux.setVisitante(jugJugadores[j].getNombre());
                parAux.setClave((i * 10) + j);
                parPartidos.push_back(parAux);
            }
        }
    }
    random_shuffle(parPartidos.begin(), parPartidos.end());
    random_shuffle(parPartidos.begin(), parPartidos.end(), myrandom);
}

void ordenaGrupos(int iN){
    Jugador jugTemp;
    for (int i = 0; i < iN / 2; i++) {
        for (int j = i + 1; j < iN / 2; j++) {
            if (i != j) {
                if (jugJugadores[j].getPuntos() > jugJugadores[i].getPuntos()) {
                    jugTemp = jugJugadores[i];
                    jugJugadores[i] = jugJugadores[j];
                    jugJugadores[j] = jugTemp;
                }
            }
        }
    }
    
    for (int i = iN / 2; i < iN ; i++) {
        for (int j = iN / 2; j < iN; j++) {
            if (i != j) {
                if (jugJugadores[j].getPuntos() > jugJugadores[i].getPuntos()) {
                    jugTemp = jugJugadores[i];
                    jugJugadores[i] = jugJugadores[j];
                    jugJugadores[j] = jugTemp;
                }
            }
        }
    }
}

void muestraGrupos(int iN){

    ordenaGrupos(iN);
    cout << "Grupo 1" << endl;
    cout << setw(10) << left << "Equipos";
    cout << "GF GC Dif Pts" << endl;
    for (int k = 0; k < iN / 2; k++) {
        cout << setw(10) << left << jugJugadores[k].getNombre() << " ";
        cout << setw(2) << jugJugadores[k].getGolesF() << " ";
        cout << setw(2) << jugJugadores[k].getGolesC() << " ";
        cout << setw(3) << jugJugadores[k].getDif() << " ";
        cout << setw(3) << jugJugadores[k].getPuntos() << " " << endl;
    }
    
    cout << endl << "Grupo 2" << endl;
    cout << setw(10) << left << "Equipos";
    cout << "GF GC Dif Pts" << endl;
    for (int k = iN / 2; k < iN; k++) {
        cout << setw(10) << left << jugJugadores[k].getNombre() << " ";
        cout << setw(2) << jugJugadores[k].getGolesF() << " ";
        cout << setw(2) << jugJugadores[k].getGolesC() << " ";
        cout << setw(3) << jugJugadores[k].getDif() << " ";
        cout << setw(3) << jugJugadores[k].getPuntos() << endl;
    }
}

void muestraPartidos() {
    for (int i = 0; i < parPartidos.size(); i++)
        cout << "P" << i + 1 << ": " << parPartidos[i].getLocal() << " vs " << parPartidos[i].getVisitante() << endl;
}

void muestraPartidosF() {
    for (int i = 0; i < parPartidosF.size(); i++)
        cout << "P" << i + 1 << ": " << parPartidosF[i].getLocal() << " vs " << parPartidosF[i].getVisitante() << endl;
}

void ingresaMarcadorF() {
    int iLocal, iVisitante, iLClave = 0, iVClave = 0, iClave, iClave2;
    bool bExiste = false;
    string sLocal, sVisitante;
    
    do {
        cout << "Ingresa nombre del jugador local" << endl;
        cin >> sLocal;
        for (int i = 0; i < jugJugadoresF.size() && !bExiste; i++) {
            if (sLocal == jugJugadoresF[i].getNombre()) {
                bExiste = true;
                iLClave = i;
            }
        }
    } while (!bExiste);
    
    bExiste = false;
    
    do {
        cout << "Ingresa nombre del jugador visitante" << endl;
        cin >> sVisitante;
        for (int i = 0; i < jugJugadoresF.size() && !bExiste; i++) {
            if (sVisitante == jugJugadoresF[i].getNombre()) {
                bExiste = true;
                iVClave = i;
            }
        }
    } while (!bExiste && (sLocal == sVisitante));
    
    iClave = ((iLClave * 10) + iVClave);
    iClave2 = ((iVClave * 10) + iLClave);
    
    cout << "Ingresa goles del local" << endl;
    cin >> iLocal;
    
    cout << "Ingresa goles del visitante" << endl;
    cin >> iVisitante;
    
    jugJugadoresF[iLClave].sumarGolesF(iLocal);
    jugJugadoresF[iLClave].sumarGolesC(iVisitante);
    jugJugadoresF[iVClave].sumarGolesF(iVisitante);
    jugJugadoresF[iVClave].sumarGolesC(iLocal);
    
    for (int i = 0; i < parPartidosF.size(); i++) {
        if (parPartidosF[i].getClave() == iClave) {
            parPartidosF[i].setMLocal(iLocal);
            parPartidosF[i].setMVisitante(iVisitante);
            parPartidosF[i].setJugado();
            if (iLocal > iVisitante) {
                jugJugadoresF[iLClave].sumarPuntos(3);
            }
            else if (iVisitante > iLocal) {
                jugJugadoresF[iVClave].sumarPuntos(3);
            }
            else {
                jugJugadoresF[iLClave].sumarPuntos(1);
                jugJugadoresF[iVClave].sumarPuntos(1);
            }
        }
        else if (parPartidosF[i].getClave() == iClave2) {
            if (parPartidosF[i].getJugado()) {
                int iPuntosL, iPuntosV;
                int iGolesL = iLocal + parPartidosF[i].getMVisitante();
                int iGolesV = iVisitante + parPartidosF[i].getMLocal();
                
                if (iLocal > iVisitante) {
                    iPuntosL = 3;
                    iPuntosV = 0;
                }
                else if (iVisitante > iLocal) {
                    iPuntosL = 0;
                    iPuntosV = 3;
                }
                else {
                    iPuntosL = 1;
                    iPuntosV = 1;
                }
                
                if (parPartidosF[i].ganador() == sLocal) {
                    iPuntosL += 3;
                }
                else if (parPartidosF[i].ganador() == sVisitante)
                    iPuntosV += 3;
                else {
                    iPuntosL++;
                    iPuntosV++;
                }
                
                jugJugadoresF[iLClave].sumarPuntos(1);
                
                if (iPuntosV > iPuntosL) {
                    jugJugadoresF[iLClave].sumarPuntos(-1);
                    jugJugadoresF[iVClave].sumarPuntos(1);
                }
                else if (iPuntosV == iPuntosL) {
                    if (iGolesV > iGolesL) {
                        jugJugadoresF[iLClave].sumarPuntos(-1);
                        jugJugadoresF[iVClave].sumarPuntos(1);
                    }
                    else if (iGolesV == iGolesL) {
                        if (iVisitante > parPartidosF[i].getMVisitante()) {
                            jugJugadoresF[iLClave].sumarPuntos(-1);
                            jugJugadoresF[iVClave].sumarPuntos(1);
                        }
                        else if (iVisitante == parPartidosF[i].getMVisitante())
                            jugJugadoresF[iLClave].sumarPuntos(-1);
                    }
                }
            }
        }
    }
}

void ingresaMarcador() {
    int iLocal, iVisitante, iLClave = 0, iVClave = 0, iLClaveT = 0, iVClaveT = 0, iClave, iClave2;
    bool bExiste = false, bExisteTL = false, bExisteTV = false;
    string sLocal, sVisitante;
    
    do {
        cout << "Ingresa nombre del jugador local" << endl;
        cin >> sLocal;
        for (int i = 0; i < jugJugadores.size() && !bExiste; i++) {
            if (sLocal == jugJugadores[i].getNombre()) {
                bExiste = true;
                iLClave = i;
            }
        }
        for (int i = 0; i < jugJugadoresTabla.size() && !bExisteTL; i++) {
            if (sLocal == jugJugadoresTabla[i].getNombre()) {
                bExisteTL = true;
                iLClaveT = i;
            }
        }
    } while (!bExiste);
    
    bExiste = false;
    
    do {
        cout << "Ingresa nombre del jugador visitante" << endl;
        cin >> sVisitante;
        for (int i = 0; i < jugJugadores.size() && !bExiste; i++) {
            if (sVisitante == jugJugadores[i].getNombre()) {
                bExiste = true;
                iVClave = i;
            }
        }
        for (int i = 0; i < jugJugadoresTabla.size() && !bExisteTV; i++) {
            if (sVisitante == jugJugadoresTabla[i].getNombre()) {
                bExisteTV = true;
                iVClaveT = i;
            }
        }
    } while (!bExiste && (sLocal == sVisitante));
    
    iClave = ((iLClave * 10) + iVClave);
    iClave2 = ((iVClave * 10) + iLClave);
    
    cout << "Ingresa goles del local" << endl;
    cin >> iLocal;
    
    cout << "Ingresa goles del visitante" << endl;
    cin >> iVisitante;
    
    jugJugadores[iLClave].sumarGolesF(iLocal);
    jugJugadores[iLClave].sumarGolesC(iVisitante);
    jugJugadores[iVClave].sumarGolesF(iVisitante);
    jugJugadores[iVClave].sumarGolesC(iLocal);
    
    if (bExisteTL) {
        jugJugadoresTabla[iLClaveT].sumarGolesF(iLocal);
        jugJugadoresTabla[iLClaveT].sumarGolesC(iVisitante);
    }
    if (bExisteTV) {
        jugJugadoresTabla[iVClaveT].sumarGolesF(iVisitante);
        jugJugadoresTabla[iVClaveT].sumarGolesC(iLocal);
    }
    
    for (int i = 0; i < parPartidos.size(); i++) {
        if (parPartidos[i].getClave() == iClave) {
            parPartidos[i].setMLocal(iLocal);
            parPartidos[i].setMVisitante(iVisitante);
            parPartidos[i].setJugado();
            if (iLocal > iVisitante) {
                jugJugadores[iLClave].sumarPuntos(3);
                if (bExisteTL) {
                    jugJugadoresTabla[iLClaveT].sumarPuntos(3);
                }
            }
            else if (iVisitante > iLocal) {
                jugJugadores[iVClave].sumarPuntos(3);
                if (bExisteTV) {
                    jugJugadoresTabla[iVClaveT].sumarPuntos(3);
                }
            }
            else {
                jugJugadores[iLClave].sumarPuntos(1);
                jugJugadores[iVClave].sumarPuntos(1);
                if (bExisteTL) {
                    jugJugadoresTabla[iLClaveT].sumarPuntos(1);
                }
                if (bExisteTV) {
                    jugJugadoresTabla[iVClaveT].sumarPuntos(1);
                }
            }
        }
        else if (parPartidos[i].getClave() == iClave2) {
            if (parPartidos[i].getJugado()) {
                int iPuntosL, iPuntosV;
                int iGolesL = iLocal + parPartidos[i].getMVisitante();
                int iGolesV = iVisitante + parPartidos[i].getMLocal();
                
                if (iLocal > iVisitante) {
                    iPuntosL = 3;
                    iPuntosV = 0;
                }
                else if (iVisitante > iLocal) {
                    iPuntosL = 0;
                    iPuntosV = 3;
                }
                else {
                    iPuntosL = 1;
                    iPuntosV = 1;
                }
                
                if (parPartidos[i].ganador() == sLocal) {
                    iPuntosL += 3;
                }
                else if (parPartidos[i].ganador() == sVisitante)
                    iPuntosV += 3;
                else {
                    iPuntosL++;
                    iPuntosV++;
                }
                
                jugJugadores[iLClave].sumarPuntos(1);
                
                if (iPuntosV > iPuntosL) {
                    jugJugadores[iLClave].sumarPuntos(-1);
                    jugJugadores[iVClave].sumarPuntos(1);
                }
                else if (iPuntosV == iPuntosL) {
                    if (iGolesV > iGolesL) {
                        jugJugadores[iLClave].sumarPuntos(-1);
                        jugJugadores[iVClave].sumarPuntos(1);
                    }
                    else if (iGolesV == iGolesL) {
                        if (iVisitante > parPartidos[i].getMVisitante()) {
                            jugJugadores[iLClave].sumarPuntos(-1);
                            jugJugadores[iVClave].sumarPuntos(1);
                        }
                        else if (iVisitante == parPartidos[i].getMVisitante())
                            jugJugadores[iLClave].sumarPuntos(-1);
                    }
                }
            }
        }
    }
}

void final() {
    int i1A = 0, i1B = 2;
    string sAux;
    
    if (jugJugadoresF[1].getPuntos() > jugJugadoresF[0].getPuntos()) {
        i1A = 1;
    }
    else if (jugJugadoresF[1].getPuntos() == jugJugadoresF[0].getPuntos()) {
        if (jugJugadoresF[1].getGolesF() > jugJugadoresF[0].getGolesF()) {
            i1A = 1;
        }
        else if (jugJugadoresF[1].getGolesF() == jugJugadoresF[0].getGolesF()) {
            if (jugJugadoresF[1].getGolesC() > jugJugadoresF[0].getGolesC()) {
                i1A = 1;
            }
            else if (jugJugadoresF[1].getGolesC() == jugJugadoresF[0].getGolesC()){
                cout << "Ingrese el nombre del ganador de la serie entre " << jugJugadoresF[0].getNombre() << " y " << jugJugadoresF[1].getNombre() << endl;
                cin >> sAux;
                if (sAux == jugJugadoresF[1].getNombre()) {
                    i1A = 1;
                }
            }
        }
    }
    
    if (jugJugadoresF[3].getPuntos() > jugJugadoresF[2].getPuntos()) {
        i1B = 3;
    }
    else if (jugJugadoresF[3].getPuntos() == jugJugadoresF[2].getPuntos()) {
        if (jugJugadoresF[3].getGolesF() > jugJugadoresF[2].getGolesF()) {
            i1A = 3;
        }
        else if (jugJugadoresF[3].getGolesF() == jugJugadoresF[2].getGolesF()) {
            if (jugJugadoresF[3].getGolesC() > jugJugadoresF[2].getGolesC()) {
                i1A = 3;
            }
            else if (jugJugadoresF[3].getGolesC() == jugJugadoresF[2].getGolesC()){
                cout << "Ingrese el nombre del ganador de la serie entre " << jugJugadoresF[2].getNombre() << " y " << jugJugadoresF[3].getNombre() << endl;
                cin >> sAux;
                if (sAux == jugJugadoresF[3].getNombre()) {
                    i1A = 3;
                }
            }
        }
    }
    
    
    cout << "La final será entre " << jugJugadoresF[i1A].getNombre() << " y " << jugJugadoresF[i1B].getNombre() << endl;
    cout << "Ingrese al campeón" << endl;
    cin >> sAux;
    cout << "Felicidades a " << sAux << " que hoy se lleva la " << sAux << "Copa de Naciones" << endl;
}

void generaFinalistas(int iN) {
    int i1A = 0, i2A, i1B = iN / 2, i2B = iN / 2;
    bool empateTodo1 = false;
    
    ordenaGrupos(iN);
    
    for (int i = 1; i < iN / 2; i++) {
        if (jugJugadores[i].getPuntos() > jugJugadores[i1A].getPuntos()) {
            i1A = i;
            if (empateTodo1) {
                empateTodo1 = false;
            }
        }
        else if (jugJugadores[i].getPuntos() == jugJugadores[i1A].getPuntos()) {
            if (jugJugadores[i].getGolesF() > jugJugadores[i1A].getGolesF()) {
                i1A = i;
                if (empateTodo1) {
                    empateTodo1 = false;
                }
            }
            else if (jugJugadores[i].getGolesF() == jugJugadores[i1A].getGolesF()) {
                if (jugJugadores[i].getGolesC() > jugJugadores[i1A].getGolesC()) {
                    i1A = i;
                    if (empateTodo1) {
                        empateTodo1 = false;
                    }
                }
                else if (jugJugadores[i].getGolesC() == jugJugadores[i1A].getGolesC()){
                    int iPL = 0, iPV = 0, iGFL = 0, iGFV = 0, iGCL = 0, iGCV = 0;
                    
                    for (int j = 0; j < parPartidos.size(); j++) {
                        if (parPartidos[j].getClave() == (i * 10) + i1A) {
                            if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                iPL += 3;
                            }
                            else if (parPartidos[j].ganador() == jugJugadores[i1A].getNombre())
                                iPV += 3;
                            else {
                                iPV++;
                                iPL++;
                            }
                            iGFL = parPartidos[j].getMLocal();
                            iGCV = parPartidos[j].getMLocal();
                            iGCL = parPartidos[j].getMVisitante();
                            iGFV = parPartidos[j].getMVisitante();
                            j += 1000;
                        }
                    }
                    
                    for (int j = 0; j < parPartidos.size(); j++) {
                        if (parPartidos[j].getClave() == (i1A * 10) + i) {
                            if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                iPL += 3;
                            }
                            else if (parPartidos[j].ganador() == jugJugadores[i1A].getNombre())
                                iPV += 3;
                            else {
                                iPV++;
                                iPL++;
                            }
                            iGFV = parPartidos[j].getMLocal();
                            iGCL = parPartidos[j].getMLocal();
                            iGCV = parPartidos[j].getMVisitante();
                            iGFL = parPartidos[j].getMVisitante();
                            j += 1000;
                        }
                    }
                    
                    if (iPL > iPV) {
                        i1A = i;
                        if (empateTodo1) {
                            empateTodo1 = false;
                        }
                    }
                    else if (iPL == iPV) {
                        if (iGFL > iGFV) {
                            i1A = i;
                            if (empateTodo1) {
                                empateTodo1 = false;
                            }
                        }
                        else if (iGFL == iGFV){
                            if (iGCL > iGCV) {
                                i1A = i;
                                if (empateTodo1) {
                                    empateTodo1 = false;
                                }
                            }
                            else if (iGCL == iGCV) {
                                empateTodo1 = true;
                                int iRand = rand() % 2;
                                if (iRand == 0) {
                                    i1A = i;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (empateTodo1) {
        cout << "El ganador del primer lugar del grupo 1 se eligió de manera aleatoria" << endl;
    }
    
    empateTodo1 = false;
    
    if (i1A == 0) {
        i2A = 1;
    }
    else
        i2A = 0;
    
    for (int i = 0; i < iN / 2; i++) {
        if ((i != i1A) && (i != i2A)) {
            if (jugJugadores[i].getPuntos() > jugJugadores[i2A].getPuntos()) {
                i2A = i;
                if (empateTodo1) {
                    empateTodo1 = false;
                }
            }
            else if (jugJugadores[i].getPuntos() == jugJugadores[i2A].getPuntos()) {
                if (jugJugadores[i].getGolesF() > jugJugadores[i2A].getGolesF()) {
                    i2A = i;
                    if (empateTodo1) {
                        empateTodo1 = false;
                    }
                }
                else if (jugJugadores[i].getGolesF() == jugJugadores[i2A].getGolesF()) {
                    if (jugJugadores[i].getGolesC() > jugJugadores[i2A].getGolesC()) {
                        i2A = i;
                        if (empateTodo1) {
                            empateTodo1 = false;
                        }
                    }
                    else if (jugJugadores[i].getGolesC() == jugJugadores[i2A].getGolesC()){
                        int iPL = 0, iPV = 0, iGFL = 0, iGFV = 0, iGCL = 0, iGCV = 0;
                        
                        for (int j = 0; j < parPartidos.size(); j++) {
                            if (parPartidos[j].getClave() == (i * 10) + i2A) {
                                if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                    iPL += 3;
                                }
                                else if (parPartidos[j].ganador() == jugJugadores[i2A].getNombre())
                                    iPV += 3;
                                else {
                                    iPV++;
                                    iPL++;
                                }
                                iGFL = parPartidos[j].getMLocal();
                                iGCV = parPartidos[j].getMLocal();
                                iGCL = parPartidos[j].getMVisitante();
                                iGFV = parPartidos[j].getMVisitante();
                                j += 1000;
                            }
                        }
                        
                        for (int j = 0; j < parPartidos.size(); j++) {
                            if (parPartidos[j].getClave() == (i2A * 10) + i) {
                                if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                    iPL += 3;
                                }
                                else if (parPartidos[j].ganador() == jugJugadores[i2A].getNombre())
                                    iPV += 3;
                                else {
                                    iPV++;
                                    iPL++;
                                }
                                iGFV = parPartidos[j].getMLocal();
                                iGCL = parPartidos[j].getMLocal();
                                iGCV = parPartidos[j].getMVisitante();
                                iGFL = parPartidos[j].getMVisitante();
                                j += 1000;
                            }
                        }
                        
                        if (iPL > iPV) {
                            i2A = i;
                            if (empateTodo1) {
                                empateTodo1 = false;
                            }
                        }
                        else if (iPL == iPV) {
                            if (iGFL > iGFV) {
                                i2A = i;
                                if (empateTodo1) {
                                    empateTodo1 = false;
                                }
                            }
                            else if (iGFL == iGFV){
                                if (iGCL > iGCV) {
                                    i2A = i;
                                    if (empateTodo1) {
                                        empateTodo1 = false;
                                    }
                                }
                                else if (iGCL == iGCV) {
                                    empateTodo1 = true;
                                    int iRand = rand() % 2;
                                    if (iRand == 0) {
                                        i2A = i;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (empateTodo1) {
        cout << "El ganador del segundo lugar del grupo 1 se eligió de manera aleatoria" << endl;
    }
    
    // Grupo 2
    for (int i = iN / 2; i < iN; i++) {
        if (jugJugadores[i].getPuntos() > jugJugadores[i1B].getPuntos()) {
            i1B = i;
            if (empateTodo1) {
                empateTodo1 = false;
            }
        }
        else if (jugJugadores[i].getPuntos() == jugJugadores[i1B].getPuntos()) {
            if (jugJugadores[i].getGolesF() > jugJugadores[i1B].getGolesF()) {
                i1B = i;
                if (empateTodo1) {
                    empateTodo1 = false;
                }
            }
            else if (jugJugadores[i].getGolesF() == jugJugadores[i1B].getGolesF()) {
                if (jugJugadores[i].getGolesC() > jugJugadores[i1B].getGolesC()) {
                    i1B = i;
                    if (empateTodo1) {
                        empateTodo1 = false;
                    }
                }
                else if (jugJugadores[i].getGolesC() == jugJugadores[i1B].getGolesC()){
                    int iPL = 0, iPV = 0, iGFL = 0, iGFV = 0, iGCL = 0, iGCV = 0;
                    
                    for (int j = 0; j < parPartidos.size(); j++) {
                        if (parPartidos[j].getClave() == (i * 10) + i1B) {
                            if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                iPL += 3;
                            }
                            else if (parPartidos[j].ganador() == jugJugadores[i1B].getNombre())
                                iPV += 3;
                            else {
                                iPV++;
                                iPL++;
                            }
                            iGFL = parPartidos[j].getMLocal();
                            iGCV = parPartidos[j].getMLocal();
                            iGCL = parPartidos[j].getMVisitante();
                            iGFV = parPartidos[j].getMVisitante();
                            j += 1000;
                        }
                    }
                    
                    for (int j = 0; j < parPartidos.size(); j++) {
                        if (parPartidos[j].getClave() == (i1B * 10) + i) {
                            if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                iPL += 3;
                            }
                            else if (parPartidos[j].ganador() == jugJugadores[i1B].getNombre())
                                iPV += 3;
                            else {
                                iPV++;
                                iPL++;
                            }
                            iGFV = parPartidos[j].getMLocal();
                            iGCL = parPartidos[j].getMLocal();
                            iGCV = parPartidos[j].getMVisitante();
                            iGFL = parPartidos[j].getMVisitante();
                            j += 1000;
                        }
                    }
                    
                    if (iPL > iPV) {
                        i1B = i;
                        if (empateTodo1) {
                            empateTodo1 = false;
                        }
                    }
                    else if (iPL == iPV) {
                        if (iGFL > iGFV) {
                            i1B = i;
                            if (empateTodo1) {
                                empateTodo1 = false;
                            }
                        }
                        else if (iGFL == iGFV){
                            if (iGCL > iGCV) {
                                i1B = i;
                                if (empateTodo1) {
                                    empateTodo1 = false;
                                }
                            }
                            else if (iGCL == iGCV) {
                                empateTodo1 = true;
                                int iRand = rand() % 2;
                                if (iRand == 0) {
                                    i1B = i;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (empateTodo1) {
        cout << "El ganador del primer lugar del grupo 2 se eligió de manera aleatoria" << endl;
    }
    
    empateTodo1 = false;
    
    if (i1B == (iN / 2)) {
        i2B = (iN / 2) + 1;
    }
    else
        i2B = (iN / 2);
    
    for (int i = iN / 2; i < iN; i++) {
        if ((i != i1B) && (i != i2B)) {
            if (jugJugadores[i].getPuntos() > jugJugadores[i2B].getPuntos()) {
                i2B = i;
                if (empateTodo1) {
                    empateTodo1 = false;
                }
            }
            else if (jugJugadores[i].getPuntos() == jugJugadores[i2B].getPuntos()) {
                if (jugJugadores[i].getGolesF() > jugJugadores[i2B].getGolesF()) {
                    i2B = i;
                    if (empateTodo1) {
                        empateTodo1 = false;
                    }
                }
                else if (jugJugadores[i].getGolesF() == jugJugadores[i2B].getGolesF()) {
                    if (jugJugadores[i].getGolesC() > jugJugadores[i2B].getGolesC()) {
                        i2B = i;
                        if (empateTodo1) {
                            empateTodo1 = false;
                        }
                    }
                    else if (jugJugadores[i].getGolesC() == jugJugadores[i2B].getGolesC()){
                        int iPL = 0, iPV = 0, iGFL = 0, iGFV = 0, iGCL = 0, iGCV = 0;
                        
                        for (int j = 0; j < parPartidos.size(); j++) {
                            if (parPartidos[j].getClave() == (i * 10) + i2B) {
                                if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                    iPL += 3;
                                }
                                else if (parPartidos[j].ganador() == jugJugadores[i2B].getNombre())
                                    iPV += 3;
                                else {
                                    iPV++;
                                    iPL++;
                                }
                                iGFL = parPartidos[j].getMLocal();
                                iGCV = parPartidos[j].getMLocal();
                                iGCL = parPartidos[j].getMVisitante();
                                iGFV = parPartidos[j].getMVisitante();
                                j += 1000;
                            }
                        }
                        
                        for (int j = 0; j < parPartidos.size(); j++) {
                            if (parPartidos[j].getClave() == (i2B * 10) + i) {
                                if (parPartidos[j].ganador() == jugJugadores[i].getNombre()) {
                                    iPL += 3;
                                }
                                else if (parPartidos[j].ganador() == jugJugadores[i2B].getNombre())
                                    iPV += 3;
                                else {
                                    iPV++;
                                    iPL++;
                                }
                                iGFV = parPartidos[j].getMLocal();
                                iGCL = parPartidos[j].getMLocal();
                                iGCV = parPartidos[j].getMVisitante();
                                iGFL = parPartidos[j].getMVisitante();
                                j += 1000;
                            }
                        }
                        
                        if (iPL > iPV) {
                            i2B = i;
                            if (empateTodo1) {
                                empateTodo1 = false;
                            }
                        }
                        else if (iPL == iPV) {
                            if (iGFL > iGFV) {
                                i2B = i;
                                if (empateTodo1) {
                                    empateTodo1 = false;
                                }
                            }
                            else if (iGFL == iGFV){
                                if (iGCL > iGCV) {
                                    i2B = i;
                                    if (empateTodo1) {
                                        empateTodo1 = false;
                                    }
                                }
                                else if (iGCL == iGCV) {
                                    empateTodo1 = true;
                                    int iRand = rand() % 2;
                                    if (iRand == 0) {
                                        i2B = i;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (empateTodo1) {
        cout << "El ganador del segundo lugar del grupo 2 se eligió de manera aleatoria" << endl;
    }
    
    muestraGrupos(iN);
    
    cout << "El primer lugar del grupo 1 es: " << jugJugadores[i1A].getNombre() << endl;
    cout << "El segundo lugar del grupo 1 es: " << jugJugadores[i2A].getNombre() << endl;
    cout << "El primer lugar del grupo 2 es: " << jugJugadores[i1B].getNombre() << endl;
    cout << "El segundo lugar del grupo 2 es: " << jugJugadores[i2B].getNombre() << endl;
    
    jugJugadoresF.push_back(jugJugadores[i1A]);
    jugJugadoresF.push_back(jugJugadores[i2A]);
    jugJugadoresF.push_back(jugJugadores[i1B]);
    jugJugadoresF.push_back(jugJugadores[i2B]);
    
    for (int i = 0; i < jugJugadoresF.size(); i++) {
        jugJugadoresF[i].resetPuntos();
    }

}

void finales(int iPartidosG) {
    int iOpcion, iPartidos = 0;
    Partido parAux;
    string sAux;
    
    random_shuffle(jugJugadoresF.begin(), jugJugadoresF.end());
    // Partido 1
    parAux.setLocal(jugJugadoresF[0].getNombre());
    parAux.setVisitante(jugJugadoresF[1].getNombre());
    parAux.setClave(01);
    parPartidosF.push_back(parAux);
    // Partido 2
    parAux.setLocal(jugJugadoresF[1].getNombre());
    parAux.setVisitante(jugJugadoresF[0].getNombre());
    parAux.setClave(10);
    parPartidosF.push_back(parAux);
    // Partido 3
    parAux.setLocal(jugJugadoresF[2].getNombre());
    parAux.setVisitante(jugJugadoresF[3].getNombre());
    parAux.setClave(23);
    parPartidosF.push_back(parAux);
    // Partido 4
    parAux.setLocal(jugJugadoresF[3].getNombre());
    parAux.setVisitante(jugJugadoresF[2].getNombre());
    parAux.setClave(32);
    parPartidosF.push_back(parAux);
    
    random_shuffle(parPartidosF.begin(), parPartidosF.end());
    
    do {
        cout << "Selecciona la opción deseada:" << endl;
        cout << "1. Mostrar partidos" << endl;
        cout << "2. Ingresar marcador" << endl;
        cin >> iOpcion;
        switch (iOpcion) {
            case 1:
                muestraPartidosF();
                break;
            case 2:
                ingresaMarcadorF();
                iPartidos++;
                if (iPartidos == 4) {
                    final();
                    iOpcion = 3;
                }
                break;
            default:
                break;
        }
    } while (iOpcion != 3);
}

void grupos(int iN){
    int iOpcion, iPartidos = 0;
    do {
        cout << "Selecciona la opción deseada:" << endl;
        cout << "1. Mostrar grupos" << endl;
        cout << "2. Mostrar partidos" << endl;
        cout << "3. Ingresar marcador" << endl;
        if (iPartidos >= parPartidos.size()) {
            cout << "4. Pasar a la siguiente ronda" << endl;
        }
        cin >> iOpcion;
        switch (iOpcion) {
            case 1:
                muestraGrupos(iN);
                break;
            case 2:
                muestraPartidos();
                break;
            case 3:
                ingresaMarcador();
                iPartidos++;
                break;
            case 4:
                if (iPartidos >= parPartidos.size()) {
                    generaFinalistas(iN);
                }
                break;
            case 45:
                cout << "Seguro quieres pasar a la siguiente ronda? 4 Si, cualquier número para No" << endl;
                cin >> iOpcion;
                if (iOpcion == 4) {
                    generaFinalistas(iN);
                }
            default:
                break;
        }
    } while (iOpcion != 4);
    finales(parPartidos.size());
}

int main() {
    string sAux;
    int iN = 4, iOpcion, iAux;
    ifstream ifTabla;
    Jugador jugAux;
    
    ifTabla.open("tabla.txt");
    while (ifTabla >> sAux) {
        jugAux.setNombre(sAux);
        ifTabla >> iAux;
        jugAux.setPJ(iAux);
        ifTabla >> iAux;
        jugAux.setGolesF(iAux);
        ifTabla >> iAux;
        jugAux.setGolesC(iAux);
        ifTabla >> iAux;
        jugAux.setPuntos(iAux);
        jugJugadoresTabla.push_back(jugAux);
    }
    ifTabla.close();
    
    srand (time(NULL));
    
    cout << "Ingresa número de jugadores: " << endl;
    cin >> iN;
    ingresaJugadores(iN);
    
    do {
        cout << "Presiona 1 para grupos o 2 para finales (solo para 4 personas) " << endl;
        cin >> iOpcion;
    } while (iOpcion != 1 && iOpcion != 2);
    
    if (iOpcion == 1) {
        grupos(iN);
    }
    else if (iOpcion == 2)
        finales(0);
    
    
    return 0;
}
