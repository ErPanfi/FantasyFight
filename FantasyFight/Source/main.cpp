#include <stdio.h>

#include "MyString.h"

int main()
{
	char provaChar[] = "pasticcio"; 

	MyString prova = MyString();

	//String prova2 = String(provaChar);

	//String prova3 = String(prova2);

	std::cin >> prova;

	MyString prova2 = MyString();

	MyString prova3 = MyString(provaChar);

	prova2= prova + itoa(2,provaChar,10);

	

	

	/*prova2 = prova2 + prova + prova3;*/

	
	//if ( prova2 > prova)
	//{
	//	/*prova2.stampa();
	//	std::cout << " vero" << "\n";
	//	prova2.copy(prova3);
	//	prova2.stampa();
	//	std::cout << " vero" << "\n";*/
	//	
	//}

	std::cout << "compare: " << prova.compare(prova) << "\n";


	std::cout << "prova " << prova << " prova2 " << prova2 << "\n";

	system("Pause");

}