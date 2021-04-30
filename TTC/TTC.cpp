#include "TTC.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
int comp(const void*, const void*);
Data::Data()
{
    cout << "������� ������ ����� � ��������" << endl;
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
    cout << "������� ���������� �������" << endl;
    for (int i = 0; i < rows; i++)
    {
        cin >> this->a[i];
    }
    cout << "������� ����������� � �������" << endl;

    for (int i = 0; i < cols; i++)
    {
        cin >> this->b[i];
    }
    cout << "������� ������� ���������" << endl;

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
    cout << "���������� ������� ������� �������� " << endl;
    for (int i = 0; i < this->rows; i++)
    {
        cout << this->a[i] << ",";
    }
    cout << endl;
    cout << "���������� ������� ������ �� ������� " << endl;
    for (int i = 0; i < this->cols; i++)
    {
        cout << this->b[i] << ",";
    }
    cout << endl;
    cout << "������� ���������" << endl;
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
  //  delete[] this->u;
    //delete[] this->v;
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
            
            //X[0][j + 1] = -1;

            X[i][j] = a[i];
            i++;
            j++;
        }
    }
    this->print();
    Potential();
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
                    if (X[i][j + q] == -1)
                        X[i][j + q] = 0;
                    if (X[i+r][j + q] == -1)
                        X[i+r][j + q] = 0;
                    if (X[i+r][j] == -1)
                        X[i+r][j] = 0;
                    t=min(min(X[i][j + q], X[i + r][j + q]),min(X[i + r][j],X[i+r][j]));
                    
                    X[i][j] +=t ;
                    X[i+r][j] -= t;
                    X[i][j+q] -= t;
                    X[i+r][j+q] += t;
                    this->print();
                    Potential();
                }
                
            }
            if ((i + r < rows) && (j - q >0 ))
            {
                if ((X[i][j - q] != 0) && (X[i + r][j - q] != 0) && (X[i + r][j] != 0))
                {
                    if (X[i][j - q] == -1)
                        X[i][j - q] = 0;
                    if (X[i + r][j - q] == -1)
                        X[i + r][j - q] = 0;
                    if (X[i + r][j] == -1)
                        X[i + r][j] = 0;
                    t = min(min(X[i][j - q], X[i + r][j - q]), min(X[i + r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i + r][j] -= t;
                    X[i][j - q] -= t;
                    X[i + r][j - q] += t;
                    this->print();
 
                    Potential();
                }
            }
            if ((i - r>0) && (j + q < cols))
            {
                if ((X[i][j + q] != 0) && (X[i - r][j + q] != 0) && (X[i - r][j] != 0))
                {
                    if (X[i][j + q] == -1)
                        X[i][j + q] = 0;
                    if (X[i - r][j + q] == -1)
                        X[i - r][j + q] = 0;
                    if (X[i - r][j] == -1)
                        X[i - r][j] = 0;
                    t = min(min(X[i][j + q], X[i - r][j + q]), min(X[i - r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i - r][j] -= t;
                    X[i][j + q] -= t;
                    X[i - r][j + q] += t;
                    this->print();
                    Potential();
                }
            }
            if ((i - r>0 ) && (j - q > 0))
            {
                if ((X[i][j - q] != 0) && (X[i - r][j - q] != 0) && (X[i - r][j] != 0))
                {
                    if (X[i][j - q] == -1)
                        X[i][j - q] = 0;
                    if (X[i - r][j - q] == -1)
                        X[i - r][j - q] = 0;
                    if (X[i - r][j] == -1)
                        X[i - r][j] = 0;
                    t = min(min(X[i][j - q], X[i - r][j - q]), min(X[i - r][j], X[i+r][j]));
                    
                    X[i][j] += t;
                    X[i - r][j] -= t;
                    X[i][j - q] -= t;
                    X[i - r][j - q] += t;
                    this->print();
                    Potential();
                }
            }
        }
        
        
    }
}
void NWcorner::Potential()
{
    u = new int[rows];
    v = new int[cols];
    u[0] = 0;
    for (int i = 0, j = 0; i < rows;i++)
    {
        j = 0;
        
        if (X[i][j] < 0)
        {
            v[j] = c[i][j] - u[i];
            
            j++;
        }
        while (X[i][j] == 0)
            j++;
        if (i != 0)
        {
            
            u[i] = c[i][j] - v[j];

        }
            
        for (; j < cols;)
        {
            if (X[i][j] < 0)
            {
                v[j] = c[i][j] - u[i];
                
                j++;
            }
            while (X[i][j] == 0)
                j++;
            v[j] = c[i][j] - u[i];
            j++;
        }
    }
    for (int i = 0; i < rows; i++)
        cout << "u" << i<<"=" << u[i] << endl;
    cout << endl;
    for (int i = 0; i < cols; i++)
        cout << "v" << i <<"="<< v[i] << endl;
    Optimal();
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
    //u = new int[rows];
   // v = new int[cols];
    
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
    cout << "������� �������������:" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->W[i][j] << "  ";
        }
        cout << endl;
    }
    int s=0;
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

        qsort(op, s, sizeof(int), comp);
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (W[i][j] > c[i][j])
                {
                    if (W[i][j] - c[i][j] == op[s - 1])
                    {
                        delete[] op;
                        delete[] this->u;
                        delete[] this->v;
                        Correct(i, j);
                        
                        
                    }
                }
    }
    
    if (s == 0)
        cout << "������� ����������";
    
    // ������� ������ ������� ,������� ����� ������� �� �������������� ,� ��� � ���� ������� ��������� ������� ��������� ������� 
}

void NWcorner::print()
{
    cout << "������� ������-��������� ����" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->X[i][j] << "  ";
        }
        cout << endl;
    }
}
int comp(const void* i, const void* j)
{
    return *(int*)i - *(int*)j;
}