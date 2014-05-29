#include "sincalc.h"
#include <QVector>


extern "C" SINCALCSHARED_EXPORT
double Focus(double y,double t)
{
    //qDebug()<<"Focus"<<endl;
    return 0; // -y*sin(t);
}

extern "C" SINCALCSHARED_EXPORT
double Interact(int r1, int r2, double k1, double A, double len) //TODO: новые параметры функции взаимодействия
//double Interact(int r1, int r2)
{
    //double k1 = 5.1;

    if (r1<=r2)
    {
        return 0;
    }
    else
    {
        //qDebug()<<"Interact = "<<A*sin(k1*(r1-r2))/len;
        return A*sin(k1*(r1-r2))/len;
    }
}

extern "C" SINCALCSHARED_EXPORT
double Radial(double y)
{
    //qDebug()<<"Radial"<<endl;
    return y;
}


extern "C" SINCALCSHARED_EXPORT
double** EulerCalc(UsrParm UP) // TODO: Принимает в качестве параметра структуру со всеми данными
//для вычисления от пользователя
{
    qDebug()<<"Start"<<endl;
    //Зависимые переменные функции
    double T = UP.TmSec;
    double h = UP.Stp;
    int N = UP.BdyNum;
    double x1 = UP.LftEdge;
    double x2 = UP.RgtEdge;

    //Собственные переменные функции
    double dM = T/h; //TODO: Проверить приведение типов! Шаг пока всегда должен быть кратен 10!!
    double length = fabs(x1-x2), WkForceCur = 0, WkForceNext = 0, y1 = 0, z1 = 0;
    double dist = length/(N-1);
    int M = int(dM);

    qDebug()<<"T = "<<T<<"h = "<<h<<"N = "<<N<<"x1 = "<<x1<<"x2 = "<<x2;
    qDebug()<<"M = "<<M<<"length = "<<length<<"dist = "<<dist;

    qDebug()<<"Step 1"<<endl;


    double **ptrZ = new double* [N]; // N строки в массиве
    for (int count = 0; count < N; count++)
        ptrZ[count] = new double [M]; // и M столбцов

    double **ptrY = new double* [N]; // N строки в массиве
    for (int count = 0; count < N; count++)
        ptrY[count] = new double [M]; // и M столбцов

    for (int count_row = 0; count_row<N; count_row++)
        for (int count_col = 0; count_col<M; count_col++)
            ptrY[count_row][count_col] = UP.InitVal;

    qDebug()<<"Step 2"<<endl;
    qDebug()<<"ptrY"<<*ptrY;


    for (int i = 0 ; i<N; i++)

        for (int j = 0; j<M-2; j++)
        {

            WkForceCur = 0;
            WkForceNext = 0;

            for (int k = 0; k<i; k++)//TODO: Поправить длину в циклах
                WkForceCur = WkForceCur + Radial(ptrY[k][j])*Interact(dist*i, dist*k, UP.FrcyCoeff, UP.AmpCoeff, length);

            y1 = ptrY[i][j] + h*ptrZ[i][j];
            z1 = ptrZ[i][j] + h*(Focus(ptrY[i][j],h*j) + WkForceCur);

            //qDebug()<<"Y1 = "<<y1;

            for (int m = 0; m<i-1; m++)
                 WkForceNext = WkForceNext + Radial(ptrY[m][j+1])*Interact(dist*i,dist*m,  UP.FrcyCoeff, UP.AmpCoeff, length);

            ptrY[i][j+1] = ptrY[i][j] + (h/2)*(ptrZ[i][j]+z1);
            ptrZ[i][j+1] = ptrZ[i][j] + (h/2)*((Focus(ptrY[i][j],h*j)) + Focus(y1,h*(j+1)) + WkForceCur + WkForceNext);

            y1 = 0;
            z1 = 0;


        }

    qDebug()<<"Stop = "<<*ptrY;
    return ptrY;
}

extern "C" SINCALCSHARED_EXPORT
double SinCalc(double x, UsrParm UP, double*** resArr)//Тестовая функция
{
    double y = sin(x);

    *resArr = EulerCalc(UP);
    qDebug()<<"Step N"<<endl;
    return y;

}

