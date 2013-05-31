#ifndef String_H
#define String_H

#include <iostream>

class String
{
      friend std::ostream &operator<<(std::ostream & , const String &);
      friend std::istream &operator>>(std::istream & , String &);
      
public:
             String();
             String(const char st[]);
             String (const String &str , int start=0 , int end=0);
             ~String();

			 const char* getstr() const;
             void stampa() const ;
             int len()const;
             String &copy(const String &str);
             void append(const String str);
             int compare(const String str) const;
			 void toString (int val);
      
             String &operator= (const String str);
             String &operator+= (const String str);
             
             bool operator== (const String str);
             bool operator!= (const String str);
             bool operator< (const String str);
             bool operator<= (const String str);
             bool operator> (const String str);
             bool operator>= (const String str);
      
private:
              char *Stringa;

};
      
#endif
