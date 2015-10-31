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
#include "Funcionario.h"

using namespace std;

class SaldoIndisponivel
{
public:
	SaldoIndisponivel(){};
};

class Empresa
{
private:
	string nomeEmpresa;
	long saldo;
	vector<Camiao *> camioes;
	vector<Servico> servicos;
	vector<Cliente> clientes;
	vector<Funcionario> funcionarios;
	
public:
	Empresa(string doc);
	vector<Camiao *> getCamioes();
	vector<Servico> getServicos();
	vector<Cliente> getClientes();
	vector<Funcionario> getFuncionarios();
	void adicionaCamiao(Camiao *camiao);
	void adicionaCliente(Cliente cliente);
	void novoServico(Servico servico);
	void contrataFuncionario(Funcionario funcionario);
	long getSaldo();
	void pagaSalario();
	string getNome() const;
	void imprimeSaldo() const;
	void imprimeServico();
	void ListaServicosExecucao()const;
	void ListaServicosCliente()const;
	void ListaServicosCamiao()const;
};



#endif /* EMPRESA_H_ */
