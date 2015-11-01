/*
 * Camiao.cpp
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */

#include "Camiao.h"

int Camiao::IDg = 1;

Camiao::Camiao(string marca, string tipo, int capacidade)
{
	this->marca = marca;
	this->tipo = tipo;
	this->capacidade = capacidade;
	disponivel = true;
	ID = IDg;

	IDg++;
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

Normal::Normal(string marca, string tipo, int capacidade):Camiao(marca, tipo, capacidade)
{
}

int Normal::getPreco(int dist)
{
	return 6*dist;
}

Congelacao::Congelacao(string marca, string tipo, int capacidade):Camiao(marca, tipo, capacidade)
{}

int Congelacao::getPreco(int dist)
{
}

Perigosos::Perigosos(string marca, string tipo, int capacidade):Camiao(marca, tipo, capacidade)
{}

int Perigosos::getPreco(int dist, string nivelp)
{
}

Animais::Animais(string marca, string tipo, int capacidade):Camiao(marca, tipo, capacidade)
{
}

int Animais::getPreco(int dist)
{
	return 7 * dist;
}

