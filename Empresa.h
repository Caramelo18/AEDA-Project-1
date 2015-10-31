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

class FicheiroInexistente
{
	string ficheiro;
public:
	FicheiroInexistente(string nome){ficheiro = nome;}
	string getFicheiro(){return ficheiro;}
};

class ClienteJaExistente
{
	string nome;
	unsigned long nif;
public:
	ClienteJaExistente(string nome,unsigned long nif){this->nome = nome;this->nif = nif;};
	string getNome(){return nome;}
	unsigned long getNif(){return nif;}
};

class SaldoIndisponivel
{
public:
	SaldoIndisponivel(){};
};

class Empresa
{
private:
	string nomeEmpresa, ficca, ficcli, ficfun, ficser;
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
	void adicionaCliente();
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
	void listaClientes() const;
};



#endif /* EMPRESA_H_ */
