/*
 * Empresa.cpp
 */
#include "Empresa.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


Empresa::Empresa()
{
	saldo = 0;
}

Empresa::Empresa(string doc)
{

	vector<Servico> ser;
	servicos = ser;
	vector<Camiao *> cams;
	camioes = cams;
	vector<Cliente> clis;
	clientes = clis;
	priority_queue<Oficina> ofi;
	oficinas = ofi;


	ficca = doc + "/Camioes.txt";
	ficcli = doc + "/Clientes.txt";
	ficfun = doc + "/Funcionarios.txt";
	ficser = doc + "/Servicos.txt";
	ficofi = doc + "/Oficinas.txt";


	fstream fich(ficca.c_str());
	long sal;
	string nome;
	if (!fich)
	{
		string opt;
		cout << "Nao existe empresa. Pretende criar uma nova empresa? ";
		cin >> opt;
		if (opt == "S" || opt == "s" || opt == "Sim" || opt == "sim")
		{
			cout << "Insira o nome da empresa: ";
			cin.ignore(100, '\n');
			getline(cin, nome);
			cout << "Insira o saldo inicial da empresa: ";
			cin >> sal;
			nomeEmpresa = nome;
			saldo = sal;
			fich << nome << endl << "Saldo: " << sal << endl << "Camioes: " << endl;
			ofstream fich2(ficfun.c_str());
			fich2 << "Funcionarios: " << endl;
			ofstream fich3(ficcli.c_str());
			fich3 << "Clientes:";
			ofstream fich4(ficser.c_str());
			fich4 << "Servicos:" << endl;
			ofstream fich5(ficofi.c_str());
			fich5 << "Oficinas:" << endl;
		}
		return;
	}
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

	vector<Funcionario> vec;

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
		unsigned int horas;
		unsigned long BI;
		stringstream ss;
		getline(fich2,temp);

		ss << temp;
		ss >>  salario >> BI >> disp >> horas;

		Funcionario *func = new Funcionario(nomeFunc, salario, BI, disp, horas);
		funcionarios.insert(func);
		Funcionario copia = *func;
		vec.push_back(copia);

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
		string in;
		getline(fich3, temp);
		ss << temp;
		ss >> Nif >> in;

		Cliente cli = Cliente(nomeCli, Nif);
		if(in == "A")
			clientes.push_back(cli);
		else
			clInact.insert(cli);
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

	//
	ifstream fich5(ficofi.c_str());
	if (!fich5)
		throw FicheiroInexistente(ficofi);
	getline(fich5, temp);

	while(!fich5.eof())
	{
		string nomeOfi;
		getline(fich5,nomeOfi);

		getline(fich5, temp);
		stringstream ss;
		int disp;
		string marca;
		ss << temp;
		ss >> marca >> disp;

		vector<string> matriculas;
		string matri;

		while(ss >> matri)
		{
			cout << matri << endl;
			matriculas.push_back(matri);
		}
		vector<Camiao*>cami;
		for(unsigned int i=0; i < matriculas.size(); i++)
		{
			matri= matriculas[i];
			cami.push_back(procuraCamiao(matri));
		}

		for(unsigned int i = 0; i < cami.size(); i++)
			cami[i]->setDisponivel(false);

		Oficina Ofi(nomeOfi, marca, disp, cami);
		oficinas.push(Ofi);

	}

	fich5.close();
	set<Funcionario*, classcomp>::iterator it;

	for(it = funcionarios.begin(); it != funcionarios.end(); it++)
	{
		for(unsigned int i = 0; i < vec.size(); i++)
		{
			if ((*it)->getNome() == vec[i].getNome())
			{
				(*it)->setHoras(vec[i].getHoras());
				break;
			}
		}
	}

	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}

}

vector<Camiao *> Empresa::getCamioes()
{
	return camioes;
}

set<Funcionario *, classcomp> Empresa::getFuncionarios()
{
	return funcionarios;
}

vector<Funcionario *> Empresa::getFuncionariosvetor()
{
	vector<Funcionario *> res;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		res.push_back(*iterator);
	}

	return res;
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
		if (clientes[i].getNif() == Nif)
			throw ClienteJaExistente(nome, Nif);
	}

	clientes.push_back(cliente);

	ofstream fich(ficcli.c_str(), ofstream::app);

	fich << endl;
	fich << cliente.getNome() << endl << cliente.getNif() << "  A";

	cout << "Cliente adicionado com sucesso" << endl;

	fich.close();
}

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif)
{

	vector<Funcionario *> res;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		res.push_back(*iterator);
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, res);

	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}

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
	fich << endl;
	for (unsigned int i = 0; i < s.getFuncionarios().size(); i++)
		fich << s.getFuncionarios()[i]->getBI() << " ";

	fich.close();
	actualizaFicheiro();
}


void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp)
{

	vector<Funcionario *> res;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		res.push_back(*iterator);
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, temp, res);


	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}

	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";
	fich << " " << temp;

	fich << endl <<  origem << endl << destino;

	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";
	fich << endl;
	for (unsigned int i = 0; i < s.getFuncionarios().size(); i++)
		fich << s.getFuncionarios()[i]->getBI() << " ";

	fich.close();
	actualizaFicheiro();
}

void Empresa::novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p)
{

	vector<Funcionario *> res;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		res.push_back(*iterator);
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, nivel_p, res);


	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}


	servicos.push_back(s);

	saldo += s.getPreco();

	ofstream fich(ficser.c_str(), ofstream::app);

	fich << endl;
	fich << s.getID() << " " << distancia << " " << tipo_produto << " " << capacidade;
	if(s.getTerminado())
		fich << " T";
	else
		fich << " E";

	fich << " " << nivel_p;
	fich << endl <<  origem << endl << destino;
	fich << endl << Nif << endl;
	for (unsigned int i = 0; i < s.getCamioes().size(); i++)
		fich << s.getCamioes()[i]->getMatricula() << " ";
	fich << endl;
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

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		if((*iterator)->getBI() == BI)
		{
			cerr << "Funcionario com o BI " << BI << " ja existe." << endl;
			return;
		}
	}

	Funcionario *f = new Funcionario(nome,salario,BI,"D",0);
	funcionarios.insert(f);
	actualizaFicheiro();

}

void Empresa::pagaSalario()
{
	int salarios_total = 0;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		salarios_total = salarios_total + (*iterator)->getSalario();
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

void  Empresa::imprimeServico(Servico s)
{
	cout << endl;
	cout << "Servico " << s.getID() <<":" << endl;
	if(pesquisaCliente(s.getNif(), 0) == 1)
	{
		defineClienteActivo(s.getNif());
		cout << "Cliente: " << clientes[posCliente(s.getNif())].getNome() << endl;
		defineClienteInactivo(s.getNif());
	}
	else
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
		imprimeServico(servicos[i]);

}

void Empresa::ListaServicosExecucao()
{
	for(unsigned i=0; i <servicos.size();i++)
	{
		if(!servicos[i].getTerminado())
			imprimeServico(servicos[i]);
	}
}

void Empresa::ListaServicosCliente()
{
	unsigned long nif;
	cout << "Insira o NIF do cliente: ";
	cin >> nif;
	int i;
	try
	{
		i = posCliente(nif);
	}
	catch (ClienteNaoExistente &c)
	{
		cout << "Cliente nao existe. " << endl;
		return;
	}

	cout << clientes[i].getNome() << ":" << endl;
	for(unsigned j=0; j < servicos.size();j++)
	{
		if(clientes[i].getNif()==servicos[j].getNif())
			imprimeServico(servicos[j]);
	}
	cout << endl;

}

void Empresa::ListaServicosCamiao()
{

	unsigned int count = 0;
	for (unsigned i=0; i < camioes.size();i++)
	{

		for(unsigned int j = 0; j < servicos.size(); j++)
		{

			for(unsigned int k = 0; k < servicos[j].getCamioes().size(); k++)
			{
				if (camioes[i]->getMatricula() == servicos[j].getCamioes()[k]->getMatricula())
				{
					cout << "Camiao " << camioes[i]->getTipo() << " com matricula " << camioes[i]->getMatricula() << ":" << endl;
					imprimeServico(servicos[j]);
					count++;
					cout << endl << endl;
				}
			}
			count = 0;
		}
	}
}

bool ordenaApontaCamioes( Camiao *C1, Camiao *C2)
{

	if(C1->getMarca() < C2->getMarca())
		return true;
	if(C1->getMarca()==C2->getMarca())
	{
		if(C1->getCapacidade() < C2->getCapacidade())

			return true;
		else
			return false;
	}
	else
		return false;

}
void Empresa::ListaCamioesOrdenados()const
{

	vector<Camiao *> C =camioes;
	sort(C.begin(),C.end(),ordenaApontaCamioes);

	for (unsigned int i = 0; i < C.size(); i++)
	{
		cout << "Camiao " << i+1 << ":" << endl;
		C[i]->imprimeCamiao();
	}



}
void Empresa::listaClientes() const
{
	cout << "Clientes: " << endl;
	for (unsigned int i = 0; i < clientes.size(); i++)
		cout << i + 1 << ": " << clientes[i].getNome() << " - " << clientes[i].getNif() << endl;

}

void Empresa::listaClientesOrdenados()
{
	vector<Cliente> cli= clientes;
	insertionSort(cli);

	cout << "Clientes: " << endl;
	for (unsigned int i = 0; i < cli.size(); i++)
		cout << i + 1 << ": " << cli[i].getNome() << " - " << cli[i].getNif() << endl;

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

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		fich1 << endl << (*iterator)->getNome() << endl << (*iterator)->getSalario() << " " << (*iterator)->getBI();
		if ((*iterator)->getDisponivel())
			fich1 << " D " ;
		else if (!(*iterator)->getDisponivel())
			fich1 << " N " ;
		fich1 << (*iterator)->getHoras();

	}
	ofstream fich2(ficofi.c_str());
	fich2 << "Oficinas: ";

	priority_queue<Oficina> copia=oficinas;
	while(!copia.empty())
	{
		Oficina F=copia.top();
		copia.pop();
		fich2 << endl << F.getNome() << endl;
		fich2 << F.getMarca() << " " << F.getDisp();

		for (unsigned int i=0; i < F.getVeiculos().size(); i++)
			fich2 << " " << F.getVeiculos()[i]->getMatricula();
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

		set<Funcionario*, classcomp>::iterator iterator;

		for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
		{
			if((*iterator)->getBI() == funcs[i])
			{
				f.push_back(*iterator);
				(*iterator)->setDisponibilidade(true);
			}
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, f);


	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}


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
			set<Funcionario*, classcomp>::iterator iterator;

			for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
			{
				if((*iterator)->getBI() == funcs[i])
					(*iterator)->setDisponibilidade(false);
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
		set<Funcionario*, classcomp>::iterator iterator;

		for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
		{
			if((*iterator)->getBI() == funcs[i])
			{
				f.push_back(*iterator);
				(*iterator)->setDisponibilidade(true);
			}
		}
	}
	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, temp, f);


	vector<Funcionario *> copia;

	set<Funcionario*, classcomp>::iterator iterator2;

	for(iterator2 = funcionarios.begin(); iterator2 != funcionarios.end(); iterator2++)
	{
		copia.push_back(*iterator2);
		funcionarios.erase(*iterator2);
	}

	for(unsigned int i=0; i < copia.size(); i++)
	{
		funcionarios.insert(copia[i]);
	}


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
			set<Funcionario*, classcomp>::iterator iterator;

			for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
			{
				if((*iterator)->getBI() == funcs[i])
					(*iterator)->setDisponibilidade(false);
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
		set<Funcionario*, classcomp>::iterator iterator;

		for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
		{
			if((*iterator)->getBI() == funcs[i])
			{
				f.push_back(*iterator);
				(*iterator)->setDisponibilidade(true);
			}
		}
	}

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, c, nivel_p, f);

	vector<Funcionario *> copia;

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
			set<Funcionario*, classcomp>::iterator iterator;

			for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
			{
				if((*iterator)->getBI() == funcs[i])
					(*iterator)->setDisponibilidade(false);
			}
		}
	}

	if (ter)
		s.termina_servico();

	servicos.push_back(s);
}

void Empresa::EscreveServicoTerminado(int ID, string tipo)
{
	ofstream fich(ficser.c_str());

	fich << "Servicos: ";

	for (unsigned int i = 0; i < servicos.size(); i++)
	{
		fich << endl;
		if (servicos[i].getTipo_produto() == "Congelacao")
		{
			fich << servicos[i].getID() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
		}
		else if (servicos[i].getTipo_produto() == "Perigosos")
		{
			fich << servicos[i].getID() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
		}
		else
		{
			fich << servicos[i].getID() << " " << servicos[i].getDistancia() << " " << servicos[i].getTipo_produto() << " " << servicos[i].getCapacidade();
			if(servicos[i].getTerminado())
				fich << " T ";
			else
				fich << " E ";
		}

		fich << endl << servicos[i].getOrigem() << endl << servicos[i].getDestino();
		fich << endl << servicos[i].getNif() << endl;
		for (unsigned int j = 0; j < servicos[i].getCamioes().size(); j++)
			fich << servicos[i].getCamioes()[j]->getMatricula() << " ";
		fich << endl;
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
	if (capacidade <= 0)
	{
		cerr << "Capacidade invalida" << endl;
		return;
	}
	cout << "Insira a matricula: ";
	cin >> matricula;
	for(unsigned int i = 0; i < camioes.size(); i++)
	{
		if (camioes[i]->getMatricula() == matricula)
			throw CamiaoJaExistente(matricula);
	}

	cout << "Insira o preco do camiao: ";
	cin >> preco;
	if(preco > saldo)
		throw SaldoIndisponivel();
	else if (preco < 0)
	{
		cout << "Preco invalido" << endl;
		return;
	}
	saldo -= preco;
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
	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		(*iterator)->imprimeFuncionario();
	}
}

bool ordenaApontaFuncionarios( const Funcionario *f1,  const Funcionario *f2)
{
	if (f1->getNome()< f2->getNome())
		return true;
	if(f1->getNome()== f2->getNome())
	{
		if(f1->getBI()< f2->getBI())
			return true;
		else
			return false;
	}
	else
		return false;
}
void Empresa::listaFuncionariosOrdenada()const
{
	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		(*iterator)->imprimeFuncionario();

	}

}

void Empresa::listaFuncionariosDisponiveis() const
{
	unsigned int cnt = 0;

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		if((*iterator)->getDisponivel())
		{
			cnt++;
			(*iterator)->imprimeFuncionario();
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

	set<Funcionario*, classcomp>::iterator iterator;

	for(iterator = funcionarios.begin(); iterator != funcionarios.end(); iterator++)
	{
		if ((*iterator)->getBI() == BI)
		{
			if(!(*iterator)->getDisponivel())
				cout << "Impossivel despedir funcionario, transporte em curso" << endl;
			else
			{
				funcionarios.erase(*iterator);
				actualizaFicheiro();
				break;
			}
		}
	}
}

void Empresa::retiraCamiao(string matricula)
{
	unsigned int i;
	for (i = 0; i < camioes.size(); i++)
	{
		if(camioes[i]->getMatricula() == matricula)
			break;
	}

	if(i == camioes.size())
	{
		cout << "Camiao inexistente" << endl;
		return;
	}

	else
		camioes.erase(camioes.begin() + i);

	actualizaFicheiro();

	cout << "Camiao retirado com sucesso" << endl;
}

void Empresa::retiraCliente(unsigned long Nif)
{
	int pos;

	try
	{
		pos = posCliente(Nif);
	}
	catch (ClienteNaoExistente &c)
	{
		cout << "Cliente nao existe. " << endl;
		return;
	}

	clientes.erase(clientes.begin() + pos);

	ofstream fich(ficcli.c_str());

	fich << "Clientes:";
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		fich << endl;
		fich << clientes[i].getNome() << endl << clientes[i].getNif() << " A";
	}
	cout << "Cliente retirado com sucesso" << endl;

	fich.close();
}

void Empresa::editaCliente()
{
	int op;
	string nome;
	unsigned long Nif;

	cout << "1 - Alterar o nome" << endl;
	cout << "2 - Alterar o Nif" << endl;
	cout << endl;
	cout << "Escolha a opção pretendida: ";
	cin >> op;
	cout << endl;

	unsigned int i;

	if (op == 1)
	{
		cout << "Insira o Nif do cliente ao qual pretende editar o nome: ";
		cin >> Nif;

		for(i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].getNif() == Nif)
				break;
		}

		if (i == clientes.size())
		{
			cout << "Nao existe nenhum cliente com o Nif " << Nif << endl;
			return;
		}

		cin.ignore(1000, '\n');
		cout << "Insira o novo nome: ";
		getline(cin, nome);
		cin.clear();

		clientes[i].setNome(nome);

		ofstream fich(ficcli.c_str());

		fich << "Clientes:";
		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			fich << endl;
			fich << clientes[i].getNome() << endl << clientes[i].getNif();
		}
		fich.close();

		cout << "Cliente alterado com sucesso" << endl;
	}

	else if (op == 2)
	{

		cout << "Insira o nome do cliente ao qual pretende editar o Nif: ";
		cin >> nome;

		unsigned int i;

		for(i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].getNome() == nome)
				break;
		}

		if (i == clientes.size())
		{
			cout << "Nao existe nenhum cliente com o Nome " << nome << endl;
			return;
		}

		cout << "Insira o novo Nif: ";
		cin >> Nif;


		clientes[i].setNif(Nif);

		ofstream fich(ficcli.c_str());

		fich << "Clientes:";
		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			fich << endl;
			fich << clientes[i].getNome() << endl << clientes[i].getNif();
		}

		fich.close();

		cout << "Cliente alterado com sucesso" << endl;
	}

	else
		cout << "Opcao Invalida" << endl;
}

void Empresa::adicionaOficina()
{
	string marca;
	string nome;


	cout << "Insira o nome da Oficina: ";
	cin.ignore(1000,'\n');
	getline(cin, nome);

	cout << "Insira a marca da Oficina: ";
	getline(cin, marca);

	vector<Camiao*> v;
	Oficina F(nome, marca, 0,v);

	existeOficina(F);

	oficinas.push(F);

	actualizaFicheiro();
	cout << "Oficina adicionada com sucesso" << endl;


}

Oficina Empresa::serUsual(Camiao* C)
{
	bool encontrou = false;
	priority_queue<Oficina>  copia;
	Oficina F;

	if(oficinas.empty())
		throw OficinaInexistente ();

	while(!oficinas.empty())
	{
		F = oficinas.top();
		oficinas.pop();

		if(!F.camiaoNaOficina(C))
		{
			encontrou = true;
			break;
		}
		else
			copia.push(F);


	}
	while(!copia.empty())
	{
		Oficina FF = copia.top();
		copia.pop();
		oficinas.push(FF);
	}
	//

	if(!encontrou)
		throw OficinaNaoApropriada();

	return F;
}


Oficina Empresa::serEspeci(Camiao* C)
{
	priority_queue<Oficina>  copia;

	string marca = C->getMarca();
	Oficina F;
	bool encontrou = false;

	if(oficinas.empty())
		throw OficinaNaoApropriada();

	while(!oficinas.empty())
	{
		F = oficinas.top();
		oficinas.pop();

		if(F.getMarca() == marca)
		{
			if(!F.camiaoNaOficina(C))
			{

				encontrou = true;
				break;
			}
			else
				copia.push(F);
		}
		else
			copia.push(F);

	}
	while(!copia.empty())
	{
		Oficina FF = copia.top();
		copia.pop();
		oficinas.push(FF);
	}

	if(!encontrou)
		throw OficinaNaoApropriada();

	cout << "encontrou uma oficina serEspeci" << endl;
	return F;
}

void Empresa::fazSerEspeci()
{
	cout << "Matricula do Camiao: ";
	string matricula;

	cin.ignore(1000, '\n');
	getline(cin, matricula);

	Camiao* C = procuraCamiao(matricula);
	if(!C->getDisponivel())
	{
		cout << "Camiao indisponivel" << endl;
		return;
	}

	Oficina F;
	try
	{
		F = serEspeci(C);
	}
	catch(OficinaNaoApropriada & FF)
	{
		cout << "Nao existe oficina apropriada para este tipo de servico" << endl;
		return;
	}

	for(unsigned int i=0; i < camioes.size(); i++)
	{
		if(camioes[i]->getMatricula() == C->getMatricula())
		{
			camioes[i]->setDisponivel(false);
			break;
		}
	}
	F.fazServico(C);

	oficinas.push(F);

}

void Empresa::fazSerUsual(){

	cout << "Matricula do Camiao: ";
	string matricula;

	cin.ignore(1000, '\n');
	getline(cin, matricula);

	Camiao* C = procuraCamiao(matricula);
	if(!C->getDisponivel())
	{
		cout << "Camiao indisponivel" << endl;
		return;
	}

	Oficina F;
	try
	{
		F = serUsual( C);
	}
	catch(OficinaInexistente & f)
	{
		cout << "Nao existe oficinas" << endl;
		return;
	}

	try
	{
		for(unsigned int i=0; i < camioes.size(); i++)
		{
			if(camioes[i]->getMatricula() == C->getMatricula())
			{
				camioes[i]->setDisponivel(false);
				break;
			}
		}
		F.fazServico(C);
	}
	catch(OficinaNaoApropriada & f)
	{
		cout << "Nao existe oficina apropriada para este tipo de servico" << endl;
		return;
	}


	oficinas.push(F);
}

Camiao* Empresa::procuraCamiao(string Matri)
{
	string marca;
	bool encontrou = false;
	unsigned int i;
	for(i = 0; i < camioes.size(); i++)
	{
		if(camioes[i]->getMatricula() == Matri)
		{
			encontrou = true;
			break;
		}

	}
	if(! encontrou)
		throw CamiaoNaoExistente();

	return camioes[i];


}

vector<Oficina> Empresa::procuraCamiaoNaFila(Camiao* C)
{
	priority_queue<Oficina> copia;
	Oficina F;
	vector <Oficina> oficinasAtualizar;

	bool encontrou = false;

	while(!oficinas.empty())
	{
		F = oficinas.top();
		oficinas.pop();

		if(F.camiaoNaOficina(C))
		{
			oficinasAtualizar.push_back(F);
			encontrou = true;
		}
		else
			copia.push(F);
	}

	while(!copia.empty())
	{
		Oficina esta= copia.top();
		copia.pop();
		oficinas.push(esta);
	}

	if(!encontrou)
		return oficinasAtualizar;
}

void Empresa::termiServico()
{
	cout << "Matricula do veiculo que pretende terminar o servico: ";

	string matricula;
	cin.ignore(1000, '\n');
	getline(cin, matricula);
	Camiao* C;

	try
	{
		C = procuraCamiao(matricula);
	}
	catch (CamiaoNaoExistente & C)
	{
		cout << "Camiao nao existente na empresa" << endl;
		return;
	}

	vector<Oficina> ofi;
	ofi= procuraCamiaoNaFila(C);

	for(unsigned int i=0; i < camioes.size(); i++)
	{
		if(camioes[i]->getMatricula() == C->getMatricula())
			camioes[i]->setDisponivel(true);
		break;
	}

	for(unsigned int i=0; i < ofi.size(); i++)
	{
		ofi[i].termServico(C);
		oficinas.push(ofi[i]);
		cout << "terminou um servico" << endl;
	}
}

void Empresa::listaOficinas()
{
	if(oficinas.empty())
		cout << "Sem oficinas para mostrar" << endl;

	priority_queue<Oficina> copia = oficinas;
	while(!copia.empty())
	{
		Oficina F = copia.top();
		cout << F;
		copia.pop();
	}
}

Oficina Empresa::procuraOficina(Oficina F)
{
	priority_queue<Oficina> copia ;
	bool encontrou = false;
	bool temVeiculos = false;
	Oficina esta;

	while (!oficinas.empty())
	{
		esta = oficinas.top();
		oficinas.pop();

		if(F.getMarca() == esta.getMarca() && F.getNome() == esta.getNome())
		{
			encontrou = true;
			if(esta.getVeiculos().size() == 0)
				break;

			else
			{
				copia.push(esta);
				temVeiculos = true;
			}

		}
		else
			copia.push(esta);
	}

	while(! copia.empty())
	{
		oficinas.push(copia.top());
		copia.pop();
	}

	if(! encontrou)
		throw OficinaInexistente();

	if(temVeiculos)
		throw OficinaNaoApropriada();

	return esta;
}

void Empresa::removeOficina()
{
	string marca;
	string nome;

	cout << "Insira o nome da Oficina: ";
	cin.ignore(1000,'\n');
	getline(cin, nome);

	cout << "Insira a marca da Oficina: ";
	getline(cin, marca);

	vector<Camiao*> v;
	Oficina F(nome, marca, 0, v);

	try
	{
		procuraOficina(F);
	}
	catch(OficinaNaoApropriada & f)
	{
		cout << "Nao e possivel remover a oficina, esta ocupada" << endl;
		return;
	}

	cout << "Oficina removida com sucesso" << endl;
}

bool Empresa::existeOficina(Oficina F)
{
	priority_queue<Oficina> copia = oficinas ;
	bool encontrou = false;
	Oficina esta;

	while (!copia.empty())
	{
		esta = copia.top();
		copia.pop();

		if(F.getMarca() == esta.getMarca() && F.getNome() == esta.getNome())
			throw OficinaJaExistente();

	}
	return false;
}

void Empresa::imprimeClientesIn () const
{
	if(clInact.empty())
	{
		cout << "Sem clientes inactivos" << endl;
	}
	hashClientes::const_iterator it;

	for(it = clInact.begin(); it != clInact.end(); it++)
		cout << it->getNome() << " - " << it->getNif() << endl;

}

void Empresa::actualizaClientes()
{
	ofstream fich(ficcli.c_str());

	fich << "Clientes:";
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		fich << endl;
		fich << clientes[i].getNome() << endl << clientes[i].getNif() << " A";
	}

	hashClientes::iterator it;
	for(it = clInact.begin(); it != clInact.end(); it++)
	{
		fich << endl;
		fich << it->getNome() << endl << it->getNif() << " I";
	}
	fich.close();
}

void Empresa::defineClienteInactivo(unsigned long nif)
{
	int pos;

	try
	{
		pos = posCliente(nif);
	}
	catch (ClienteNaoExistente &c)
	{
		cout << "Cliente nao existe. " << endl;
		return;
	}

	Cliente c = clientes[pos];
	clientes.erase(clientes.begin() + pos);
	clInact.insert(c);
	actualizaClientes();
}

void Empresa::defineClienteActivo(unsigned long nif)
{
	hashClientes::iterator it;
	string nome;
	for(it = clInact.begin(); it != clInact.end(); it++)
	{
		if(it->getNif() == nif)
		{
			nome = it->getNome();
			clInact.erase(*it);
			Cliente c = Cliente(nome, nif);
			clientes.push_back(c);
			actualizaClientes();
			return;
		}
	}

	cout << "Cliente nao esta inactivo" << endl;

}

int Empresa::pesquisaCliente(unsigned long nif, int show)
{

	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getNif() == nif)
		{
			if(show == 1)
				cout << clientes[i].getNome() << " - " << nif << " - Activo" << endl;
			return 0;
		}
	}

	hashClientes::iterator it;
	for(it = clInact.begin(); it != clInact.end(); it++)
	{
		if(it->getNif() == nif)
		{
			if(show == 1)
				cout << it->getNome() << " - " << nif << " - Inactivo" << endl;
			return 1;
		}
	}

	if(show == 1)
		cout << "Cliente nao encontrado" << endl;
	return -1;
}


