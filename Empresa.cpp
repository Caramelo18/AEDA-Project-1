/*
 * Empresa.cpp
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */
#include "Empresa.h"
#include <fstream>
#include <sstream>

Empresa::Empresa(string doc)
{
	saldo = 0;
	vector<Servico> ser;
	servicos = ser;
	vector<*Camiao> cams;
	camioes = cams;
	vector<Cliente> clis;
	clientes = clis;
	vector<Funcionario> funcs;
	funcionarios = funcs;


	ifstream fich("C:/Users/Bruno/git/AEDA-Project-1/Empresa.txt");
	if (!fich)
		cerr << "Ficheiro nao encontrado";


		string nome;
		string temp;
		getline(fich,nome);
		getline(fich,temp);
		getline(fich,temp);

		do
		{
			string marca;
			string tipo;
			int capacidade;
			stringstream ss;

			ss << temp;
			ss >> marca >> tipo >> capacidade;

			Camiao cam = Camiao::Camiao(marca, tipo, capacidade);
			camioes.push_back(cam);

			getline(fich,temp);

		}while(temp != "Funcionarios:");

		getline(fich,temp);

		do
		{
			string nomeFunc;
			int salario;
			unsigned long BI;
			stringstream ss;

			ss << temp;
			ss >> nomeFunc >> salario >> BI;

			Funcionario func = Funcionario::Funcionario(nomeFunc, salario, BI);
			funcionarios.push_back(func);

			getline(fich,temp);

		}while(temp != "Clientes:");

		getline(fich,temp);

		while (! fich.eof())
		{
			string nomeCli;
			unsigned long Nif;
			stringstream ss;

			ss << temp;
			ss >> nomeCli >> Nif;

			Cliente cli = Cliente::Cliente(nomeCli, Nif);
			clientes.push_back(cli);
		}
	fich.close();
}

vector<*Camiao> Empresa::getCamioes()
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

long Empresa::getsaldo()
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
