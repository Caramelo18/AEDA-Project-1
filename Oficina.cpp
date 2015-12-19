#include "Oficina.h"


Oficina ::Oficina()
{}

Oficina ::Oficina(string nome, string marca, int disp , string matriculaCami)
{
	this->nome=nome;
	this->marca = marca;
	this->disp = disp;
	this->matriculaCami = matriculaCami;
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

string Oficina::getMatri()const
{
	return matriculaCami;
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

void Oficina::fazServico(string Matri)
{
	disp += 5;
	matriculaCami = Matri;
}

void Oficina::termServico()
{
	disp = 0;
	matriculaCami = "";
}

ostream &operator<<(ostream &s, const Oficina  F)
{
	s << "Nome: " <<  F.getNome() << endl;
	s << "Marca: " << F.getMarca() << endl;
	s << "Disponibilidade: " << F.getDisp()<< endl;
	s << "Matricula associada: ";


	if(F.getMatri()== "")
		s << "sem matricula associada";
	else
		s << F.getMatri();
	s <<  endl;

	return s;
}
