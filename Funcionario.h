/*
 * Funcionario.h
 *
 *  Created on: 29/10/2015
 *      Author: fabio
 */

#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_

#include <string>

using namespace std;

class FuncionariosIndisponiveis
{
public:
	FuncionariosIndisponiveis() {}
};


class Funcionario
{
private:
	string nome;
	int salario;
	unsigned long BI;
	bool disponivel;
public:
	Funcionario(string nome, int salario, unsigned long BI, string disp);
	string getNome() const;
	int getSalario() const;
	void setSalario(int salario);
	unsigned int getBI() const;
	bool getDisponivel() const;
	void setDisponibilidade(bool disp);
};

#endif /* FUNCIONARIO_H_ */
