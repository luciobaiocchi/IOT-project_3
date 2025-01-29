package connections.mqtt;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;
import model.TempManager;

public class MQTTAgent extends AbstractVerticle {

    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private static final String TOPIC_SUBSCRIBE = "temperature"; 
    private static final String TOPIC_SEND = "frequency";

    private MqttClient client;
    private int updateFrequency = 5000;
	private TempManager tm;

	public MQTTAgent (TempManager tm){
		this.tm = tm;
	}

    @Override
    public void start() {
        client = MqttClient.create(vertx);

        connectToBroker();
    }

    private void connectToBroker() {
        client.connect(1883, BROKER_ADDRESS, connection -> {
            if (connection.succeeded()) {
                log("Connesso al broker MQTT!");

                client.publishHandler(message -> {
                    String receivedTemperature = message.payload().toString();
					tm.addTemp(Integer.parseInt(receivedTemperature));
					log(String.valueOf(tm.getLast()));
                }).subscribe(TOPIC_SUBSCRIBE, MqttQoS.AT_LEAST_ONCE.value());

                sendFrequency(updateFrequency);
            } else {
                log("Connessione fallita. Riprovo tra 5 secondi...");
                vertx.setTimer(5000, id -> connectToBroker());
            }
        });

        client.closeHandler(v -> {
            log("Connessione persa. Riconnessione...");
            connectToBroker();
        });
    }

    public void sendFrequency(int frequency) {
        if (client.isConnected()) {
            updateFrequency = frequency;
            client.publish(TOPIC_SEND,
                    Buffer.buffer(String.valueOf(frequency)),
                    MqttQoS.AT_LEAST_ONCE,
                    false,
                    false);
            log("Frequenza inviata: " + frequency + " ms");
        } else {
            log("Non connesso! Impossibile inviare la frequenza.");
        }
    }

    private void log(String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }
}
