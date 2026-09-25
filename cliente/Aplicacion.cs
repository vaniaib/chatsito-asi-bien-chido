    using System;
//    using System.Collections.Generic;
    // using System.Linq;
    // using System.Text;
    using System.Threading.Tasks;
//    using System.Net;
    using System.Net.Sockets;
    using System.IO;
// namespace CteP;


public class Aplicacion{

    //private Mensaje m;    
private int puerto;
private string ip;
private bool continuaEjecucion;
private TcpClient cliente;
private StreamReader lector;
private StreamWriter escritor;

public event Action<Mensaje> MensajeRecibido;
public event Action<string> Error;

public Aplicacion(int p, string s){
    puerto = p;
    ip = s;
    continuaEjecucion = true;
				  }

public async Task Conectar(){
    try{
	cliente = new TcpClient();
	await cliente.ConnectAsync(ip, puerto);
	NetworkStream stream = cliente.GetStream();
	lector = new StreamReader(stream);
	escritor = new StreamWriter(stream){
	    AutoFlush = true
	};
	_ = RecibirMensajes();
       }
       catch (Exception e)
       {
	   Error?.Invoke(e.Message);
       }
			    }

public async Task Enviar(Mensaje mensaje){
    try{
	string json = Parser.convierteajson(mensaje);
	await escritor.WriteLineAsync(json);
    }
    catch (Exception e){
	Error?.Invoke(e.Message);
    }
}

private async Task RecibirMensajes(){
    try{
	while (continuaEjecucion){
	    string json = await lector.ReadLineAsync();
	    if (json == null)
		break;
	    //  Console.WriteLine("JSON RECIBIDO: [" + json + "]");
	    Mensaje mensaje = Parser.convierteamensaje(json);
	    MensajeRecibido?.Invoke(mensaje);
	}
    }
    catch (Exception e)
    {
	Error?.Invoke(e.Message);
    }
}

public void Desconectar(){
    escritor?.Close();
    lector?.Close();
    cliente?.Close();
}
					 
		       }

// void ejecuta(){
// 	while (continuaEjecucion){
// 	    try{
// 		TcpClient tcpcint = new TcpClient();
// 		Console.WriteLine("Conectando");
// 		tcpcint.Connect(ip, puerto);
// 		Console.WriteLine("Conectando con el server");
// 		Console.WriteLine("Escirbe");
// 		String str = Console.ReadLine();
// 		if (str == "QUIT"){
// 		    continuaEjecucion = false;
// 		    break;
// 		}
// 		Stream stm = tcpcint.GetStream();
// 		ASCIIEncoding asen = new ASCIIEncoding();
// 		byte[] ba = asen.GetBytes(str);
// 		Console.WriteLine("Transmitiendo");
// 		stm.write(ba, 0, ba.Length);
// 		byte[] bb = new byte[100];
// 		int k = stm.Read(bb, 0, 100);
// 		string acuse = "";
// 		for(int i = 0; i < k; i++)
// 		    acuse += Convert.ToChar(bb[i]);
// 		Console.WriteLine("Servidor" + acuse);
// 		tcpcint.Close();		
	    
// 	    }catch(Exception e){
// 		Console.writeLine("Error con :" + e.StackTrace);
// 	    }
	
	
	
// 		}
// }

// 		       }
