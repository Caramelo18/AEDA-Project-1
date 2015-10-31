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
#include <cstdio>

//fazer funcao wait

void wait()
{
	cin.ignore(1000,'\n');
	cout << "Prima enter para regressar ao menu principal: ";
	cin.get();
	return;
}

void adicionaServico(Empresa &e)
{
	string tipo;
	int dist;
	cout << "Introduza o tipo de transporte (normal, congelacao, perigosos, animais): ";
	cin >> tipo;


	if (tipo == "normal" || tipo == "Normal" || tipo == "")
	{
		Normal c = Normal("exemplo", tipo, 20000);
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "O preco do servido pretendido e: " << c.getPreco(dist) << endl;
	}
	else if (tipo == "congelacao" || tipo == "Congelacao")
	{
		Congelacao c = Congelacao("exemplo", tipo, 20000);
		int temp;
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "Introduza a temperatura desejada: ";
		cin >> temp;
		cout << "O preco do servido pretendido e: " <<c.getPreco(dist, temp) << endl;

	}
	else if (tipo == "perigosos" || tipo == "Perigosos")
	{
		Perigosos c = Perigosos("exemplo", tipo, 20000);
		string nivelp;
		cout << "Insira o nivel de perigosidade (inflamavel, toxica, corrosiva, radioactiva): ";
		cin >> nivelp;
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		if(c.getPreco(dist, nivelp) != -1)
			cout << "O preco do servido pretendido e: " << c.getPreco(dist, nivelp) << endl;
		else cout << "Nivel de perigosidade invalido" << endl;

	}
	else if (tipo == "animais" || tipo == "Animais")
	{
		Animais c = Animais("exemplo", tipo, 20000);
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "O preco do servido pretendido e: " << c.getPreco(dist) << endl;
	}
	else
		cout << "Tipo invalido" << endl;

	wait();
}

void gestaoFinanceira(Empresa &e)
{
	int op;
	cout << " 1 - Verificar saldo" << endl;
	cout << " 2 - Pagar salarios" << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;

	if (op == 1)
	{
		e.imprimeSaldo();
	}
	else if (op == 2)
	{//Tem de se tentar apanhar a exceção do saldo insuficiente
		try
		{
			e.pagaSalario(); // falta actualizar saldo no ficheiro
		}
		catch(SaldoIndisponivel&)
		{
			cout << "Saldo insuficiente" << endl;
		}

		cout << "Salarios pagos." << endl;
		e.imprimeSaldo();
	}
	else
		cout << "Tipo invalido" << endl;

	wait();
}

void consultaServicos(Empresa &e)
{
	int op;
	cout << " 1 - Lista de servicos em execucao" << endl;
	cout << " 2 - Lista de servicos do cliente" << endl;
	cout << " 3 - Lista de servicos de um camiao" << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;

	wait();

	switch(op)
	{
	case 1:
		//
		e.ListaServicosExecucao();
		break;
	case 2:
		//
		e.ListaServicosCliente();
		break;
	case 3:
		//
		e.ListaServicosCamiao();
		break;
	}

}

void gestaoClientes(Empresa &e)
{
	int op;
	cout << " 1 - Lista de clientes" << endl;
	cout << " 2 - Adicionar clientes" << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;

	wait();
}

void gestaoCamioes(Empresa &e)
{
	int op;
	cout << "1 - Ver lista de camioes" << endl;
	cout << "2 - Ver lista de camioes disponiveis" << endl;
	cout << "3 - Adicionar camiao" << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;

	wait();
}


int main()
{/*
	string directorio;
	cout << "Por favor insira o directorio da pasta que contem os ficheiros da Empresa: ";
	cin >> directorio;
 */
	//string directorio = "C:/Users/Bruno/git/AEDA-Project";
	string directorio = "C:/Users/fabio/Documents/workspace/AEDA-Project-1";
	Empresa e = Empresa(directorio);

	do
	{
		cout << e.getNome() << endl << endl;

		cout << "1 - Adicionar servicos" << endl;
		cout << "2 - Gestao financeira" << endl;
		cout << "3 - Consultar servicos" << endl;
		cout << "4 - Gestao de clientes" << endl;
		cout << "5 - Gestao de camioes" << endl;


		int op;
		cout << "" << endl;
		cout << "Por favor insira a opcao desejada: ";
		cin >> op;

		switch (op)
		{
		case 1:
			//
			adicionaServico(e);
			break;
		case 2:
			//
			gestaoFinanceira(e);
			break;
		case 3:
			//
			consultaServicos(e);
			break;
		case 4:
			//
			gestaoClientes(e);
			break;
		case 5:
			//
			gestaoCamioes(e);
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			system("CLS");
			break;
		}
		system("CLS");
	}while(!cin.eof());

	system("pause");
	return 0;
}



