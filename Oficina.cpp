#include "Oficina.h"


Oficina::Oficina()
{}

Oficina::Oficina(string nome, string marca, int disp, vector<Camiao*> camioes)
{
	this->nome=nome;
	this->marca = marca;
	this->disp = disp;
	this->Cami = camioes;

}

string Oficina::getNome()const
{
	return nome;
}

string Oficina::getMarca()const{
	return marca;
}

int Oficina::getDisp()const
{
	return disp;
}

vector<Camiao*> Oficina::getVeiculos()const
{
	return Cami;
}

bool Oficina::operator <(const Oficina F)const
{
	if(disp > F.getDisp())
		return true;

	if(disp == F.getDisp())
	{
		if(marca > F.getMarca())

			return true;
		else
			return false;
	}
	else
		return false;
}

void Oficina::fazServico(Camiao* C)
{

		disp += 5;

		cout << Cami.size();
		Cami.push_back(C);
		cout << Cami.size();



}

void Oficina::termServico(Camiao* C)
{
	disp -= 5;

	for(int i=0; i < Cami.size(); i++)
	{
		if(Cami[i] == C)
		{
			Cami.erase(Cami.begin()+ i);
			break;
		}

	}
}

bool Oficina::camiaoNaOficina(Camiao* C)
{
	cout << "entrou na oficina" << endl;
	for(int i=0; i < Cami.size(); i++)
	{

		cout << Cami.size();
		cout << getVeiculos()[i]->getMarca();
		if((Cami[i]->getMarca() == C->getMarca()) && (Cami[i]->getMatricula() == C->getMatricula()))
		{
			cout << "esta na fila" << endl;
			return true;
		}

	}
	cout << "nao esta na fila" << endl;
	return false;

}

ostream &operator<<(ostream &s, const Oficina  &F)
{
	s << "Nome: " <<  F.getNome() << endl;
	s << "Marca: " << F.getMarca() << endl;
	s << "Disponibilidade: " << F.getDisp()<< endl;
	s << "Matriculas associadas: ";


	if(F.getVeiculos().size()== 0)
		s << "sem matricula associada";
	else
	{
		for(int i=0; i < F.getVeiculos().size(); i++)
		{
			string matricula;
			matricula = F.getVeiculos()[i]->getMatricula();
			s << matricula << "  ";
		}
	}

	s <<  endl << endl;

	return s;
}
