/*
 * ManuPCBot.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include <string>
#include <cstdlib>
#include <iostream>

#include "GreedyBot.h"
using namespace std;

GreedyBot::GreedyBot() {
	// Inicializar las variables necesarias para ejecutar la partida

}

GreedyBot::~GreedyBot() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void GreedyBot::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string GreedyBot::getName() {
	return "GreedyBot"; // Sustituir por el nombre del bot
}

Move GreedyBot::nextMove(const vector<Move> &adversary, const GameState &state) {


	Player turno= this->getPlayer();
	long timeout= this->getTimeOut();

	Move movimiento= M_NONE;

	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. NO USAR cin NI cout.
	// Para salidas por consola (debug) utilizar cerr. Ejemplo:
	// cerr<< "Lo que quiero mostrar"<<endl;


	// OJO: Recordatorio. El nombre del bot y de la clase deben coincidir.
	// En caso contrario, el bot no podrá participar en la competición.
	// Se deberá sustituir el nombre MiBot como nombre de la clase por otro
	// seleccionado por el alumno. Se deberá actualizar también el nombre
	// devuelto por el método getName() acordemente.


	// Greedy: Escogerá el movimiento que más puntos le proporcione.
	// En caso de haber varios, se quedará con el que le deje repetir turno
	// o, en otro caso, en primero que haya.

	int puntos= -10000;

	// Recorremos los 6 movimientos posibles
	for (int i= 1; i<=6; i++) {

		// Comprobamos si hay semillas en la casilla i
		if (state.getSeedsAt(turno, (Position) i) >0) {

			// Si las hay, intentamos ver cómo queda el tablero si
			// hacemos el movimiento de la casilla i
			GameState hijo= state.simulateMove( (Move) i);

			// Si nos da más puntos de los que tenemos
			// con respecto al contrario, lo hacemos
			if (hijo.getScore(turno) > puntos) {
				puntos= hijo.getScore(turno);
				movimiento= (Move) i;

			// O si nos da los mismos puntos pero tiramos de nuevo,
			// cogemos el movimiento i
			} else if (hijo.getScore(turno) == puntos) {
				if (hijo.getCurrentPlayer() == turno)
					movimiento= (Move)i;
			}
		}

	}


	return movimiento;
}
