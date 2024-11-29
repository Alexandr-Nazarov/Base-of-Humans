#pragma once
#include <iostream>
#include <ctype.h>
class MyString
{
  char* m_pStr;	
public:
    MyString();

    const char* GetString() const;

    explicit MyString(const char* str);
    
    MyString(const MyString& other);
    MyString(MyString&&);
  


    void SetNewString(const char*);
    void SetNewString(MyString&);

    MyString& operator=(const MyString& str);
    MyString& operator=(const char* str);
    MyString& operator=(MyString&& str);
  
  
    friend std::ostream& operator<< (std::ostream& out, const MyString& str);

    MyString operator+(const MyString& str);
    MyString& operator+= (const MyString& str);
    MyString operator--(int);
    MyString& operator++();

    ~MyString();
    operator char* () { return m_pStr; }
};


MyString ConcatenString(const char*,...);