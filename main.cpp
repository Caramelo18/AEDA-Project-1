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


void wait()
{
	cin.ignore(1000,'\n');
	cout << "Prima enter para regressar ao menu principal ";
	cin.get();
	return;
}

void adicionaServico(Empresa &e)
{
	string tipo;
	int dist;
	cout << "Introduza o tipo de transporte (normal, congelacao, perigosos, animais): ";
	cin >> tipo;
	if (tipo == "normal" || tipo == "Normal")
	{
		string conf;
		int cap;
		string test = "abcd";
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		try
		{
			s = Servico(test, test, dist, "Normal", cap, 111, v);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		cout << "O preco do servido pretendido e: " << s.getPreco() << endl;
		cout << "Deseja adicionar o servico? ";
		cin >> conf;
		if (conf == "sim" || conf == "Sim" || conf == "s" || conf == "S")
		{
			string ori, dest;
			unsigned long nif;
			cout << "Insira o NIF do cliente: ";
			cin >> nif;
			try
			{
				e.posCliente(nif);
			}
			catch(ClienteNaoExistente &c)
			{
				cout << "Cliente nao existente." << endl;
				wait();
				return;
			}
			cout << "Insira a origem: ";
			cin >> ori;
			cout << "Insira o destino: ";
			cin >> dest;
			e.novoServico(ori, dest, dist, "Normal", cap, nif);
		}
	}
	else if (tipo == "congelacao" || tipo == "Congelacao")
	{
		string conf;
		int cap;
		int temp;
		string test = "abcd";
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		cout << "Insira a temperatura pretendida para o transporte: ";
		cin >> temp;
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		try
		{
			s = Servico(test, test, dist, "Congelacao", cap, 111, v, temp);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		cout << "O preco do servido pretendido e: " << s.getPreco() << endl;
		cout << "Deseja adicionar o servico? ";
		cin >> conf;
		if (conf == "sim" || conf == "Sim" || conf == "s" || conf == "S")
		{
			string ori, dest;
			unsigned long nif;
			cout << "Insira o NIF do cliente: ";
			cin >> nif;
			try
			{
				e.posCliente(nif);
			}
			catch(ClienteNaoExistente &c)
			{
				cout << "Cliente nao existente." << endl;
				wait();
				return;
			}
			cout << "Insira a origem: ";
			cin >> ori;
			cout << "Insira o destino: ";
			cin >> dest;
			e.novoServico(ori, dest, dist, "Congelacao", cap, nif, temp);
		}

	}
	else if (tipo == "perigosos" || tipo == "Perigosos")
	{
		string conf;
		int cap;
		string nivel;
		string test = "abcd";
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		cout << "Insira o nivel de perigosidade do transporte (inflamavel, toxica, corrosiva ou radioactiva): ";
		cin >> nivel;
		if (nivel != "inflamavel" && nivel != "toxica" && nivel != "corrosiva" && nivel != "radioactiva")
		{
			cerr << "Nivel de perigosidade invalido" << endl;
			wait();
			return;
		}
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		try
		{
			s = Servico(test, test, dist, "Perigosos", cap, 111, v, nivel);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		cout << "O preco do servido pretendido e: " << s.getPreco() << endl;
		cout << "Deseja adicionar o servico? ";
		cin >> conf;
		if (conf == "sim" || conf == "Sim" || conf == "s" || conf == "S")
		{
			string ori, dest;
			unsigned long nif;
			cout << "Insira o NIF do cliente: ";
			cin >> nif;
			try
			{
				e.posCliente(nif);
			}
			catch(ClienteNaoExistente &c)
			{
				cout << "Cliente nao existente." << endl;
				wait();
				return;
			}
			cout << "Insira a origem: ";
			cin >> ori;
			cout << "Insira o destino: ";
			cin >> dest;
			e.novoServico(ori, dest, dist, "Perigosos", cap, nif, nivel);
		}

	}
	else if (tipo == "animais" || tipo == "Animais")
	{
		string conf;
		int cap;
		string test = "abcd";
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		try
		{
			s = Servico(test, test, dist, "Animais", cap, 111, v);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		cout << "O preco do servido pretendido e: " << s.getPreco() << endl;
		cout << "Deseja adicionar o servico? ";
		cin >> conf;
		if (conf == "sim" || conf == "Sim" || conf == "s" || conf == "S")
		{
			string ori, dest;
			unsigned long nif;
			cout << "Insira o NIF do cliente: ";
			cin >> nif;
			try
			{
				e.posCliente(nif);
			}
			catch(ClienteNaoExistente &c)
			{
				cout << "Cliente nao existente." << endl;
				wait();
				return;
			}
			cout << "Insira a origem: ";
			cin >> ori;
			cout << "Insira o destino: ";
			cin >> dest;
			e.novoServico(ori, dest, dist, "Animais", cap, nif);
		}
	}
	else
		cout << "Tipo invalido" << endl;

	wait();
}

void terminaServico(Empresa &e)
{
	int ID;
	cout << "Indique o ID do Servico que pretende terminar: ";
	cin >> ID;

	try
	{
		e.terminaServico(ID);
	}
	catch(ServicoInexistente &s)
	{
		cout << "Servico Inexistente" << endl;
		wait();
		return;
	}

	cout << "Servico terminado" << endl;
	wait();
}

void gestaoFinanceira(Empresa &e)
{
	int op;
	cout << " 1 - Verificar saldo" << endl;
	cout << " 2 - Pagar salarios" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	cout << endl;

	if (op == 1)
	{
		e.imprimeSaldo();
	}
	else if (op == 2)
	{
		try
		{
			e.pagaSalario();
		}
		catch(SaldoIndisponivel &s)
		{
			cout << "Saldo insuficiente" << endl;
			wait();
			return;
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
	cout << " 1 - Lista de servicos" << endl;
	cout << " 2 - Lista de servicos em execucao" << endl;
	cout << " 3 - Lista de servicos do cliente" << endl;
	cout << " 4 - Lista de servicos de um camiao" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	cout << endl;

	switch(op)
	{
	case 1:
		e.imprimeServicos();
		break;
	case 2:
		e.ListaServicosExecucao();
		break;
	case 3:
		e.ListaServicosCliente();
		break;
	case 4:
		e.ListaServicosCamiao();
	}
	wait();
}

void gestaoClientes(Empresa &e)
{
	int op;
	cout << " 1 - Lista de clientes" << endl;
	cout << " 2 - Adicionar clientes" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	cout << endl;

	switch(op)
	{
	case 1:
		//
		e.listaClientes();
		break;
	case 2:
		//
		e.adicionaCliente();
		break;
	}

	wait();
}

void gestaoCamioes(Empresa &e)
{
	int op;
	cout << "1 - Ver lista de camioes" << endl;
	cout << "2 - Ver lista de camioes disponiveis" << endl;
	cout << "3 - Adicionar camiao" << endl;
	cout << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	cout << endl;

	switch(op)
	{
	case 1:
		e.ImprimeListaCamioes();
		break;
	case 2:
		e.ImprimeListaCamioesDisponiveis();
		break;
	case 3:
		e.AdicionaCamiao();
		break;
	}

	wait();
}


int main()
{/*
	string directorio;
	cout << "Por favor insira o directorio da pasta que contem os ficheiros da Empresa: ";
	cin >> directorio;
 */
	string directorio = "C:/Users/Bruno/git/AEDA-Project";
	//string directorio = "C:/Users/Acer-PC/git/AEDA-Project-1";
	//string directorio = "C:/Users/POS/git/AEDA-Project-1";
	//string directorio = "C:/Users/fabio/Documents/workspace/AEDA-Project-1";
	Empresa e = Empresa(directorio);

	do
	{
		cout << e.getNome() << endl << endl;

		cout << "1 - Gestao de servicos" << endl;
		cout << "2 - Gestao financeira" << endl;
		cout << "3 - Consultar servicos" << endl;
		cout << "4 - Gestao de clientes" << endl;
		cout << "5 - Gestao de camioes" << endl << endl;
		// falta adicionar contratar funcionario

		int op;
		cout << "Por favor insira a opcao desejada: ";
		cin >> op;
		cout << "" << endl;

		switch (op)
		{
		case 1:
			//
			cout << " 1 - Adicionar Servico" << endl;
			cout << " 2 - Terminar Servico" << endl << endl;

			int op;
			cout << "Por favor insira a opcao desejada: ";
			cin >> op;
			cout << endl;

			if (op == 1)
				adicionaServico(e);

			else if (op == 2)
				terminaServico(e);

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

	e.actualizaFicheiro();
	return 0;
}



