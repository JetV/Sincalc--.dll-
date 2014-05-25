#ifndef SINCALC_H
#define SINCALC_H

#include "sincalc_global.h"
#include <math.h>
#include <QDebug> //TODO: Убрать



extern "C" SINCALCSHARED_EXPORT
struct UsrParm {
    double InitVal;
    double TmSec;
    double Stp;
    int BdyNum;
    double PhsCoeff;
    double AmpCoeff;
    int PlotType;
};


extern "C" SINCALCSHARED_EXPORT
double Focus(double y,double t);

extern "C" SINCALCSHARED_EXPORT
double Interact(int r1, int r2, double k1, double A);

extern "C" SINCALCSHARED_EXPORT
double Radial(double y);

extern "C" SINCALCSHARED_EXPORT
void EulerCalc(UsrParm UP); // TODO: Принимает в качестве параметра структуру со всеми данными
//для вычисления от пользователя

extern "C" SINCALCSHARED_EXPORT
double SinCalc(double x, UsrParm UP);//Тестовая функция

#endif // SINCALC_H
