package connections.http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import model.Mode;
import model.TempState;
import model.TempManager;


public class DataService extends AbstractVerticle {

    private int port;
    private TempManager tManager;
	private Mode mState;

    public DataService(final int port, final TempManager tManager, final Mode mState) {
		this.tManager = tManager;
		this.mState = mState;
        this.port = port;
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(BodyHandler.create());
        router.post("/api/data").handler(this::handleAddNewData);
        router.get("/api/data").handler(this::handleGetData);
        vertx
            .createHttpServer()
            .requestHandler(router)
            .listen(port);

        log("Service ready on port: " + port);
    }

    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        JsonObject res = routingContext.getBodyAsJson();
		log("post" + res);
        if (res == null) {
            sendError(400, response);
        } else {
			if (res.containsKey("new_mode")){
				this.mState.changeMode();
			}else if (res.containsKey("stop_alarm" ) && tManager.getTempState() == TempState.ALLARM){
                tManager.resetAllarm();
            }
            response.setStatusCode(200).end();
        }
    }

    private void handleGetData(RoutingContext routingContext) {
        JsonArray arr = new JsonArray();
		JsonObject data = new JsonObject();
		data.put("max", tManager.getMax());
		data.put("min", tManager.getMin());
		data.put("val", tManager.getLast());
		data.put("tst", tManager.getTempState());
		data.put("opn", tManager.getOpening());
		data.put("main_state", mState.getMode());
		arr.add(data);
        routingContext.response()
		.putHeader("content-type", "application/json")
		.end(arr.encodePrettily());
		log("get" + arr);
    }

    private void sendError(int statusCode, HttpServerResponse response) {
		log("error");
        response.setStatusCode(statusCode).end();
    }

    private void log(String msg) {
        System.out.println("[DATA SERVICE] " + msg);
    }
}