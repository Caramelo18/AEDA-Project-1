/*
 * Empresa.cpp
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */
#include "Empresa.h"
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
		string matricula;
		int capacidade;
		stringstream ss;

		ss << temp;
		ss >> marca >> tipo >> capacidade >> matricula;

		if (tipo == "Normal")
		{
			Normal *cam = new Normal(marca, tipo, capacidade, matricula);
			camioes.push_back(cam);
		}

		if (tipo == "Congelacao")
		{
			Congelacao *cam1 = new Congelacao(marca, tipo, capacidade, matricula);
			camioes.push_back(cam1);
		}

		if (tipo == "Perigosos")
		{
			Perigosos *cam2 = new Perigosos(marca, tipo, capacidade, matricula);
			camioes.push_back(cam2);
		}

		if (tipo == "Animais")
		{
			Animais *cam3 = new Animais(marca, tipo, capacidade, matricula);
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

	ifstream fich4(ficser.c_str());
	if (!fich)
	{
		cerr << "Ficheiro nao encontrado";
		//fazer throw aqui
	}
	getline(fich4, temp);
	while(!fich4.eof())
	{
		getline(fich4, temp);
		stringstream ss;
		int id, distancia, cap;
		string origem, destino, tipo_produto, estado;
		ss << temp;
		ss >> id >> origem >> destino >> distancia >> tipo_produto >> cap >> estado;
		bool ter;
		if (estado == "T")
			ter = true;
		else
			ter = false;
		int gr;
		string grp;
		if (tipo_produto == "Congelacao")
			ss >> gr;
		else if (tipo_produto == "Perigosos")
			ss >> grp;

		getline(fich4, temp); // nif cliente
		int nif;
		stringstream ni(temp);
		ni >> nif;
		getline(fich4, temp); // matriculas dos camioes
		stringstream matri(temp);
		vector<string> mat;
		string m;
		while (matri >> m)
			mat.push_back(m);
		if (tipo_produto == "Congelacao")
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, gr, mat, ter);
		else if (tipo_produto == "Perigosos")
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, grp, mat, ter);
		else
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, mat, ter);
	}




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

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes);

	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << origem << " " << destino << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";

	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";

	fich.close();
}


void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, temp);

	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << origem << " " << destino << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";
	fich << " " << temp;

	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";

	fich.close();
}

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, nivel_p);

	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << origem << " " << destino << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";

	fich << " " << nivel_p;

	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";


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

void  Empresa::imprimeServico(Servico s) const
{
	cout << "Servico " << s.getID() <<":" << endl;
	cout << "Cliente: " << clientes[posCliente(s.getNif())].getNome() << endl;
	cout << s.getOrigem() << " - " << s.getDestino() << " - Distancia: " << s.getDistancia() << endl;
	cout << "Camioes Utilizados:" << endl;
	for(unsigned int j = 0; j < s.getCamioes().size(); j++)
	{
		cout << "Camiao " << j+1 << ": " << s.getCamioes()[j]->getMarca() << " - " << s.getCamioes()[j]->getMatricula() << " - " <<s.getCamioes()[j]->getTipo() << endl;
	}
	if (s.getTerminado())
		cout << "Terminado" << endl;
	else
		cout << "Em curso" << endl;
	cout << endl;
}

void Empresa::imprimeServicos() const
{
	for(unsigned int i = 0; i < servicos.size(); i++)
	{
		imprimeServico(servicos[i]);
	}
}

void Empresa::ListaServicosExecucao()const
{
	for(unsigned i=0; i <servicos.size();i++)
	{
		if(!servicos[i].getTerminado())
		{
			imprimeServico(servicos[i]);
		}
	}
}

void Empresa::ListaServicosCliente()const
{

	for (unsigned i=0; i < clientes.size();i++)
	{
		for(unsigned j=0; j < servicos.size();j++)
		{
			if(clientes[i].getNif()==servicos[j].getNif())
			{
				cout << clientes[i].getNome() << " :" << endl;
				cout << "Origem: " <<  servicos[j].getOrigem() << endl;
				cout << "Destino: " << servicos[j].getDestino() << endl;
				cout << "Distancia: " << servicos[j].getDistancia() << endl;
				cout << "Tipo de produto: " << servicos[j].getTipo_produto() << endl;
				cout << endl;

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
				cout << camioes[i]->getTipo() << " " << camioes[i]->getCapacidade() << " " << camioes[i]->getMarca() << endl;
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

int Empresa::posCliente(unsigned long nif) const
{
	for (unsigned int i = 0; i < clientes.size(); i++)
		if (clientes[i].getNif() == nif)
			return i;

	throw ClienteNaoExistente();
}

void Empresa::actualizaFicheiro()
{
	ofstream fich(ficca.c_str());
	if (!fich)
		cerr << "Ficheiro nao encontrado";

	fich << nomeEmpresa << endl;
	fich << "Saldo: " << saldo << endl;
	fich << "Camioes:";
	for(unsigned int i = 0; i < camioes.size(); i++)
		fich << endl << camioes[i]->getMarca() << " " << camioes[i]->getTipo() << " " << camioes[i]->getCapacidade() << " " << camioes[i]->getMatricula();
}

void Empresa::terminaServico(int ID)
{
	unsigned int i;
	for (i = 0; i < servicos.size(); i++)
	{
		if(servicos[i].getID() == ID)
			break;
	}

	if (i >= servicos.size())
		throw ServicoInexistente();

	servicos[i].termina_servico();

	EscreveServicoTerminado(ID, servicos[i].getTipo_produto());
}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<string> mat, bool ter)
{
	vector<Camiao *> c;

	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size();j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
				c.push_back(camioes[j]);
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c);

	if (!ter)
	{
		for (unsigned int i = 0; i < mat.size(); i++)
		{
			for (unsigned int j = 0; j < camioes.size();j++)
			{
				if(camioes[j]->getMatricula() == mat[i])
					camioes[j]->setDisponivel(false);
			}
		}
	}
	if (ter)
		s.setTermina();

	servicos.push_back(s);

}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp, vector<string> mat, bool ter)
{
	vector<Camiao *> c;

	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size(); j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
				c.push_back(camioes[j]);
		}
	}
	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c);
	if (!ter)
	{
		for (unsigned int i = 0; i < mat.size(); i++)
		{
			for (unsigned int j = 0; j < camioes.size(); j++)
			{
				if(camioes[j]->getMatricula() == mat[i])
					camioes[j]->setDisponivel(false);
			}
		}
	}
	servicos.push_back(s);
}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p, vector<string> mat, bool ter)
{
	vector<Camiao *> c;
	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size(); j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
				c.push_back(camioes[j]);
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c);

	if (!ter)
	{
		for (unsigned int i = 0; i < mat.size(); i++)
		{
			for (unsigned int j = 0; j < camioes.size(); j++)
			{
				if(camioes[j]->getMatricula() == mat[i])
					camioes[j]->setDisponivel(false);
			}
		}
	}
	servicos.push_back(s);
}

void Empresa::EscreveServicoTerminado(int ID, string tipo)
{
	ifstream fchl(ficser.c_str());
	int t = 0;
	string nivelp = "";
	while(!fchl.eof())
	{
		string line;
		stringstream ss;
		int iden;
		getline(fchl, line);
		ss << line;
		ss >> iden;
		if (iden == ID)
		{
			string temp;
			if(tipo == "Congelacao")
			{
				ss >> temp >> temp >> temp >> temp >> temp >> temp >> t;
			}
			else if (tipo == "Perigosos")
			{
				ss >> temp >> temp >> temp >> temp >> temp >> temp >> nivelp;
			}
		}
	}
	ofstream fich(ficser.c_str());

	fich << "Servicos: ";

	for (unsigned int i = 0; i < servicos.size(); i++)
	{
		fich << endl;
		if (servicos[i].getTipo_produto() == "Congelacao")
		{
			fich << servicos[i].getID() << " " << servicos[i].getOrigem() << " " << servicos[i].getDestino() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
			fich << t;
		}
		else if (servicos[i].getTipo_produto() == "Perigosos")
		{
			fich << servicos[i].getID() << " " << servicos[i].getOrigem() << " " << servicos[i].getDestino() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
			fich << nivelp;
		}
		else
		{
			fich << servicos[i].getID() << " " << servicos[i].getOrigem() << " " << servicos[i].getDestino() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
		}


		//falta conseguir escrever a temperatura e o tipo de perigosidade nos seus casos respetivos

		fich << endl << servicos[i].getNif() << endl;
		for (unsigned int j = 0; j < servicos[i].getCamioes().size(); j++)
			fich << servicos[i].getCamioes()[j]->getMatricula() << " ";

	}
	fich.close();
}


void Empresa::ImprimeListaCamioes()
{
	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		cout << "Camiao " << i+1 << ":" << endl;
		cout << "Marca: " << camioes[i]->getMarca() << endl;
		cout << "Tipo: " << camioes[i]->getTipo() << endl;
		cout << "Matricula: " << camioes[i]->getMatricula() << endl;
		cout << "Capacidade: " << camioes[i]->getCapacidade() << " Kg" << endl;
		cout << endl;
	}
}

void Empresa::ImprimeListaCamioesDisponiveis()
{
	unsigned int j = 1;
	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		if(camioes[i]->getDisponivel())
		{
			cout << "Camiao " << j << ":" << endl;
			cout << "Marca: " << camioes[i]->getMarca() << endl;
			cout << "Tipo: " << camioes[i]->getTipo() << endl;
			cout << "Matricula: " << camioes[i]->getMatricula() << endl;
			cout << "Capacidade: " << camioes[i]->getCapacidade() << " Kg" << endl;
			cout << endl;
			j++;
		}
	}
}

void Empresa::AdicionaCamiao()
{
	string tipo;
	string marca;
	int capacidade;
	string matricula;

	cout << "Insira o tipo de camiao que pretende adicionar: ";
	cin >> tipo;
	if (tipo != "Perigoso" && tipo != "perigoso" && tipo != "Congelacao" && tipo != "congelacao" && tipo != "Animais" && tipo != "animais" && tipo != "Normal" && tipo != "normal")
	{
		cout << "Tipo de camiao invalido" << endl;
		return;
	}
	cout << "Insira a marca: ";
	cin >> marca;
	cout << "Insira a capacidade: ";
	cin >> capacidade;
	cout << "Insira a matricula: ";
	cin >> matricula;
	cout << endl;
	if (tipo == "Normal" || tipo == "normal")
	{
		Normal *c = new Normal(marca, tipo, capacidade, matricula);
		camioes.push_back(c);
	}

	else if (tipo == "Perigoso" || tipo == "perigoso")
	{
		Perigosos *c = new Perigosos(marca, tipo, capacidade, matricula);
		camioes.push_back(c);
	}

	else if (tipo == "Congelacao" || tipo == "congelacao")
	{
		Congelacao *c = new Congelacao(marca, tipo, capacidade, matricula);
		camioes.push_back(c);
	}

	else if (tipo == "Animais" || tipo == "animais")
	{
		Animais *c = new Animais(marca, tipo, capacidade, matricula);
		camioes.push_back(c);
	}


	actualizaFicheiro();

	cout << "Camiao adicionado com sucesso" << endl << endl;
}
