#pragma once

#include <memory>

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

class Item
{
public:
	virtual ~Item() { }
	Item(const char* data) : m_data(std::make_unique<std::string>(data)) {  }
	Item(Item&& item) = default; // interview fix: add a move ctor
	virtual const std::string GetContent() const { return m_data ? *m_data : ""; }
private:
	std::unique_ptr<std::string> m_data;
};

class ItemEx : public Item
{
public:
	ItemEx(const char* data, const char* dataEx) : Item(data), m_dataEx(std::make_unique<std::string>(dataEx)) {  }
	ItemEx(ItemEx&& item) = default; // interview fix: add a move ctor
	virtual const std::string GetContent() const override { return Item::GetContent() + (m_dataEx ? *m_dataEx : ""); }
private:
	std::unique_ptr<std::string> m_dataEx;
};

template<typename T>
T BuildFromString(const std::string& s)
{
	T data;
	for (char c : s)
	{
		data.push_back(static_cast<typename T::value_type>(c));
	}
	return data;
}

class Impl;
class Class
{
public:
	Class();
	void DoSomething();
private:
	std::unique_ptr<Impl> m_impl;
};
