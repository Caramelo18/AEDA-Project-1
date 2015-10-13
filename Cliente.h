/*
 * Cliente.h
 *
 *  Created on: 13/10/2015
 *      Author: POS
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
protected:
	string Nome;
	unsigned long Nif;
};

#endif /* CLIENTE_H_ */
