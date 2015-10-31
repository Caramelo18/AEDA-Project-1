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
#include <vector>
#include <string>

Empresa::Empresa(string doc)
{

	vector<Servico> ser;
	servicos = ser;
	vector<Camiao *> cams;
	camioes = cams;
	vector<Cliente> clis;
	clientes = clis;
	vector<Funcionario> funcs;
	funcionarios = funcs;

	ficca = doc + "/Camioes.txt";
	ficcli = doc + "/Clientes.txt";
	ficfun = doc + "/Funcionarios.txt";
	ficser = doc + "/Servicos.txt";


	ifstream fich(ficca.c_str());
	if (!fich)
	{
		cerr << "Ficheiro nao encontrado";
		//fazer throw aqui
	}

	long sal;
	string nome;
	string temp;
	getline(fich,nome);
	nomeEmpresa = nome;
	getline(fich, temp);
	stringstream sald;
	sald << temp;
	sald >> temp >> sal;
	saldo = sal;
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

	ofstream fich(ficca.c_str(), ofstream::app);

	fich << endl;
	fich << camiao->getMarca() << " " << camiao->getTipo() << " " << camiao->getCapacidade();

	fich.close();

}

void Empresa::adicionaCliente()
{
	string nome;
	unsigned long Nif;

	cout << "Novo Cliente: " << endl;

	cout << "Nome: ";
	cin >> nome;
	cout << "Nif: ";
	cin >> Nif;
	cout << endl;

	Cliente cliente = Cliente(nome, Nif);

	for (unsigned int  i = 0; i < clientes.size(); i++)
	{
		if (clientes[i] == cliente)
			throw ClienteJaExistente(nome, Nif);
	}

	clientes.push_back(cliente);

	ofstream fich(ficcli.c_str(), ofstream::app);

	fich << endl;
	fich << cliente.getNome() << " "  << cliente.getNif();//Ainda nao esta a ler

	cout << "Cliente adicionado com sucesso" << endl;

	fich.close();
}

void Empresa::novoServico(Servico servico)
{
	servicos.push_back(servico);

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << servico.getOrigem() << " " << servico.getDestino() << " " << servico.getDistancia() << servico.getTipo_produto() << servico.getCapacidade();

	fich.close();
}

void Empresa::contrataFuncionario(Funcionario funcionario)
{
	funcionarios.push_back(funcionario);

	ofstream fich(ficfun.c_str(), ofstream::app);

	fich << endl;
	fich << funcionario.getNome() << " " << funcionario.getSalario() << " " << funcionario.getBI();

	fich.close();
}

long Empresa::getSaldo()
{
	cout << saldo << endl;
	return saldo;
}

void Empresa::pagaSalario()
{
	int salarios_total = 0;
	for(unsigned int i = 0; i < funcionarios.size(); i++)
	{
		salarios_total = salarios_total + funcionarios[i].getSalario();
	}

	if (salarios_total > saldo)
		throw SaldoIndisponivel();
	else saldo -= salarios_total;
}

string Empresa::getNome() const
{
	return nomeEmpresa;
}

void Empresa::imprimeSaldo() const
{
	cout << "O seu saldo autal e de: " << saldo << " euros" << endl;
}

void Empresa::imprimeServico()
{
	for(unsigned int i = 0; i < servicos.size(); i++)
	{
		cout << "Servico " << i <<":" << endl;
		cout << "Camioes Utilizados:" << endl;
		for(unsigned int j = 0; j < servicos[i].getCamioes().size(); j++)
		{
			//"Camiao " << j + 1 << ": " << servicos[i].getCamioes[j]->getMarca() << "-" << servicos[i].getCamioes[j]->getTipo() ;
			//Nao esta a funionar, esta a dar erro

		}

		//Ainda nao esta completa
	}
}


void Empresa::ListaServicosExecucao()const
{
	for(unsigned i=0; i <servicos.size();i++)
	{
		if(servicos[i].getIniciado())
		{
			cout << servicos[i].getOrigem() << endl;
			cout << servicos[i].getDestino() << endl;
			cout << servicos[i].getDistancia() << endl;
			cout << servicos[i].getTipo_produto() << endl;
			cout << endl << endl;
		}
	}
}

void Empresa::ListaServicosCliente()const
{

	for (unsigned i=0; i < clientes.size();i++)
	{
		cout << clientes[i].getNome() << " :" << endl;

		for(unsigned j=0; j < servicos.size();j++)
		{
			if(clientes[i].getNif()==servicos[j].getNif())
			{
				cout << servicos[i].getOrigem() << endl;
				cout << servicos[i].getDestino() << endl;
				cout << servicos[i].getDistancia() << endl;
				cout << servicos[i].getTipo_produto() << endl;
				cout << endl << endl;

			}
		}
	}
}

void Empresa::ListaServicosCamiao()const
{
	vector<string> v_tipo;

	for (unsigned i=0; i < camioes.size();i++)
		v_tipo.push_back(camioes[i]->getTipo());


	for (unsigned i=0; i < v_tipo.size();i++)
	{
		for (unsigned j=i+1; j < v_tipo.size(); j++)
		{
			if (v_tipo[i]==v_tipo[j])
			{
				v_tipo.erase(v_tipo.begin()+j);//vou fazer um vetor só com os tipos de camioes que ha sem repetidos
				j--;
			}
		}
	}


	//vou imprimir cada tipo de serviço com todos os camioes desse serviço juntos

	for (unsigned i=0; i < v_tipo.size();i++)
	{
		for(unsigned j=0; j < camioes.size();j++)
		{
			if(v_tipo[i]==camioes[i]->getTipo())
			{
				cout << camioes[i]->getTipo();
				cout << camioes[i]->getCapacidade();
				cout << camioes[i]->getMarca();
				cout << endl << endl;
			}

		}
	}
}

void Empresa::listaClientes() const
{
	cout << "Clientes: " << endl;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		cout << i + 1 << ": " << clientes[i].getNome() << " - " << clientes[i].getNif() << endl;
	}
}
