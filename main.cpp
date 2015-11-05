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
#include <conio.h>
#include <ctype.h>


void wait()
{
	cin.ignore(1000,'\n');
	cout << "Prima enter para regressar ao menu principal ";
	cin.get();
	return;
}

int pass()
{
	int i = 0;
	string pass;
	while(i < 3)
	{
		if (i > 0)
			cout << "Tem " <<3 - i << " tentativas restantes" << endl;
		cout << "Insira a password: ";
		cin >> pass;
		if (pass == "admin")
			return 0;
		i++;
	}
	return -1;
}

void adicionaServico(Empresa &e)
{
	string tipo;
	int dist;
	cout << "Introduza o tipo de transporte (normal, congelacao, perigosos, animais): ";
	cin >> tipo;
	cin.clear();
	if (tipo == "normal" || tipo == "Normal")
	{
		string conf;
		int cap;
		string test = "abcd";
		cout << "Introduza a distancia do transporte a efectuar: ";
		cin >> dist;
		if (dist <= 10)
		{
			cout << "Distancia invalida" << endl;
			wait();
			return;
		}
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		vector<Funcionario *> func = e.getFuncionarios();
		try
		{
			s = Servico(test, test, dist, "Normal", cap, 111, v, func);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		catch(FuncionariosIndisponiveis &f)
		{
			cout << "Impossivel realizar servico, funcionarios insuficientes" << endl;
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
			cin.ignore(1000, '\n');
			getline(cin,ori);
			cin.clear();
			cout << "Insira o destino: ";
			getline(cin,dest);
			cin.clear();
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
		if (dist <= 10)
		{
			cout << "Distancia invalida" << endl;
			wait();
			return;
		}
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		cout << "Insira a temperatura pretendida para o transporte: ";
		cin >> temp;
		if (temp > 20 || temp < -10)
		{
			cout << "Temperatura invalida" << endl;
			wait();
			return;
		}
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		vector<Funcionario *> func = e.getFuncionarios();
		try
		{
			s = Servico(test, test, dist, "Congelacao", cap, 111, v, temp, func);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		catch(FuncionariosIndisponiveis &f)
		{
			cout << "Impossivel realizar servico, funcionarios insuficientes" << endl;
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
			cin.ignore(1000, '\n');
			getline(cin,ori);
			cin.clear();
			cout << "Insira o destino: ";
			getline(cin,dest);
			cin.clear();
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
		if (dist <= 10)
		{
			cout << "Distancia invalida" << endl;
			wait();
			return;
		}
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
		vector<Funcionario *> func = e.getFuncionarios();
		try
		{
			s = Servico(test, test, dist, "Perigosos", cap, 111, v, nivel, func);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		catch(FuncionariosIndisponiveis &f)
		{
			cout << "Impossivel realizar servico, funcionarios insuficientes" << endl;
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
			cin.ignore(1000, '\n');
			getline(cin,ori);
			cin.clear();
			cout << "Insira o destino: ";
			getline(cin,dest);
			cin.clear();
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
		if (dist <= 10)
		{
			cout << "Distancia invalida" << endl;
			wait();
			return;
		}
		cout << "Insira a quantidade da carga a transportar: ";
		cin >> cap;
		Servico s;
		vector<Camiao *> v = e.getCamioes();
		vector<Funcionario *> func = e.getFuncionarios();
		try
		{
			s = Servico(test, test, dist, "Animais", cap, 111, v, func);
		}
		catch (camioesIndisponiveis &c)
		{
			cout << "Impossivel realizar servico, camioes insuficientes" << endl;
			wait();
			return;
		}
		catch(FuncionariosIndisponiveis &f)
		{
			cout << "Impossivel realizar servico, funcionarios insuficientes" << endl;
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
			cin.ignore(1000, '\n');
			getline(cin,ori);
			cin.clear();
			cout << "Insira o destino: ";
			getline(cin,dest);
			cin.clear();
			e.novoServico(ori, dest, dist, "Animais", cap, nif);
		}
	}
	else
		cout << "Tipo invalido" << endl;

	cout << "Prima enter para regressar ao menu principal ";
	cin.get();
	return;
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
			if (pass() == 0)
				e.pagaSalario();
			else
			{
				cout << "Password errada" << endl;
				wait();
				return;
			}
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
		try
		{
			if (pass() == 0)
				e.AdicionaCamiao();
			else
			{
				cout << "Password errada" << endl;
				wait();
				return;
			}
		}
		catch(SaldoIndisponivel &s)
		{
			cout << "Impossivel adicionar camiao, saldo insuficiente" << endl;
		}
		break;
	}

	wait();
}

void gestaoFuncionarios(Empresa &e)
{
	int op;
	cout << "1 - Ver lista de funcionarios" << endl;
	cout << "2 - Ver lista de funcionarios disponiveis" << endl;
	cout << "3 - Contratar funcionario" << endl;
	cout << "4 - Despedir funcionario" << endl;
	cout << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	cout << endl;

	switch(op)
	{
	case 1:
		e.listaFuncionarios();
		break;
	case 2:
		e.listaFuncionariosDisponiveis();
		break;
	case 3:
		if(pass() == 0)
			e.contrataFuncionario();
		else cout << "Password errada" << endl;
		break;
	case 4:
		if (pass() == 0)
			e.despedeFuncionario();
		else cout << "Password errada" << endl;
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
	//string directorio = "C:/Users/Bruno/git/AEDA-Project";
	//string directorio = "C:/Users/Acer-PC/git/AEDA-Project-1";
	//string directorio = "C:/Users/POS/git/AEDA-Project-1";
	string directorio = "C:/Users/fabio/Documents/workspace/AEDA-Project-1";
	Empresa e;
	try
	{
		e = Empresa(directorio);
	}
	catch(FicheiroInexistente &f)
	{
		cout << "Ficheiro " << f.getFicheiro() << " inexistente" << endl;
		system("pause");
		return 1;
	}

	int opc;
	do
	{
		cout << e.getNome() << endl << endl;

		cout << "1 - Gestao de servicos" << endl;
		cout << "2 - Gestao financeira" << endl;
		cout << "3 - Consultar servicos" << endl;
		cout << "4 - Gestao de clientes" << endl;
		cout << "5 - Gestao de camioes" << endl;
		cout << "6 - Gestao de funcionarios" << endl << endl;

		cout << "Por favor insira a opcao desejada (0 para sair): ";
		cin >> opc;

		cout << endl;

		switch (opc)
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
			gestaoFinanceira(e);
			break;
		case 3:
			consultaServicos(e);
			break;
		case 4:
			gestaoClientes(e);
			break;
		case 5:
			gestaoCamioes(e);
			break;
		case 6:
			gestaoFuncionarios(e);
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			system("CLS");
			break;
		}
		system("CLS");
	}while(opc != 0);

	e.actualizaFicheiro();
	return 0;
}



