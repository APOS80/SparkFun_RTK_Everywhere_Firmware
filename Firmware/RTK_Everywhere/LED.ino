void gnssStatusLedOn()
{
    if (pin_gnssStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_gnssStatusLED, HIGH);
}

void gnssStatusLedOff()
{
    if (pin_gnssStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_gnssStatusLED, LOW);
}

void gnssStatusLedBlink()
{
    if (pin_gnssStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_gnssStatusLED, !digitalRead(pin_gnssStatusLED));
}

void bluetoothLedOn()
{
    if (pin_bluetoothStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_bluetoothStatusLED, HIGH);
}

void bluetoothLedOff()
{
    if (pin_bluetoothStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_bluetoothStatusLED, LOW);
}

void bluetoothLedBlink()
{
    if (pin_bluetoothStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_bluetoothStatusLED, !digitalRead(pin_bluetoothStatusLED));
}

void baseStatusLedOn()
{
    if (pin_baseStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_baseStatusLED, HIGH);
}

void baseStatusLedOff()
{
    if (pin_baseStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_baseStatusLED, LOW);
}

void baseStatusLedBlink()
{
    if (pin_baseStatusLED != PIN_UNDEFINED)
        digitalWrite(pin_baseStatusLED, !digitalRead(pin_baseStatusLED));
}
