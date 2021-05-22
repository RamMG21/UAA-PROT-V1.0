/**	@details	Programa "Best Hit E- Value Filter v2.0" que transcribe 
*   las entradas de un archivo de Best Hits que se encuentren por debajo 
*	de un cierto e-value 
*   Rutina para transcribir los resultado de hits bidireccionales 
*   con valores e-value filtrados a un nuevo archivo eva
*	@author		Luis Daniel Cuéllar Garrido
*	@version	2.0
*	@date		29/05/2018
*	@copyright	GPLv3
*/

#include <dirent.h>		// Para abrir, cerrar y manejar directorios
#include <fstream>		// Para leer y/ó escribir archivos de texto plano u hojas de calculo
#include <iostream>		// Para instrucciones de entrada y salida como "cout"
#include <math.h>		// Para obtener exponente con función logaritmo
#include <sstream>		// Para crear objetos de tipo stream "std::istringstream"
#include <stdlib.h>		// Para convertir valores de tipo string a doble flotante "atof"
#include <string.h>		// Para manegar cadenas de caracteres de tipo String

int main(int argc, char** argv) {
	int valor, contador, evalue;// Enteros con los valores evalue, un contador y el valor evalue 
    std::string linea, termino;	// Strings donde se almacenarán cadenas de texto
    std::string nameHongo, newname, outputTxt, txt;	// Strings para guardar el nombre del archivo resultante
    std::ifstream leer;					// Constructor ifstream para almacenar texto en buffer de entrada
	std::ofstream escribir;				// Constructor ofstream para almacenar texto en buffer de salida
	DIR *dir;							// Declaramos apuntador "dir"
	struct dirent *ent;					// Declaramos estructura "dirent" con apuntador "ent"
	
  	dir = opendir (".");				// Abrimos dirección el directorio actual en "dir"
	printf 
(" e-value entero por debajo del cual filtrar\n(El valor define umbral como cantidad de ceros despues del punto): e-");
	std::cin >> evalue;		
	while ((ent = readdir (dir)) != NULL) {	// Mientras existan archivos en directorio actual
		if ((strcmp(ent -> d_name, ".") != 0) 
		&& (strcmp(ent -> d_name, "..") != 0)) { /* Si los nombres de archivos leídos 
												en "ent" no es el directorio actual (".") ni el padre ("..") */															
      		nameHongo = ent -> d_name;// Guardo el nombre del archivo en "nameHongo"
      		size_t x = nameHongo.find(".");	// Almacenamos el tamaño del nombre de "nameHongo" hasta el caracter de extensión "." en "x"
        	txt = nameHongo.substr(x);// Almacenamos desde caracter de la posición "x" de "nameHongo" en substring "txt"
        	newname = nameHongo.substr(0,x);// 
			if(txt == ".txt") {	// Si el substring "txt" es igual a ".txt" (verificamos que sea un archivo txt)
      			leer.open(nameHongo.c_str());// Abre el archivo ".txt" y lo guarda en buffer "leer" como cadena de caracteres
	      		outputTxt = newname + ".eva";// Almaceno nombre de archivo de salida en "outputTxt" como "nameHongo" + "eva"
	      		escribir.open(outputTxt.c_str());// Crea archivo txt guardaran resultados con el nombre almacenado en "outputTxt"		
				while (getline(leer, linea)) {// Leo una nueva linea en cada iteración del while
					std::istringstream renglon (linea);	// Almaceno mi string "linea" en un stream llamado "renglon"
					contador = 0;
					getline (renglon, termino, '\t');// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
					if (termino != "Query:") {		// Validación 
						while (getline (renglon, termino, '\t')) {// leo stream "renglon" hasta siguiente espacio en blanco y guardo en "termino"
							contador++;
							if (contador == 1)	{// Si el término leído es el anterior inmediato a E-Value
								getline (renglon, termino, '\t');// Leo valor de evalue y lo guardo en string "termino"
								valor = ::atof(termino.c_str());// Convierto valor del evalue de string a doble flotante			
								if (valor > evalue) {
									while (getline (renglon, termino, '\t')) {// leo stream "renglon" hasta siguiente espacio en blanco y guardo en "termino"
										contador++;
										if (contador == 7) {// Si el término leído es el anterior inmediato a E-Value
											getline (renglon, termino, '\t');// Leo valor de evalue y lo guardo en string "termino"
											valor = ::atof(termino.c_str());// Convierto valor del evalue de string a doble flotante			
											if (valor > evalue) {
												escribir << linea << '\n';// Escribo Bidirectional Best Hit en el nuevo archivo txt
											}
										}
									}
								}
							}
						}
					} else	escribir << linea << '\n';// Escribo linea en el caso de que la primer palabra sea "Query"
					getline (renglon, termino, '\n');// Leo hasta el final de la linea
				}
			}
		}	
		escribir.close();// Cierro el buffer "escribir" y libero la memoria
		leer.close();	// Cierro el buffer "leer" y libero la memoria
	}
	printf("\nSe ha finalizado la ejecucion del programa:\n\n");
	system("pause");// Pausa para vizualizar resultados
	return 0;
}

/**	Notas:---------------------------------------------------------------------------------------
*	@note	Implementar el método como libreria para otros programas
*   @note	Implementar paso de parámetros para incluir los archivos desde terminal de Windows
*/
