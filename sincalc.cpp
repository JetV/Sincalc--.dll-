#include "sincalc.h"

//extern "C" SINCALCSHARED_EXPORT

extern "C" SINCALCSHARED_EXPORT
double Focus(double y,double t)
{
    //qDebug()<<"Focus"<<endl;
    return 0; // -y*sin(t);
}

extern "C" SINCALCSHARED_EXPORT
double Interact(int r1, int r2, double k1, double A) //TODO: новые параметры функции взаимодействия
//double Interact(int r1, int r2)
{

    //double k1 = 5.1;

    if (r1<=r2)
    {
        //qDebug()<<"Interact 1"<<endl;
        return 0;
    }
    else
    {
        //qDebug()<<"Interact 2"<<endl;
        return A*sin(k1*(r1-r2));
    }
}

extern "C" SINCALCSHARED_EXPORT
double Radial(double y)
{
    //qDebug()<<"Radial"<<endl;
    return y;
}


extern "C" SINCALCSHARED_EXPORT
void EulerCalc(UsrParm UP) // TODO: Принимает в качестве параметра структуру со всеми данными
//для вычисления от пользователя
{
    qDebug()<<"Start"<<endl;
    //Зависимые переменные функции
    double T = UP.TmSec;
    double h = UP.Stp;
    int N = UP.BdyNum;


    //Собственные переменные функции
    int M = T/h; //TODO: Проверить приведение типов! Шаг пока всегда должен быть кратен 10!!
    double l = 1/N, s = 0, WkForceCur = 0, WkForceNext = 0, y1 = 0, z1 = 0;;

    double **ptrZ = new double* [N]; // N строки в массиве
    for (int count = 0; count < N; count++)
        ptrZ[count] = new double [M]; // и M столбцов

    double **ptrY = new double* [N]; // N строки в массиве
    for (int count = 0; count < N; count++)
        ptrY[count] = new double [M]; // и M столбцов

    for (int count_row = 0; count_row<N; count_row++)
        for (int count_col = 0; count_col<M; count_col++)
            ptrY[count_row][count_col] = UP.InitVal;


    double *ptr_z = new double [N];

    for (int i = 0 ; i<N; i++)
        for (int j = 0; j<M-2; j++)
        {
            if (j>1)
                WkForceCur = WkForceNext;

            for (int k = 0; k<i; k++)
            {
                WkForceCur = WkForceCur + Radial(ptrY[k][j])*Interact(i, k, UP.PhsCoeff, UP.AmpCoeff);
                s = Interact(l*i,l*k,  UP.PhsCoeff, UP.AmpCoeff);
                y1 = ptrY[i][j] + h*ptrZ[i][j];
                z1 = ptrZ[i][j] + h*Focus(ptrY[i][j],h*j);

                for (int m = 0; m<i-1; m++)
                    WkForceNext = WkForceNext + Radial(ptrY[k][j+1])*Interact(l*i,l*k,  UP.PhsCoeff, UP.AmpCoeff);

                ptrY[i][j+1] = ptrY[i][j] + (h/2)*(ptrZ[i][j]+z1);
                ptrZ[i][j+1] = ptrZ[i][j] + (h/2)*((Focus(ptrY[i][j],h*j)) + Focus(y1,h*(j+1)) + WkForceCur + WkForceNext);
            }
        }
    y1 = 0;
    z1 = 0;
    qDebug()<<"Stop"<<endl;
    return;
}

extern "C" SINCALCSHARED_EXPORT
double SinCalc(double x, UsrParm UP)//Тестовая функция
{
    double y = sin(x);

    EulerCalc(UP);
    return y;

}

