/*
 * main.cpp
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Servico.h"
#include <cstdlib>

int main()
{/*
	string directorio;
	cout << "Por favor insira o directorio da pasta que contem os ficheiros da Empresa: ";
	cin >> directorio;
 */
	string directorio = "C:/Users/fabio/Documents/workspace/AEDA-Project-1";
	Empresa e = Empresa(directorio);

	do
	{
		cout << e.getNome() << endl << endl;

		cout << "1 - Pedir orcamento" << endl;
		cout << "2 - Gestao financeira" << endl;
		cout << "3 - Consultar servicos" << endl;
		cout << "4 - Gestao clientes" << endl;
		cout << "5 - Gestao de camioes" << endl;


		int op;
		cout << "" << endl;
		cout << "Por favor insira a opcao desejada: ";
		cin >> op;


		switch (op)
		{
		case 1:
			//
			cout << 1 << endl;
			break;
		case 2:
			//
			cout << 2 << endl;
			break;
		case 3:
			//
			cout << 3 << endl;
			break;
		case 4:
			//
			cout << 4 << endl;
			break;
		case 5:
			//
			cout << 5 << endl;
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			//system("CLS");
			break;
		}
		system("CLS");
	}while(!cin.eof());

	system("pause");
	return 0;
}



