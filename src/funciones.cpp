#include "funciones.h"
#include <iostream>
#include <cstdlib>	// para convertir string a numerico.
using namespace std;

// Información conocida previamente para poder obtener y procesar los registros del archivo.

const int CANTIDAD_COLUMNAS = 12;
const int CANTIDAD_METROBUSES = 229;
const int OPCION_FINALIZAR = 4;	// numero de opcion del menu para finalizar el programa.

// informacion para mostrarle al usuario un rango mas acotado donde escoger una de las posibilades.
const double LONGITUD_MINIMA_ACEPTADA = -59.0;
const double LONGITUD_MAXIMA_ACEPTADA = -58.0;
const double LATITUD_MINIMA_ACEPTADA = -35.0;
const double LATITUD_MAXIMA_ACEPTADA = -34.0;

void ejecutarPrograma() {
	darLaBienvenida();

	string cabeceras[CANTIDAD_COLUMNAS]; // nombres de las cabeceras de la tabla de los registros.

	Metrobus metrobuses[CANTIDAD_METROBUSES];

	procesarArchivo(cabeceras, metrobuses);

	usarMenuDelPrograma(cabeceras, metrobuses);
}

void darLaBienvenida() {
	cout << ".:::: BIENVENIDO AL PROGRAMA \"Ciudad Digital V1.0\" ::::." << endl;

	cout << "Desarrollado por: Valeriano, Juan Gabriel." << endl << endl;
}

void procesarArchivo(string cabeceras[], Metrobus registros[]) {
	ifstream archivo;

	string ruta = "estaciones-de-metrobus.csv";

	archivo.open(ruta.c_str());

	obtenerCabeceras(archivo, cabeceras);

	obtenerRegistros(archivo, registros);

	archivo.close();
}

void obtenerCabeceras(ifstream &archivo, string cabeceras[]) {
	string contenido = "";

	for(int categoria = 1; categoria <= CANTIDAD_COLUMNAS; categoria++) {

		if ( categoria != CANTIDAD_COLUMNAS ) {

			getline(archivo, contenido, ',');

		} else {

			getline(archivo, contenido, '\n');	// lee el campo hasta que encuentra el salto de linea a otro registro

			contenido = contenido.substr(0, contenido.length()-1); // quita el salto de linea guardado del ultimo campo.

		}

		cabeceras[categoria-1] = contenido;

	}
}

void obtenerRegistros(ifstream &archivo, Metrobus registros[]) {

	for(int registro = 1; registro <= CANTIDAD_METROBUSES; registro++) {

		Metrobus nuevoRegistro = armarRegistroLeido(archivo);

		registros[registro-1] = nuevoRegistro;

	}
}

Metrobus armarRegistroLeido(ifstream &archivo) {
	Metrobus nuevoRegistro;

	std::string longitud = "";
	std::getline(archivo, longitud, ',');
	nuevoRegistro.longitud = std::atof(longitud.c_str());

	std::string latitud = "";
	std::getline(archivo, latitud, ',');
	nuevoRegistro.latitud = std::atof(latitud.c_str());

	std::string id = "";
	std::getline(archivo, id, ',');
	nuevoRegistro.identificador = std::atoi(latitud.c_str());

	std::string nombre = "";
	std::getline(archivo, nombre, ',');
	nuevoRegistro.nombre = nombre;

	std::string calle1 = "";
	std::getline(archivo, calle1, ',');
	nuevoRegistro.calle1 = calle1;

	std::string calle2 = "";
	std::getline(archivo, calle2, ',');
	nuevoRegistro.calle2 = calle2;

	std::string interseccion = "";
	std::getline(archivo, interseccion, ',');
	nuevoRegistro.interseccion = interseccion;

	std::string lineaSentidoNorte = "";
	std::getline(archivo, lineaSentidoNorte, ',');
	nuevoRegistro.lineaSentidoNorte = lineaSentidoNorte;

	std::string lineaSentidoSur = "";
	std::getline(archivo, lineaSentidoSur, ',');
	nuevoRegistro.lineaSentidoSur = lineaSentidoSur;

	std::string metrobus = "";
	std::getline(archivo, metrobus, ',');
	nuevoRegistro.metrobus = metrobus;

	std::string nombreSentido = "";
	std::getline(archivo, nombreSentido, ',');
	nuevoRegistro.nombreSentido = nombreSentido;

	std::string observacion = "";
	std::getline(archivo, observacion, '\n');
	observacion = observacion.substr(0, observacion.length()-1);
	nuevoRegistro.observacion = observacion;

	return nuevoRegistro;
}

void usarMenuDelPrograma(string cabeceras[], Metrobus registros[]) {
	bool terminar = false;

	do {
		mostrarMenu();

		int opcionElegida = elegirUnaOpcionDelMenu();

//		ejecutarOpcionElegida(cabeceras, registros, opcionElegida);

		terminar = (opcionElegida == OPCION_FINALIZAR);

	} while(!terminar);
}

void mostrarMenu() {
	cout << "<<< MENU DEL PROGRAMA. >>>" << endl << endl;

	cout << "1. Filtrar por longitud." << endl;

	cout << "2. Filtrar por latitud." << endl;

	cout << "3. Filtrar por id." << endl;

	cout << "4. Salir." << endl << endl;
}

int elegirUnaOpcionDelMenu() {
	int eleccion = 0;

	bool eleccionValida = false;

	do {

		cout << "Escoga una de las opciones disponibles: ";

		cin >> eleccion;

		if( (eleccion <= 0) || (eleccion > 4)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = (eleccion > 0) && (eleccion <= 4);

	} while(!eleccionValida);

	return eleccion;
}

void ejecutarOpcionElegida(string cabeceras[], Metrobus registros[], int opcionElegida) {
	switch(opcionElegida) {
	case 1:	double filtrarDesde = 0;
			double filtrarHasta = 0;
			elegirRangoDeFiltradoPorLongitud(filtrarDesde, filtrarHasta);
			filtrarRegistrosPorLongitud(cabeceras, registros, filtrarDesde, filtrarHasta);
			break;

	case 2:	// filtrarRegistrosPorLatitud(cabeceras, registros);
			break;

	case 3:	// filtrarRegistrosPorId(cabeceras, registros);
			break;

	case 4: terminarPrograma();
			break;
	}
}

void elegirRangoDeFiltradoPorLongitud(double &filtrarDesde, double &filtrarHasta) {
	bool eleccionValida = false;

	do {

		cout << "Escoga DESDE que numero quiere filtrar por longitud." << endl;

		cout << "Los valores permitidos van desde " << LONGITUD_MINIMA_ACEPTADA << " hasta " << LONGITUD_MAXIMA_ACEPTADA << " :";

		cin >> filtrarDesde;

		if( (filtrarDesde < LONGITUD_MINIMA_ACEPTADA) || (filtrarDesde > LONGITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = (filtrarDesde > LONGITUD_MINIMA_ACEPTADA) && (filtrarDesde <= LONGITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);

	eleccionValida = false;

	do {

		cout << "Escoga HASTA que numero quiere filtrar por longitud." << endl;

		cout << "Los valores permitidos van desde " << filtrarDesde << " hasta " << LONGITUD_MAXIMA_ACEPTADA << " :";

		cin >> filtrarHasta;

		if( (filtrarHasta < filtrarDesde) || (filtrarHasta > LONGITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = (filtrarHasta > filtrarDesde) && (filtrarHasta <= LONGITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);
}

void filtrarRegistrosPorLongitud(string cabeceras[], Metrobus registros[], double filtrarDesde, double filtrarHasta) {
	int cantidadDeRegistrosValidos = 0;

	for(int elemento = 1; elemento <= CANTIDAD_METROBUSES; elemento++) {
		Metrobus registroCandidato = registros[elemento-1];

		double longitudCandidata = registroCandidato.longitud;

		bool candidatoValido = (longitudCandidata >= filtrarDesde)&&(longitudCandidata <= filtrarHasta);

		if(candidatoValido) {
			mostrarDatosDelRegistro(registroCandidato);

			cantidadDeRegistrosValidos++;
		}
	}

	cout << ">>> La cantidad de registros que cumplen con lo pedido es de " << cantidadDeRegistrosValidos << "." << endl;
}

void mostrarDatosDelRegistro(Metrobus registroCandidato) {

}

void terminarPrograma(){
	cout << ".:::: PROGRAMA FINALIZADO ::::." << endl;

	cout << "Presione enter para terminar...";

	getchar();
}

/*
* Mostrar menu.
	* Pedir rango de valores del filtro.
		| Guardar rango.
		| Validar rango.
		| Mostrar registros filtrados.
* 	* Salir del menu.
 */
