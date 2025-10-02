# avr-control

Interactive CLI for testing the hardware.
This version uses interrupt-driven UART transmit to allow
continuous data acquisition.
```
    T [n]         - start timers with CONV period=n default 10000
    G n           - set integrator range 0-7
    C n           - enable/disable charge test mode
    A [d [a]]     - stream data at 800/d Hz average a samples
    L d           - set LEDs
    R             - read ADC repeatedly
    P             - read ADC and print
    D n           - set DAC
    M en ch       - set mux en=0/1 ch=0..7
    F             - capture fast and display
    ---
    W t r [d...]  - write I2C
```
Some notes:

* 'A' has a few options:
```
    A          output at default 1Hz, average 800 samples
	A 100      output at 800/100 = 8Hz, average 100 samples
	A 800 1    output at 1Hz, no averaging
```
* 'P' captures and displays data at about 1HZ.
<br>It always captures with the same phase of CONV
* 'F' captures 100 samples at the max rate continuously
<br>When any UART rx is seen, it stops and dumps the data
<br>The last column is the state of CONV (integrator A/B)


## Enhancements for further testing

Readout rate with T = 10000 should be exactly 1.6kHz.

After discussion with Lina:

New readout mode.  Variable rate from 100Hz to .02Hz.
Average up to 2^12 samples.
