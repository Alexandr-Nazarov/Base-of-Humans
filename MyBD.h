#pragma once
#include <iostream>
#include "myString.h"
enum Sex { UNDEF, MALE, FMALE };
class MyData {
public:
	enum Sex { UNDEF, MALE, FMALE };
private:
	Sex sex;
	size_t m_age;
	MyString m_job;
	float m_salary;
public: 
	MyData() { sex = UNDEF; m_age = 0; m_salary = 0; m_job = "undef"; }
	MyData(Sex s, size_t age, const char* job, float sal) { sex = s; m_age = age; m_job = job; m_salary = sal; }  
	~MyData() {}
	MyData(const MyData& d); 
    MyData& operator=(const MyData& d); 
	MyData(MyData&& d);
	MyData& operator=(MyData&& d);
	friend std::ostream& operator<<(std::ostream& os, const MyData& d); 

	
	MyData(int s, size_t age, const char* job, float sal) { sex = static_cast<Sex>(s%3); m_age = age; m_job = job; m_salary = sal; }
	void operator()(Sex s, size_t age, const char* job, float sal);
	void operator()(int s, size_t age, const char* job, float sal);
	
};



class Pair {

	MyString key; //ключ - фамилия
	MyData pData; // 

	Pair() { }
	Pair(const char* k, const MyData& d) : key(k), pData (d){}
	~Pair() {/*if (pData != nullptr)	delete[] pData;*/}
	Pair(const Pair& other);
	Pair& operator=(const Pair& other);
	Pair(Pair&& other);
	Pair& operator=(Pair&& other);
	bool operator==(const char* k) const;
	friend class Base;
	friend std::ostream& operator<<(std::ostream& os, const Pair& pair);
	

	void operator()(MyString k, const MyData&d);
};




class Base {
	size_t count; //количество элементов в базе
	size_t capacity; //емкость базы

	Pair **pBase; //указатель на базу данных
	static int name_number;
	int name;
public:
	
	Base() {
		count = 0;
		capacity = 0;
		pBase = nullptr;
		name_number++;
		name = name_number;
	}
	Base(const Base& bd);
    Base& operator=(const Base& bd);
	Base(Base&& bd);
	Base& operator=(Base&& bd);
    MyData& operator[](const char* key);
	int deletePair(const char* key);
	friend std::ostream& operator<<(std::ostream& os, const Base& bd);

	
	void Sort();
	~Base();
};
