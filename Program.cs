using System;

class Program
{
    static void Main(string[] args)
    {
        var acceso = new AccesoADatosJSON(); // o CSV
        var cadeteria = new Cadeteria(acceso, "cadeteria.json", "cadetes.json");

        // Simulación de alta de pedido
        var productos = new List<Producto> { new Producto(Producto.Comida.Pizza), new Producto(Producto.Comida.Empanada) };
        cadeteria.CrearPedido(1, "Sin cebolla", "Carlos", "Av. Roca 123", "3814567890", "Frente a la plaza", productos);

        // Asignación
        cadeteria.AsignarCadeteAPedido(1, 1);
        cadeteria.CambiarEstadoPedido(1, "Entregado");

        // Mostrar informe
        var informe = cadeteria.ObtenerInforme();
        foreach (var linea in informe)
            Console.WriteLine(linea);
    }
}
