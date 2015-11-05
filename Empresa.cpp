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
	vector<Funcionario *> funcs;
	funcionarios = funcs;

	ficca = doc + "/Camioes.txt";
	ficcli = doc + "/Clientes.txt";
	ficfun = doc + "/Funcionarios.txt";
	ficser = doc + "/Servicos.txt";


	ifstream fich(ficca.c_str());
	if (!fich)
		throw FicheiroInexistente(ficca);

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
		throw FicheiroInexistente(ficfun);

	getline(fich2,temp);

	while(!fich2.eof())
	{
		string nomeFunc;
		getline(fich2,nomeFunc);
		int salario;
		string disp;
		unsigned long BI;
		stringstream ss;
		getline(fich2,temp);

		ss << temp;
		ss >>  salario >> BI >> disp;

		Funcionario *func = new Funcionario(nomeFunc, salario, BI, disp);
		funcionarios.push_back(func);

	}

	fich2.close();

	ifstream fich3(ficcli.c_str());
	if (!fich3)
		throw FicheiroInexistente(ficcli);

	getline(fich3, temp);
	while (! fich3.eof())
	{
		string nomeCli;
		getline(fich3,nomeCli);
		unsigned long Nif;
		stringstream ss;
		getline(fich3, temp);
		ss << temp;
		ss >> Nif;

		Cliente cli = Cliente(nomeCli, Nif);
		clientes.push_back(cli);
	}
	fich3.close();


	ifstream fich4(ficser.c_str());
	if (!fich4)
		throw FicheiroInexistente(ficser);
	getline(fich4, temp);
	while(!fich4.eof())
	{
		getline(fich4, temp);
		stringstream ss;
		int id, distancia, cap;
		string origem, destino, tipo_produto, estado;
		ss << temp;
		ss >> id >> distancia >> tipo_produto >> cap >> estado;
		getline(fich4, origem);
		getline(fich4, destino);
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
		/*for (unsigned int i = 0; i < mat.size();i++)
		{
			if(!funcionarios[i]->getDisponivel())
				funcionarios[i]->setDisponibilidade(true);
		}*/
		getline(fich4, temp);
		stringstream funcionarios(temp);
		vector<unsigned long> funcs;
		unsigned long f;
		while (funcionarios >> f)
			funcs.push_back(f);

		if (tipo_produto == "Congelacao")
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, gr, mat, funcs, ter);
		else if (tipo_produto == "Perigosos")
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, grp, mat, funcs, ter);
		else
			leNovoServico(origem, destino, distancia, tipo_produto, cap, nif, mat, funcs, ter);
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

vector<Funcionario *> Empresa::getFuncionarios()
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
	cin.ignore(1000,'\n');
	getline(cin, nome);
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
	fich << cliente.getNome() << endl << cliente.getNif();

	cout << "Cliente adicionado com sucesso" << endl;

	fich.close();
}

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, funcionarios);

	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";

	fich << endl << origem << endl << destino;
	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";
	for (unsigned int i = 0; i < s.getFuncionarios().size(); i++)
		fich << s.getFuncionarios()[i]->getBI() << " ";

	fich.close();
	actualizaFicheiro();
}


void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, temp, funcionarios);

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
	for (unsigned int i = 0; i < s.getFuncionarios().size(); i++)
		fich << s.getFuncionarios()[i]->getBI() << " ";

	fich.close();
	actualizaFicheiro();
}

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p)
{

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, nivel_p, funcionarios);

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
	for (unsigned int i = 0; i < s.getFuncionarios().size(); i++)
		fich << s.getFuncionarios()[i]->getBI() << " ";


	fich.close();
	actualizaFicheiro();
}

void Empresa::contrataFuncionario()
{
	string nome;
	int salario;
	unsigned int BI;
	cout << "Insira o nome do funcionario: ";
	cin.ignore(1000,'\n');
	getline(cin,nome);
	cout << "Insira o salario do funcionario: ";
	cin >> salario;
	cout << "Insira o BI do funcionario: ";
	cin >> BI;

	Funcionario *f = new Funcionario(nome,salario,BI,"D");
	funcionarios.push_back(f);
	actualizaFicheiro();

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
		salarios_total = salarios_total + funcionarios[i]->getSalario();
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
	cout << endl;
	cout << "Servico " << s.getID() <<":" << endl;
	cout << "Cliente: " << clientes[posCliente(s.getNif())].getNome() << endl;
	cout << s.getOrigem() << " - " << s.getDestino() << " - Distancia: " << s.getDistancia() << "km" <<endl;
	cout << "Camioes Utilizados:" << endl;
	for(unsigned int j = 0; j < s.getCamioes().size(); j++)
	{
		cout << "Camiao " << j+1 << ": " << s.getCamioes()[j]->getMarca() << " - " << s.getCamioes()[j]->getMatricula() << " - " <<s.getCamioes()[j]->getTipo() << endl;
	}
	for(unsigned int j = 0; j < s.getFuncionarios().size(); j++)
	{
		cout << "Funcionario " << j+1 << ": " << s.getFuncionarios()[j]->getNome() << " - " << s.getFuncionarios()[j]->getBI() << endl;
	}
	if (s.getTerminado())
		cout << "Terminado" << endl;
	else
		cout << "Em curso" << endl;

}

void Empresa::imprimeServicos()
{
	for(unsigned int i = 0; i < servicos.size(); i++)
	{
		imprimeServico(servicos[i]);
		unsigned int mot = servicos[i].getCamioes().size();
	}
}

void Empresa::ListaServicosExecucao()const
{
	for(unsigned i=0; i <servicos.size();i++)
	{
		if(!servicos[i].getTerminado())
			imprimeServico(servicos[i]);
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

	fich << nomeEmpresa << endl;
	fich << "Saldo: " << saldo << endl;
	fich << "Camioes:";
	for(unsigned int i = 0; i < camioes.size(); i++)
		fich << endl << camioes[i]->getMarca() << " " << camioes[i]->getTipo() << " " << camioes[i]->getCapacidade() << " " << camioes[i]->getMatricula();

	ofstream fich1(ficfun.c_str());
	fich1 << "Funcionarios: ";
	for (unsigned int i = 0; i < funcionarios.size(); i++)
	{
		fich1 << endl << funcionarios[i]->getNome() << endl << funcionarios[i]->getSalario() << " " << funcionarios[i]->getBI();
		if (funcionarios[i]->getDisponivel())
			fich1 << " D" ;
		else if (!funcionarios[i]->getDisponivel())
			fich1 << " E" ;
	}
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
	actualizaFicheiro();
}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<string> mat, vector<unsigned long> funcs, bool ter)
{
	vector<Camiao *> c;

	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size();j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
			{
				c.push_back(camioes[j]);
				camioes[j]->setDisponivel(true);
			}
		}
	}

	vector<Funcionario *> f;

	for (unsigned int i = 0; i < funcs.size(); i++)
	{
		for (unsigned int j = 0; j < funcionarios.size(); j++)
		{
			if(funcionarios[j]->getBI() == funcs[i])
			{
				f.push_back(funcionarios[j]);
				funcionarios[j]->setDisponibilidade(true);
			}
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, f);

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

		for (unsigned int i = 0; i < funcs.size(); i++)
		{
			for (unsigned int j = 0; j < funcionarios.size(); j++)
			{
				if(funcionarios[j]->getBI() == funcs[i])
					funcionarios[j]->setDisponibilidade(false);
			}
		}
	}
	if (ter)
		s.termina_servico();
	servicos.push_back(s);

}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp, vector<string> mat, vector<unsigned long> funcs, bool ter)
{
	vector<Camiao *> c;

	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size(); j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
			{
				c.push_back(camioes[j]);
				camioes[j]->setDisponivel(true);
			}
		}
	}


	vector<Funcionario *> f;

	for (unsigned int i = 0; i < funcs.size(); i++)
	{
		for (unsigned int j = 0; j < funcionarios.size(); j++)
		{
			if(funcionarios[j]->getBI() == funcs[i])
			{
				f.push_back(funcionarios[j]);
				funcionarios[j]->setDisponibilidade(true);
			}
		}
	}
	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, temp, f);
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

		for (unsigned int i = 0; i < funcs.size(); i++)
		{
			for (unsigned int j = 0; j < funcionarios.size(); j++)
			{
				if(funcionarios[j]->getBI() == funcs[i])
					funcionarios[j]->setDisponibilidade(false);
			}
		}
	}
	if (ter)
		s.termina_servico();
	servicos.push_back(s);
}

void Empresa::leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p, vector<string> mat, vector<unsigned long> funcs, bool ter)
{
	vector<Camiao *> c;
	for (unsigned int i = 0; i < mat.size(); i++)
	{
		for (unsigned int j = 0; j < camioes.size(); j++)
		{
			if(camioes[j]->getMatricula() == mat[i])
			{
				c.push_back(camioes[j]);
				camioes[j]->setDisponivel(true);
			}
		}
	}

	vector<Funcionario *> f;

	for (unsigned int i = 0; i < funcs.size(); i++)
	{
		for (unsigned int j = 0; j < funcionarios.size(); j++)
		{
			if(funcionarios[j]->getBI() == funcs[i])
			{
				f.push_back(funcionarios[j]);
				funcionarios[j]->setDisponibilidade(true);
			}
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, nivel_p, f);

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

		for (unsigned int i = 0; i < funcs.size(); i++)
		{
			for (unsigned int j = 0; j < funcionarios.size(); j++)
			{
				if(funcionarios[j]->getBI() == funcs[i])
					funcionarios[j]->setDisponibilidade(false);
			}
		}
	}

	if (ter)
		s.termina_servico();

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

		fich << endl << servicos[i].getNif() << endl;
		for (unsigned int j = 0; j < servicos[i].getCamioes().size(); j++)
			fich << servicos[i].getCamioes()[j]->getMatricula() << " ";
		for (unsigned int k = 0; k < servicos[i].getFuncionarios().size(); k++)
			fich << servicos[i].getFuncionarios()[k]->getBI() << " ";

	}
	fich.close();
}


void Empresa::ImprimeListaCamioes()
{
	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		cout << "Camiao " << i+1 << ":" << endl;
		camioes[i]->imprimeCamiao();
	}
}

void Empresa::ImprimeListaCamioesDisponiveis()
{
	unsigned int cnt = 0;
	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		if(camioes[i]->getDisponivel())
		{
			cout << "Camiao " << i+1 << ":" << endl;
			camioes[i]->imprimeCamiao();
			cnt++;
		}
	}
	if (cnt == 0)
		cout << "Sem camioes disponiveis" << endl << endl;
}

void Empresa::AdicionaCamiao()
{
	string tipo;
	string marca;
	int capacidade;
	string matricula;
	int preco;

	cout << "Insira o tipo de camiao que pretende adicionar: ";
	cin >> tipo;
	if (tipo != "Perigosos" && tipo != "perigosos" && tipo != "Congelacao" && tipo != "congelacao" && tipo != "Animais" && tipo != "animais" && tipo != "Normal" && tipo != "normal")
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
	cout << "Insira o preco do camiao: ";
	cin >> preco;
	if(preco > saldo)
		throw SaldoIndisponivel();
	cout << endl;
	if (tipo == "Normal" || tipo == "normal")
	{
		Normal *c = new Normal(marca, tipo, capacidade, matricula);
		camioes.push_back(c);
	}

	else if (tipo == "Perigosos" || tipo == "perigosos")
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

void Empresa::listaFuncionarios() const
{
	for (unsigned int i = 0; i < funcionarios.size(); i++)
		funcionarios[i]->imprimeFuncionario();
}

void Empresa::listaFuncionariosDisponiveis() const
{
	unsigned int cnt = 0;
	for (unsigned int i = 0; i < funcionarios.size(); i++)
	{
		if(funcionarios[i]->getDisponivel())
		{
			cnt++;
			funcionarios[i]->imprimeFuncionario();
		}
	}
	if (cnt == 0)
		cout << "Sem funcionarios disponiveis" << endl;
}

void Empresa::despedeFuncionario()
{
	unsigned long BI;
	cout << "Insira o BI do funcionario a despedir: ";
	cin >> BI;
	unsigned int i;
	for (i = 0; i < funcionarios.size(); i++)
	{
		if (funcionarios[i]->getBI() == BI)
		{
			if(!funcionarios[i]->getDisponivel())
				cout << "Impossivel despedir funcionario, transporte em curso" << endl;
			else
			{
				funcionarios.erase(funcionarios.begin()+i);
				actualizaFicheiro();
				break;
			}
		}
	}
}
