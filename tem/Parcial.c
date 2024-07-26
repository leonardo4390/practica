/*
*    AUTHOR: Catedra de lenguajes de Taller 1 
*    DATE: 05/2024
*    LICENCE: Creative Commons 
*/

#include "funciones.h"


// DECLARE SUS FUNCIONES ACA
nodo *crearNodo(Producto productos);
nodo *crearLista();
void insertarLista(nodo **lista, Producto productos);
nodo *moverSucursal(nodo **lista,char *sucursal);
void marcarID(nodo *lista, int id);
void eliminarInactivos(nodo **lista);
nodo *sucursalLimite(nodo **lista);
void pasarADepositoSiExcedeStock(nodo **sucursalTucuman, nodo **deposito, int limiteStock);
void liberarLista(nodo **lista);


int main() 
{    
    Producto * TodosLosProductos  = ProductoElectronicos();
    //nodo * ListadoDeProductos = CrearListaVacia();
    //nodo * SucursalTucuman = CrearListaVacia();
    //nodo * SucursalSalta = CrearListaVacia();
    //nodo * Deposito = CrearListaVacia();
    int cambieEstaVariablePorlaFuncionCorrespondiente = 0;

    MostrarProductosDeArreglo(TodosLosProductos, 40, "Productos de Proveedor 1");
    
    printf("PUNTO 1\n");
    // PUNTO 1. mover del arreglo los productos a la lista correspondiente según la sucursal de destino     
    // Llame a sus funciones aquí
    nodo * ListadoDeProductos = crearLista();
    for (int i = 0; i < 40; i++)
    {
        insertarLista(&ListadoDeProductos,TodosLosProductos[i]);
    }

    nodo * SucursalSalta = moverSucursal(&ListadoDeProductos,"Salta");
    nodo * SucursalTucuman = moverSucursal(&ListadoDeProductos,"Tucuman");
    nodo * Deposito = moverSucursal(&ListadoDeProductos,"Deposito");
    MostrarLista(SucursalSalta, "Productos Salta");
    MostrarLista(SucursalTucuman, "Productos Tucuman");
    MostrarLista(Deposito, "Productos Deposito");
    // FIN PUNTO 1


    printf("PUNTO 2\n");
    // PUNTO 2. marque como inactivo los productos ingresados por el usuario
    for (int i = 0; i < 5; i++) 
    {
        int id;
        do {
            printf("Ingrese el ID del producto a dar de baja: \n");
            scanf(" %d", &id);
        } while (id < 0 || id > 40);
        // Aquí puedes hacer lo que necesites con el ID para cada sucursal
        // Llame a sus funciones aquí
        marcarID(SucursalSalta,id);
        marcarID(SucursalTucuman,id);
        marcarID(Deposito,id);
        

    }
    MostrarLista(SucursalSalta, "Productos Salta");
    MostrarLista(SucursalTucuman, "Productos Tucuman");
    MostrarLista(Deposito, "Productos Deposito");
    // FIN PUNTO 2

    printf("PUNTO 3\n");
    // PUNTO 3. eliminar inactivos
    // Llame a sus funciones aquí
    eliminarInactivos(&SucursalSalta);
    eliminarInactivos(&SucursalTucuman);
    eliminarInactivos(&Deposito);


    MostrarLista(SucursalSalta, "Productos Salta");
    MostrarLista(SucursalTucuman, "Productos Tucuman");
    MostrarLista(Deposito, "Productos Deposito");
    // FIN PUNTO 3

    printf("PUNTO 4\n");
    // PUNTO 4. Pasar a la lista deposito desde Tucumán, cuando el total de stock de la sucursal Tucumán supere los 40 elementos
    // Llame a sus funciones aquí
    Deposito = sucursalLimite(&SucursalTucuman);
    //pasarADepositoSiExcedeStock(&SucursalTucuman, &Deposito, 40);

    MostrarLista(SucursalTucuman, "Productos Tucuman");
    MostrarLista(Deposito, "Productos Deposito");
    // FIN PUNTO 4

    printf("PUNTO 5\n");
    MostrarCantidadProductos(SucursalSalta);
    MostrarCantidadProductos(SucursalTucuman);
    MostrarCantidadProductos(Deposito);
    // PUNTO 5. libere la memoria reservada. 
    // Llame a sus funciones aquí

    liberarLista(&SucursalSalta);
    liberarLista(&SucursalTucuman);
    liberarLista(&Deposito);
    MostrarLista(SucursalSalta, "Productos Salta");
    MostrarLista(SucursalTucuman, "Productos Tucuman");
    MostrarLista(Deposito, "Productos Deposito");
    // FIN PUNTO 5
    
    /*fin del programa*/
    printf("\nFin parcial\n"); 
    return 0;
}

// IMPLEMENTE SUS FUNCIONES ACA
nodo *crearNodo(Producto productos)
{
    nodo *nuevoNodo=(nodo *)malloc(sizeof(nodo));
    nuevoNodo->Producto=productos;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

nodo *crearLista()
{
    return NULL;
}

void insertarLista(nodo **lista, Producto productos)
{
    nodo *nuevo = crearNodo(productos);
    nuevo->Siguiente = *lista;
    *lista = nuevo;
}

nodo *moverSucursal(nodo **lista,char *sucursal)
{
    nodo *listaSucursal = NULL;
    nodo *prev = NULL;
    nodo *temp = *lista;
    while (temp != NULL)
    {
        if (strcmp(temp->Producto.Sucursal,sucursal)==0)
        {
            if (prev == NULL)
            {
                *lista = temp->Siguiente;
            }else{
                prev->Siguiente = temp->Siguiente;
            }
            insertarLista(&listaSucursal,temp->Producto);
            temp = (prev == NULL)? *lista : prev->Siguiente;
            
        }
        else{
            prev = temp;
            temp = temp->Siguiente;
        }
        
    }
    return listaSucursal;
    
}

void marcarID(nodo *lista, int id)
{
    nodo *temp = lista;
    while (temp != NULL)
    {
        if (temp->Producto.Id == id)
        {
            temp->Producto.Activo = 0;
        }

        temp = temp->Siguiente;
        
    }
}

void eliminarInactivos(nodo **lista)
{
    nodo *actual = *lista;
    nodo *anterior = NULL;

    while (actual != NULL) {
        if (actual->Producto.Activo == 0) {
            if (anterior == NULL) { // Si es el primer nodo
                *lista = actual->Siguiente;
                free(actual);
                actual = *lista;
            } else {
                anterior->Siguiente = actual->Siguiente;
                free(actual);
                actual = anterior->Siguiente;
            }
        } else {
            anterior = actual;
            actual = actual->Siguiente;
        }
    }
}

nodo *sucursalLimite(nodo **lista)
{
    nodo *listaDeposito = NULL;
    nodo *prev = NULL;
    nodo *temp = *lista;
    int acumulado = 0;

    while (temp != NULL)
    {
        acumulado +=temp->Producto.Stock;
        if (acumulado > 40)
        {
            if (prev == NULL)
            {
                *lista = temp->Siguiente;
            }else{
                prev->Siguiente = temp->Siguiente;
            }
            
            insertarLista(&listaDeposito,temp->Producto);
            temp = (prev == NULL) ? *lista : prev->Siguiente;
        }
        else{
            prev = temp;
            temp = temp->Siguiente;
        }
        
    }
    return listaDeposito;
    
}
/*void pasarADepositoSiExcedeStock(nodo **sucursalTucuman, nodo **deposito, int limiteStock)
{
    nodo *actual = *sucursalTucuman;
    nodo *anterior = NULL;
    int stockTotal = 0;

    // Calcular el stock total de SucursalTucuman
    while (actual != NULL) {
        stockTotal += actual->Producto.Stock;
        actual = actual->Siguiente;
    }

    // Si el stock total excede el límite, mover productos a Deposito
    if (stockTotal > limiteStock) {
        actual = *sucursalTucuman;
        while (actual != NULL) {
            if (stockTotal > limiteStock) {
                stockTotal -= actual->Producto.Stock;
                if (anterior == NULL) { // Si es el primer nodo
                    *sucursalTucuman = actual->Siguiente;
                    insertarLista(deposito, actual->Producto);
                    nodo *temp = actual;
                    actual = actual->Siguiente;
                    free(temp);
                } else {
                    anterior->Siguiente = actual->Siguiente;
                    insertarLista(deposito, actual->Producto);
                    nodo *temp = actual;
                    actual = actual->Siguiente;
                    free(temp);
                }
            } else {
                anterior = actual;
                actual = actual->Siguiente;
            }
        }
    }
}*/


void liberarLista(nodo **lista)
{
    nodo *temp;

    while (*lista != NULL)
    {
        temp = *lista;
        *lista = temp->Siguiente;
        free(temp);
    }
    
}
