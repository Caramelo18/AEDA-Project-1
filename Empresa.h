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
#include "Cliente.h"
#include "Servico.h"

using namespace std;

class Empresa
{
private:
	string nomeEmpresa;
	long saldo;
	vector<*Camiao> camioes;
	vector<Servico> servicos;
	vector<Cliente> clientes;
	vector<Funcionario> funcionarios;
	
public:
	Empresa(string doc);
	vector<*Camiao> getCamioes();
	vector<Servico> getServicos();
	vector<Cliente> getClientes();
	vector<Funcionario> getFuncionarios();
	void adicionaCamiao(Camiao *camiao);
	void adicionaCliente(Cliente cliente);
	void novoServico(Servico servico);
	void contrataFuncionario(Funcionario funcionario);
	long getsaldo();
	void pagaSalario();
};



#endif /* EMPRESA_H_ */
