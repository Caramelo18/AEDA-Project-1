/*
 * Servico.cpp
 *
 *  Created on: 13/10/2015
 *      Author: POS
 */

#include "Servico.h"


Servico::Servico(string origem, string destino,float distancia, string tipo_produto, float quantidade)
{
	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->quantidade = quantidade;
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


float Servico::getDistancia()const
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

float Servico::getQuantidade()const
{
	return quantidade;
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
	int quantia = quantidade;


	for(int i=0; i < Camioes.size(); i++)

		if (Camioes[i].getDisponivel()==true)
		{
			quantia = quantia - Camioes[i]. getCapacidade();
			veiculos_ocupados.push_back(i);
		}

	if (quantia <= 0 )
		{
		for(int i=0; i <veiculos_ocupados.size(); i++)
			Camioes[i].setDisponivel( false);

		setInicia();
		}



	return veiculos_ocupados;
}

void Servico::termina_servico()
{
	for(int i=0; i <veiculos_ocupados.size(); i++)
		Camioes[i].setDisponivel(true);

	setTermina();

}


