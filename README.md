# ddc-adc-eval

Evaluation board for DDC112 ADC (Arduino UNO shield?).
See `led-photodiode-avr` design for working board.

## Notes from DDC112 datasheet:

* CLK freq range 1-10MHz
* Can generate 8MHz easily using AVR CTC
  <br>Conversion rate then 1.6kHz max
* It is recommended CONV toggle within ±10ns of the rising edge of CLK
* Mode (Cont vs Ncont) selected by state of CONT pin at power-up
  <br>can also switch based on T(INT): space between CONV edges > 4794 clocks
  (600uS at 8MHz clock)
* Data ready at ~526uS at 8MHz (4208 clocks)

## Readout strategy

* Readout function takes ~32us for 20 bits
* So maybe use CONV period of 558 + 10us (568us or 4544 clocks - 9088 period)

## Version 2 ECOs

### Main board

* [sch] Add transistors, expand to support 8 LEDs
* [sch] Change to common anode configuration (incl connector pinout)
* [sch] Correct external caps on DDC (2 -> 4 C's)
* [sch] Add 12 bit ADC for temperature sensor
* [sch] Testpoints?

### Optical board

* Fix photodiode pinout
* Add temp sensor next to photodiode on copper pad
* Add two Marubeni footprints next to D1 and D3
* Wire 8 LED drivers to the 9 LEDs with a jumper to choose between e.g. D3 and one Marubeni channel.
* Change to common anode topology
* 
