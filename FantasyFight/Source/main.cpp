#include <stdio.h>

#include "MyString.h"

int main()
{
	char provaChar[] = "ciao"; 

	MyString prova = MyString();

	//String prova2 = String(provaChar);

	//String prova3 = String(prova2);

	std::cin >> prova;

	MyString prova2 = MyString();

	prova2=prova;

	prova2 += prova;


	

	std::cout << "prova " << prova << " prova2 " << prova2 << "\n";

	system("Pause");

}