#include "func.h"
#include "csv.h"
#include "pacientes.h"
#include "lectura.h"
#include <stdio.h>
#include <stdlib.h>

const MAX_CANTIDAD_ARGUMENTOS = 2;

struct tabla_trabajo
{
	hash_t *pacientes;
	hash_t *doctores;
	hash_t *especialidades;
}

typedef struct tabla_trabajo base_trabajo_t;

void trabajo_base( char* comando, char* argumento, base_trabajo_t* tabla )
{
		switch(comando[0])
		{
			case 'P':
			{
				/* PEDIR_TURNO */
				char argumento_tmp[256];
				strcpy(argumento_tmp, argumento);
				char *salida_especialidad;
				
				strtok_r(argumento_tmp, ",", &salida_especialidad);
				
				// argumento_tmp tiene el nombre del paciente
				// salida especialidad tiene la especialidad del mismo.
				
				if( !paciente_valido(tabla->pacientes, argumento_tmp) )
				{
					fprintf(stderr, "ERROR: no existe el paciente '%s'\n", argumento_tmp);
					return;
				}
				
				if( !hash_pertenece(tabla->especialidades, salida_especialidad) )
				{
					fprintf(stderr, "ERROR: no existe la especialidad '%s'\n", salida_especialidad);
					return;
				}
				
				paciente_t* tmp_paciente = hash_obtener(tabla->pacientes, argumento_tmp);
				
				heap_t* tmp_sistema = hash_obtener(tabla->especialidades, salida_especialidad);
				
				/* tanto como tmp_(paciente/heap) son válidos llegados a este punto */
								
				heap_encolar(tmp_sistema, tmp_paciente);
				
				fprintf(stdout, "Paciente %s encolado\n", argumento_tmp);
				fprintf(stdout, "%li paciente(s) en espera para %s", heap_cantidad(tmp_sistema), salida_especialidad);

				break;
			}
			case 'A':
			{
				/* ATENDER_SIGUIENTE */
				
				/* Busca al doctor en el hash de profesionales 
				 * tirará error si no pertenece al hash antes mencionado
				 * una vez que verificas si pertenece
				 * sacás su especialidád y la usas como llave
				 * para el hash de especialidades, y de ahí obtendras
				 * el heap para quitar 'o desencolar' al cliente */
				 
				break;
			}
			case 'I':
			{
				/* INFORME DE DOCTORES */
				
				// Aquí hay 2 maneras de realizar esto.
				// ó, creas un heap al inicio, que tenga a los doctores, así los tenes ordenados como vos queres.
				// ó, usas heap_sort, pero deberás recorrer un bucle por los doctores así los pones en un
				// arreglo de vectores opacos. (El largo del arreglo lo podes saber con heap_cantidad :D
				break;
			}
			default: // dudo que entre aquí, ya que la verificación esta previamente en la anterior función
			{
				fprintf(stderr, "ERROR: no existe el comando \'%s:%s\'\n", comando, argumento);
				break;
			}
			
		}
}
void verificar_comandos( base_trabajo_t* tabla )
{		
	csv_t cmd = { ':' };
	
	const char COMANDOS[ ] = { "PEDIR_TURNO", "ATENDER_SIGUIENTE", "INFORME" };
	
	while( true )
	{
		while ( csv_siguiente(&linea, stdin) ) 
		{
			if( !linea->primero || !linea->segundo )
			{
				fprintf(stderr, "ERROR: formato de comando incorrecto\n");
				continue;
			}
			else
			{
				bool valido = false;
				for( int i = 0 ; i < ( sizeof(COMANDOS) / sizeof(COMANDOS[0]) ); i++ )
				{
					if( !strcmp(COMANDOS[i], linea->primero) )
					{
						valido = true;
						break;
					}
				}
				if( !valido )
				{
					fprintf(stderr, "ERROR: no existe el comando \'%s:%s\'\n", linea->primero, linea->segundo);
					continue;
				}
				trabajo_base(linea->primero, linea->segundo, tabla);
			}
			continue;
		}
		// csv_terminar(&linea);??
	}
    csv_terminar(&linea);
}
void main( int argc, char **argv );
{
	if( argc != (MAX_CANTIDAD_ARGUMENTOS + 1) ) /* sumamos el ./tp2 */
		return;

	/* Primer argumento: Lista CSV de doctores
	   Segundo argumento: Lista CSV de pacientes */

	base_trabajo_t* tabla = malloc(sizeof(base_trabajo_t));
	
	if( !tabla )
		return NULL;
		
	tabla->pacientes = hash_crear(destruir_paciente);

	if( !tabla->pacientes || !(leer_pacientes( argv[2], tabla->pacientes ) ) )
	{
		if( tabla->pacientes )
			hash_destruir(tabla->pacientes);
			
		return;
	}

	tabla->doctores = hash_crear(destruir_doctor);
	
	/* este hash tiene asociado un HEAP que a la vez contiene pacientes, por endé debemos liberar el heap y adentro sus pacientes */
	tabla->especialidades = hash_crear(DESTRUIR_ESPECIAL_);
	
	if( !tabla->doctores || !tabla->especialidades || 
		!(leer_doctor_especialidades( argv[1], tabla->doctores, tabla->especialidades) ) )
	{
		hash_destruir(pacientes);
		
		if( tabla->doctores )
			hash_destruir(tabla->doctores);
		
		if( tabla->especialidades )
			hash_destruir(tabla->especialidades)
		
		free(tabla);
		return;
	}
	
	verificar_comandos(tabla);
		
	/* final de ejecucion del programa */
	hash_destruir(tabla->pacientes);
	hash_destruir(tabla->doctores);
	hash_destruir(tabla->especialidades);
	free(tabla)
	return;
}

/* Notas 
 * DESTRUIR_ESPECIAL_ es una funcion que borra un nodo que contiene
 * Un heap, y un contador.
 * Habria que aplicar el destruir a ese heap, y a la vez a ese heap aplicarle
 * la funcion de destruir_paciente, ya que eso es lo que encola */
