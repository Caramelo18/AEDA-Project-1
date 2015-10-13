/*
 * Empresa.h
 *
 *  Created on: 13/10/2015
 *      Author: fabio
 */

#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Empresa
{
private:
	vector<int> camioes;
	
	
	vector<int> servicos;
	vector<int> clientes;
public:
	vector<int> getCamioes();
};



#endif /* EMPRESA_H_ */
