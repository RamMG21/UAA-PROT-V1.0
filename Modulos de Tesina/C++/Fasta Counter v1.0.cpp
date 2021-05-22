/**	@details	Programa que cuenta las entradas de un archivo de información genomica en formato fasta.
*	@author		Luis Daniel Cuéllar Garrido
*	@version	1.0
*	@date		18/01/2021
*	@copyright	GPLv3
*/

// Librerias-------------------------------------------------------------------------------------

#include <dirent.h>																// Para abrir, cerrar y manejar directorios
#include <iostream>																// Para instrucciones de entrada y salida como "cout"
#include <fstream>																// Para leer y/ó escribir archivos de texto plano u hojas de calculo

// 	Inicio de la función (método) principal "main"-----------------------------------------------

int main(int argc, char** argv)
{

// 	Constantes y variables locales---------------------------------------------------------------

    std::string linea, termino, word;											// Creo strings donde se almacenarán las palabras leídas
    int count = 0;																// Variables para almacenar los conteos de entradas de un archivo fasta
    std::string nameHongo, newname, outputTxt, txt;								// Strings para guardar el nombre del archivo resultante

// Rutina para transcribir los resultado de hits bidireccionales con valores e-value filtrados a un nuevo archivo txt-------------------------------------------

    std::ifstream leer;															// Constructor ifstream para almacenar texto en buffer de entrada
	std::ofstream escribir;														// Constructor ofstream para almacenar texto en buffer de salida
	DIR *dir;																	// Declaramos apuntador "dir"
	struct dirent *ent;															// Declaramos estructura "dirent" con apuntador "ent"
  	dir = opendir (".");														// Abrimos dirección del directorio actual en "dir"
  	escribir.open("Conteo.cnt");												// Creamos archivo cnt donde se guardaran los resultados con el nombre almacenado en "outputTxt"
  		
	while ((ent = readdir (dir)) != NULL)										// Mientras existan archivos en directorio actual
    {

		if ((strcmp(ent -> d_name, ".") != 0) && (strcmp(ent -> d_name, "..") != 0))
		{																		// Si los nombres de archivos leídos en "ent" no es el directorio actual (".") ni el padre ("..")
      		nameHongo = ent -> d_name;  			  							// Guardo el nombre del archivo en "nameHongo"
			size_t x = nameHongo.find(".");										// Almacenamos el tamaño del nombre de "nameHongo" hasta el caracter de extensión "." en "x"
        	txt = nameHongo.substr(x);											// Almacenamos desde caracter de la posición "x" de "nameHongo" en substring "txt"
        	newname = nameHongo.substr(0,x);									// Alacenamos nombre sin extension
        	
//        	if(txt == ".fna")		  											// Si el substring "txt" es igual a ".fna" (verificamos que sea un archivo fasta de acidos nucléicos)
			if(txt == ".faa")		  											// Si el substring "txt" es igual a ".faa" (verificamos que sea un archivo fasta de aminoacidos)
        	{
      			leer.open(nameHongo.c_str());									// Abre el archivo fasta y lo guarda en buffer "leer" como cadena de caracteres
	      		outputTxt = newname + ".cnt";									// Almaceno nombre de archivo de salida en "outputTxt" como "nameHongo" + "cnt"
	      		

// Rutina para contar bbhs--------------------------------------------------------------------------------------------------------------------------------------
	
				while (getline(leer, linea, '\n'))								// Leo una nueva palabra en cada iteración del while
				{	
					word = linea.substr(0,1);									// Extraemos el primer caracter del la primer palabra del renglón
	
					if (word == ">")											// Si la palabra encontrada es ">"			
					{
						count++;												// Incrementa la cuenta de entradas
					}			
				}
		
				escribir << newname << '\t' << count << '\n';
				count = 0;
				leer.close();
			}
			
		}
		
	}
	
	escribir.close();															// Cierro el buffer "escribir" y libero la memoria
	printf("\nSe ha finalizado la ejecucion del programa:\n\n");
		system("pause");														// Pausa para vizualizar resultados
		return 0;
}

/**	Notas:---------------------------------------------------------------------------------------
*	@note	Implementar el método como libreria para otros programas
*   @note	Corregir bug de que el formato del csv no es igual al standard de Excel (muy posiblemente añade comas al final de cada fila)
*/
