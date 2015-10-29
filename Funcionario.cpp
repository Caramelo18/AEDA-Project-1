#include "Funcionario.h"

Funcionario::Funcionario(string nome, int salario, unsigned long BI)
{
	this->nome = nome;
	this->salario = salario;
	this->BI = BI;
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
