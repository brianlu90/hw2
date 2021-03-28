(1) D5, D6, D7 is for Confirm, 50Hz, and 100Hz button respectively.
    D13 is for analog output(triangle wave).
    A0 is for analog input(sampling).
    D1, D0, D2 is for serial Tx, serial Rx, and reset pin of uLCD respectively.
(2) After running the C++ code, the uLCD will show two frequency options.
    Choose one of it and then press the Confirm button.
    The program will start sampling the wave automatically.
(3) Run the Python code FFT.py to get the sampled results. The results, which
    include the sampled waveform and the FFT of the waveform, will be shown 
    in the graph after a while.