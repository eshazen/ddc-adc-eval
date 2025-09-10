# avr-clock-test

Interactive CLI for testing the hardware.  As of now the timer setting, DAC, LED and MUX are working

    L d           - set LEDs
    T n           - start timers with CONV period=n
    G n           - set integrator range 0-7
    A             - readout ADC
    D n           - set DAC
    M en ch       - set mux en=0/1 ch=0..7
    ---
    AV            - read without wait for data valid
    AR            - repeated readout for scope test
    W t r [d...]  - write I2C
    V             - read timer1 value
    X             - reset timers

