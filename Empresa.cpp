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


	ifstream fich("C:/Users/Bruno/git/AEDA-Project-1/Camioes.txt");
	if (!fich)
		cerr << "Ficheiro nao encontrado";


		string nome;
		string temp;
		getline(fich,nome);
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

		ifstream fich2("C:/Users/Bruno/git/AEDA-Project-1/Funcionarios.txt");
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

		ifstream fich3("C:/Users/Bruno/git/AEDA-Project-1/Clientes.txt");
		if (!fich3)
			cerr << "Ficheiro nao encontrado";

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

}

void Empresa::adicionaCliente(Cliente cliente)
{
	clientes.push_back(cliente);
}

void Empresa::novoServico(Servico servico)
{
	servicos.push_back(servico);
}

void Empresa::contrataFuncionario(Funcionario funcionario)
{
	funcionarios.push_back(funcionario);
}

long Empresa::getSaldo()
{
	return saldo;
}

void Empresa::pagaSalario()
{
	for(usigned int i = 0; funcionarios.size(); i++)
	{
		saldo = saldo - funcionarios[i].getSalario();
	}
}
