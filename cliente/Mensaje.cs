using System.Collections.Generic;

public class Mensaje{
    
    public string type { get; set; }
    public string username { get; set; }
    //    public string usernames { get; set; }
    //
    public string status { get; set; }
    public string text { get; set; }
    public string roomname { get; set; }
    public string operation { get; set; }
    public string result { get; set; }
    public string extra { get; set; }
    public List<string> invitadosSala { get; set; }
    public List<string> usernames { get; set; }
    public Dictionary<string, string> users { get; set; }
}
