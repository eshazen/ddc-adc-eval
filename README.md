# ddc-adc-eval

Evaluation board for DDC112 ADC (Arduino UNO shield?)

## Notes from DDC112 datasheet:

* CLK freq range 1-10MHz
* Can generate 8MHz easily using AVR CTC
  <br>Conversion rate then 1.6kHz max
* It is recommended CONV toggle within ±10ns of the rising edge of CLK
* Mode (Cont vs Ncont) selected by state of CONT pin at power-up
  <br>can also switch based on T(INT): space between CONV edges > 4794 clocks
  (600uS at 8MHz clock)
* Data ready at ~526uS at 8MHz

## To do

* Add analog switches for 3 LEDs.  Candidates:
  <br>ADG728 (not in stock, TSSOP)
  <br>LTC1380 (I2C) from ChatGPT!
* Think about grounding at VRs
* GND areas on back?
* Add LEDs
* Stacking header P/Ns
