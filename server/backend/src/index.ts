import Fastify from "fastify";
import cors from "@fastify/cors";
import mqtt from "mqtt";

import 'dotenv/config'

const mqttBroker: string = process.env.MQTT_BROKER!;
const topic: string = process.env.TOPIC ?? "remodian/cmd";
const port: number = parseInt(process.env.HTTP_PORT ?? "1713");

const server = Fastify({ logger: true });
const client = mqtt.connect(mqttBroker);

const cmds = {
    powerOn: 0x6b,
    powerOff: 0x0c,
    volUp: 0x10,
    volDown: 0x11
}

function setupRoute(route: string, cmd: number) {
    server.post(route, () => {
        client.publish(topic, JSON.stringify({ cmd }));

        return { success: true };
    })
}

setupRoute("/power/on", cmds.powerOn)
setupRoute("/power/off", cmds.powerOff)
setupRoute("/volume/up", cmds.volUp)
setupRoute("/volume/down", cmds.volDown)

const start = async () => {
    await server.register(cors, {
        origin: "*", // or ["https://yourdomain.com"]
        methods: ["GET", "POST", "PUT", "DELETE", "OPTIONS"]
    });

    try {
        await server.listen({ port, host: "0.0.0.0" });
        console.log("Server running at http://0.0.0.0:" + port);
    } catch (err) {
        server.log.error(err);
        process.exit(1);
    }
};

start();

process.on('SIGTERM', () => {
    console.log('Received SIGTERM, shutting down gracefully...');
    process.exit(0);
})
process.on('SIGINT', () => {
    console.log('Received SIGINT (Ctrl+C)');
    process.exit(0);
});
