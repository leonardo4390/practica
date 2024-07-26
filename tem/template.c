#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

/* estas estructuras estan en la libreria funciones.h
typedef struct TProducto
{
    char * Descripcion;
    char * Categoria;
    int Precio;
    int Stock;

}TProducto;

typedef struct Tnodo
{
    TProducto dato;
    struct Tnodo *siguiente;
}Tnodo;
*/
// DECLARE SUS FUNCIONES AQUI
Tnodo *crearNodo(TProducto producto);
Tnodo *crearLista();
void insertarLista(Tnodo **lista, TProducto producto);
Tnodo *filtrarPrecio(Tnodo *lista, float precio);
int productoSinStock(Tnodo *lista);
Tnodo *moverProductoPorStock(Tnodo **lista, int stock);
void liberarLista(Tnodo **lista);

int main()
{
    TProducto * ProductosDeProveedor1  = ProveedorDeLacteosPanaderiaLiquidos();
    MostrarProductosDeArreglo(ProductosDeProveedor1, 17, "Proveedor 1");

     
    // PUNTO 1. Insertar todos los productos en una única lista
    //Tnodo *listaDeProductos=NULL;
    // llame sus funciones aquí
    Tnodo *listaDeProductos=crearLista();
    for (int i = 0; i < 17; i++)
    {
        insertarLista(&listaDeProductos,ProductosDeProveedor1[i]);
    }
    
    MostrarLista(listaDeProductos, "Todos los productos");
    // FIN PUNTO 1

    // PUNTO 2. Ingrese un precio y filtre los productos que tengan un precio mayor al ingresado
    //Tnodo *productosFiltradosPorPrecio=NULL;
    float precio;
    printf("Ingrese precio: \n");
    scanf("%f", &precio); 
    printf("Precio ingresado: %f",precio);
    
    //llame sus funciones aqui
    Tnodo *productosFiltradosPorPrecio=filtrarPrecio(listaDeProductos,precio);
    MostrarLista(productosFiltradosPorPrecio, "Productos con precio filtrado"); 
    // FIN PUNTO 2

    // PUNTO 3. Contar productos sin stock y mostrar la cantidad
    int cantidadSinStock; 
    // llame sus funciones aquí
    cantidadSinStock = productoSinStock(listaDeProductos);
    MostrarCantidadSinStock(cantidadSinStock); 
    //FIN PUNTO 3

    // PUNTO 4. Desenlazar los productos sin stock y mostrarlos
    //Tnodo *productosFiltradoPorStock=NULL;
    int stock;
    printf("Ingrese stock: \n");
    scanf("%d", &stock); 
    printf("Stock ingresado: %d",stock);
    // llame sus funciones aquí
    Tnodo *productosFiltradoPorStock=moverProductoPorStock(&listaDeProductos,stock);
    MostrarLista(productosFiltradoPorStock, "Productos con stock mayor al ingresado");
    MostrarLista(listaDeProductos, "Productos con stock menor a al ingresado"); 
    // FIN PUNTO 4
    
    //PUNTO 5. Liberar todas las listas
    // llame sus funciones aquí
    liberarLista(&listaDeProductos);
    liberarLista(&productosFiltradosPorPrecio);
    liberarLista(&productosFiltradoPorStock);

    MostrarLista(listaDeProductos, "Lista vacia de listaDeProductos "); 
    MostrarLista(productosFiltradosPorPrecio, "Lista vacia de productosFiltradosPorPrecio");
    MostrarLista(productosFiltradoPorStock, "Lista vacia de productosSinStock");
    // FIN PUNTO 5
}

//IMPLEMENTE SUS FUNCIONES AQUI
Tnodo *crearNodo(TProducto producto)
{
    Tnodo *nuevoNodo = (Tnodo *)malloc(sizeof(Tnodo));
    nuevoNodo->dato = producto;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

Tnodo *crearLista()
{
    return NULL;
}

void insertarLista(Tnodo **lista, TProducto producto)
{
    Tnodo *nuevo = crearNodo(producto);
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

Tnodo *filtrarPrecio(Tnodo *lista, float precio)
{
    Tnodo *listaPrecioFiltrado = NULL;
    Tnodo *temp = lista;

    while (temp != NULL)
    {
        if (temp->dato.Precio>precio)
        {
            insertarLista(&listaPrecioFiltrado,temp->dato);
        }
        temp = temp->siguiente;
        
    }

    return listaPrecioFiltrado;
    
}
int productoSinStock(Tnodo *lista)
{
    int cantidad = 0;
    Tnodo *temp = lista;
    while (temp != NULL)
    {
        if (temp->dato.Stock == 0)
        {
            cantidad ++;
        }
        temp = temp->siguiente;
    }
    return cantidad;
    
}
Tnodo *moverProductoPorStock(Tnodo **lista, int stock)
{
    Tnodo *listaPorStock = NULL;
    Tnodo *prev = NULL;
    Tnodo *temp = *lista;

    while (temp != NULL)
    {
        if (temp->dato.Stock > stock)
        {
            if (prev == NULL)
            {
                *lista = temp->siguiente;
            }else{
                prev->siguiente = temp->siguiente;
            }
            insertarLista(&listaPorStock,temp->dato);
            temp = (prev == NULL) ? *lista : prev->siguiente;
            
        }
        else{
            prev = temp;
            temp = temp->siguiente;
        }
        
    }
    return listaPorStock;
    
}

void liberarLista(Tnodo **lista)
{
    Tnodo *temp;

    while (*lista != NULL)
    {
        temp = *lista;
        *lista = temp->siguiente;
        free(temp);
    }
    
}