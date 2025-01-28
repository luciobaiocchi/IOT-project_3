import connections.http.DataService;
import io.vertx.core.Vertx;
import model.TempManager;
import model.Logic;

public class Main {
    public static void main(String[] args) {
        new Logic().run();
    }
}