/*
 * main.cpp
 */

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Servico.h"
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <ctype.h>

/**
 * \brief Funcao que faz com que se tenha de premir a tecla enter para sair da pagina onde estamos e normalmente regressar para o menu principal de maneira a que quando se imprima algo fique impresso no ecra ate que algum de enter e nao saia logo para o menu principal
 */
void wait()
{
	cin.ignore(1000,'\n');
	cout << "Prima enter para regressar ao menu principal ";
	cin.get();
	return;
}

/**
 * \brief Funcao que permite apenas ao gestor da Empresa, conhecedor da palavra-passe aceder a algumas funcoes do programa
 * \return Retorna o sucesso ou nao da tentetiva de adivinhar a palavra-passe
 */
int pass()
{
	int i = 0;
	string pass;
	while(i < 3)
	{
		if (i > 0)
			cout << "Tem " << 3 - i << " tentativas restantes" << endl;
		cout << "Insira a password: ";
		cin >> pass;
		if (pass == "admin")
			return 0;
		i++;
	}
	return -1;
}

/**
 * \brief Funcao que adiciona um novo servico a empresa
 * \param e Empresa a qual vai ser adicionada o novo servico
 */
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
		if (cap <= 0)
		{
			cout << "Quantidade de carga a transportar invalida" << endl;
			wait();
			return;
		}
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
		if (cap <= 0)
		{
			cout << "Quantidade de carga a transportar invalida" << endl;
			wait();
			return;
		}
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
		if (cap <= 0)
		{
			cout << "Quantidade de carga a transportar invalida" << endl;
			wait();
			return;
		}
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
		if (cap <= 0)
		{
			cout << "Quantidade de carga a transportar invalida" << endl;
			wait();
			return;
		}
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

/**
 * \brief Funcao que termina um determinado Servico
 * \param e Empresa na qual vai ser terminado o Servico
 */
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

/**
 * \brief Funcao onde se gere a parte financeira da Empresa (Chama funcoes mais expecificas definidas nas suas classes)
 * \param e Empresa onde se vai fazer a gestao financeira
 */
void gestaoFinanceira(Empresa &e)
{
	int op;
	cout << " 1 - Verificar saldo" << endl;
	cout << " 2 - Pagar salarios" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	if(cin.eof())
		cin.clear();
	else if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000,'\n');
	}

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
	{
		cout << "Opcao invalida" << endl;
		return;
	}

	wait();
}
/**
 * \brief Funcao que permite fazer a consulta dos Servicos, como os Servicos todos da Empresa, os que estao em execucao, etc.
 */
void consultaServicos(Empresa &e)
{
	int op;
	cout << " 1 - Lista de servicos" << endl;
	cout << " 2 - Lista de servicos em execucao" << endl;
	cout << " 3 - Lista de servicos do cliente" << endl;
	cout << " 4 - Lista de servicos de um camiao" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	if(cin.eof())
	{
		cin.clear();
		return;
	}
	else if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000,'\n');
		return;
	}
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
		break;
	default:
		return;
	}
	wait();
}

/**
 * \brief Funcao que permite gerir os Clientes da Empresa, como verificaar os Clientes que existem, adicionar novos Clientes
 * \param e Empresa na qual se vai gerir os Clientes
 */
void gestaoClientes(Empresa &e)
{
	int op;
	cout << " 1 - Lista de clientes" << endl;
	cout << " 2 - Lista de clientes ordenada" << endl;
	cout << " 3 - Adicionar clientes" << endl << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	if(cin.eof())
	{
		cin.clear();
		return;
	}
	else if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000,'\n');
		return;
	}
	cout << endl;

	switch(op)
	{
	case 1:
		e.listaClientes();
		break;
	case 2:
		e.listaClientesOrdenados();
		break;
	case 3:
		try
		{
			e.adicionaCliente();
		}
		catch (ClienteJaExistente &c)
		{
			cout << "Cliente com o NIF " << c.getNif() << " ja existe." << endl;
		}
		break;
	default:
		return;
	}
	wait();
}

/**
 * \brief Funcao que permite gerir os Camioes da Empresa, como verificar os Camioes disponiveis, adicionar Camioes novos
 * \param e Empresa na qual se vai gerir os Camioes
 */
void gestaoCamioes(Empresa &e)
{
	int op;
	cout << "1 - Ver lista de camioes" << endl;
	cout << "2 - Ver lista de camioes disponiveis" << endl;
	cout << "3 - Ver lista de camioes ordenada" << endl;
	cout << "4 - Adicionar camiao" << endl;
	cout << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	if(cin.eof())
	{
		cin.clear();
		return;
	}
	else if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000,'\n');
		return;
	}
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
		e.ListaCamioesOrdenados();
		break;
	case 4:
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
		catch(CamiaoJaExistente &c)
		{
			cout << "Impossivel adicionar camiao, ja existe um camiao com a matricula "<< c.getMatricula() << endl;
		}
		break;
	default:
		return;
	}

	wait();
}

/**
 * \brief Funcao que permite gerir os Funcionarios da Empresa, como verificaar os Funcionarios que existem, adicionar novos Funcionarios, despedir Funcionarios tambem
 * \param e Empresa na qual se vai gerir os Clientes
 */
void gestaoFuncionarios(Empresa &e)
{
	int op;
	cout << "1 - Ver lista de funcionarios" << endl;
	cout << "2 - Ver lista de funcionarios disponiveis" << endl;
	cout << "3 - Ver lista de funcionarios ordenada" << endl;
	cout << "4 - Contratar funcionario" << endl;
	cout << "5 - Despedir funcionario" << endl;

	cout << endl;
	cout << "Por favor escolha a opcao pretendida: ";
	cin >> op;
	if(cin.eof())
	{
		cin.clear();
		return;
	}
	else if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000,'\n');
		return;
	}
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
		e.listaFuncionariosOrdenada();
		break;
	case 4:
		if(pass() == 0)
			e.contrataFuncionario();
		else cout << "Password errada" << endl;
		break;
	case 5:
		if (pass() == 0)
			e.despedeFuncionario();
		else cout << "Password errada" << endl;
		break;

	default:
		return;
	}
	wait();

}

/**
 * \brief Funcao principal onde se insere os ficheiros de configuracao da empresa toda e por onde se desenrola toda a aplicacao
 */
int main()
{
	string directorio;
	cout << "Por favor insira o directorio da pasta que contem os ficheiros da Empresa: ";
	cin >> directorio;

	system("cls");
	//string directorio = "C:/Users/Bruno/git/AEDA-Project";
	//string directorio = "C:/Users/Acer-PC/git/AEDA-Project-1";
	//string directorio = "C:/Users/POS/git/AEDA-Project-1";
	//string directorio = "C:/Users/fabio/Documents/workspace/AEDA-Project-1";
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

	int opc = 10;
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
		if(cin.eof())
			cin.clear();
		else if (cin.fail())
		{
			opc = 10;
			cin.clear();
			cin.ignore(1000,'\n');
		}

		switch (opc)
		{
		case 1:
			//
			cout << " 1 - Adicionar Servico" << endl;
			cout << " 2 - Terminar Servico" << endl << endl;
			int op;
			cout << "Por favor insira a opcao desejada: ";
			cin >> op;
			if(cin.eof())
				cin.clear();
			else if (cin.fail())
			{
				opc = 10;
				cin.clear();
				cin.ignore(1000,'\n');
			}

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
			break;
		}
		system("CLS");
	}while(opc != 0);

	e.actualizaFicheiro();

	return 0;
}




