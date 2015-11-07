#ifndef CLINICA_DOCTORES
#define CLINICA_DOCTORES

#include <stdbool.h>
#include <stddef.h>

typedef struct _doctor doctor_t;

doctor_t* crear_doctor( char* nombre, char* especialidad );
hash_destruir_dato_t destruir_doctor( void *ptrdoctor );

#endif
