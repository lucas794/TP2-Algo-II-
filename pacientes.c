#include <stdio.h>
#include "pacientes.h"
#include "doctores.h"

struct _paciente
{
	char *nombre_paciente;
	size_t contribucion;
};


bool paciente_valido(const hash_t* t_pacientes, const char *nombre_paciente)
{
	return hash_pertenece(t_pacientes, nombre_paciente);
}

paciente_t* crear_paciente(char *nombre, size_t contribucion)
{
	paciente_t* pac = malloc(sizeof(paciente_t));
	
	if( !pac )
		return NULL;
		
	pac->nombre_paciente = strdup(nombre);
	pac->contribucion = contribucion;
	
	return pac;
}

hash_destruir_dato_t destruir_paciente(void *dato)
{
	paciente_t* pac = dato;
	
	free(pac->nombre_paciente);
	free(pac);
}
