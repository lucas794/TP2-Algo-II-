#ifndef CLINICA_PACIENTES
#define CLINICA_PACIENTES

#include <stdbool.h>
#include <stddef.h>
#include "hash.h"

typedef struct _paciente paciente_t;

/* 	paciente_valido
	Dado el nombre de un paciente, se devolverá true o falso en el
	caso que corresponda sí este último está en la tabla de clientes
	del hospital.

	pre condiciones:
		La tabla de pacientes del hospital debe ser válida.
*/
bool paciente_valido(const hash_t* t_pacientes, const char *nombre_paciente);

paciente_t* crear_paciente(char *nombre, size_t contribucion);

hash_destruir_dato_t destruir_paciente(void *);
/* free nombre_paciente */

#endif
