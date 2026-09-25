using System;
using System.Threading.Tasks;


public class Cliente{
    static void Main(string[] args){
	try{
	    string ip = Console.ReadLine();
	    int puerto = int.Parse(Console.ReadLine());	
	    Aplicacion aplicacion = new Aplicacion(puerto, ip);
	    aplicacion.Conectar().Wait();
	    Vista v =
            new Vista(aplicacion);
	    v.Iniciar().Wait();
	    aplicacion.Desconectar();
	}catch(Exception e){
	    Console.Write("alo salio mal"+ e);
	}
    }   
}
