#ifndef FANTASYFIGHT_STRING_H
#define FANTASYFIGHT_STRING_H

#include <fstream>
#include <iostream>


class MyString
{
      friend std::ostream& operator<<(std::ostream & , const MyString &);
      friend std::istream& operator>>(std::istream & , MyString &);
	  friend MyString operator+(const char[], MyString &);
      
public:
             MyString();
             MyString(const char st[]);
             MyString (const MyString &str , int start=0 , int end=0);
             ~MyString();

			 const char* getstr() const;
             void stampa() const ;
             int len()const;
             MyString &copy(const MyString &str);
             void append(const MyString str);
             int compare(const MyString str) const;
			
      
             MyString &operator= (const MyString str);
             MyString &operator= (const char str[]);
             MyString &operator+= (const MyString str);
             MyString operator+ (const MyString str) const;	//this returns a string copy, shouldn't modify original

             bool operator== (const MyString str) const;
             bool operator!= (const MyString str) const;
             bool operator< (const MyString str) const;
             bool operator<= (const MyString str) const;
             bool operator> (const MyString str) const;
             bool operator>= (const MyString str) const;

private:
              char *Stringa;

};
      
#endif
