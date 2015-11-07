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
 * Base para a criação e gestão de serviços
 */
class Servico
{
public:
	/*
	 * Criação de um Serviço por definição
	 *
	 * @param
	 *
	 * @return
	 */
	Servico();
	/*
	 * Criação de um Serviço para um camião do tipo Normal e Animais
	 *
	 * @param origem Origem do serviço
	 * @param destino Destino do serviço
	 * @param distancia Distancia total do serviço
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o serviço
	 * @param c Camioes que se encontram a executar o serviço
	 * @param f Funcionarios que se encontram a executar o serviço
	 *
	 * @return
	 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, vector<Funcionario *> &f);
	/*
	 * Criação de um Serviço para um camião do tipo Congelação
	 *
	 * @param origem Origem do serviço
	 * @param destino Destino do serviço
	 * @param distancia Distancia total do serviço
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o serviço
	 * @param c Camioes que se encontram a executar o serviço
	 * @param temp Temperatura necessaria no transporte no produto
	 * @param f Funcionarios que se encontram a executar o serviço
	 *
	 * @return
	 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, int temp, vector<Funcionario *> &f);
	/*
	 * Criação de um Serviço para um camião do tipo Perigosos
	 *
	 * @param origem Origem do serviço
	 * @param destino Destino do serviço
	 * @param distancia Distancia total do serviço
	 * @param tipo_produto Tipo de produto a transportar
	 * @param quantidade Quantidade de produto a transportar
	 * @param Nif Nif do Cliente que encomendou o serviço
	 * @param c Camioes que se encontram a executar o serviço
	 * @param nivel_p Nivel de perigosidade do produto
	 * @param f Funcionarios que se encontram a executar o serviço
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
	 * Verifica se o serviço esta terminado ou não
	 *
	 * @param
	 *
	 * @return Serviço terminado ou em execução
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
	 * Termina o serviço e actualiza todo o vetor de camioes, pondo desocupado os camioes que estao em veiculos ocupados
	 *
	 * @param
	 *
	 * @return
	 */
	void termina_servico();
	/*
	 * Compara dois serviços e diz se o primeiro é mais pequeno que o segundo, um serviçoi é mais pequeno que o outro se a sua distância for menor ou se esta for igual, qual delas usufrui de menos capacidade
	 *
	 * @param Ser Serviço com o qual o primeiro vai ser comparado
	 *
	 * @return se o serviço é mais pequeno que o que recebe como argumento
	 */
	bool operator < (const Servico &Ser)const;
	/*
	 * Retorna os camioes utilizados no serviço
	 *
	 * @param
	 *
	 * @return Camioes utilizados no serviço
	 */
	vector<Camiao*> getCamioes();
	/*
	 * Retorna os funcionarios que executraram o serviço
	 *
	 * @param
	 *
	 * @return Funcionarios que executraram o serviço
	 */
	vector<Funcionario*> getFuncionarios();
	/*
	 * Calcula o preço para um determinado serviço
	 *
	 * @param
	 *
	 * @return Preço do serviço a executar
	 */
	int getPreco() const;
	/*
	 * Retorna o ID do serviço
	 *
	 * @param
	 *
	 * @return ID que identifica o serviço
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
