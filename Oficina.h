/*
 * Oficina.h
 */

#ifndef OFICINA_H_
#define OFICINA_H_

#include <string>
#include <iostream>

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
#endif /* OFICINA_H_ */
