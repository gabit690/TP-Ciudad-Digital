#include "funciones.h"
#include <iostream>
#include <iomanip>	// para funcion de seteo de precision
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

	string ruta = "src/estaciones-de-metrobus.csv";

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
	nuevoRegistro.identificador = std::atoi(id.c_str());

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

		ejecutarOpcionElegida(cabeceras, registros, opcionElegida);

		terminar = (opcionElegida == OPCION_FINALIZAR);

	} while(!terminar);
}

void mostrarMenu() {
	cout << "<<< MENU DEL PROGRAMA. >>>" << endl << endl;

	cout << "1. Filtrar por LONGITUD." << endl;

	cout << "2. Filtrar por LATITUD." << endl;

	cout << "3. Filtrar por ID." << endl;

	cout << "4. Salir." << endl << endl;
}

int elegirUnaOpcionDelMenu() {
	int eleccion = 0;

	bool eleccionValida = false;

	do {

		cout << "Ingrese el número de la opcion que desea realizar: ";

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
	case 1:	{ double filtrarLongitudDesde = 0;
			double filtrarLongitudHasta = 0;
			elegirRangoDeFiltradoPorLongitud(filtrarLongitudDesde, filtrarLongitudHasta);
			filtrarRegistrosPorLongitud(cabeceras, registros, filtrarLongitudDesde, filtrarLongitudHasta); }
			break;

	case 2:	{ double filtrarLatitudDesde = 0;
			double filtrarLatitudHasta = 0;
			elegirRangoDeFiltradoPorLatitud(filtrarLatitudDesde, filtrarLatitudHasta);
			filtrarRegistrosPorLatitud(cabeceras, registros, filtrarLatitudDesde, filtrarLatitudHasta); }
			break;

	case 3:	{ int idElegido = obtenerIdParaFiltrado();
			filtrarRegistrosPorId(cabeceras, registros, idElegido); }
			break;

	case 4: terminarPrograma();
			break;
	}
}

void elegirRangoDeFiltradoPorLongitud(double &filtrarDesde, double &filtrarHasta) {
	bool eleccionValida = false;

	do {

		cout << endl;

		cout << "Ingrese DESDE que número quiere filtrar por LONGITUD." << endl;

		cout << "Los valores DECIMALES permitidos van desde " << LONGITUD_MINIMA_ACEPTADA << " hasta " << LONGITUD_MAXIMA_ACEPTADA << ": ";

		cin >> filtrarDesde;

		if( (filtrarDesde < LONGITUD_MINIMA_ACEPTADA) || (filtrarDesde > LONGITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		} else {
			cout << endl;

			cout << "El dato ingresado es válido." << endl;
		}

		eleccionValida = (filtrarDesde >= LONGITUD_MINIMA_ACEPTADA) && (filtrarDesde <= LONGITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);

	eleccionValida = false;

	do {

		cout << endl;

		cout << "Ingrese HASTA que número quiere filtrar por LONGITUD." << endl;

		cout << "Los valores DECIMALES permitidos van desde " << filtrarDesde << " hasta " << LONGITUD_MAXIMA_ACEPTADA << ": ";

		cin >> filtrarHasta;

		if( (filtrarHasta < filtrarDesde) || (filtrarHasta > LONGITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = (filtrarHasta >= filtrarDesde) && (filtrarHasta <= LONGITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);
}

void filtrarRegistrosPorLongitud(string cabeceras[], Metrobus registros[], double filtrarDesde, double filtrarHasta) {
	int cantidadDeRegistrosValidos = 0;

	cout << endl;

	cout << "*************************************************" << endl << endl;

	for(int elemento = 1; elemento <= CANTIDAD_METROBUSES; elemento++) {
		Metrobus registroCandidato = registros[elemento-1];

		double longitudCandidata = registroCandidato.longitud;

		bool candidatoValido = (longitudCandidata >= filtrarDesde)&&(longitudCandidata <= filtrarHasta);

		if(candidatoValido) {
			mostrarDatosDelRegistro(registroCandidato);

			cantidadDeRegistrosValidos++;
		}
	}

	cout << ">>> La cantidad de registros que cumplen con lo pedido es de " << cantidadDeRegistrosValidos << "." << endl << endl;

	cout << "*************************************************" << endl << endl;
}

void mostrarDatosDelRegistro(Metrobus registroCandidato) {
	cout << "~ID: " << registroCandidato.identificador << endl;

	cout << "~Nombre: " << registroCandidato.nombre << endl;

	cout << "~Longitud: " << setprecision(15) << registroCandidato.longitud << endl;

	cout << "~Latitud: " << setprecision(15) << registroCandidato.latitud << endl;

	cout << "~Calle 1: " << registroCandidato.calle1 << endl;

	cout << "~Calle 2: " << registroCandidato.calle2 << endl;

	cout << "~Interseccion: " << registroCandidato.interseccion << endl;

	cout << "~Linea sentido norte: " << registroCandidato.lineaSentidoNorte << endl;

	cout << "~Linea sentido sur: " << registroCandidato.lineaSentidoSur << endl;

	cout << "~Metrobus: " << registroCandidato.metrobus << endl;

	cout << "~Nombre sentido: " << registroCandidato.nombreSentido << endl;

	cout << "~Observacion: " << registroCandidato.observacion << endl << endl;
}

void elegirRangoDeFiltradoPorLatitud(double &filtrarDesde, double &filtrarHasta) {
	bool eleccionValida = false;

	do {

		cout << endl;

		cout << "Ingrese DESDE que número quiere filtrar por LATITUD." << endl;

		cout << "Los valores DECIMALES permitidos van desde " << LATITUD_MINIMA_ACEPTADA << " hasta " << LATITUD_MAXIMA_ACEPTADA << ": ";

		cin >> filtrarDesde;

		if( (filtrarDesde < LATITUD_MINIMA_ACEPTADA) || (filtrarDesde > LATITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}  else {
			cout << endl;

			cout << "El dato ingresado es válido." << endl;
		}

		eleccionValida = (filtrarDesde >= LATITUD_MINIMA_ACEPTADA) && (filtrarDesde <= LATITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);

	eleccionValida = false;

	do {

		cout << endl;

		cout << "Ingrese HASTA que número quiere filtrar por LATITUD." << endl;

		cout << "Los valores DECIMALES permitidos van desde " << filtrarDesde << " hasta " << LATITUD_MAXIMA_ACEPTADA << ": ";

		cin >> filtrarHasta;

		if( (filtrarHasta < filtrarDesde) || (filtrarHasta > LATITUD_MAXIMA_ACEPTADA)) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = (filtrarHasta >= filtrarDesde) && (filtrarHasta <= LATITUD_MAXIMA_ACEPTADA);

	} while(!eleccionValida);
}

void filtrarRegistrosPorLatitud(string cabeceras[], Metrobus registros[], double filtrarDesde, double filtrarHasta) {
	int cantidadDeRegistrosValidos = 0;

	cout << endl;

	cout << "*************************************************" << endl << endl;

	for(int elemento = 1; elemento <= CANTIDAD_METROBUSES; elemento++) {
		Metrobus registroCandidato = registros[elemento-1];

		double latitudCandidata = registroCandidato.latitud;

		bool candidatoValido = (latitudCandidata >= filtrarDesde)&&(latitudCandidata <= filtrarHasta);

		if(candidatoValido) {
			mostrarDatosDelRegistro(registroCandidato);

			cantidadDeRegistrosValidos++;
		}
	}

	cout << ">>> La cantidad de registros que cumplen con lo pedido es de " << cantidadDeRegistrosValidos << "." << endl << endl;

	cout << "*************************************************" << endl << endl;
}

int obtenerIdParaFiltrado() {
	int eleccion = 0;

	bool eleccionValida = false;

	do {

		cout << endl;

		cout << "Ingrese el IDENTIFICADOR del metrobus buscado: ";

		cin >> eleccion;

		if( eleccion <= 0 ) {
			cout << endl;

			cout << "El dato ingresado es inválido. Inténtelo de nuevo." << endl;
		}

		eleccionValida = ( eleccion > 0 );

	} while(!eleccionValida);

	return eleccion;
}

void filtrarRegistrosPorId(string cabeceras[], Metrobus registros[], int filtrarID) {
	bool idEncontrado = false;

	int registroAnalizado = 1;

	cout << endl;

	cout << "*************************************************" << endl << endl;

	while( (!idEncontrado) &&  (registroAnalizado <= CANTIDAD_METROBUSES) ) {
		Metrobus registroCandidato = registros[registroAnalizado-1];

		idEncontrado = (registroCandidato.identificador == filtrarID);

		if( idEncontrado ) {
			mostrarDatosDelRegistro(registroCandidato);
		} else {
			registroAnalizado++;
		}
	}

	if ( !idEncontrado ) {
		cout << ">>> No hay ningún metrobus con ese ID." << endl << endl;
	}

	cout << "*************************************************" << endl << endl;
}

void terminarPrograma(){
	cin.ignore(256, '\n'); // Se limpia el buffer para que la espera de la presion de la tecla ENTER funcione.

	cout << endl;

	cout << ".:::: PROGRAMA FINALIZADO ::::." << endl;

	cout << "Presione enter para terminar...";

	getchar();
}
