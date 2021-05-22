/**	@details	Programa que transfiere los mejores hits de un archivo BLAST+ a un documento de texto plano
*	@author		Luis Daniel Cuéllar Garrido
*	@version	3.0
*	@date		22/07/2019
*	@copyright	GPLv3
*/

// Librerias----------------------------------------------------------------------------------------------------------------------------------------------------

#include <dirent.h>															// Para abrir, cerrar y manejar directorios
#include <fstream>															// Para leer y/ó escribir archivos de texto plano u hojas de calculo
#include <iostream>															// Para instrucciones de entrada y salida como "cout"
#include <math.h>															// Para obtener exponente con función logaritmo
#include <sstream>															// Para crear objetos de tipo stream "std::istringstream"
#include <stdlib.h>															// Para convertir valores de tipo string a doble flotante "atof"
#include <string.h>															// Para manegar cadenas de caracteres de tipo String

// 	Inicio de la función (método) principal "main"--------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{

// 	Constantes y variables locales------------------------------------------------------------------------------------------------------------------------------

	int exponente, contador = 0;											// Enteros donde se almacenarán los valores de los exponentes y un contador
	double valor;															// Valor doble donde se almacenará el resultado de similitud del BLAST
    char caracter;															// Char donde se almacenarán caracteres individuales
    bool expect, identities, positives, gaps;								// Variables booleanas para verificar si se han obtenido los resultados
    std::string linea, termino;												// Strings donde se almacenarán cadenas de texto
    std::string bhtfile, filename, extension;								// Strings para guardar el nombre del archivo resultante

// Rutina para transcribir los resultados de BLAST de un directorio a un sus correspondientes archivos en formato bht-------------------------------------------

    std::ifstream leer;														// Constructor ifstream para almacenar texto en buffer de entrada
	std::ofstream escribir;													// Constructor ofstream para almacenar texto en buffer de salida
	DIR *dir;																// Declaramos apuntador "dir"
	struct dirent *ent;														// Declaramos estructura "dirent" con apuntador "ent"
  	dir = opendir (".");													// Abrimos dirección el directorio actual en "dir"
  		
	while ((ent = readdir (dir)) != NULL)									// Mientras existan archivos en directorio actual
    {	
		if ((strcmp(ent -> d_name, ".") != 0) && (strcmp(ent -> d_name, "..") != 0))
		{																	// Si los nombres de archivos leídos en "ent" no es el directorio actual (".") ni el padre ("..")
      		filename = ent -> d_name;  			  							// Guardo el nombre del archivo en "filename"
      		size_t x = filename.find(".");									// Almacenamos el tamaño del nombre de "filename" hasta el caracter de extensión "." en "x"
        	extension = filename.substr(x);									// Almacenamos desde caracter de la posición "x" de "filename" en substring "extension"
        	
			if(extension == ".txt")  										// Si el substring "extension" es igual a ".txt" (verificamos que sea un archivo txt)
        	{
      			leer.open(filename.c_str());								// Abre el archivo ".txt" y lo guarda en buffer "leer" como cadena de caracteres
	      		bhtfile = filename.substr(0,x) + ".bht";					// Almaceno nombre de archivo de salida en "bhtfile" como "filename" + ".bht"
	      		escribir.open(bhtfile.c_str());								// Creamos archivo bht donde se guardaran los resultados con el nombre almacenado en "bhtfile"
//				getline(leer, linea);										// Caso especial para omitir el primer termino "BLASTN" ó "BLASTP" (Activar para BLAST 2.2.16)
					
				while (getline(leer, linea))								// Leo una nueva linea en cada iteración del while
				{
					std::istringstream renglon (linea);						// Almaceno mi string "linea" en un stream llamado "renglon"
		
					while (getline (renglon, termino, ' '))					// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
					{
						if (termino == "Query=")							// Si la palabra leída es "Query="
						{
//							getline (renglon, termino, '*');				// leo stream "renglon" hasta siguiente caracter "*" y lo guardo en "termino" (BLAST 2.2.16)
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta espacio en blanco y lo guardo en "termino" (BLAST 2.3.0+)				
				
/*							if (termino.size() == 3)						// Si el término leído es de tres caracteres pertenece a una colección (Caso especial)
							{
								escribir << termino << '|';					// Escribo nombre de proteína y barra en archivo txt
								getline (renglon, termino, '*');			// leo stream "renglon" hasta siguiente caracter "*" y lo guardo en "termino"
								escribir << termino << '|';					// Escribo nombre de proteína y barra en archivo txt
//								renglon.get(caracter);						// Salto un caracter del stream renglon (No se ocupa pero lo deje para no olvidar instrucción)
								getline (renglon, termino, '*');			// leo stream "renglon" hasta siguiente caracter "*" y lo guardo en "termino"
							}												// Caso especial para quitar etiqueta de laboratorio (Activar para BLAST 2.2.16)
*/															
							escribir << termino << '\t';					// Escribo nombre de gen o proteína y salto de tabulador en archivo txt
						}
			
						if (termino == "*****")								// Si el término leído es "*****"
						{
							getline (renglon, termino, '\n');				// Leo hasta el final de la linea (Caso especial para evitar encontrar de nuevo *****)
							escribir << "no_hits_found" << '\t' << "0" << '\t' << "0" << '\t' << "0" << '\t' << "0" << '\t';
						}													// Escribo "no_hits_found", salto de tabulador, cinco veces "0" y un salto de linea
			
						if (termino == "Value")								// Si la palabra leída es "Value"
						{
							expect = false;									// Indicar que no se han obtenido resultados de esta proteína
							identities = false;								// Indicar que no se han obtenido resultados de esta proteína
							positives = false;								// Indicar que no se han obtenido resultados de esta proteína
							gaps = false;									// Indicar que no se han obtenido resultados de esta proteína
							contador = 0;									// Reinicio el contador de resultados
							getline (leer, linea);							// Leo una nueva linea (Caso especial para saltar siguiente linea)
							getline (leer, linea);							// Leo una nueva linea (Caso especial para leer terminos de siguiente linea)
							std::istringstream renglon (linea);				// Almaceno mi string "linea" en un stream llamado "renglon"
//							getline (renglon, termino, '*');				// leo stream "renglon" hasta siguiente caracter "*" y lo guardo en "termino" (BLAST 2.2.16)
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta espacio en blanco y lo guardo en "termino" (BLAST 2.3.0+)
				
							if (termino.size() == 3)						// Si el término leído es de tres caracteres pertenece a una colección (Caso especial)
							{
								getline (renglon, termino, '*');			// leo stream "renglon" hasta siguiente caracter "*" y lo guardo en "termino"
								getline (renglon, termino, '0');			// leo stream "renglon" hasta siguiente caracter "0" y lo guardo en "termino"
								escribir << termino << '_';					// Escribo nombre de proteína y un guión bajo en archivo txt
								renglon.get(caracter);						// Salto un caracter del stream renglon
								getline (renglon, termino, 'g');			// leo stream "renglon" hasta siguiente caracter "g" y lo guardo en "termino"
							}

							escribir << termino << '\t';					// Escribo nombre de gen o proteína y salto de tabulador en archivo txt				
						}
			
						if (termino == "Expect" && expect == false)
						{
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
							valor = ::atof(termino.c_str());				// Convierto valor del hit de string a doble flotante
								
							if (valor < 1)
							{
								exponente = ceil(-log10 (valor));			// Obtengo valor del exponente con logaritmo base 10 redondeado al entero más alto
									
								if (valor == 0 || exponente > 999)			// Si el valor del hit es cero ó la cantidad de ceros después del punto es mayor a 999
								{
									escribir << "999" << '\t';				// Escribo el valor normalizado del hit en 999 y un salto de tabulador en archivo txt
								}

								else escribir << exponente << '\t';			// Escribo valor del hit normalizado a su exponente y un salto de tabulador en archivo txt
							}
								
							else escribir << 0 << '\t';						// Escribo valor del hit normalizado a su exponente y un salto de tabulador en archivo txt
							expect = true;									// Indicar que ya han obtenido resultados de esta proteína
							contador++;										// Incremento el contador de resultados
						}
			
						if (termino == "Identities" && identities == false)
						{
							getline (renglon, termino, '(');				// leo stream "renglon" hasta siguiente caracter "(" y lo guardo en "termino"
							getline (renglon, termino, '%');				// leo stream "renglon" hasta siguiente caracter "%" y lo guardo en "termino"
							escribir << termino << '\t';					// Escribo porciento de identidad y un salto de tabulador en archivo txt
							identities = true;								// Indicar que ya han obtenido resultados de esta proteína
							contador++;										// Incremento el contador de resultados
						}
			
						if (termino == "Positives" && positives == false)
						{
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
							getline (renglon, termino, '/');				// leo stream "renglon" hasta siguiente caracter "/" y lo guardo en "termino"
							escribir << termino << '\t';					// Escribo cantidad de coincidencias y un salto de tabulador en archivo txt
							positives = true;								// Indicar que ya han obtenido resultados de esta proteína
							contador++;										// Incremento el contador de resultados
						}
			
						if (termino == "Gaps" && gaps == false)
						{
							getline (renglon, termino, '/');				// leo stream "renglon" hasta siguiente caracter "/" y lo guardo en "termino"
							getline (renglon, termino, ' ');				// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
							escribir << termino << '\t'; 					// Escribo longitud de alineamiento, salto de tabulador
							gaps = true;									// Indicar que ya han obtenido resultados de esta proteína
							contador++;										// Incremento el contador de resultados
						}
			
//						if (termino == "BLASTN" || termino == "BLASTP")		// Si la palabra leída es "BLASTN" o "BLASTP" (Activar para BLAST 2.2.16)
						if (termino == "used:")								// Si la palabra leída es "used:" (Activar para BLAST 2.3.0+)
						{
							escribir << "1" << '\n';						// Escribo cantidad de hits y salto de linea en archivo txt
						}
					}
				}
			}
			
//			escribir << "1" << '\n';										// Caso especial para ultima linea dado que "BLASTP" ya no aparecerá (BLAST 2.2.16)
			escribir.close();												// Cierro el buffer "escribir" y libero la memoria
			leer.close();													//
		}
	}
	
	printf("\nSe ha finalizado la ejecucion del programa:\n\n");
	system("pause");														// Pausa para vizualizar resultados
	return 0;
}

/**	Notas:---------------------------------------------------------------------------------------
*	@note	Implementar el método como libreria para otros programas
*   @note	Implementar paso de parámetros para incluir los archivos desde terminal de Windows
*/
