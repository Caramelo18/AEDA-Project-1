/*
 * Empresa.cpp
 */
#include "Empresa.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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

vector<Funcionario *> Empresa::getFuncionarios()
{
	return funcionarios;
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
	fich << endl;
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

	Servico s = Servico(origem, destino, distancia, tipo_produto, capacidade, Nif, camioes, nivel_p, funcionarios);

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

	for (unsigned int i = 0; i < funcionarios.size(); i++)
		if(funcionarios[i]->getBI() == BI)
		{
			cerr << "Funcionario com o BI " << BI << " ja existe." << endl;
			return;
		}

	Funcionario *f = new Funcionario(nome,salario,BI,"D");
	funcionarios.push_back(f);
	actualizaFicheiro();

}

void Empresa::pagaSalario()
{
	int salarios_total = 0;

	for(unsigned int i = 0; i < funcionarios.size(); i++)
		salarios_total = salarios_total + funcionarios[i]->getSalario();

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
		imprimeServico(servicos[i]);

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
	for (unsigned int i = 0; i < funcionarios.size(); i++)
	{
		fich1 << endl << funcionarios[i]->getNome() << endl << funcionarios[i]->getSalario() << " " << funcionarios[i]->getBI();
		if (funcionarios[i]->getDisponivel())
			fich1 << " D" ;
		else if (!funcionarios[i]->getDisponivel())
			fich1 << " N" ;
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
	for (unsigned int i = 0; i < funcionarios.size(); i++)
		funcionarios[i]->imprimeFuncionario();
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
	vector<Funcionario *> f = funcionarios;
	insertionSort(f);

	for (unsigned int i = 0; i < f.size(); i++)
		f[i]->imprimeFuncionario();
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
	unsigned int i;
	for (i = 0; i < clientes.size(); i++)
	{
		if(clientes[i].getNif() == Nif)
			break;
	}

	if(i == clientes.size())
	{
		cout << "Cliente inexistente" << endl;
		return;
	}

	else
		clientes.erase(clientes.begin() + i);

	ofstream fich(ficcli.c_str());

	fich << "Clientes:";
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		fich << endl;
		fich << clientes[i].getNome() << endl << clientes[i].getNif();
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

	cout << "Insira o nome da Oficina" << endl;
	cin >> nome;

	cout << "Insira a marca da Oficina" << endl;
	cin >> marca;

	Oficina F(nome, marca, 0, "");

	existeOficina(F);

	oficinas.push(F);
	cout << "Oficina adicionada com sucesso" << endl;

	cout << "o adiciona oficina esta a dar erro pois se se adicionar varias oficinas a funcao lista oficina funciona";
	cout << endl << "descomenta o codigo e explimenta" << endl;


	//	Oficina Ff("sd", "as", 0, "");
	//	oficinas.push(Ff);

	//	Oficina Fff("sdf", "asf", 0, "");
	//	oficinas.push(Fff);


	//listaOficinas();

}

Oficina Empresa::serUsual()
{
	Oficina F = oficinas.top();
	oficinas.pop();

	return F;
}

Oficina Empresa::serEspeci(Camiao C)
{
	priority_queue<Oficina>  copia;
	string marca = C.getMarca();
	Oficina F;

	while(!oficinas.empty())
	{
		F = oficinas.top();
		oficinas.pop();

		if(F.getMarca() == marca)
			break;
		else
			copia.push(F);

	}
	while(!copia.empty())
	{
		Oficina FF = copia.top();
		copia.pop();
		oficinas.push(FF);
	}

	return F;
}


void Empresa::fazSerEspeci()
{
	cout << "Matricula do Camiao" << endl;
	string matricula;

	getline(cin, matricula);

	Camiao C = procuraCamiao(matricula);

	Oficina F;
	F = serEspeci(C);
	F.fazServico(matricula);

	oficinas.push(F);

}

void Empresa::fazSerUsual(){

	cout << "Matricula do Camiao" << endl;
	string matricula;

	getline(cin, matricula);

	Camiao C = procuraCamiao(matricula);

	Oficina F;
	F = serUsual();
	F.fazServico(matricula);

	oficinas.push(F);
}

Camiao Empresa::procuraCamiao(string Matri)
{

	string marca;
	bool encontrou = false;
	for(int i=0; i < camioes.size(); i++)
	{
		if(camioes[i]->getMatricula() == Matri)
		{
			encontrou = true;
			marca = camioes[i]->getMarca();
		}
	}
	if(! encontrou)
		throw CamiaoNaoExistente();

	Camiao C(marca, "" ,0, Matri);

	return C;

}

Oficina Empresa::procuraCamiaoNaFila(Camiao C)
{
	priority_queue<Oficina> copia;
	Oficina Of;

	bool encontrou = false;

	while(!oficinas.empty())
	{
		Of = oficinas.top();
		oficinas.pop();

		if(Of.getMatri() == C.getMatricula())
		{
			encontrou = true;
			break;
		}
		else
			copia.push(Of);
	}

	while(!copia.empty())
	{
		Oficina esta= copia.top();
		copia.pop();
		oficinas.push(esta);
	}

	if(! encontrou)
		throw CamiaoNaoExistente();



	return Of;
}

void Empresa::termiServico(Camiao C)
{
	Oficina Of;
	Of = procuraCamiaoNaFila(C);
	Of.termServico();

	oficinas.push(Of);


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
		cout << endl << endl;
		copia.pop();
	}
}

void Empresa::listaOficinasDisponiveis()
{
	if(oficinas.empty())
		cout << "Sem oficinas para mostrar" << endl;

	priority_queue<Oficina> copia = oficinas;
	while(!copia.empty())
	{
		Oficina F = copia.top();
		copia.pop();

		if(F.getDisp() != 0)
			break;

		cout << F;
		cout << endl << endl;

	}

}

Oficina Empresa::procuraOficina(Oficina F)
{
	priority_queue<Oficina> copia ;
	bool encontrou = false;
	Oficina esta;

	while (!oficinas.empty())
	{
		esta = oficinas.top();
		oficinas.pop();

		if(F.getMarca() == esta.getMarca() && F.getNome() == esta.getNome())
		{
			encontrou = true;
			break;
		}
		else copia.push(esta);
	}
	while(! copia.empty())
	{
		oficinas.push(copia.top());
		copia.pop();
	}

	if(! encontrou)
		throw OficinaInexistente();

	return esta;
}

void Empresa::removeOficina()
{
	string marca;
	string nome;

	cout << "Insira o nome da Oficina" << endl;
	getline(cin, nome);
	cout << "Insira a marca da Oficina" << endl;

	Oficina F(nome, marca, 0, "");

	procuraOficina(F);

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

