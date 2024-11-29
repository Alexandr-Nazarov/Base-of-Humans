#include <string>
#include "myString.h"
using namespace std;

// ќпределение конструктора.
MyString::MyString() {
	m_pStr = nullptr;

}

MyString::MyString(const char* str) {

	m_pStr = nullptr;  
	if (str != nullptr) {
		m_pStr = new char[strlen(str) + 1];
		strcpy(m_pStr, str);
	}
	
}

//методы

const char* MyString::GetString() const {
	
	if (this)
	{
		if (m_pStr) return m_pStr;
		else return "NULL_STRING";
	}
	else return "NULL_Obj";
}





void MyString::SetNewString(const char* str) {
	delete[] m_pStr;
	m_pStr = new char[strlen(str) + 1];
	strcpy(m_pStr, str);
	
}

void  MyString::SetNewString(MyString& str) {
	delete[] m_pStr;
	if (str.m_pStr) {
		m_pStr = new char[strlen(str.GetString()) + 1];
		strcpy(m_pStr, str.GetString());

	}
	else m_pStr = nullptr;
}



//конструктор копировани€
MyString::MyString(const MyString& other) {
	if (other.m_pStr) {
		// delete[] m_pStr;
		m_pStr = new char[strlen(other.m_pStr) + 1];
		strcpy(m_pStr, other.m_pStr);
	}
	else m_pStr = nullptr;
}


//move-конструктор
MyString::MyString(MyString&& tmp) {
		m_pStr = tmp.m_pStr;
		tmp.m_pStr = nullptr;

}


// ќпределение деструктора.
MyString::~MyString() {
	if( m_pStr!=nullptr)
	delete[] m_pStr;
}



 MyString ConcatenString(const char* first, ...) {
	 MyString a;
	 const char** p = &first;
	 int lenght = 0;
	 while (*p) {
		 lenght += strlen(*p);
		 p++;
	 }

	 char* s = new char[lenght + 1];
	 s[0] = 0;
	 p = &first;
	 while (*p) {
		 strcat(s, *p);
		 p++;
	 }

	 a.SetNewString(s);
	 delete[] s;
	 return a;    
 }

 MyString &MyString::operator=(const MyString& str) {
	 if (this != &str) {
		 delete[] this->m_pStr;
		 m_pStr = nullptr;
		 if (str.m_pStr != nullptr) {

			 m_pStr = new char[strlen(str.m_pStr) + 1];
			 strcpy(m_pStr, str.m_pStr);
		 }
	 }
	 return *this;
 }
 
 MyString& MyString::operator=(const char* str) {
	 if (str) {
		 delete[] m_pStr;
		 m_pStr = new char[strlen(str) + 1];
		 strcpy(m_pStr, str);
	 }
	 return *this;
 }

 MyString& MyString::operator=(MyString&& str) {
	 if (str.m_pStr) {
		 if (this != &str) {
			 delete[] this->m_pStr;
			 m_pStr = str.m_pStr;
			 str.m_pStr = nullptr;
			 }
		 }
		 return *this;
 }



 std::ostream& operator<<(std::ostream& out, const MyString& str) {
	 out << str.m_pStr;
	 return out;
 }

MyString MyString::operator+ (const MyString& str)  {

	if (str.m_pStr && m_pStr) {
		char* tmp = new char[strlen(str.m_pStr) + strlen(m_pStr) + 1];
		strcpy(tmp, m_pStr);

		strcat(tmp, str.m_pStr);
		MyString a(tmp);
		delete[] tmp;
		return a;
		
	}
	else if (str.m_pStr) {

		return str;

	}
	return *this;


}

MyString& MyString::operator+= (const MyString& str) {
	if (str.m_pStr && m_pStr) {
		char* tmp = new char[strlen(str.m_pStr) + strlen(m_pStr) + 1];
		strcpy(tmp, m_pStr);
		delete[] this->m_pStr;

		strcat(tmp, str.m_pStr);
		m_pStr = tmp;
	}
	else if (str.m_pStr) {
		delete[] this->m_pStr;
		m_pStr = new char[strlen(str.m_pStr) + 1];
		strcpy(m_pStr, str.m_pStr);

	}

	return *this;
}

MyString MyString::operator--(int) {
	MyString tmp(*this);
	if (m_pStr != nullptr) {

		for (int i = 0; i < strlen(m_pStr); i++) {
			if (isupper(*(m_pStr + i))) {
				*(m_pStr + i) = static_cast<char>(tolower(*(m_pStr + i)));
			}
		}
	}
	return tmp;
}

MyString& MyString::operator++() {
	if (m_pStr != nullptr) {
		for (int i = 0; i < strlen(this->m_pStr); i++) {
			if (islower(*(m_pStr + i))) {
				*(m_pStr + i) = static_cast<char>(toupper(*(m_pStr + i)));
			}
		}
	}
	return *this;
}