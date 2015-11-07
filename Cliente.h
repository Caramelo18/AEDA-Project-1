/*
 * Cliente.h
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <iostream>
#include <string>

using namespace std;


class Cliente
{
public:
	Cliente(string Nome,unsigned long Nif);
	string getNome()const;
	unsigned long getNif()const;
	bool operator <(const Cliente &Cli)const;
	bool operator ==(const Cliente &c)const;
protected:
	string Nome;
	unsigned long Nif;
};

#endif /* CLIENTE_H_ */
