using System;
public interface IAccesoADatos
{
    string[] LeerCadeteria(string ruta);
    List<string[]> LeerCadetes(string ruta);
}