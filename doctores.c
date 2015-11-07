#include "doctores.h"
#include "hash.h"

struct _doctor
{
	char *nombre_del_profesional;
	size_t pacientes_atendidos;
	char *especialidad;
};

doctor_t* crear_doctor( char* nombre, char* especialidad )
{
	doctor_t* doc = malloc( sizeof(doc) );
	
	if( !doc )
		return NULL;
		
	doc->nombre_del_profesional = strdup( nombre );
	doc->especialidad = strdup( especialidad );
	doc->pacientes_atendidos = 0;
	
	return doc;
}

hash_destruir_dato_t destruir_doctor( void *ptrdoctor )
{
	doctor_t* doc = ptrdoctor;
	
	free(doc->nombre_del_profesional);
	free(doc->especialidad);
	free(doc);
}
