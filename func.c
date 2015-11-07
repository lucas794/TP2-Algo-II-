#include "func.h"
#include "doctores.h"
#include "pacientes.h"
#include "csv.h"
#include "hash.h"

bool leer_pacientes( char *srcfile, hash_t* asignacion_de_tabla )
{
	FILE *arch_csv;
	
	if( !(arch_csv = fopen(srcfile, "r")) )
		return false;
		
    csv_t linea = {','};

    while( csv_siguiente(&linea, arch_csv) )
	{
		/* Necesito crear nodos de 'pacientes' */
		paciente_t* nuevo = crear_paciente(linea.primero, linea.segundo);
		
		if( !nuevo )
		{
			fclose(arch_csv);
			return false;
		}
		
		hash_guardar(asignacion_de_tabla, linea.primero, nuevo);
    }

    csv_terminar(&linea);
    fclose(arch_csv);

	return true;
}

bool leer_doctor_especialidades( char *srcfile, hash_t* tabla_doctores, hash_t* tabla_especialidades )
{
	FILE *arch_csv;
	
	if( !(arch_csv = fopen(srcfile, "r")) )
		return false;
		
    csv_t linea = {','};

    while( csv_siguiente(&linea, arch_csv) )
	{
		doctor_t *doctor = crear_doctor(linea.primero, linea.segundo);
		
		if( !doctor )
		{
			fclose(arch_csv);
			return false;
		}
		
		hash_guardar(tabla_doctores, linea.primero, doctor);
		
		heap_t* nuevo = malloc(sizeof(sistema_t));
		
		if( !nuevo )
			return NULL;
			
		nuevo = heap_crear( /* FUNCION COMPARACION */ );
		
		if( !nuevo )
		{
			fclose(arch_csv);
			return false;
		}
				
		hash_guardar(tabla_especialidades, linea.segundo, nuevo);
    }

    csv_terminar(&linea);
    fclose(arch_csv);

	return true;
}

void DESTRUIR_ESPECIAL_( void* data )
{
	sistema_t* especial = data;
	
	heap_destruir(data, destruir_paciente);
}
