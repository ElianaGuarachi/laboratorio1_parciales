/*
 * localidad.h
 *
 *  Created on: 15 oct. 2021
 *      Author: Eliana
 */

#ifndef LOCALIDAD_H_
#define LOCALIDAD_H_
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#define LIBRE 0
#define OCUPADO 1

typedef struct
{
	int idLocalidad;
	char nombreLocalidad[51];
	int isEmpty;

}eLocalidad;

int InicializarListaLocalidades(eLocalidad localidades[], int cantidad);

int MostrarListaDeLocalidades(eLocalidad localidades[], int cantidad);

void MostrarInfoUnaLocalidad(eLocalidad localidad);

#endif /* LOCALIDAD_H_ */