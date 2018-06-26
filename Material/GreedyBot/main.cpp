
#include "SimulatorLink.h"
#include "Bot.h"
#include <iostream>

// MODIFICAR: Hacer el include del fichero que contiene al Bot del alumno. Ejemplo
#include "GreedyBot.h"


using namespace std;


int main() {

	SimulatorLink sim; // Enlace con el simulador
	Bot *bot= 0; // Bot que se ejecutará en el simulador


	// MODIFICAR: Declarar aquí el bot del alumno. Ejemplo:
	GreedyBot *gb= new GreedyBot();

	// MODIFICAR: Asignar el bot del alumno a la variable bot. Ejemplo:
	bot= (Bot *) gb;


	// Se establece el bot del alumno como bot del simulador
	sim.setBot(bot);

	// Ejecutamos la simulación
	bool salida= sim.run();


	// MODIFICAR: Eliminamos el bot del alumno. Ejemplo:
	delete gb;


	// Ejecutamos la simulación
	if (!salida) {

		cerr<<"\n\n\tSIMULACION ABORTADA.\n\n";
	} else {

		cerr<<"\n\n\tFIN DE LA PARTIDA CON EXITO.\n\n";
	}

	return 0;
}
