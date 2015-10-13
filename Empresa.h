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
	string nomeEmpresa;
	long saldo;
	vector<int> camioes;
	vector<int> servicos;
	vector<int> clientes;
	vector<int> funcionarios;
	
public:
	Empresa(string doc);
	vector<int> getCamioes();
	vector<int> getServicos();
	vector<int> getClientes();
	void adicionaCamiao(Camiao *camiao);
	void adicionaCliente(Cliente cliente);
	void novoServico(Servico servico);
	void contrataFuncionario(Funcionario funcionario);
	long getsaldo();
	long pagaSalario();
};



#endif /* EMPRESA_H_ */
