//using System.Text.Json;
using Newtonsoft.Json;

public static class Parser{   

    public static string convierteajson(Mensaje m){
	return JsonConvert.SerializeObject(m);
    }
    
    public static Mensaje convierteamensaje(string s){
	return JsonConvert.DeserializeObject<Mensaje>(s);
    }
}
