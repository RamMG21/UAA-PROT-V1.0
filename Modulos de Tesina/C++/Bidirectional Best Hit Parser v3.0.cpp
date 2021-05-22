/** @details	Programa que transfiere los hits de dos archivos de mejores hits (bht) a un documento de texto plano
*	@author		Luis Daniel Cuéllar Garrido
*	@version	3.0
*	@date		10/08/2019
*	@copyright	GPLv3
*/

// Librerias----------------------------------------------------------------------------------------------------------------------------------------------------

#include <dirent.h>																			// Para abrir, cerrar y manejar directorios
#include <fstream>																			// Para leer y/ó escribir archivos de texto plano u hojas de calculo
#include <iostream>																			// Para instrucciones de entrada y salida como "cout"
#include <sstream>																			// Para crear objetos de tipo stream "std::istringstream"

// Inicio de la función (método) principal "main"---------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{

// Constantes y variables locales-------------------------------------------------------------------------------------------------------------------------------

	std::string O1Prot1, O1Prot2, O2Prot1, O2Prot2;											// Para guardar las proteinas de los organismos (O1Prot1 = Organismo 1 Proteina 1)
	std::string filename, filenameInv, extension, linea1, linea2, linea3, termino;			// Para manejar las cadenas de texto que se van a comparar
	std::string Organismo, Origen, Destino;													// Para identificar los organismos que se están comparando
	std::string ejecutar = "lista.txt";														// Nombre de la lista de organismos a ejecutar
	std::string bbhfile;																	// Para guardar el nombre del archivo de bbhs

// Rutina para transcribir los resultados de mejores hits (bht) de un directorio a un sus correspondientes archivos en formato bbh------------------------------

	std::ifstream leer, comparacion, lista;													// Para abrir el doc del organismo actual, su inverso y la lista de ejecución
	std::ofstream escribir;																	// Para escribir en el nuevo archivo
	DIR *dir;																				// Con un puntero a DIR abriremos el directorio
	struct dirent *ent;																		// En *ent habrá información sobre el archivo que se está "sacando" a cada momento
	lista.open(ejecutar.c_str());															// Abrimos el archivo con la lista de organismos que se van a ejecutar
	
	while (getline(lista, linea1, '\n'))													// Leemos el nombre de cada organismo en el string "linea1"
	{
		std::istringstream renglon(linea1);													// Almacena el string "linea1" en el stream "renglon"
		getline(renglon, Organismo, '\n');													// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
		bbhfile = Organismo + ".bbh";														// Guardamos el nombre del archivo de los bbhs
		escribir.open(bbhfile.c_str());														// Creamos archivo bbh con los resultados del nombre almacenado en "bbhfile"
		dir = opendir (".");																// Empezaremos a leer en el directorio actual
	 
		while ((ent = readdir (dir)) != NULL)												// Mientras existan archivos en directorio actual
		{
			if ((strcmp(ent -> d_name, ".") != 0) && (strcmp(ent -> d_name, "..") != 0))	// Si los archivos en "ent" no es el directorio actual (".") ni el padre ("..")
        	{
				filename = ent -> d_name;  													// Guardo el nombre del archivo en "filename"
        		size_t x = filename.find(".");												// Almacenamos el tamaño de "filename" hasta el caracter de extensión "." en "x"
        		extension = filename.substr(x);												// Almacenamos desde la posición "x" de "filename" en substring "extension"
        	
        		if(extension == ".bht")  													// Verifica si el archivo es .bht
    			{
					x = filename.find("_vs_");												// Separa el archivo .bht en los nombres de los 2 hongos comparados
    				Origen = filename.substr(0, x);											// Almaceno el nombre del organismo origen
    				Destino = filename.substr((x + 4), (filename.size()));					// Almaceno el nombre del organismo destino + extension .bht
    				Destino.resize(Destino.length() - 4);									// Eliminamos la extension del organismo destino
    				filenameInv = Destino + "_vs_" + Origen + ".bht";						// Almacenamos el nombre de la cadena inversa de la original estaba .bht
    			
					if(Origen == Organismo)													// Para validar que sólo haga los vs del organismo actual
    				{
						leer.open(filename.c_str()); 										// Abre el archivo del organismo actual vs otro
    					escribir << "Query:" << '\t' << Destino << '\n'; 					// Escribo el nombre del organismo destino en una linea del archivo .bbh
	        		
						while (getline(leer, linea2, '\n')) 								// Leo una nueva linea en cada iteración del while
		            	{	
							std::istringstream renglon(linea2);								// Almacena el string "linea2" en el stream "renglon"
		            		getline(renglon,termino,'\t');									// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
		            		O1Prot1 = termino;												// Almacena la proteina 1 del organismo 1
							getline(renglon,termino,'\t');									// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
		            		O1Prot2 = termino;												// Almacena la proteina 2 del organismo 1
		            		comparacion.open(filenameInv.c_str());							// Abre el archivo del organismo a comparar (otro vs actual)
	            	
							while (getline(comparacion, linea3, '\n'))						// Leo una nueva linea en cada iteración del while
	            			{
								std::istringstream renglon(linea3);							// Almacena el string "linea3" en el stream "renglon"
	            				getline(renglon,termino,'\t');								// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
	            				O2Prot1 = termino;											// Almacena la proteina 1 del organismo 2
								getline(renglon,termino,'\t');								// leo stream "renglon" hasta siguiente espacio en blanco y lo guardo en "termino"
	            				O2Prot2 = termino;											// Almacena la proteina 2 del organismo 2
							
								if(O1Prot1 == O2Prot2 && O1Prot2 == O2Prot1)				// Si las proteinas coinciden en los dos sentidos
	            				{																
									escribir << linea2 << '\t';								// Escribe la linea en el nuevo archivo
	            					escribir << linea3 << '\n';								// Escribe la linea en el nuevo archivo
	            					break;
								}
							}
					
							comparacion.close();											// Cierra el archivo del hongo de comparacion
	          			}
          		
						leer.close();														// Cierra el archivo del hongo Principal vs Otro hongo
					}
        		}
      		}
    	}
   
   		closedir (dir);
    	escribir.close();
	}

lista.close();
printf("\nSe ha finalizado la ejecucion del programa:\n\n");
system("pause");																			// Pausa para vizualizar resultados
return 0;
}
