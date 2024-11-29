#include "MyBD.h"
//===========================================MyData===========================
MyData::MyData(const MyData& other) :  sex (other.sex),m_age(other.m_age), m_job( other.m_job),	m_salary (other.m_salary) {}


MyData& MyData:: operator=(const MyData& other) {
//	MyData a;													
	if (this != &other) {
		this->sex = other.sex; 
		this->m_age = other.m_age;
		this->m_salary = other.m_salary;
		this->m_job = other.m_job;
	} 
	return *this;
}


MyData::MyData(MyData&& tmp) : sex(tmp.sex), m_age(tmp.m_age), m_salary(tmp.m_salary), m_job(std::move(tmp.m_job)) {}

MyData& MyData::operator=(MyData&& tmp) {
	this->sex = tmp.sex;
	this->m_age = tmp.m_age;
	this->m_salary = tmp.m_salary;
	this->m_job = std::move( tmp.m_job);
	//tmp.m_job = nullptr;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const MyData& data) {
	out << "\tSex: " << ((data.sex==0)? "Undef": ((data.sex == 1) ? "Male": "Female")) << "\t Age: " << data.m_age << "\t Job: " << data.m_job << "\t Salary: " << data.m_salary << "";
	return out;
}

void MyData::operator()(Sex s, size_t age, const char* job, float sal) {
	sex = s;
	m_age = age;
	m_job = job;
	m_salary = sal;
}

void MyData::operator()(int s, size_t age, const char* job, float sal) {
	sex = static_cast<Sex>(s % 3);
	m_age = age;
	m_job = job;
	m_salary = sal;
}
//===========================================Pair===========================


Pair::Pair(const Pair& other) : key(other.key), pData(other.pData)	{}

Pair& Pair::operator=(const Pair& ref) {
	key = ref.key;
	pData = ref.pData;
	return *this;
}

Pair::Pair(Pair&& other) : key(other.key), pData(std::move(other.pData)) {}

Pair& Pair:: operator=(Pair&& other) {
	key = std::move( other.key );
	pData = std::move(other.pData);
//	other.pData = nullptr;
	return *this;
}

bool Pair::operator==(const char* k) const {
	return ((strcmp(this->key.GetString(), k)) == 0);
}

void Pair::operator()(MyString k, const MyData& d) {
	key = k;
	pData = d;
}

std::ostream& operator<<(std::ostream& out, const Pair& pair) {
	out << "Name: " << pair.key <<" " << pair.pData;
	return out;
}

//===========================Base==========================
int Base::name_number = 0;

Base:: Base(const Base& bd) {

	pBase = nullptr;
	count = bd.count; capacity = bd.count;
	if (count) {
		pBase = new Pair * [count];
		for (int i = 0; i < count; i++) {
			pBase[i] = new Pair(*bd.pBase[i]);
		}
	}
	name_number++;
	name = name_number;
}

Base::Base(Base&& bd) {

	pBase = bd.pBase;  
	count = bd.count; 
	capacity = bd.count;
	name_number++;
	name = name_number;
	
	
	bd.pBase = nullptr;
	bd.count = 0;
	bd.capacity = 0;
}



Base& Base::operator=(const Base& bd) {   
	if (this != &bd) {
			
			{													
				for (int i = 0; i < count; i++) {
					pBase[i] = nullptr;
					delete pBase[i]; 
				}
				pBase = nullptr;
				delete[] pBase;   
			}
			

			if (bd.count) {
				pBase = new Pair * [bd.count];
				for (int i = 0; i < bd.count; i++) {
					pBase[i] = new Pair(*bd.pBase[i]);
				}
			}
			
		count = bd.count;
		capacity = bd.count;
		

	}
	return *this;
}



Base& Base::operator=(Base&& bd) {  
	if (this != &bd) {


		{  
			for (int i = 0; i < count; i++) { 
				pBase[i] = nullptr;
				delete pBase[i]; 
			}    
			pBase = nullptr;
			delete[] pBase; 
		}
		
	

		count = bd.count;						
		capacity = bd.capacity;
		pBase = std::move(bd.pBase);


		bd.pBase = nullptr;
		bd.count = 0;
		bd.capacity = 0;
	}
	return *this;
}

MyData& Base::operator[](const char* key) {

	for (size_t i = 0; i < count; i++) {
		if (*pBase[i] == key) 
			return pBase[i]->pData  ;
	}

	if(count >= capacity) {
		//перераспределяем память
		int zapas = 2;
		capacity += zapas;
		Pair** tmp = new Pair * [capacity];
		for (int i = 0; i < (capacity - zapas); i++) {
		
				tmp[i] = pBase[i];
		
			}
		delete[] pBase;
		pBase = tmp;
		}
	
//	//добавляем сотрудника

	pBase[count] = new Pair(key, MyData());
	pBase[count]->key = key;

	return pBase[count++]->pData;
}


std::ostream& operator<<(std::ostream& out, const Base& bd) {
	out << '\n'<<"Base#"<<bd.name<<'\n';
	for (int i = 0; i < bd.count; i++)
		out << bd.pBase[i][0] << "\n";

	return out;
}

int Base::deletePair(const char* nameDel) {  
	for (size_t i = 0; i < count; i++) 
		if (*pBase[i] == nameDel) {
		
			delete pBase[i];
			for (i; i < count - 1; i++) {
				pBase[i] = pBase[i + 1];
			}

		}
	return count--;
}

void Base::Sort() {
	if (count > 0) {
		Pair* tmp; 
		for (int i = 0; i < count-1; i++) {
			for (int j = 0; j < count -1- i; j++) {
				int sravnenie = 0;
				sravnenie = strcmp(static_cast<char*>(pBase[j]->key), static_cast<char*>(pBase[j + 1]->key));
				if (sravnenie > 0) {
					tmp = pBase[j + 1];
					pBase[j + 1] = pBase[j];
					pBase[j] = tmp;
				}
			}
		}
	}
}


Base::~Base() {

	for (int i = 0; i < count; i++) {
		pBase[i] = nullptr;
		delete pBase[i];
	}
	pBase = nullptr;
	delete[] pBase;   
}