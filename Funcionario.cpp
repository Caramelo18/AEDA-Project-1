#include "Funcionario.h"

Funcionario::Funcionario(string nome, int salario, unsigned long BI, string disp)
{
	this->nome = nome;
	this->salario = salario;
	this->BI = BI;
	if (disp == "D")
		disponivel = true;
	else if (disp == "N")
		disponivel = false;
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

void Funcionario::setDisponibilidade(bool disp)
{
	disponivel = disp;
}
