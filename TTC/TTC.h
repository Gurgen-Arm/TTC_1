#pragma once
#include <iostream>
#include <cstdlib>
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
    int** c;//������� ��������� 
    int* a;//���������� ��������, ������ 
    int* b;//���������� ����������� ���������
    int rows;//������� �������
    int cols;//�������

};



class NWcorner :public Data
{
private:
    int** X; //������� ��
    int** W; //������� �����������
    int* u;
    int* v;
public:
    NWcorner();
    ~NWcorner();

    void Potential(); // ������ �����������
    void Calculate(); // ������� 
    void Correct(int i,int j);// ����� �� t
    void print();
    void Optimal();
    void Create();
    void Sum();
};



