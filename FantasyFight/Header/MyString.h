#ifndef FANTASYFIGHT_STRING_H
#define FANTASYFIGHT_STRING_H

#include <fstream>
#include <iostream>


class MyString
{
      friend std::ostream& operator<<(std::ostream & , const MyString &);
      friend std::istream& operator>>(std::istream & , MyString &);
      
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
             MyString &operator+= (const MyString str);
             MyString &operator+ (const MyString str);

             bool operator== (const MyString str);
             bool operator!= (const MyString str);
             bool operator< (const MyString str);
             bool operator<= (const MyString str);
             bool operator> (const MyString str);
             bool operator>= (const MyString str);
      
private:
              char *Stringa;

};
      
#endif
