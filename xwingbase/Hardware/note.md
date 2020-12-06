## Parts

### LEDs
Theorical Specs (though I get different nm values in Fritzing, always reassuring)
20m for ALL LED
red led: 620-630nm / 1.8...2.3V
blue led: 460-470nm / 2.8...3.6V
white led: 610-620nm / 2.8...3.6V
green led: 520-530nm /  2.8...3.6V
yellow led: 460-470nm / 1.8...2.3V

### Resistors
220 and 330 Ohms (red-red, orange-orange)

### On-off interruptor
Connected to Gnd, cuts the circuit for LEDs.

### Later?

  - Sound requires speakers and a SD reader, but Imperial March and effects would be nice.
  - Light detector would be nice for some "Force User" moves :)

## Software

- Needs a MQTT client (will set MQTT server up on our main server)
- Needs a DNS solver (main server could change IP)
- Needs interrupt/millis based flow for each LED, since they model independent systems)

## Tasks

I'll try to use Github's system to keep track of tasks to be done.
