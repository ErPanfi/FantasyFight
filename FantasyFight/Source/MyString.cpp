#include "MyString.h"


using std::cout;
using std::cin;
using std::ostream;
using std::istream;



MyString::MyString()
{ 
	Stringa = new char [1];
	*Stringa = '\0';
}

MyString::MyString(const char st[])
{
	int dim;
	for (dim=0 ; st[dim]!='\0' ; dim++ );                       
		
	Stringa = new char [dim+1];
		
	for (int i=0 ; i<=dim ; i++)
	{
		Stringa[i] = st[i];
	}
}

MyString::MyString(const MyString &str , int start, int end)//vedere &
{
	if (end==0)
		end = str.len();
                     
	int len = end - start +1;
	Stringa = new char[len];
                    
	for (int i=start ; i<end ; i++)
	{
		Stringa[i-start] = str.Stringa[i];
	}
	
	Stringa[len-1] = '\0';
}

MyString::~MyString()
{
	delete[] Stringa;
}

ostream& operator<< (ostream& output, const MyString& str) 
{
	 for (int i=0; str.Stringa[i]; i++)
	 {
		output << str.Stringa[i];
	 }

	 return output;
}

istream& operator>> (istream& input, MyString& str)
{
	delete[] str.Stringa;
	char tmp[80];
	cin.getline(tmp , 80 , '\n');
         
	int dim;
	for (dim=0 ; tmp[dim] != '\n' ; dim++);
	
	str.Stringa = new char [dim + 1];
         
	for (int i=0 ; i<= dim ; i++)
	{
		str.Stringa[i] = tmp[i];
	}        
	return input;
}

MyString& MyString::operator= (const MyString str)
{
	delete[] Stringa;
	Stringa = new char[str.len()+1];
	for (int i=0 ; i<str.len()+1 ; i++)
	Stringa[i]=str.Stringa[i];
	return *this; 
} 

MyString& MyString::operator+= (const MyString str)
{
	int orS=len();                   
	int nSize = orS + str.len()+1;   
	MyString temp(Stringa);
	delete[] Stringa;                
	Stringa = new char [nSize];      
	int i;
	for (i=0 ; i<orS ; i++)
		Stringa[i]=temp.Stringa[i];
        
	delete[] temp.Stringa;
            
	for (; i<nSize ; i++)
		Stringa [i] = str.Stringa[i-orS];
	return *this;
}

bool MyString::operator== (const MyString str)
{
     if (len() != str.len())
        return false;
     else
         for (int i=0 ; i< len() ; i++)
             if (Stringa[i] != str.Stringa[i])
                return false;
     return true;
}



bool MyString::operator!= (const MyString str)
{
	if (len() != str.len())
        return false;
     else
         for (int i=0 ; i< len() ; i++)
             if (Stringa[i] != str.Stringa[i])
                return true;
     return false;
}

bool MyString::operator< (const MyString str)
{
     if (compare(str) < 0)
         return true;
     return false;
}
     
bool MyString::operator<= (const MyString str)
{
     if (compare(str) <= 0)
        return true;
     return false;
}
     
bool MyString::operator> (const MyString str)
{
     if (compare(str) > 0)
        return true;
     return false;
}
     

bool MyString::operator>= (const MyString str)
{
     if (compare(str) >= 0)
        return true;
     return false;
}


int MyString::len()const
{
    int dim;
    for (dim=0 ; Stringa[dim] != '\0' ; dim++);
    
    return dim;
}

const char* MyString::getstr() const
{
	return Stringa;
}

void MyString::stampa() const
{
    for (int i=0 ; Stringa[i] != '\0' ;i++)
        cout << Stringa[i];
}

MyString& MyString::copy(const MyString &str)
{
	delete[] Stringa;
	int dim;
       
	for (dim =0; str.Stringa[dim] != '\0' ; dim++)
	;
	dim++;
       
	Stringa = new char [dim];
       
	for (int i=0 ; i<=dim ; i++)
	Stringa[i]=str.Stringa[i];
       
	return *this;
}

void MyString::toString (int val)
{

	int counter = 1;
	int valtemp = val;
	while (valtemp > 0)
	{
		valtemp = valtemp/10;
		counter++;
	}

	
	
	Stringa = new char [counter];


	
	int tempVal;
	//valtemp = val;

	for (int i = 0 ; i < counter ; i++)
	{
		tempVal = valtemp % 10;
		Stringa[i] =(char)(tempVal);
		valtemp = valtemp / 10;
		//prova = str.Stringa[i];
	}

	Stringa[counter] = '\0';

}

void MyString::append (const MyString str)
{
	int orS = len();                  
	int nSize = orS + str.len()+1;  
	MyString temp(Stringa);
	delete[] Stringa;             
	Stringa = new char [nSize];     
	int i;
	for (i=0 ; i<orS ; i++)
		Stringa[i]=temp.Stringa[i];
        
	delete[] temp.Stringa;
            
	for (; i<nSize ; i++)
		Stringa [i] = str.Stringa[i-orS];

}

int MyString::compare(const MyString str) const
{
	if(str.len() == len()){
		for (int i=0 ; i<len(); i++) 
			if (str.Stringa[i] != Stringa[i])
				if (Stringa[i] > Stringa[i])
					return -1;
				else return 1;
	return 0;
	}
else
    if (len() < str.len())
        return -1;
else
    return 1;
}
