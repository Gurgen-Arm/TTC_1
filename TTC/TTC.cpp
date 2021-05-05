#include "TTC.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Data::Data()
{
    cout << "Iput rows and cols" << endl;
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
    cout << "Input quantity of products" << endl;
    for (int i = 0; i < rows; i++)
    {
        cin >> this->a[i];
    }
    cout << "Input quantity of consumers" << endl;

    for (int i = 0; i < cols; i++)
    {
        cin >> this->b[i];
    }
    cout << "Input cost matrix" << endl;

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
    cout << "a: " << endl;
    for (int i = 0; i < this->rows; i++)
    {
        cout << this->a[i] << ",";
    }
    cout << endl;
    cout << "b: " << endl;
    for (int i = 0; i < this->cols; i++)
    {
        cout << this->b[i] << ",";
    }
    cout << endl;
    cout << "c:" << endl;
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

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            this->X[i][j] = 0;
        }
    }

}
void NWcorner::Calculate()
{
    for (int i = 0, j = 0; (i < rows) && (j < cols); )
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
            if(i!=rows-1&&j!=cols-1)
                X[i+1][j] = -1;
            //cout << "Я вызвался"<<i<<" "<<j << endl;
            X[i][j] = a[i];
            i++;
            j++;
        }
    }
    this->print();
    Potential();
}
void NWcorner::Potential()
{
    u = new int[rows];
    v = new int[cols];
    for (int i = 0; i < rows; i++)
        u[i] = 0;
    for (int j = 0; j < cols; j++)
        v[j] = 0;
    //filling potentials
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {

            if ((i >= 1) && (j == 0))
                for (int cj = 0; cj < cols; cj++)
                {
                    if ((X[i][cj] != 0) && (v[cj] != 0) && (c[i][j] != u[i] + v[j]))
                    {
                        u[i] = c[i][cj] - v[cj];
                        break;
                    }
                }
            if (X[i][j] == -1)
                v[j] = c[i][j] - u[i];
            if (X[i][j] == 0)
                continue;
            if ((v[j] == 0) && (c[i][j] != u[i] + v[j]))
                v[j] = c[i][j] - u[i];
          
        }
    for (int i = 0; i < rows; i++)
        cout << "u" << i << ":" << u[i] << endl;
    for (int j = 0; j < cols; j++)
        cout << "v" << j << ":" << v[j] << endl;
    Optimal();
   
}
void NWcorner::Optimal()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            W[i][j] = u[i] + v[j];
    cout << "Matrix of optimal:" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->W[i][j] << "  ";
        }
        cout << endl;
    }
    int s = 0;
    int* op;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (W[i][j] > c[i][j])
                s++;
    if (s > 0)
    {
        op = new int[s];
        for (int i = 0; i < s; i++)
            op[i] = 0;
        for (int i = 0, f = 0; (i < rows) && (f < s); i++)
            for (int j = 0; (j < cols) && (f < s); j++)
                if (W[i][j] > c[i][j])
                {
                    op[f] = W[i][j] - c[i][j];
                    f++;
                }
        int maxEl = op[0];
        for (int g = 0; g < s; g++)
            if (op[g] > maxEl)
                maxEl = op[g];
        
        int Ai = 0;
        int Aj = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (W[i][j] > c[i][j])
                {
                    if ((W[i][j] - c[i][j]) == maxEl)
                    {
                        Ai = i;
                        Aj = j;
                    }
                }

        delete[] op;
        delete[] this->u;
        delete[] this->v;
        Correct(Ai, Aj);
    }

    if (s == 0)
    {

        cout << "Matrix is optimal";
        Sum();
    }



}
void NWcorner::Correct(int i, int j)
{
    int t;
    bool key = false;
    for (int r = 1; r < rows; r++)
    {
        if (key) break;
        for (int q = 1; q < cols; q++)
        {
            if ((i + r < rows) && (j + q < cols) && !key)
            {
                if ((X[i][j + q] != 0) && (X[i + r][j + q] != 0) && (X[i + r][j] != 0))
                {
                    if (X[i][j + q] < 0)
                        X[i][j + q] = 0;
                    else if (X[i + r][j + q] < 0)
                        X[i + r][j + q] = 0;
                    else if (X[i + r][j] < 0)
                        X[i + r][j] = 0;
                    t = min(X[i][j+q],X[i+r][j]);
                    
                    X[i][j] += t;
                    X[i + r][j + q] += t;
                    X[i + r][j] -= t;
                    X[i][j + q] -= t;
                    if (X[i][j + q] == X[i + r][j])
                        X[i][j + q] = -1;
                    
                    this->print();
                    key = true;
                    break;
                }

            }
            if ((i + r < rows) && (j - q >= 0) && !key)
            {
                if ((X[i][j - q] != 0) && (X[i + r][j - q] != 0) && (X[i + r][j] != 0))
                {
                    if (X[i][j - q] < 0)
                        X[i][j - q] = 0;
                    else if (X[i + r][j -q] < 0)
                        X[i + r][j - q] = 0;
                    else if (X[i + r][j] < 0)
                        X[i + r][j] = 0;
                    t = min(X[i][j - q], X[i + r][j]);

                    X[i][j] += t;
                    X[i + r][j - q] += t;
                    X[i + r][j] -= t;
                    X[i][j - q] -= t;
                    if (X[i][j - q] == X[i + r][j])
                        X[i][j - q] = -1;
                    this->print();
                    key = true;
                    break;
                }


            }
            if ((i - r >= 0) && (j + q < cols))
            {
                if ((X[i][j + q] != 0) && (X[i - r][j + q] != 0) && (X[i - r][j] != 0))
                {
                    if (X[i][j + q] < 0)
                        X[i][j + q] = 0;
                    else if (X[i - r][j + q] < 0)
                        X[i - r][j + q] = 0;
                    else if (X[i - r][j] < 0)
                        X[i - r][j] = 0;
                    t = min(X[i][j + q], X[i - r][j]);

                    X[i][j] += t;
                    X[i - r][j + q] += t;
                    X[i - r][j] -= t;
                    X[i][j + q] -= t;
                    if (X[i-r][j] == X[i][j+q])
                        X[i-r][j] = -1;
                    this->print();
                    key = true;
                    break;
                }

            }
            if ((i - r >= 0) && (j - q > 0) && !key)
            {
                if ((X[i][j - q] != 0) && (X[i - r][j - q] != 0) && (X[i - r][j] != 0))
                {
                    if (X[i][j - q] < 0)
                        X[i][j - q] = 0;
                    else if (X[i - r][j - q] < 0)
                        X[i - r][j - q] = 0;
                    else if (X[i - r][j] < 0)
                        X[i - r][j] = 0;
                    t = min(X[i][j - q],  X[i - r][j]);

                    X[i][j] += t;
                    X[i - r][j - q] += t;
                    X[i - r][j] -= t;
                    X[i][j - q] -= t;
                    if (X[i-r][j] == X[i][j-q])
                        X[i-r][j] = -1;
                    this->print();
                    key = true;
                    break;
                }

            }
        }
    }
    Potential();
}


void NWcorner::Sum()
{
    int sum = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (X[i][j] >= 0)
                sum += X[i][j] * c[i][j];
            else
                sum += 0;
        }
    cout << "cost of transport = " << sum;
}


void NWcorner::print()
{
    cout << "NW corner matrix" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            if(X[i][j]>=0)
                cout << this->X[i][j] << "  ";
            else
                cout << "0" << "  ";
        }
        cout << endl;
    }
}

