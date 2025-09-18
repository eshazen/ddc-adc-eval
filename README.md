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
