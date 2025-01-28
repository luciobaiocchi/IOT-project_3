import connections.http.DataService;
import io.vertx.core.Vertx;
import model.TempManager;
import model.Logic;

public class Main {
    public static void main(String[] args) {
        Vertx vertx = Vertx.vertx();
        TempManager tManager = new TempManager(200); // Inizializza con 200 valori casuali
        DataService service = new DataService(8080, tManager);
        vertx.deployVerticle(service);

        Logic logic = new Logic(tManager);
        logic.run();
    }
}