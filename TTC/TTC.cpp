#include "TTC.h"
#include <cstdlib>
#include <iostream>
Data::Data()
{
    cout << "Введите размер строк и столбцов" << endl;
    cin >> this->rows;
    cin >> this->cols;
    Create();
    inicialization();
}
void Data::Create()
{
    c = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        c[i] = new int[cols];
    }
    a = new int[rows];
    b = new int[cols];
}
void Data::inicialization()
{
    cout << "Введите количество товаров" << endl;
    for (int i = 0; i < rows; i++)
    {
        cin >> this->a[i];
    }
    cout << "Введите потребность в товарах" << endl;

    for (int i = 0; i < cols; i++)
    {
        cin >> this->b[i];
    }
    cout << "Введите таблицу стоимости" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> this->c[i][j];
        }
    }
}
void  Data::print()
{
    cout << "Количество товаров пунктах доставки " << endl;
    for (int i = 0; i < this->rows; i++)
    {
        cout << this->a[i] << ",";
    }
    cout << endl;
    cout << "Количество товаров нужных на складах " << endl;
    for (int i = 0; i < this->cols; i++)
    {
        cout << this->b[i] << ",";
    }
    cout << endl;
    cout << "Матрица стоимости" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->c[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
Data::~Data()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->c[i];
    }
    delete[] this->c;
    delete[] this->a;
    delete[] this->b;
}

NWcorner::NWcorner() 
{
    Create();
    Calculate();
    print();
    Potential();
}

NWcorner::~NWcorner()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->X[i];
    }
    delete[] this->X;
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->W[i];
    }
    delete[] this->W;
    delete[] this->u;
    delete[] this->v;
}

void NWcorner::Calculate()
{
    for (int i = 0,j=0; (i < rows) && (j < cols); )
    {

        if (b[j] - a[i] < 0)
        {
            X[i][j] = b[j];
            a[i] = a[i] - b[j];
            j++;
        }
        if (b[j] - a[i] > 0)
        {
            X[i][j] = a[i];
            b[j] = b[j] - a[i];
            i++;
        }
        if (b[j] - a[i] == 0)
        {
            X[i][j] = a[i];
            i++;
            j++;
        }
    }
}
void NWcorner::Correct(int i,int j)
{
    for (int r = 0; r < rows; r++)
    {
        for (int q = 0; q < cols; q++)
        {

        }
    }
}
void NWcorner::Potential()
{
    u[0] = 0;
    for (int i = 0, j = 0; i < rows;i++)
    {
        j = 0;
        if (X[i][j] == 0)
            j++;
        if (i != 0)
            u[i] = c[i][j] - v[j];
        for (; j < cols;)
        {
            if (X[i][j] == 0)
                break;
            v[j] = c[i][j] - u[i];
            j++;
        }
    }
    for (int i = 0; i < rows; i++)
        cout << "u" << i<<"=" << u[i] << endl;
    cout << endl;
    for (int i = 0; i < cols; i++)
        cout << "v" << i <<"="<< v[i] << endl;
}
void NWcorner::Create()
{
    X = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        X[i] = new int[cols];
    }
    W = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        W[i] = new int[cols];
    }
    u = new int[rows];
    v = new int[cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
             this->X[i][j]=0;
        }
    }
}
void NWcorner::Optimal()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            W[i][j] = u[i] + v[i];
    if((X[0][0]!=0)&&(W[0][0]>c[0][0]))
        Correct(0,0);
    if ((X[0][cols-1] != 0) && (W[0][cols-1] > c[0][cols-1]))
        Correct(0, cols-1);
    if ((X[rows-1][0] != 0) && (W[rows-1][0] > c[rows-1][0]))
        Correct(rows-1, 0);
    if ((X[rows-1][cols-1] != 0) && (W[rows-1][cols-1] > c[rows-1][cols-1]))
        Correct(rows-1, cols-1);
    // сохдать булеву функцию ,которая будет следить за оптимальностью ,а это в свою очередь запускает процесс остальных функций 
}
void NWcorner::print()
{
    cout << "Матрица Северо-Западного угла" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->X[i][j] << "  ";
        }
        cout << endl;
    }
}