#pragma once

using namespace std;

class Converter
{
public:
    operator int()
    {
        return (int)this; // (int)*this - endless recursion, stack overflow
    }
};

class AAA
{
public:
    AAA(int n)
    {
        _ai = new int[n];
    }

    ~AAA()
    {
        delete _ai;
    }

private:
    int* _ai;
};


class BBB : public AAA
{
public:
    BBB(int k) : AAA(k)
    {
        _ac = new char[k];
    }

    ~BBB()
    {
        delete _ac;
    }

private:
    char* _ac;
};


class Base
{
public:
    Base() { init(); }
    ~Base() {}

    virtual void log() = 0;

private:
    void init() { log(); }
};

class Derived : public Base
{
public:
    Derived() {}
    ~Derived() {}

    virtual void log() { std::cout << "Derived created" << std::endl; }
};

template<typename T>
void typeInferer(T&& param)
{
}
