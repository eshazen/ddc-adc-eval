# avr-clock-test

Interactive CLI for testing the hardware.

    L d           - set LEDs
    T n           - start timers with CONV period=n
    G n           - set integrator range 0-7
    A             - readout ADC
    R             - read ADC repeatedly
    P             - read ADC and print
    D n           - set DAC
    M en ch       - set mux en=0/1 ch=0..7
    C n           - enable/disable charge test mode
    F             - capture fast and display
    ---
    W t r [d...]  - write I2C
    V             - read timer1 value
    X             - reset timers

Some notes:

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



