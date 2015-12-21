#include "Oficina.h"


Oficina ::Oficina()
{}

Oficina ::Oficina(string nome, string marca, int disp)
{
	this->nome=nome;
	this->marca = marca;
	this->disp = disp;
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
	return Camioes;
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
	Camioes.push_back(C);
	//falta ver se ja tem o camiao
}

void Oficina::termServico(Camiao* C)
{
	disp -= 5;

	for(int i=0; i < Camioes.size(); i++)
	{
		if(Camioes[i] == C)
		{
			Camioes.erase(Camioes.begin()+ i);
			break;
		}

	}
}

bool Oficina::camiaoNaOficina(Camiao* C)
{
	cout << "entrou na oficina" << endl;
	for(int i=0; i < Camioes.size(); i++)
	{
		cout << "entrou no ciclo" << endl;
		if((Camioes[i]->getMarca() == C->getMarca()) && (Camioes[i]->getMatricula() == C->getMatricula()))
			{
			cout << "esta na fila" << endl;
			return true;
			}

	}
	cout << "nao esta na fila";
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
		s << "toma";


//		for(int i=0; i < F.getVeiculos().size(); i++)
//		{
//			string matricula;
//			matricula = F.getVeiculos()[i]->getMatricula();
//			s << matricula << " ";
//		}
	}

	s <<  endl << endl;

	return s;
}
