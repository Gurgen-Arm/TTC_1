#include "TTC.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
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
    Optimal();
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
            
            X[0][j + 1] = -1;

            X[i][j] = a[i];
            i++;
            j++;
        }
    }
}
void NWcorner::Correct(int i,int j)
{
    
    int t;
    for (int r = 1; r < rows; r++)
    {
        for (int q = 1; q < cols; q++)
        {
            if ((i + r < rows) && (j + q < cols))
            {
                if((X[i][j+q]!=0)&&(X[i+r][j+q]!=0)&&(X[i+r][j]!=0))
                {
                    t=min(min(X[i][j + q], X[i + r][j + q]),min(X[i + r][j],X[i+r][j]));
                    
                    X[i][j] +=t ;
                    X[i+r][j] -= t;
                    X[i][j+q] -= t;
                    X[i+r][j+q] += t;
                    this->print();
                }
                
            }
            if ((i + r < rows) && (j - q < cols))
            {
                if ((X[i][j - q] != 0) && (X[i + r][j - q] != 0) && (X[i + r][j] != 0))
                {
                    t = min(min(X[i][j - q], X[i + r][j - q]), min(X[i + r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i + r][j] -= t;
                    X[i][j - q] -= t;
                    X[i + r][j - q] += t;
                    this->print();
                }
            }
            if ((i - r < rows) && (j + q < cols))
            {
                if ((X[i][j + q] != 0) && (X[i - r][j + q] != 0) && (X[i - r][j] != 0))
                {
                    t = min(min(X[i][j + q], X[i - r][j + q]), min(X[i - r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i - r][j] -= t;
                    X[i][j + q] -= t;
                    X[i - r][j + q] += t;
                    this->print();
                }
            }
            if ((i - r < rows) && (j - q < cols))
            {
                if ((X[i][j - q] != 0) && (X[i - r][j - q] != 0) && (X[i - r][j] != 0))
                {
                    t = min(min(X[i][j - q], X[i - r][j - q]), min(X[i - r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i - r][j] -= t;
                    X[i][j - q] -= t;
                    X[i - r][j - q] += t;
                    this->print();
                }
            }
        }
        
        
    }
}
void NWcorner::Potential()
{
    u[0] = 0;
    for (int i = 0, j = 0; i < rows;i++)
    {
        j = 0;
        
        if (X[i][j] < 0)
        {
            v[j] = c[i][j] - u[i];
            X[i][j] = 0;
            j++;
        }
        while (X[i][j] == 0)
            j++;
        if (i != 0)
            u[i] = c[i][j] - v[j];
        for (; j < cols;)
        {
            if (X[i][j] < 0)
            {
                v[j] = c[i][j] - u[i];
                X[i][j] = 0;
                j++;
            }
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
            W[i][j] = u[i] + v[j];
    cout << "Матрица Оптимальности:" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->W[i][j] << "  ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (W[i][j] > c[i][j])
                Correct(i, j);
         
    
    // создать булеву функцию ,которая будет следить за оптимальностью ,а это в свою очередь запускает процесс остальных функций 
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