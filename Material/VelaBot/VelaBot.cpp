/*
 * VelaBot.cpp
 *
 *  Created on: May 2018.
 *      Author: Sergio Vela Pelegrina.
 */

#include "VelaBot.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <list>
#include <limits>
#include <cassert>
using namespace std;

VelaBot::VelaBot() {
	// Inicializar las variables necesarias para ejecutar la partida
	srand(time(0));

}

VelaBot::~VelaBot() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void VelaBot::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string VelaBot::getName() {
	return "VelaBot";
}

struct nodo{
	GameState estado;
	list<int> camino;
};

/*
    Devuelve el máximo de dos valores
    que se le pasan como parámetro.
*/
int VelaBot::CalculaMaximo(int numero1, int numero2){
	int max = numero1;

	if(numero2 > numero1)
		max = numero2;

	return max;
}

/*
    Devuelve el mínimo de dos valores
    que se le pasan como parámetro.
*/
int VelaBot::CalculaMinimo(int numero1, int numero2){
	int min = numero1;

	if(numero2 < numero1)
		min = numero2;

	return min;
}

/*
    Método para calcular la heurística de mi algoritmo.
    Consiste en sumar las semillas que hay en mis casillas,
    restarle las semillas que hay en las casillas de mi
    adversario y le sumo mi puntuación.
*/
int VelaBot::EvaluaNodo(Nodo& mi_nodo,const Player& j){
    Player contrario = J1;

    if(j == J1)
        contrario = J2;

    int mis_semillas = 0;
    int semillas_contrario = 0;

    for(int i = 0; i < 7; i++){
        mis_semillas += mi_nodo.estado.getSeedsAt(j, (Position) i);
        semillas_contrario += mi_nodo.estado.getSeedsAt(contrario, (Position) i);
    }

    int mi_puntuacion = mi_nodo.estado.getScore(j);

    int semillas_diferencia = mis_semillas - semillas_contrario;

    return (semillas_diferencia + mi_puntuacion);

}

/*
    Algoritmo donde implemento el algoritmo
    de poda alfa beta.
*/
int VelaBot::PodaAlfaBeta(Nodo& mi_nodo, int profundidad,const Player& j, int alfa, int beta){

    //Si no estamos en un nodo hoja o hemos alcanzado el límite de profundidad.
	if((profundidad > 0) && !mi_nodo.estado.isFinalState()){

        //Si es nuestro turno. (Nodo MAX).
		if(j == mi_nodo.estado.getCurrentPlayer()){

            /*
                Es nuestro turno. Por lo que el nodo es un MAX, 
                Le pasamos al método nuestro jugador, y si nos toca el turno,
                entraríamos en el if. En caso contrario, es el turno del otro
                jugador y pasaríamos al else.
            */

			int mejor_valor = numeric_limits<int>::min();
        	Move mejor_movimiento;

        	bool podar = false;

            //Recorro mis casillas.
        	for(int i = 1; i < 7 && !podar; i++){
            	Nodo hijo = {mi_nodo.estado.simulateMove((Move) i), (Move) i};

                int valor = PodaAlfaBeta(hijo, profundidad-1,j ,alfa, beta);

            	if(valor > mejor_valor){
                	mejor_valor = valor;   //Almacenamos el mejor valor posible.
                	mi_nodo.mov = (Move) i;  //Almacenamos el mejor movimiento.
            	}

            	alfa = CalculaMaximo(alfa, mejor_valor);

                //Podamos.
            	if(beta <= alfa)   
            		podar = true;
			}

			return mejor_valor;
		}

		else{

            /*
                Es turno de nuestro contrincante, por lo que
                es un nodo MIN. 
            */

        	int mejor_valor = std::numeric_limits<int>::max();
        	Move mejor_movimiento;

        	bool podar = false;

        	for(int i = 1; i < 7 && !podar; i++){
            	Nodo hijo = {mi_nodo.estado.simulateMove((Move) i), (Move) i};

                int valor = PodaAlfaBeta(hijo, profundidad-1,j, alfa, beta);

            	if(valor < mejor_valor){
                	mejor_valor = valor;   //Almacenamos el mejor valor posible.
                	mi_nodo.mov = (Move) i;  //Almacenamos el mejor movimiento.
            	}

            	beta = CalculaMinimo(beta, mejor_valor);

            	if(beta <= alfa)   //Podamos.
                	podar = true;
        	}

        	return mejor_valor;
    	}
	}

/*
    Estamos en nodo hoja o hemos alcanzado el límite
    De profundidad. Llamamos a la función que calcula
    mi heurística.
*/
	else{

		return EvaluaNodo(mi_nodo, j);
	}
}


Move VelaBot::nextMove(const vector<Move> &adversary, const GameState &estado){

    Player yo = this->getPlayer();
    long timeout = this->getTimeOut();

    int alfa = numeric_limits<int>::min();  //Menos infinito.
    int beta = numeric_limits<int>::max();  //Más infinito.

    int profundidad = 11;   //Límite de profundidad.
    
    Nodo n = {estado, M_NONE};

    int movimiento = PodaAlfaBeta(n, profundidad, yo, alfa, beta);

    return n.mov;
}