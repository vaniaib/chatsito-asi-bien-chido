using System;
using System.Threading.Tasks;

public class Vista{
    private Aplicacion cliente;
    private bool ejecuta;
    public Vista(Aplicacion cliente){
        this.cliente = cliente;
        cliente.MensajeRecibido += MostrarMensaje;
        cliente.Error += MostrarError;
	ejecuta = true;
    }

    public async Task Iniciar(){
        Console.WriteLine("||| CHAT |||");
        Console.WriteLine();
        while (ejecuta){
            Console.Write("|> ");
            string entrada = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(entrada))
                continue;
	    //comandoparser.parsear
            Mensaje mensaje = Escribe.Traduce(entrada);
            if (mensaje == null)
                continue;
            await cliente.Enviar(mensaje);
            if (mensaje.type == "DISCONNECT")
                break;
        }
    }

private void MostrarMensaje(Mensaje mensaje){
        switch (mensaje.type)
        {
            case "NEW_USER":

                Console.WriteLine($"Nuevo usuario: {mensaje.username}");
                break;

            case "NEW_STATUS":

                Console.WriteLine($"{mensaje.username} cambió a " + $"{mensaje.status}");		
                break;

            case "USER_LIST":

                Console.WriteLine("Lista de usuarios:");
                if (mensaje.users != null){
                    foreach (var usuario in mensaje.users){
                        Console.WriteLine($"{usuario.Key} - " + $"{usuario.Value}");
                    }
                }
                break;

            case "TEXT_FROM":

                Console.WriteLine($"{mensaje.username}: " +  $"{mensaje.text}");
                break;

            case "PUBLIC_TEXT_FROM":

                Console.WriteLine($"[PÚBLICO] " + $"{mensaje.username}: " + $"{mensaje.text}");
                break;

            case "INVITATION":
                Console.WriteLine($"{mensaje.username} te invitó a " + $"{mensaje.roomname}");
                break;

            case "JOINED_ROOM":
                Console.WriteLine($"{mensaje.username} entró a la sala" + $"{mensaje.roomname}");
                break;

            case "ROOM_USER_LIST":
                Console.WriteLine($"Usuarios en {mensaje.roomname}:");
                if (mensaje.users != null){
                    foreach (var usuario in mensaje.users){
                        Console.WriteLine($"{usuario.Key} - " +  $"{usuario.Value}");
                    }
                }

                break;

            case "ROOM_TEXT_FROM":
                Console.WriteLine($"[{mensaje.roomname}] " + $"{mensaje.username}: " + $"{mensaje.text}");
                break;

            case "LEFT_ROOM":
                Console.WriteLine($"{mensaje.username} salió de " + $"{mensaje.roomname}");
                break;

            case "DISCONNECTED":
                Console.WriteLine($"{mensaje.username} se desconectó.");
                break;

            case "RESPONSE":
                Console.WriteLine($"Respuesta: " + $"{mensaje.operation} - " +  $"{mensaje.result}");
                if (!string.IsNullOrEmpty(mensaje.extra)){
                    Console.WriteLine($"Información: {mensaje.extra}");
                }
                break;
        }
    }

    private void MostrarError(string error)
    {
        Console.WriteLine();
        Console.WriteLine("ERROR: " + error);
    }
}
