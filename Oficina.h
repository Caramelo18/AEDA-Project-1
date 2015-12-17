/*
 * Empresa.h
 */

#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <vector>
#include <string>
#include <iostream>
#include "Cliente.h"
#include "Servico.h"
#include "Funcionario.h"
#include "Camiao.h"
#include "InsertionSort.h"

using namespace std;

class Oficina
{
public:
	Oficina(string nome, string marca, int disp);
	string getNome()const;
	string getMarca()const;
	int getDisp()const;
	bool operator <(const Oficina F)const;

private:
	string nome;
	string marca;
	int disp;



};
#endif /* EMPRESA_H_ */
