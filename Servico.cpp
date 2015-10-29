/*
 * Servico.cpp
 *
 *  Created on: 13/10/2015
 *      Author: POS
 */

#include "Servico.h"


Servico::Servico(string origem, string destino,float distancia, string tipo_produto, float capacidade)
{
	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = capacidade;
	iniciado = false;
	terminado = false;
}

string Servico::getOrigem()const
{
	return origem;
}

string Servico::getDestino()const
{
	return destino;
}


int Servico::getDistancia()const
{
	return distancia;
}

string Servico::getTipo_produto()const
{
	return tipo_produto;
}

bool Servico::getIniciado()const
{
	return iniciado;
}

bool Servico::getTerminado()const
{
	return terminado;
}

int Servico::getCapacidade()const
{
	return capacidade;
}

void Servico::setInicia()
{
	iniciado = true;
}

void Servico::setTermina()
{
	terminado = true;
}

vector<int> Servico::inicia_servico()
{
	int quantia = capacidade;


	for(int i=0; i < Camioes.size(); i++)

		if (Camioes[i]->getDisponivel()==true)
		{
			quantia = quantia - Camioes[i]->getCapacidade();
			veiculos_ocupados.push_back(i);
		}

	if (quantia <= 0 )
	{
		for(int i=0; i <veiculos_ocupados.size(); i++)
			Camioes[i]->setDisponivel( false);

		setInicia();
	}



	return veiculos_ocupados;
}

void Servico::termina_servico()
{
	for(int i=0; i <veiculos_ocupados.size(); i++)
		Camioes[i]->setDisponivel(true);

	setTermina();

}

bool Servico::operator < (const Servico &Ser)const
{
	if (distancia < Ser.getDistancia())
		return true;

	if(distancia == Ser.getDistancia())
	{
		if(capacidade < Ser.getCapacidade())
			return true;
		else
			return false;
	}
	else return false;
}


