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
    private TempManager tm;

    public MQTTAgent(TempManager tm) {
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

                // Imposta il publishHandler per gestire i messaggi in arrivo
                client.publishHandler(message -> {
                    // Recupera il payload come stringa
                    String payload = message.payload().toString();
                    log("Messaggio ricevuto: [" + payload + "]");

                    // Se il messaggio è nel formato "Temperature: XX", estrai il valore numerico
                    try {
                        int temperature = Integer.parseInt(payload);
                        tm.addTemp(temperature);
                        log("Temperatura elaborata: " + tm.getLast());
                    } catch (NumberFormatException e) {
                        log("Errore nel parsing della temperatura: " + payload);
                    }
                    /*if (parts.length > 1) {
                    } else {
                        log("Messaggio non nel formato atteso: " + payload);
                    }*/
                });

                // Sottoscrivi al topic "temperature" e logga il risultato
                client.subscribe(TOPIC_SUBSCRIBE, MqttQoS.AT_LEAST_ONCE.value(), subscribeResult -> {
                    if (subscribeResult.succeeded()) {
                        log("Sottoscrizione al topic '" + TOPIC_SUBSCRIBE + "' avvenuta con successo!");
                    } else {
                        log("Errore nella sottoscrizione al topic '" + TOPIC_SUBSCRIBE + "': " + subscribeResult.cause());
                    }
                });

                // Invia la frequenza iniziale
                sendFrequency(tm.getFreq());
            } else {
                log("Connessione fallita. Riprovo tra 5 secondi...");
                vertx.setTimer(5000, id -> connectToBroker());
            }
        });

        // Gestione della disconnessione
        client.closeHandler(v -> {
            log("Connessione persa. Riconnessione...");
            connectToBroker();
        });
    }

    public void sendFrequency(final int frequency) {
        if (client.isConnected()) {
            client.publish(
                TOPIC_SEND,
                Buffer.buffer(String.valueOf(frequency)),
                MqttQoS.AT_LEAST_ONCE,
                false,
                false
            );
            log("Frequenza inviata: " + frequency + " ms");
        } else {
            log("Non connesso! Impossibile inviare la frequenza.");
        }
    }

    private void log(final String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }
}
