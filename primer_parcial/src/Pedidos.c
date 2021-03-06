
#include "Pedidos.h"

int InicializarListaDePedidos(ePedidos pedidos[], int cantidad)
{
	int retorno=-1;
	if(pedidos != NULL && cantidad > 0)
	{
		for(int i=0; i<cantidad; i++)
		{
			pedidos[i].isEmpty = LIBRE;
			pedidos[i].tiposResiduos.pAltaDensidad = 0;
			pedidos[i].tiposResiduos.pBajaDensidad = 0;
			pedidos[i].tiposResiduos.polipropileno = 0;
			retorno=1;
		}
	}
	return retorno;
}

int BuscarLugarLibrePedidos(ePedidos pedidos[], int cantidad)
{
	int index;
	int i;
	index = -1;
	if(pedidos != NULL && cantidad > 0)
	{
		for(i=0; i< cantidad; i++)
		{
			if(pedidos[i].isEmpty == LIBRE)
			{
				index=i;
				break;
			}
		}
	}
	return index;
}

int BuscarPedidosPorId(ePedidos pedidos[], int cantidad, int id)
{
	int index = -1;
	int i;
	if(pedidos != NULL && cantidad>0)
	{
		for(i=0; i< cantidad; i++)
		{
			if(pedidos[i].isEmpty == OCUPADO && pedidos[i].idPedido == id) //bucle do while para reintentar?
			{
				index=i;
				break;
			}
		}
	}
	return index;
}

int AltaPedidoDeRecoleccion(eClientes clientes[], int tam_clientes, ePedidos pedidos[], int tam_pedidos, int* idPedidos, eLocalidad localidades[], int tam_localidades)
{
	int retorno=-1;
	int auxIdCliente;
	int indexClienteEncontrado;
	int indexPedidoLugarLibre;
	if(clientes != NULL && pedidos != NULL && tam_clientes > 0 && tam_pedidos > 0)
	{
		MostrarListaClientes(clientes, tam_clientes, localidades, tam_localidades);
		printf("\n");
		if(ObtenerEntero(&auxIdCliente, "\nIngrese el Id de un cliente: ",
				"\nError. Ingrese un numero para el id: ", 1, tam_clientes,1) == 0)
		{
			indexClienteEncontrado= BuscarClientePorId(clientes, tam_clientes, auxIdCliente);
			if(indexClienteEncontrado != -1)
			{
				indexPedidoLugarLibre = BuscarLugarLibrePedidos(pedidos, tam_pedidos);
				if(indexPedidoLugarLibre != -1) //el pedido puede ser otra funcion
				{
					if(ObtenerDecimal(&pedidos[indexPedidoLugarLibre].cantidadKilos, "\nIngrese la cantidad de kilos de residuos: ",
											"\nError. Ingrese un numero valido: ", 1, 99999,1)==0)
					{
						pedidos[indexPedidoLugarLibre].idCliente = auxIdCliente;
						pedidos[indexPedidoLugarLibre].estado = PENDIENTE;
						*idPedidos = *idPedidos+1;
						pedidos[indexPedidoLugarLibre].idPedido = *idPedidos;
						pedidos[indexPedidoLugarLibre].isEmpty = OCUPADO;
						printf("\nEl pedido fue realizado con exito.\n");
						retorno=1;
					}
				}
			}
			else
			{
				printf("\nNo hay un cliente con el id ingresado.\n");
			}
		}
	}
	return retorno;
}

int MostrarInfoUnPedido(ePedidos pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno = -1;
	int i;
	if(clientes != NULL && tam_clientes > 0)
	{
		for(i=0; i<tam_clientes; i++)
		{
			if(clientes[i].isEmpty==OCUPADO && clientes[i].idCliente == pedidos.idCliente)
			{
				printf("\n%5d %10.2f %10d %20s", pedidos.idPedido, pedidos.cantidadKilos, pedidos.estado, clientes[i].nombreEmpresa);
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

int MostrarListaDePedidos(ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno =-1;
	int i;
	if(pedidos != NULL && tam_pedidos > 0)
	{
		for(i=0; i<tam_pedidos; i++)
		{
			if(pedidos[i].isEmpty == OCUPADO)
			{
				MostrarInfoUnPedido(pedidos[i], clientes, tam_clientes);
				retorno=0;
			}
		}
	}
	return retorno;
}

int ProcesarResiduos(ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno = -1;
	int auxIdPedidos;
	int indexIdPedidoEncontrado;
	if(pedidos != NULL && tam_pedidos > 0 && clientes != NULL && tam_clientes > 0)
	{
		if(MostrarListaDePedidosPendientes(pedidos, tam_pedidos, clientes, tam_clientes)==0)
		{
			printf("\n");
			if(ObtenerEntero(&auxIdPedidos, "\nIngrese el id del pedido que fue procesado: ",
					"\nError. Ingrese un numero valido", 1, tam_pedidos, 1)==0)
			{
				indexIdPedidoEncontrado = BuscarPedidosPorId(pedidos, tam_pedidos, auxIdPedidos);
				if(indexIdPedidoEncontrado != -1 )
				{
					PedirIngresoDeTiposDeResiduosReciclados (pedidos, indexIdPedidoEncontrado);
					if(VerificarIngresoDeTiposDeResiduos(pedidos, indexIdPedidoEncontrado)==0)
					{
						pedidos[indexIdPedidoEncontrado].estado = COMPLETADO;
						printf("\nEl ingreso de la cantidad de plastico reciclado fue realizado con exito\n");
						retorno=0;
					}
					else
					{
						pedidos[indexIdPedidoEncontrado].tiposResiduos.pAltaDensidad = 0;
						pedidos[indexIdPedidoEncontrado].tiposResiduos.pBajaDensidad = 0;
						pedidos[indexIdPedidoEncontrado].tiposResiduos.polipropileno = 0;
					}
				}
				else
				{
					printf("\nNo hay pedidos con el Id ingresado\n");
				}
			}
		}
		else
		{
			printf("\nNo hay pedidos para procesar\n");
		}
	}
	return retorno;
}

void PedirIngresoDeTiposDeResiduosReciclados (ePedidos pedidos[], int index) // mas generico?
{
	if(pedidos != NULL)
	{
		ObtenerDecimal(&pedidos[index].tiposResiduos.pAltaDensidad,
								"\nIngrese cantidad de kilos de HDPE (alta densidad): ", "\nError. Ingrese un numero valido: ", 1, 99999.99,3);
		ObtenerDecimal(&pedidos[index].tiposResiduos.pBajaDensidad,
								"\nIngrese cantidad de kilos de LDPE (baja densidad): ", "\nError. Ingrese un numero valido: ", 1, 99999.99,3);
		ObtenerDecimal(&pedidos[index].tiposResiduos.polipropileno,
								"\nIngrese cantidad de kilos de Polipropileno: ", "\nError. Ingrese un numero valido: ", 1, 99999.99,3);
	}
}

int VerificarIngresoDeTiposDeResiduos(ePedidos pedidos[], int index)
{
	int retorno=0;
	float sumaDeKilos;
	if(pedidos != NULL)
	{
		sumaDeKilos= pedidos[index].tiposResiduos.pAltaDensidad +
				pedidos[index].tiposResiduos.pBajaDensidad +
				pedidos[index].tiposResiduos.polipropileno;
		if(sumaDeKilos > pedidos[index].cantidadKilos)
		{
			printf("\nNo puede haber mas kilos de plasticos reciclados de la cantidad total que se ingreso\n");
			retorno=-1;
		}
	}

	return retorno;
}

int MostrarListaDePedidosPendientes(ePedidos pedidos[], int tam_pedidos, eClientes clientes[], int tam_clientes)
{
	int retorno =-1;
	int i;
	if(pedidos != NULL && tam_pedidos > 0)
	{
		for(i=0; i<tam_pedidos; i++)
		{
			if(pedidos[i].isEmpty == OCUPADO && pedidos[i].estado == PENDIENTE)
			{
				MostrarInfoUnPedido(pedidos[i], clientes, tam_clientes);
				retorno=0;
			}
		}
	}
	return retorno;
}





