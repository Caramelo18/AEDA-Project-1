/*
 * Servico.h
 */

#ifndef SERVICO_H_
#define SERVICO_H_

#include "Camiao.h"
#include "Funcionario.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Base para a cria��o e gest�o de servi�os
 */
class Servico
{
public:
	/*
	 * Cria��o de um Servi�o por defini��o
	 *
	 * @param
	 *
	 * @return
	 */
	Servico();
	/*
	 * Cria��o de um Servi�o para um cami�o do tipo Normal e Animais
	 *
	 * @param origem Origem do servi�o
	 * @param destino Destino do servi�o
	 * @param distancia Distancia total do servi�o
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o servi�o
	 * @param c Camioes que se encontram a executar o servi�o
	 * @param f Funcionarios que se encontram a executar o servi�o
	 *
	 * @return
	 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, vector<Funcionario *> &f);
	/*
	 * Cria��o de um Servi�o para um cami�o do tipo Congela��o
	 *
	 * @param origem Origem do servi�o
	 * @param destino Destino do servi�o
	 * @param distancia Distancia total do servi�o
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o servi�o
	 * @param c Camioes que se encontram a executar o servi�o
	 * @param temp Temperatura necessaria no transporte no produto
	 * @param f Funcionarios que se encontram a executar o servi�o
	 *
	 * @return
	 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, int temp, vector<Funcionario *> &f);
	/*
	 * Cria��o de um Servi�o para um cami�o do tipo Perigosos
	 *
	 * @param origem Origem do servi�o
	 * @param destino Destino do servi�o
	 * @param distancia Distancia total do servi�o
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o servi�o
	 * @param c Camioes que se encontram a executar o servi�o
	 * @param nivel_p Nivel de perigosidade do produto
	 * @param f Funcionarios que se encontram a executar o servi�o
	 *
	 * @return
	 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, string nivel_p, vector<Funcionario *> &f);
	/*
	 * Retorna a Origem do produto
	 *
	 * @param
	 *
	 * @return Origem do produto
	 */
	string getOrigem()const;
	/*
	 * Retorna o Destino do produto
	 *
	 * @param
	 *
	 * @return Destino do produto
	 */
	string getDestino()const;
	/*
	 * Retorna a Distancia do produto
	 *
	 * @param
	 *
	 * @return Distancia do produto
	 */
	int getDistancia()const;
	/*
	 * Retorna o Tipo de produto
	 *
	 * @param
	 *
	 * @return Tipo de produto
	 */
	string getTipo_produto()const;
	/*
	 * Verifica se o servi�o esta terminado ou n�o
	 *
	 * @param
	 *
	 * @return Servi�o terminado ou em execu��o
	 */
	bool getTerminado()const;
	/*
	 * Retorna a Capacidade do produto
	 *
	 * @param
	 *
	 * @return Capacidade do produto
	 */
	int getCapacidade()const;
	/*
	 * Retorna o Nif do produto
	 *
	 * @param
	 *
	 * @return Nif do produto
	 */
	unsigned long getNif()const;
	/*
	 * Termina o servi�o e actualiza todo o vetor de camioes, pondo desocupado os camioes que estao em veiculos ocupados
	 *
	 * @param
	 *
	 * @return
	 */
	void termina_servico();
	/*
	 * Compara dois servi�os e diz se o primeiro � mais pequeno que o segundo, um servi�oi � mais pequeno que o outro se a sua dist�ncia for menor ou se esta for igual, qual delas usufrui de menos capacidade
	 *
	 * @param Ser Servi�o com o qual o primeiro vai ser comparado
	 *
	 * @return se o servi�o � mais pequeno que o que recebe como argumento
	 */
	bool operator < (const Servico &Ser)const;
	/*
	 * Retorna os camioes utilizados no servi�o
	 *
	 * @param
	 *
	 * @return Camioes utilizados no servi�o
	 */
	vector<Camiao*> getCamioes();
	/*
	 * Retorna os funcionarios que executraram o servi�o
	 *
	 * @param
	 *
	 * @return Funcionarios que executraram o servi�o
	 */
	vector<Funcionario*> getFuncionarios();
	/*
	 * Calcula o pre�o para um determinado servi�o
	 *
	 * @param
	 *
	 * @return Pre�o do servi�o a executar
	 */
	int getPreco() const;
	/*
	 * Retorna o ID do servi�o
	 *
	 * @param
	 *
	 * @return ID que identifica o servi�o
	 */
	int getID() const;
	/*
	 * Incrementa o ID global de maneira a que os ids surjam de forma sequencial
	 *
	 * @param
	 *
	 * @return
	 */
	static void incGlobalID();

private:
	static int globalID;
	int ID;
	vector<Camiao*> Camioes;
	vector<Funcionario*> Funcionarios;
	string origem;
	string destino;
	int distancia;
	int capacidade;
	string tipo_produto;
	bool terminado;
	unsigned long Nif;
	int preco;

};

class ServicoNaoIniciado
{
public:


};

#endif /* SERVICO_H_ */
