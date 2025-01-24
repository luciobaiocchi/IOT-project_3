import connections.http.DataService;
import io.vertx.core.Vertx;

import model.TempManager;
import model.Logic;


public class Main {
    public static void main(String[] args)
    {   
        Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080);
		vertx.deployVerticle(service);
        
        TempManager tManager = new TempManager(200);
        Logic logic = new Logic(tManager);
        logic.run();
    
    }
}
