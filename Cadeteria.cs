using System;

public class Cadeteria
{
    private string nombre;
    private string telefono;
    public List<Cadete> Cadetes { get; private set; }
    public List<Pedido> Pedidos { get; private set; }

    public Cadeteria(IAccesoADatos acceso, string rutaCadeteria, string rutaCadetes)
    {
        var datosCadeteria = acceso.LeerCadeteria(rutaCadeteria);
        nombre = datosCadeteria[0];
        telefono = datosCadeteria[1];

        Cadetes = new List<Cadete>();
        var datosCadetes = acceso.LeerCadetes(rutaCadetes);
        foreach (var fila in datosCadetes)
        {
            Cadetes.Add(new Cadete(fila[0], fila[1], fila[2]));
        }

        Pedidos = new List<Pedido>();
    }

    // 🔍 Información general
    public string ObtenerNombre() => nombre;
    public string ObtenerTelefono() => telefono;

    // 📦 Gestión de pedidos
    public void CrearPedido(int nro, string obs, string nombreCliente, string direccion, string telefono, string referencia, List<Producto> productos)
    {
        var cliente = new Cliente(nombreCliente, direccion, telefono, referencia);
        var pedido = new Pedido(nro, obs, cliente, "Pendiente");
        foreach (var p in productos) pedido.AgregarProducto(p);
        Pedidos.Add(pedido);
    }

    public bool AsignarCadeteAPedido(int idCadete, int nroPedido)
    {
        var cadete = Cadetes.FirstOrDefault(c => c.Id == idCadete);
        var pedido = Pedidos.FirstOrDefault(p => p.Nro == nroPedido);
        if (cadete != null && pedido != null)
        {
            pedido.AsignarCadete(cadete);
            return true;
        }
        return false;
    }

    public bool CambiarEstadoPedido(int nroPedido, string nuevoEstado)
    {
        var pedido = Pedidos.FirstOrDefault(p => p.Nro == nroPedido);
        if (pedido != null)
        {
            pedido.Estado = nuevoEstado;
            return true;
        }
        return false;
    }

    // 📊 Informes
    public List<string> ObtenerInforme()
    {
        var informe = new List<string> { $"Informe de actividad - {nombre}" };
        foreach (var cadete in Cadetes)
        {
            int entregados = Pedidos.Count(p => p.CadeteAsignado?.Id == cadete.Id && p.EstaEntregado());
            int total = Pedidos.Count(p => p.CadeteAsignado?.Id == cadete.Id);
            informe.Add($"Cadete: {cadete.Nombre} - ID: {cadete.Id}");
            informe.Add($"Pedidos asignados: {total}");
            informe.Add($"Pedidos entregados: {entregados}");
            informe.Add($"Jornal: ${entregados * 500}");
        }

        int sinAsignar = Pedidos.Count(p => p.CadeteAsignado == null);
        informe.Add($"Pedidos sin asignar: {sinAsignar}");
        return informe;
    }

    public int CalcularJornal(int idCadete)
    {
        return Pedidos
            .Where(p => p.CadeteAsignado?.Id == idCadete && p.EstaEntregado())
            .Count() * 500;
    }

    // 📋 Listados
    public List<string> ListarPedidos()
    {
        return Pedidos.Select(p =>
            $"Pedido #{p.Nro} - Cliente: {p.Datocliente.Nombre} - Estado: {p.Estado} - Cadete: {(p.CadeteAsignado != null ? p.CadeteAsignado.Nombre : "Sin asignar")}"
        ).ToList();
    }

    public List<string> ListarCadetes()
    {
        return Cadetes.Select(c =>
            $"ID: {c.Id} - {c.Nombre} - Tel: {c.Telefono}"
        ).ToList();
    }

    // 🔎 Acceso directo
    public Pedido ObtenerPedidoPorNumero(int nro)
    {
        return Pedidos.FirstOrDefault(p => p.Nro == nro);
    }

    public Cadete ObtenerCadetePorId(int id)
    {
        return Cadetes.FirstOrDefault(c => c.Id == id);
    }

    public List<Pedido> ObtenerPedidosAsignadosACadete(int idCadete)
    {
        return Pedidos.Where(p => p.CadeteAsignado?.Id == idCadete).ToList();
    }

    public List<Pedido> ObtenerPedidosSinAsignar()
    {
        return Pedidos.Where(p => p.CadeteAsignado == null).ToList();
    }
}