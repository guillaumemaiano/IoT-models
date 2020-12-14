#include "Lights.h"

extern const uint8_t whiteLED_TIE;// = D5; // GPIO14

void fighterTIELights() {
	if (digitalRead(whiteLED_TIE) == LOW) {
		digitalWrite(whiteLED_TIE,
				HIGH);
	} else {
		digitalWrite(whiteLED_TIE,
				LOW);
	}
}
