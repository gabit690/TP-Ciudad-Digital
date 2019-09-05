#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <fstream>
#include <string>

/*
 * PRE.: -.
 * POST.: Pone en funcionamiento al programa cuyo objetivo es poder filtrar y ver los datos
 * de un archivo csv obtenido de la página de gobierno de la ciudad de Buenos Aires
 * acerca de los metrobuses.
 */
	void ejecutarPrograma();

/*
 * PRE.: -.
 * POST.: muestra un mensaje de bienvenida al usuario del programa.
 */
	void darLaBienvenida();

/*
 * Contenido de los campos de un registro del archivo de metrobuses.
 */
	struct Metrobus {
		double longitud;
		double latitud;
		int identificador;
		std::string nombre;
		std::string calle1;
		std::string calle2;
		std::string interseccion;
		std::string lineaSentidoNorte;
		std::string lineaSentidoSur;
		std::string metrobus;
		std::string nombreSentido;
		std::string observacion;
	};

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES.
 * POST.: Obtiene los registros dentro del archivo de metrobuses.
 */
	void procesarArchivo(std::string cabeceras[], Metrobus registros[]);

/*
 * PRE.: 'archivo' esta abierto y corresponde al archivo de registros de metrobuses.
 * 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * POST.: Lee la primera linea del archivo y obtiene las cabeceras de los campos.
 */
	void obtenerCabeceras(std::ifstream &archivo, std::string cabeceras[]);

/*
 * PRE.: 'archivo' esta abierto y se leyo previamente la linea de cabeceras.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES.
 * POST.: Lee el resto de las lineas del archivo y obtiene todos los registros de los metrobuses.
 */
	void obtenerRegistros(std::ifstream &archivo, Metrobus registros[]);

/*
 * PRE.: 'archivo' esta abierto y se leyo previamente la linea de cabeceras.
 * POST.: devuelve un registro con la informacion de una linea leida del archivo.
 */
	Metrobus armarRegistroLeido(std::ifstream &archivo);

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES
 * y contiene la informacion del archivo de metrobuses procesado.
 * POST.: accede al menu del programa el cual cuenta con las opciones que se pueden aplicar
 * a la informacion obtenida del archivo de metrobuses.
 */
	void usarMenuDelPrograma(std::string cabeceras[], Metrobus registros[]);

/*
 * PRE.: -.
 * POST.: muestra el menu del programa.
 */
	void mostrarMenu();

/*
 * PRE.: -.
 * POST.: obtiene un numero correspondiente a una de las opciones del menu.
 */
	int elegirUnaOpcionDelMenu();

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES
 * y contiene la informacion del archivo de metrobuses procesado.
 * 'opcionElegida' es un numero que corresponde a una de las opciones del menu.
 * POST.: Realiza la opcion elegida.
 */
	void ejecutarOpcionElegida(std::string cabeceras[], Metrobus registros[], int opcionElegida);

/*
 * PRE.: -.
 * POST.: obtiene los valores a partir de los cuales se filtraran los registros por rango de longitud.
 */
	void elegirRangoDeFiltradoPorLongitud(double &filtrarDesde, double &filtrarHasta);

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES
 * y contiene la informacion del archivo de metrobuses procesado.
 * 'filtrarDesde' y 'filtrarHasta' son decimales que estan en [LONGITUD_MINIMA_ACEPTADA, LONGITUD_MAXIMA_ACEPTADA].
 * POST.: muestra la informacion de los registros cuya longitud esta en [LONGITUD_MINIMA_ACEPTADA, LONGITUD_MAXIMA_ACEPTADA].
 */
	void filtrarRegistrosPorLongitud(std::string cabeceras[], Metrobus registros[], double filtrarDesde, double filtrarHasta);

/*
 * PRE.: 'registroCandidato' es un registro inicializado previamente.
 * POST.: muestra la informacion dentro del registro.
 */
	void mostrarDatosDelRegistro(Metrobus registroCandidato);

/*
 * PRE.: -.
 * POST.: obtiene los valores a partir de los cuales se filtraran los registros por rango de latitud.
 */
	void elegirRangoDeFiltradoPorLatitud(double &filtrarDesde, double &filtrarHasta);

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES
 * y contiene la informacion del archivo de metrobuses procesado.
 * 'filtrarDesde' y 'filtrarHasta' son decimales que estan en [LONGITUD_MINIMA_ACEPTADA, LONGITUD_MAXIMA_ACEPTADA].
 * POST.: muestra la informacion de los registros cuya latitud esta en [LATITUD_MINIMA_ACEPTADA, LATITUD_MAXIMA_ACEPTADA].
 */
	void filtrarRegistrosPorLatitud(std::string cabeceras[], Metrobus registros[], double filtrarDesde, double filtrarHasta);

/*
 * PRE.: -.
 * POST.: obtiene el id a partir del cual se filtraran los registros.
 */
	int obtenerIdParaFiltrado();

/*
 * PRE.: 'cabeceras[]' es un vector de tamanio determinado por el valor constante CANTIDAD_COLUMNAS.
 * 'registros[]' es un vector de tamanio determinado por el valor constante CANTIDAD_METROBUSES
 * y contiene la informacion del archivo de metrobuses procesado.
 * 'filtrarID' es un valor mayor a 0.
 * POST.: muestra (si existe) la informacion del registro cuyo identificador coincida con 'filtrarID'.
 */
	void filtrarRegistrosPorId(std::string cabeceras[], Metrobus registros[], int filtrarID);

/*
 * PRE.: -.
 * POST.: muestra un mensaje de finalizacion del programa al usuario.
 */
	void terminarPrograma();

#endif /* FUNCIONES_H_ */
