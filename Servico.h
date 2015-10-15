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
	Servico(string origem, string destino,float distancia, string tipo_produto, float quantidade);
	string getOrigem()const;
	string getDestino()const;
	float getDistancia()const;
	string getTipo_produto()const;
	bool getIniciado()const;
	bool getTerminado()const;
	float getQuantidade()const;
	void setInicia();
	void setTermina();
	vector<int> inicia_servico();//retorna o vetor com o indice dos camioes ocupados, se não inicia retorna um vetor nulo
	void termina_servico();

private:
	static  float ID;
	vector<int> veiculos_ocupados;
	vector<Camiao*> Camioes;
	string origem;
	string destino;
	float distancia;
	float quantidade;
	string tipo_produto;
	bool iniciado;
	bool terminado;
};

#endif /* SERVICO_H_ */
