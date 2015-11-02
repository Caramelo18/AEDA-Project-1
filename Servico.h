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
#include <vector>

using namespace std;

class Servico
{
public:
	Servico();
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c);
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, int temp);
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, string nivel_p);
	string getOrigem()const;
	string getDestino()const;
	int getDistancia()const;
	string getTipo_produto()const;
	bool getIniciado()const;
	bool getTerminado()const;
	int getCapacidade()const;
	unsigned long getNif()const;
	void setInicia();
	void setTermina();
	void termina_servico();//atualiza todo o vetor de camioes, pondo desocupado os camioes que estao em veiculos ocupados
	bool operator < (const Servico &Ser)const;
	vector<Camiao*> getCamioes();
	int getPreco() const;
	int getID() const;

private:
	static int globalID;
	int ID;
	vector<Camiao*> Camioes;
	string origem;
	string destino;
	int distancia;
	int capacidade;
	string tipo_produto;
	bool iniciado;
	bool terminado;
	unsigned long Nif;//variavel para associar o cliente a um serviço
	int preco;

};

class ServicoNaoIniciado
{
public:


};

#endif /* SERVICO_H_ */
