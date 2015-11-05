/*
 * Camiao.h
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include <string>
#include <iostream>

using namespace std;

class camioesIndisponiveis
{
public:
	camioesIndisponiveis(){}
};


class Camiao
{
protected:
	int capacidade;
	string tipo;
	string marca;
	bool disponivel;
	static int IDg;
	int ID;
	string matricula;
public:
	Camiao(string marca, string tipo, int capacidade, string matricula);
	virtual int getPreco(int dist);
	int getCapacidade();
	string getTipo();
	string getMarca();
	bool getDisponivel();
	void setDisponivel( bool bo);
	string getMatricula() const;
	void imprimeCamiao() const;
};


class Normal: public Camiao
{
public:
	Normal(string marca, string tipo, int capacidade, string matricula);
	int getPreco(int dist);
};

class Congelacao: public Camiao
{
public:
	Congelacao(string marca, string tipo, int capacidade, string matricula);
	int getPreco (int dist);
};

class Perigosos: public Camiao
{
public:
	Perigosos(string marca, string tipo, int capacidade, string matricula);
	int getPreco(int dist, string nivelp);
};

class Animais: public Camiao
{
public:
	Animais(string marca, string tipo, int capacidade, string matricula);
	int getPreco(int dist);
};

#endif /* CAMIAO_H_ */
