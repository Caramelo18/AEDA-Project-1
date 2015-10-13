/*
 * Camiao.h
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include <string>

using namespace std;

class Camiao
{
protected:
	int capacidade;
	string tipo;
	string marca;
	bool disponivel;
	static int IDg;
	int ID;
public:
	Camiao(string marca, string tipo, int capacidade);
	virtual int getPreco(int dist) = 0;
	int getCapacidade();
	string getTipo();
	string getMarca();
};

class Normal: public Camiao
{
public:
	Normal(string marca, string tipo, int capacidade);
	int getPreco(int dist);
};

class Congelacao: public Camiao
{
public:
	Congelacao(string marca, string tipo, int capacidade);
	int getPreco (int dist, int temp);
};

class Perigosos: public Camiao
{
private:
	string nivelp;
public:
	Perigosos(string marca, string tipo, int capacidade, string nivelp);
	int getPreco(int dist);
};

class Animais: public Camiao
{
public:
	Animais(string marca, string tipo, int capacidade);
	int getPreco(int dist);
};

#endif /* CAMIAO_H_ */
