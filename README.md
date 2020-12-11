# Store code for my models

## Notes
I'm currently using NodeMCU boards from LoLin. They're fickle things.

If issues, check the cable first, then verify the esp8266 optional board repository is enabled in ArduinoIDE, then verify there is no double of the libraries.

If the board spews garbage to the console, check the baudrate in the code and in the serial console.

## Branches

Stable branch is 'main'
Unstable branch is 'develop'
Code goes in work branches defined by [this precommit hook](https://github.com/guillaumemaiano/IoT-models/blob/develop/admin/hooks/pre-commit), then is PR'ed and validated.

Since I'm alone, it's mostly to get the benefit of a second web-based diff check, and if I ever get around to having a test suite, maybe do that too ;)
