#include "MyString.h"


using std::cout;
using std::cin;
using std::ostream;
using std::istream;

void MyString::reset()
{
	m_stringSize = 0;
	m_string = nullptr;
}

void MyString::unInit()
{
	delete[] m_string;
	reset();
}

void MyString::initFromCharSequence(const char seq[])
{
	//clean object state 
	if(m_string)
		unInit();
	//detect sequence length
	for(m_stringSize = 0; m_stringSize < MAX_STRING_LEN - 1 && seq[m_stringSize] != END_STRING_CHAR; ++m_stringSize);
	
	//allocate space for sequence + terminator
	m_string = new char[++m_stringSize];

	//copy sequence and insert terminator in last cell
	for(unsigned int i = 0; i < m_stringSize - 1; ++i)
		m_string[i] = seq[i];
	m_string[m_stringSize - 1] = END_STRING_CHAR;
}

void MyString::initFromOther(const MyString &other)
{
	initFromCharSequence(other.m_string);
}

MyString::MyString()
{ 
	reset();
	const char empty[] = {'\0'};
	initFromCharSequence(empty);
}

MyString::MyString(const char st[])
{
	reset();
	initFromCharSequence(st);
}
/*
MyString::MyString(const MyString &str , int start, int end)
{
	if (end==0)
		end = str.len();
                     
	int len = end - start +1;
	Stringa = new char[len];
                    
	for (int i=start ; i<end ; i++)
	{
		Stringa[i-start] = str.Stringa[i];
	}
	
	Stringa[len-1] = END_STRING_CHAR;
}
*/

MyString::MyString(const MyString &other)
{
	reset();
	initFromOther(other);
}

MyString::~MyString()
{
	unInit();
}

MyString::MyString(int x)
{
	reset();
	char temp[MAX_STRING_LEN];
	_itoa_s(x, temp, 10);
	initFromCharSequence(temp);
}

ostream& operator<< (ostream& output, const MyString& str) 
{
	 for (int i=0; str.m_string[i]; i++)
	 {
		output << str.m_string[i];
	 }

	 return output;
}

istream& operator>> (istream& input, MyString& str)
{
	str.unInit();
	char tmp[MyString::MAX_STRING_LEN];
	cin.getline(tmp , MyString::MAX_STRING_LEN , '\n');
         
	int dim;
	for (dim = 0 ; dim < MyString::END_STRING_CHAR && tmp[dim] != MyString::END_STRING_CHAR ; ++dim);
	
	str.m_string = new char [dim + 1];
         
	for (int i=0 ; i<= dim ; i++)
	{
		str.m_string[i] = tmp[i];
	}        
	return input;
}

MyString& MyString::operator= (const MyString& str)
{
	if(this != &str)
	{
		unInit();
		initFromOther(str);
	}

	return *this;
} 

MyString& MyString::operator= (const char str[])
{
	unInit();
	initFromCharSequence(str);
	return *this; 
} 

MyString& MyString::operator+= (const MyString& str)
{
	//VIETATO DUPLICARE CODICE GIA' SCRITTO IN ALTRE SUBROUTINES!!!! ┻━┻ ︵ヽ(`Д´)ﾉ︵ ┻━┻
	/*
	int orS=len();                   
	int nSize = orS + str.len()+1;   
	MyString temp(Stringa);
	delete[] Stringa;                
	Stringa = new char [nSize];      
	int i;
	for (i=0 ; i<orS ; i++)
		Stringa[i]=temp.Stringa[i];
        
	
            
	for (; i<nSize ; i++)
		Stringa[i] = str.Stringa[i-orS];
	*/

	append(str);

	return *this;
}

bool MyString::operator== (const MyString& str) const
{
     if (len() != str.len())
        return false;
     else
		return compare(str) == 0;
}



bool MyString::operator!= (const MyString& str) const
{
	//reuse equals operator code
	/*
	if (len() != str.len())
        return false;
     else
         for (int i=0 ; i< len() ; i++)
             if (Stringa[i] != str.Stringa[i])
                return true;
     return false;
	 */
	return !(*this == str);
}

MyString MyString::operator+ (const MyString& str) const
{
	//VIETATO DUPLICARE CODICE GIA' SCRITTO IN ALTRE SUBROUTINES!!!! ┻━┻ ︵ヽ(`Д´)ﾉ︵ ┻━┻
	/*
	int orS=len();                   
	int nSize = orS + str.len()+1;   
	MyString temp(Stringa);
	delete[] Stringa;                
	Stringa = new char [nSize];      
	int i;
	for (i=0 ; i<orS ; i++)
		Stringa[i]=temp.Stringa[i];



	for (; i<nSize ; i++)
		Stringa[i] = str.Stringa[i-orS];
	*/

	MyString ret(*this);

	ret.append(str);

	return ret;
}

MyString operator+(const char prefix[], MyString &str)
{
	MyString ret(prefix);
	ret.append(str);

	return ret;
}

bool MyString::operator< (const MyString& str) const
{
     if (compare(str) < 0)
         return true;
     return false;
}
     
bool MyString::operator<= (const MyString& str) const
{
     if (compare(str) <= 0)
        return true;
     return false;
}
     
bool MyString::operator> (const MyString& str) const
{
     if (compare(str) > 0)
        return true;
     return false;
}
     

bool MyString::operator>= (const MyString& str) const
{
     if (compare(str) >= 0)
        return true;
     return false;
}


int MyString::len()const
{
	/*
    int dim;
    for (dim=0 ; Stringa[dim] != '\0' ; dim++);
    
    return dim;
	*/

	return m_stringSize - 1;	//exclude terminator character from count
}

const char* MyString::getstr() const
{
	return m_string;
}

void MyString::stampa() const
{
    for (int i=0 ; m_string[i] != END_STRING_CHAR ;i++)
        cout << m_string[i];
}

/*
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
*/


void MyString::append (const MyString& str)
{
	/*
	int orS = len();                  
	int nSize = orS + str.len()+1;  
	MyString temp(Stringa);
	delete[] Stringa;             
	Stringa = new char [nSize];     
	int i;
	for (i=0 ; i<orS ; i++)
		Stringa[i]=temp.Stringa[i];
        
	
            
	for (; i<nSize ; i++)
		Stringa [i] = str.Stringa[i-orS];
	*/

	//track old string reference
	char* oldStr = m_string;
	//allocate space for new string
	m_string = new char[m_stringSize + str.m_stringSize - 1];
	//copy from old string first
	unsigned int newLen = 0;
	for(unsigned int i = 0; i < m_stringSize - 1; ++i)
		m_string[newLen++] = oldStr[i];
	//copy from postfix string next, including the termination character
	for(unsigned int i = 0; i < str.m_stringSize; ++i)
		m_string[newLen++] = str.m_string[i];

	m_stringSize = newLen - 1;

	//delete old string 
	delete[] oldStr;
}

int MyString::compare(const MyString& str) const
{
	/*
	if(str.len() == len()){
		for (int i=0 ; i<len(); i++) 
			if (str.Stringa[i] != Stringa[i])
				if (Stringa[i] > Stringa[i])
					return -1;
				else return 1;
	return 0;
	}
else
    if (len() < str.len())	//baco -.-' "Zulu".compare("Abbazia") deve dare +1
        return -1;
else
    return 1;*/
	//detect lesser string len
	unsigned int minLen = (m_stringSize < str.m_stringSize) ? m_stringSize : str.m_stringSize;

	//compare charwise
	for(unsigned int i = 0; i < minLen; ++i)
	{
		if(m_string[i] < str.m_string[i])
			return -1;
		else if(m_string[i] > str.m_string[i])
			return 1;
	}

	//if reached this point strings are equal, up to the minLen-th character
	if(m_stringSize < str.m_stringSize)
		return -1;
	else if (m_stringSize > str.m_stringSize)
		return 1;
	else
		return 0;
}

