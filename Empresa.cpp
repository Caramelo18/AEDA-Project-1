/*
 * Empresa.cpp
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */
#include "Empresa.h"
#include "Camiao.h"
#include <fstream>
#include <sstream>

Empresa::Empresa(string doc)
{
	saldo = 0;
	vector<Servico> ser;
	servicos = ser;
	vector<Camiao *> cams;
	camioes = cams;
	vector<Cliente> clis;
	clientes = clis;
	vector<Funcionario> funcs;
	funcionarios = funcs;

	string ficca, ficcli, ficfun, ficser;
	ficca = doc + "/Camioes.txt";
	ficcli = doc + "/Clientes.txt";
	ficfun = doc + "/Funcionarios.txt";
	ficser = doc + "/Servicos.txt";


	ifstream fich(ficca.c_str());
	if (!fich)
		cerr << "Ficheiro nao encontrado";


		string nome;
		string temp;
		getline(fich,nome);
		nomeEmpresa = nome;
		getline(fich,temp);

		while(!fich.eof())
		{
			getline(fich,temp);

			string marca;
			string tipo;
			int capacidade;
			stringstream ss;

			ss << temp;
			ss >> marca >> tipo >> capacidade;

			if (tipo == "Normal")
			{
				Normal *cam = new Normal(marca, tipo, capacidade);
				camioes.push_back(cam);
			}

			if (tipo == "Congelacao")
			{
				Congelacao *cam1 = new Congelacao(marca, tipo, capacidade);
				camioes.push_back(cam1);
			}

			if (tipo == "Perigosos")
			{
				Perigosos *cam2 = new Perigosos(marca, tipo, capacidade);
				camioes.push_back(cam2);
			}

			if (tipo == "Animais")
			{
				Animais *cam3 = new Animais(marca, tipo, capacidade);
				camioes.push_back(cam3);
			}
		}

		fich.close();

		ifstream fich2(ficfun.c_str());
		if (!fich2)
			cerr << "Ficheiro nao encontrado";

		getline(fich2,temp);

		while(!fich2.eof())
		{
			getline(fich2,temp);

			string nomeFunc;
			int salario;
			unsigned long BI;
			stringstream ss;

			ss << temp;
			ss >> nomeFunc >> salario >> BI;

			Funcionario func = Funcionario(nomeFunc, salario, BI);
			funcionarios.push_back(func);

		}

		fich2.close();

		ifstream fich3(ficcli.c_str());
		if (!fich3)
			cerr << "Ficheiro nao encontrado";

		getline(fich3, temp);
		while (! fich3.eof())
		{
			getline(fich3,temp);

			string nomeCli;
			unsigned long Nif;
			stringstream ss;

			ss << temp;
			ss >> nomeCli >> Nif;

			Cliente cli = Cliente(nomeCli, Nif);
			clientes.push_back(cli);
		}
		fich3.close();
}

vector<Camiao *> Empresa::getCamioes()
{
	return camioes;
}

vector<Servico> Empresa::getServicos()
{
	return servicos;
}

vector<Cliente> Empresa::getClientes()
{
	return clientes;
}

vector<Funcionario> Empresa::getFuncionarios()
{
	return funcionarios;
}

void Empresa::adicionaCamiao(Camiao *camiao)
{
	camioes.push_back(camiao);

	fstream fich("C:/Users/Bruno/git/AEDA-Project-1/Camioes.txt", fstream::app);
	if (!fich)
		cerr << "Ficheiro nao encontrado";

	fich << endl;
	fich << camiao->getMarca() << " " << camiao->getTipo() << " " << camiao->getCapacidade();

	fich.close();

}

void Empresa::adicionaCliente(Cliente cliente)
{
	clientes.push_back(cliente);

	fstream fich("C:/Users/Bruno/git/AEDA-Project-1/Clientes.txt", fstream::app);
	if (!fich)
		cerr << "Ficheiro nao encontrado";

	fich << endl;
	fich << cliente.getNome() << " "  << cliente.getNif();

	fich.close();
}

void Empresa::novoServico(Servico servico)
{
	servicos.push_back(servico);

	fstream fich("C:/Users/Bruno/git/AEDA-Project-1/Clientes.txt", fstream::app);
	if (!fich)
		cerr << "Ficheiro nao encontrado";

	fich << endl;
	fich << servico.getOrigem() << " " << servico.getDestino() << " " << servico.getDistancia() << servico.getTipo_produto() << servico.getCapacidade();

	fich.close();
}

void Empresa::contrataFuncionario(Funcionario funcionario)
{
	funcionarios.push_back(funcionario);

	fstream fich("C:/Users/Bruno/git/AEDA-Project-1/Funcionarios.txt", fstream::app);
	if (!fich)
		cerr << "Ficheiro nao encontrado";

	fich << endl;
	fich << funcionario.getNome() << " " << funcionario.getSalario() << " " << funcionario.getBI();

	fich.close();
}

long Empresa::getSaldo()
{
	return saldo;
}

void Empresa::pagaSalario()
{
	int salarios_total = 0;
	for(unsigned int i = 0; i < funcionarios.size(); i++)
	{
		salarios_total = salarios_total - funcionarios[i].getSalario();
	}

	if (salarios_total > saldo)
		throw SaldoIndisponivel();
	else saldo -= salarios_total;
}

string Empresa::getNome() const
{
	return nomeEmpresa;
}

void Empresa::imprimeSaldo()
{
	cout << "O seu saldo autal é de: " << saldo << " euros" << endl;
}

void Empresa::imprimeServico()
{
	for(unsigned int i = 0; i < servicos.size(); i++)
	{
		cout << "Servico " << i <<":" << endl;
		cout << "Camioes Utilizados:" << endl;
		for(unsigned int j = 0; j < servicos[i].getCamioes().size(); j++)
		{
			//"Camiao " << j << ": " << servicos[i].getCamioes[j]->getMarca() << "-" << servicos[i].getCamioes[j]->getTipo() ;
		}
	}
}
