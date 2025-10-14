# Testing

### 2025-10-14

`2025-10-14_log_file1.dat` - 10 min run, LED at 2.1V through 10k, gain 1
<br>Cold start, just powered up after weekend

`2025-10-14_log_file2.dat` - 10 min run, LED at 2.6V through 10k, gain 2

`2025-10-14_log_file3.dat` - 10 min run, LED at 2.6V through 10k, gain 1
<br>After an hour or so closed and powered

`2025-10-14_log_file4.dat` - 10 min run, LED at 2.6V through 10k, gain 2
<br>After an hour or so closed and powered

`2025-10-14_log_file10.dat` - Lina's board LED at 2.1V, gain 1
<br>A few min after opening box

`2025-10-14_log_file10.dat` - Lina's board LED at 2.1V, gain 1
<br>3 ohm resistor taped ~1cm from the photodiode.
<br>Turn on at 1W at about sample 200
<br>Off at sample 267


### 2025-10-08

Testing for "Drift" per Lina's results
12:40 Start a run at gain 7 with photodiode in box, bag and lights out

`2025-10-08_log_file1.dat` - 10 minute run.  No trend seen

Try again with red LED in series with 10k at 3.0V.
The level goes up and then down at an apparently linear rate.

`2025-10-08_log_file3.dat` - 60 minute run.
<br>LED off for 1m at 1500s.

Open the box, move things around a bit and start again
Amplitude peaks, then droops at a linear rate for almost 60m

`2025-10-08_log_file4.dat` - 30 minute run.

Initial drop then stable


### 2025-09-11

Here are some waveforms from readout using the software as of 9/11/25.
Initialization is:

    >t 10000
    >g 7
    >p
    
Here is the complete cycle.  Scope channels are:

    1.  CONV
	2.  nDVALID
	3.  DCLK
	4.  DOUT
	
You can see that the digitization frequency is about 1.6kHz and that there is plenty of time to read out the 2x20 bits.

![Full readout](full_cycle_10k.png)

Here is a zoom on the readout portion.

![Readout part](readout_10k.png)
