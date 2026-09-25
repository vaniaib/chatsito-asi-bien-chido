using System;
using System.Collections.Generic;

public static class Escribe{
    
    public static Mensaje Traduce(string s){
	
        if(string.IsNullOrWhiteSpace(s)){
            return null;
        }
        if(!s.StartsWith("||")){
            Console.WriteLine("Debes iniciar tu mensaje con ||\n" + "Escribe ||HELP para ver los detalles");
            return null;
        }
        string entrada = s.Substring(2).TrimStart('|').Trim();
        string[] parte = entrada.Split(' ',2,StringSplitOptions.RemoveEmptyEntries);
        string operacion = parte[0].ToUpper();
        string argumentos = "";
        if (parte.Length > 1){
            argumentos = parte[1];
        }
        switch (operacion){
	    
            case "IDENTIFY":
                return CrearIdentify(argumentos);

            case "STATUS":
                return CrearStatus(argumentos);

            case "USERS":
                return new Mensaje{
                    type = "USERS"
                };

            case "TEXT":
                return CrearText(argumentos);

            case "PUBLIC_TEXT":
                return CrearPublicText(argumentos);

            case "NEW_ROOM":
                return new Mensaje{
                    type = "NEW_ROOM",
                    roomname = argumentos
                };

            case "INVITE":
                return CrearInvite(argumentos);

            case "JOIN_ROOM":
                return new Mensaje{
                    type = "JOIN_ROOM",
                    roomname = argumentos
                };

            case "ROOM_USERS":
                return new Mensaje{
                    type = "ROOM_USERS",
                    roomname = argumentos
                };

            case "ROOM_TEXT":
                return CrearRoomText(argumentos);

            case "LEAVE_ROOM":
                return new Mensaje{
                    type = "LEAVE_ROOM",
                    roomname = argumentos
                };

            case "DISCONNECT":
                return new Mensaje{
                    type = "DISCONNECT"
                };
	    case "HELP":
		msjAyuda();
		return null;
		
            default:
                Console.WriteLine("Operación desconocida: " + operacion);

                return null;
        }
    }

    private static Mensaje CrearIdentify(string argumentos){
        return new Mensaje{
            type = "IDENTIFY",
            username = argumentos
        };
    }

    private static Mensaje CrearStatus(string argumentos){
        return new Mensaje{
            type = "STATUS",
            status = argumentos.ToUpper()
        };
    }

    private static Mensaje CrearText(string argumentos){
        string[] partes = argumentos.Split(' ',2, StringSplitOptions.RemoveEmptyEntries);
        if (partes.Length < 2){
            Console.WriteLine("Uso: ||TEXT usuario mensaje");
            return null;
        }
        return new Mensaje{
            type = "TEXT",
            username = partes[0],
            text = partes[1]
        };
    }

    private static Mensaje CrearPublicText(string argumentos){
        return new Mensaje{
            type = "PUBLIC_TEXT",
            text = argumentos
        };
    }

    private static Mensaje CrearInvite(string argumentos){
        string[] partes = argumentos.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (partes.Length < 2){
            Console.WriteLine("Uso: ||INVITE sala usuario1 usuario2 ...");
            return null;
        }	
        string sala = partes[0];
        List<string> usuarios = new List<string>();
	//Dictionary<string, string> usuarios = new Dictionary<string, string>();
        for (int i = 1; i < partes.Length; i++){
            usuarios.Add(partes[i]);
        }
        return new Mensaje{
            type = "INVITE",
            roomname = sala,
            usernames = usuarios
        };
    }

    private static Mensaje CrearRoomText(string argumentos){
        string[] partes = argumentos.Split(' ', 2, StringSplitOptions.RemoveEmptyEntries);
        if (partes.Length < 2){
            Console.WriteLine("Uso: ||ROOM_TEXT sala mensaje");
            return null;
        }
        return new Mensaje{
            type = "ROOM_TEXT",
            roomname = partes[0],
            text = partes[1]
        };
    }
    private static string msjAyuda(){
	string s = "Para usar el chat debes:\n"
	    + " ||IDENTIFY username\n"
	    + " para identificarte en el servidor\n"
	    + "||USERS"
	    + "para ver a los usuarios conectados"
	    + "||STATUS nuevo estado"
	    + "para modificar tu estado"
	    + "||TEXT destinatario mensaje"
	    + "||PUBLIC_TEXT Hola a todos"
	    + "||NEW_ROOM Sala1";
	return s;
	    // ||INVITE Sala1 Luis Antonio
	    // ||JOIN_ROOM Sala1
	    // ||ROOM_USERS Sala1
	    // ||ROOM_TEXT Sala1 Hola sala
	    // ||LEAVE_ROOM Sala1
	    // ||DISCONNECT"
	    }
			   }
