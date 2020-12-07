from alpine:latest 
LABEL Maintainer="Guillaume Maiano <guillaume@maiano.fr>" \
      Description="Mosquitto (MQTT server) / Alpine Linux-latest"

## setup MQTT server packages

# Install packages
RUN apk --no-cache add mosquitto
# Clients might be useful for testing runs
#RUN apl --no-cache add mosquitto-clients
# Use the client to subscribe on a topic
# docker exec -ti mosquitto mosquitto_sub -h 127.0.0.1 -v -t '#'
# Use the client to publish to a topic
# docker exec -ti mosquitto mosquitto_pub -h 127.0.0.1  -t 'hello' -m 'world'

# Expose MQTT port
EXPOSE 1883

ENV PATH /usr/sbin:$PATH

ENTRYPOINT ["/usr/sbin/mosquitto"] 
