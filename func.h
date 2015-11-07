#ifndef CLINICA_MAIN
#define CLINICA_MAIN

#include <stdbool.h>
#include "heap.h"
#include "hash.h"

bool leer_pacientes( char *srcfile, hash_t* asignacion_de_tabla );

bool leer_doctor_especialidades( char *srcfile, hash_t* tabla_doctores, hash_t* tabla_especialidades );

#endif
