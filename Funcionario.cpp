/*
 * Funcionario.cpp
 */

#include "Funcionario.h"

Funcionario::Funcionario()
{
	disponivel = false;
}

Funcionario::Funcionario(string nome, int salario, unsigned long BI, string disp, unsigned int hr)
{
	this->nome = nome;
	this->salario = salario;
	this->BI = BI;
	if (disp == "D")
		disponivel = true;
	else if (disp == "N")
		disponivel = false;
	horas = hr;
}

string Funcionario::getNome() const
{
	return nome;
}

int Funcionario::getSalario() const
{
	return salario;
}

void Funcionario::setSalario(int salario)
{
	this->salario = salario;
}

unsigned int Funcionario::getBI() const
{
	return BI;
}

bool Funcionario::getDisponivel() const
{
	return disponivel;
}

unsigned int Funcionario:: getHoras() const
{
	return horas;
}

void Funcionario::setDisponibilidade(bool disp)
{
	disponivel = disp;
}

void Funcionario::imprimeFuncionario() const
{
	cout << "Nome: "<< nome << endl;
	cout << "Salario: " << salario << endl;
	cout << "BI: " << BI << endl;
	cout << "Horas diarias: " << horas << endl << endl;
}


bool Funcionario::operator<(Funcionario f)
{
	if (horas == f.horas)
	{
		return (nome < f.nome);
	}

	return (horas < f.horas);
}

void Funcionario::incrementaHoras(int distancia)
{
	horas += distancia / 80;
}

void Funcionario::setHoras(unsigned int hr)
{
	horas = hr;
}

