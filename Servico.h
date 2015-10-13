/*
 * Servico.h
 *
 *  Created on: 13/10/2015
 *      Author: POS
 */

#ifndef SERVICO_H_
#define SERVICO_H_

#include "Camiao.h"
#include <iostream>
#include <string>

using namespace std;

class Servico
{
public:
	Servico();
	string getOrigem()const;
	string getDestino()const;
	float getTempo_ocupacao()const;
	float getDestinacia()const;
	string getTipo_produto()const;
	bool getChegada_servico()const;






private:
	static  float ID;
	//vector<Camiao> Camioes;
	string origem;
	string destino;
	float tempo_ocupacao;
	float distancia;
	string tipo_produto;
	bool chegada_servico;





};





#endif /* SERVICO_H_ */
