/*
 * Camiao.cpp
 */

#include "Camiao.h"


Camiao::Camiao(string marca, string tipo, int capacidade, string matricula)
{
	this->marca = marca;
	this->tipo = tipo;
	this->capacidade = capacidade;
	disponivel = true;
	this->matricula = matricula;

}

string Camiao::getMarca()
{
	return marca;
}

int Camiao::getPreco(int dist)
{}

string Camiao::getTipo()
{
	return tipo;
}

int Camiao::getCapacidade()
{
	return capacidade;
}

bool Camiao::getDisponivel()
{
	return disponivel;
}

void Camiao::setDisponivel(bool bo)
{
	disponivel = bo;
}

Normal::Normal(string marca, string tipo, int capacidade, string matricula):Camiao(marca, tipo, capacidade, matricula)
{
}

int Normal::getPreco(int dist)
{
	return 6*dist;
}

Congelacao::Congelacao(string marca, string tipo, int capacidade, string matricula):Camiao(marca, tipo, capacidade, matricula)
{}

int Congelacao::getPreco(int dist)
{
}

Perigosos::Perigosos(string marca, string tipo, int capacidade, string matricula):Camiao(marca, tipo, capacidade, matricula)
{}

int Perigosos::getPreco(int dist, string nivelp)
{
}

Animais::Animais(string marca, string tipo, int capacidade, string matricula):Camiao(marca, tipo, capacidade, matricula)
{
}

int Animais::getPreco(int dist)
{
	return 7 * dist;
}

string Camiao::getMatricula() const
{
	return matricula;
}

void Camiao::imprimeCamiao() const
{
	cout << "Marca: " << marca << endl;
	cout << "Tipo: " << tipo << endl;
	cout << "Matricula: " << matricula << endl;
	cout << "Capacidade: " << capacidade << " Kg" << endl;
	cout << endl;
}
