==================================

MQTT is relatively pointless without encryption:
--> use CA cert x509 (let's encrypt?)

This guy did something interesting, though not automated or dockerized: https://blog.thewalr.us/2019/03/27/using-esp8266-as-an-iot-endpoint-with-encrypted-mqtt-transport/



==================================


Noel:

> tu crées un dépôt gopass dans git

tu l'initialise avec deux clés GPG : 
- une pour toi humain
- une pour ton script

dans ton script tu maj le mot de passe dans le dépôt, et dans ton app

tu exec le script dans une crontab à volonté
