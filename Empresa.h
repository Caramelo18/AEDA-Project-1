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
#include "Camiao.h"
#include <algorithm>

using namespace std;


class ServicoInexistente
{
public:
	ServicoInexistente(){}
};


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


class ClienteNaoExistente
{
public:
	ClienteNaoExistente(){}
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
	vector<Funcionario *> funcionarios;

public:
	Empresa(){}
	Empresa(string doc);
	vector<Camiao *> getCamioes();
	vector<Servico> getServicos();
	vector<Cliente> getClientes();
	vector<Funcionario *> getFuncionarios();
	void adicionaCamiao(Camiao *camiao);
	void adicionaCliente();
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif);
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp);
	void novoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p);
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<string> mat, vector<unsigned long> funcs, bool ter);
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, int temp, vector<string> mat, vector<unsigned long> funcs, bool ter);
	void leNovoServico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, string nivel_p, vector<string> mat, vector<unsigned long> funcs, bool ter);
	void contrataFuncionario();
	long getSaldo();
	void pagaSalario();
	string getNome() const;
	void imprimeSaldo() const;
	void imprimeServicos();
	void imprimeServico(Servico s) const;
	void ListaServicosExecucao()const;
	void ListaServicosCliente()const;
	void ListaServicosCamiao()const;
	void ListaCamioesOrdenados()const;
	void listaClientes() const;
	void listaClientesOrdenados();
	int posCliente(unsigned long nif) const;
	void actualizaFicheiro();
	void terminaServico(int ID);
	void EscreveServicoTerminado(int ID, string tipo);
	void ImprimeListaCamioes();
	void ImprimeListaCamioesDisponiveis();
	void AdicionaCamiao();
	void listaFuncionarios() const;
	void listaFuncionariosDisponiveis() const;
	void despedeFuncionario();
};



#endif /* EMPRESA_H_ */
