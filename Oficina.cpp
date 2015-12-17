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

bool Oficina::operator <(const Oficina F)const
{
	if(disp < F.getDisp())
		return true;

	if(disp == F.getDisp())
	{
		if(marca < F.getMarca())

			return true;
		else
			return false;
	}
	else
		return false;
}
