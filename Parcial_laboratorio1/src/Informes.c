
#include "Informes.h"

int ListadoDeClientesContandoSusPedidosPendientes(eClientes clientes[], int tam_clientes, ePedidos pedidos[], int tam_pedidos, eLocalidad localidades[], int tam_localidades)
{
	int retorno = -1;
	eAuxiliarContador pedidosPendientes[tam_clientes];
	if(pedidos != NULL && clientes != NULL && tam_pedidos > 0 && tam_clientes > 0)
	{
		if(InicializarAuxiliarContador(clientes, tam_clientes, pedidosPendientes) == 0)
		{
			if(ContadorDePedidosPendientePorCliente(pedidos, tam_pedidos, pedidosPendientes, tam_clientes) == 0)
			{
				printf("\nID CLIENTE \tNOMBRE DE LA EMPRESA    \t\tCUIT   \t\t\tDIRECCION \t\t       LOCALIDAD   \tPEDIDOS PENDIENTES\n");
				MostrarListaDeClientesConSusPedidosPendientes(clientes, tam_clientes, pedidosPendientes,localidades, tam_localidades);
				retorno=0;
			}
			else
			{
				printf("\nCONTEO MALO");
			}
		}
	}

	return retorno;
}

int ContadorDePedidosPendientePorCliente(ePedidos pedidos[], int tam_pedidos, eAuxiliarContador pedidosPendientes[], int tam_pendientes)
{
	int retorno=-1;
	int i;
	int j;
	if(pedidos != NULL && tam_pedidos > 0 && tam_pendientes > 0 && pedidosPendientes != NULL)
	{
		for(j=0; j<tam_pendientes; j++)
		{
			for(i=0; i<tam_pedidos; i++)
			{
				if(pedidosPendientes[j].isEmpty == OCUPADO && pedidosPendientes[j].id == pedidos[i].idCliente && pedidos[i].estado == PENDIENTE && pedidos[i].isEmpty == OCUPADO)
				{
					pedidosPendientes[j].contador++;
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

int InicializarAuxiliarContador(eClientes clientes[], int tam_clientes, eAuxiliarContador auxiliar[])
{
	int retorno = -1;
	int i;
	if(clientes != NULL && auxiliar != NULL && tam_clientes > 0)
	{
		for(i=0; i<tam_clientes; i++)
		{
			auxiliar[i].id = clientes[i].idCliente;
			auxiliar[i].contador = 0;
			auxiliar[i].acumulador = 0;
			auxiliar[i].isEmpty = clientes[i].isEmpty;
			retorno = 0;
		}
	}
	return retorno;
}


int MostrarListaDeClientesConSusPedidosPendientes(eClientes clientes[], int tam_clientes, eAuxiliarContador pedidosPendiente[], eLocalidad localidades[], int tam_localidades)
{
	int retorno=-1;
	int i;
	int j;
	if(clientes != NULL && tam_clientes > 0  && pedidosPendiente != NULL)
	{
		for(i=0; i<tam_clientes; i++)
		{
			if(clientes[i].isEmpty == OCUPADO)
			{
				for(j=0; i < tam_localidades; j++)
				{
					if(localidades[j].isEmpty == OCUPADO && clientes[i].idLocalidad == localidades[j].idLocalidad)
					{
						MostrarClienteConSusPedidosPendientes(clientes[i], tam_clientes, pedidosPendiente, localidades[j]);
						retorno = 0;
					}
				}
			}
		}
	}

	return retorno;
}


void MostrarClienteConSusPedidosPendientes(eClientes cliente, int tam_clientes, eAuxiliarContador pedidosPendientes[], eLocalidad localidades)
{
	int i;
	if(pedidosPendientes != NULL && tam_clientes > 0)
	{
		for(i=0; i < tam_clientes; i++)
		{
				if(pedidosPendientes[i].id == cliente.idCliente)
				{
					printf("\n%5d \t\t%20s \t%20s \t%25s %5d \t%d \t\t%d", cliente.idCliente, cliente.nombreEmpresa, cliente.cuit,
							cliente.direccion.calle, cliente.direccion.numero, cliente.idLocalidad, pedidosPendientes[i].contador);
				}
		}
	}
}

/*
 * 7) Imprimir Pedidos pendientes: Se imprimir� una lista de los pedidos que se encuentren en estado �Pendiente�
 * con la informaci�n: Cuit del cliente, direcci�n del cliente, cantidad de kilos a recolectar.
 *
 * */

int MostrarListaDePedidosEnEstadoPendiente(ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno=-1;
	int i;
	if(pedidos != NULL && clientes != NULL && tam_pedidos>0 && tam_clientes>0)
	{
		printf("\nID PEDIDO PENDIENTE \t\tCUIT EMPRESA \t\t\tDIRECCION \t\t TOTAL KG. DE RESIDUOS\n");
		for(i=0;i<tam_pedidos;i++)
		{
			if(pedidos[i].isEmpty == OCUPADO && pedidos[i].estado == PENDIENTE)
			{
				PedidoEnEstadoPerdienteConSuCliente(pedidos[i], tam_clientes, clientes);
				retorno=0;
			}
		}
		printf("\n");
	}
	return retorno;
}

void PedidoEnEstadoPerdienteConSuCliente(ePedidos pedidos, int tam_clientes, eClientes clientes[])
{
	int j;
	if(clientes != NULL && tam_clientes > 0)
	{
		for(j=0; j < tam_clientes; j++)
		{
			if(clientes[j].isEmpty == OCUPADO && clientes[j].idCliente == pedidos.idCliente)
			{
				printf("\n\t%d \t\t%20s \t%25s %5d \t%15.2f", pedidos.idPedido, clientes[j].cuit,
						clientes[j].direccion.calle, clientes[j].direccion.numero, pedidos.cantidadKilos);
			}
		}
	}
}

/*
 * 8) Imprimir Pedidos procesados: Se imprimir� una lista de los pedidos que se encuentren en estado �Completado�
 * con la informaci�n: Cuit del cliente, direcci�n del cliente, cantidad de kilos reciclados de cada tipo de pl�stico.
 *
 * */

int ImprimirPedidosProcesadosEnEstadoCompletado(ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno=-1;
	int i;
	if(pedidos != NULL && clientes != NULL && tam_pedidos>0 && tam_clientes>0)
	{
		printf("\nID PEDIDO COMPLETADO \t\tCUIT EMPRESA \t\t\tDIRECCION \t\t KG. HDPE \tKG. HDLE \t KG. PP\n");
		for(i=0;i<tam_pedidos;i++)
		{
			if(pedidos[i].isEmpty == OCUPADO && pedidos[i].estado == COMPLETADO)
			{
				PedidoEnEstadoCompletadoConInfoDeSuCliente(pedidos[i], tam_clientes, clientes);
				retorno=0;
			}
		}
		printf("\n");
	}
	return retorno;
}

void PedidoEnEstadoCompletadoConInfoDeSuCliente(ePedidos pedidos, int tam_clientes, eClientes clientes[])
{
	int j;
	if(clientes != NULL && tam_clientes > 0)
	{
		for(j=0; j < tam_clientes; j++)
		{
			if(clientes[j].isEmpty == OCUPADO && clientes[j].idCliente == pedidos.idCliente)
			{
				printf("\n\t %d \t\t%20s \t%25s %5d %15.2f %15.2f %15.2f", pedidos.idPedido, clientes[j].cuit,
						clientes[j].direccion.calle, clientes[j].direccion.numero, pedidos.tiposResiduos.pAltaDensidad,
						pedidos.tiposResiduos.pBajaDensidad, pedidos.tiposResiduos.polipropileno);
			}
		}
	}
}

//9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para dicha localidad.

int CantidadPedidosPendientesPorLocalidad (ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno=-1;
	char localidadIngresada[51];
	int i;
	int j;
	int contador=0;

	if(pedidos != NULL && tam_pedidos > 0 && clientes != NULL && tam_clientes > 0)
	{
		if(ObtenerPalabras(localidadIngresada, "\nIngrese una localidad que desee buscar: ",
				"\nError. Ingrese la localidad nuevamente: ",1))
		{
			FormatearCadena(localidadIngresada);
			if(VerificarIngresoDeLocalidad(clientes, tam_clientes, localidadIngresada) == 0)
			{
				for(i=0; i< tam_clientes;i++)
				{
					for(j=0; j < tam_pedidos; j++)
					{
						/*if(pedidos[j].isEmpty == OCUPADO &&  pedidos[j].idCliente == clientes[i].idCliente &&
								pedidos[j].estado == PENDIENTE && stricmp(clientes[i].localidad, localidadIngresada)==0)
						{
							contador++;
							retorno=0;
						}*/
					}
				}
				printf("\nLa Localidad: %s tiene %d pedidos pendientes\n", localidadIngresada, contador);
			}
			else
			{
				printf("\nNo hay pedidos con la localidad que ingreso\n");
			}
		}
	}
	return retorno;
}

int ContarEnListaDeClientesLasLocalidadesConPedidosPendiente(ePedidos pedidos[], eClientes clientes, int tam_pedidos, char localidadIngresada[])
{
	int contador=0;
	int j;
	if(pedidos != NULL && tam_pedidos)
	{
		for(j=0; j < tam_pedidos; j++)
		{
			if(pedidos[j].isEmpty == OCUPADO &&  pedidos[j].idCliente == clientes.idCliente && pedidos[j].estado == PENDIENTE)
			{
				contador++;
			}
		}
	}
	return contador;
}

int VerificarIngresoDeLocalidad(eClientes clientes[], int tam_clientes, char localidadIngresada[])
{
	int retorno=-1;
	int i;
	if(clientes != NULL && tam_clientes > 0)
	{
		for(i=0; i < tam_clientes; i++)
		{
			//if(stricmp(clientes[i].localidad, localidadIngresada)==0)
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

//10) Cantidad de kilos de polipropileno reciclado promedio por cliente. (kilos totales / cantidad de clientes)

int PromedioRecicladoDePolipropilenoPorCliente(eClientes clientes[], int tam_clientes, ePedidos pedidos[], int tam_pedidos)
{
	int retorno = -1;
	eAuxiliarContador acumulador[tam_clientes];
	if(pedidos != NULL && clientes != NULL && tam_pedidos > 0 && tam_clientes > 0)
	{
		if(InicializarAuxiliarContador(clientes, tam_clientes, acumulador) == 0)
		{
			if(AcumuladorDePolipropilenoConAuxiliar(pedidos, tam_pedidos, acumulador, tam_clientes) == 0)
			{
				if(CalculoPromedioDePolipropileno(acumulador, tam_clientes)==0)
				{
					MostrarElPromedioDePolipropilenoPorCliente(acumulador, tam_clientes, clientes);
					retorno=0;
				}
			}
		}
	}

	return retorno;
}

void MostrarElPromedioDePolipropilenoPorCliente(eAuxiliarContador auxiliar[], int tam_clientes, eClientes clientes[])
{
	int i;
	if(tam_clientes > 0 && auxiliar != NULL)
	{
		printf("\nID \t\tCLIENTE \t\tKG RECICLADOS PP");
		for(i=0; i< tam_clientes; i++)
		{
			if(auxiliar[i].isEmpty==OCUPADO)
			{
					printf("\n%2d %20s %25.2f ", auxiliar[i].id, clientes[i].nombreEmpresa, auxiliar[i].promedio);
			}
		}
	}
}

int CalculoPromedioDePolipropileno(eAuxiliarContador auxiliar[], int tam_auxiliar)
{
	int retorno = -1;
	int i;
	if(auxiliar != NULL && tam_auxiliar > 0)
	{
		for(i=0; i<tam_auxiliar; i++)
		{
			if(auxiliar[i].isEmpty == OCUPADO && auxiliar[i].acumulador > 0 && auxiliar[i].contador > 0)
			{
				auxiliar[i].promedio = auxiliar[i].acumulador/auxiliar[i].contador;
				retorno=0;
			}
		}
	}
	return retorno;
}

int AcumuladorDePolipropilenoConAuxiliar(ePedidos pedidos[], int tam_pedidos, eAuxiliarContador auxiliar[], int tam_auxiliar)
{
	int retorno=-1;
	int i;
	int j;
	if(pedidos != NULL && tam_pedidos > 0 && tam_auxiliar > 0 && auxiliar != NULL)
	{
		for(j=0; j<tam_pedidos; j++)
		{
			if(pedidos[j].isEmpty == OCUPADO)
			{
				for(i=0; i<tam_auxiliar; i++)
				{
					if(auxiliar[i].isEmpty == OCUPADO && auxiliar[i].id == pedidos[j].idCliente &&
							pedidos[j].estado == COMPLETADO)
					{
						auxiliar[i].acumulador += pedidos[j].tiposResiduos.polipropileno;
						auxiliar[i].contador++;
						retorno = 0;
						break;
					}
				}
			}
		}
	}
	return retorno;
}




