#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
class Data
{
public:
    Data();
    ~Data();
    virtual void Create();
    void inicialization();
    virtual void print();
protected:
    int** c;//Матрица стоимости 
    int* a;//количество поставки, размер 
    int* b;//количество потребности магазинов
    int rows;//строчки матрицы
    int cols;//столбцы

};



class NWcorner :public Data
{
private:
    int** X; //Матрица СЗ
    int** W; //Матрица потенциалов
    int* u;
    int* v;
public:
    NWcorner();
    ~NWcorner();

    void Potential(); // высчит потенциалов
    void Calculate(); // Рассчет 
    void Correct(int i,int j);// Циклы из t
    void print();
    void Optimal();
    void Create();
};



