/*
 * VelaBot.h
 *
 *  Created on: May 2018
 *      Author: Sergio Vela Pelegrina.
 */

#include "Bot.h"

#ifndef VelaBOT_H_
#define VelaBOT_H_

//En cada estado el movimiento que he hecho.
struct Nodo{
    GameState estado;
    Move mov;
};

class VelaBot:Bot {
//private:

	public:
		VelaBot();
		~VelaBot();

		void initialize();
		string getName();
		Move nextMove(const vector<Move> &adversary, const GameState &state);
		int CalculaMinimo(int numero1, int numero2);	//Calcula mínimo de dos números.
		int CalculaMaximo(int numero1, int numero2);	//Calcula máximo de dos números.
		int PodaAlfaBeta(Nodo& node, int profundidad, const Player& j, int alpha, int beta);	//Algoritmo de poda.
		int EvaluaNodo(Nodo& n,const Player& j);	//Heurística.
};

#endif /* VELABOT_H_ */
