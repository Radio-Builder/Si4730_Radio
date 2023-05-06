# Using a Radio Lab to Test the Si4730 Digital Radio Module
The Si4730 is a popular digital radio module that can receive AM and FM. It's a versatile and powerful module that can be used in a variety of radio applications, from simple hobby radios to more complex commercial or industrial radios. 
The Si4730 module can be programmed to perform a variety of functions, such as scanning for available radio stations, setting frequency limits, and adjusting audio settings. By using the radio lab, you can practise programming the module and experimenting with different settings to optimise its performance. In addition, the RadioLab has a TFT display and an encoder that can be used to change the frequency and recall preset radio stations. This user interface makes it easy to experiment with different settings and to tune in to your favourite stations.
There is also a Si4735 module that has HF capability and can be programmed to receive SSB and CW that can be connected up that same way and use the same software libraries.<br />

![20230429_181249](https://user-images.githubusercontent.com/132345889/236624875-e448a247-97dc-4d8b-8a89-9fd842eb790a.jpg)

![diagram](https://user-images.githubusercontent.com/132345889/236624835-8b962eb4-e083-4066-af23-ceb65f2757dc.jpg)
<br />
I got a few modules from AliExpress and I wanted to see how they performed at my location. I happen to be in an area ( Portlaoise, Co. Laois ) that has very poor FM signal strength of most FM broadcast stations and even good FM radios struggle with reception.
I did not connect the AM section as virtually all the AM stations are no longer broadcasting in Ireland, with the exception of RTE1 on 252KHz.
I soldered the module to  one of the RadioLab prototype boards and added two headers for connections. The only connections needed are <br />
    <br />1. GND
    <br />2. VCC ( 3.3V ) 
    <br />3. SDA
    <br />4. SCL
    <br />5. RESET
    <br />6. AUDIO Out
    <br />7. FM Antenna
    <br />
<br />I connected the I2C lines to the I2C header, added the reset to a GPIO 13, connected the antenna input via a capacitor to the SMA connector on the prototype board, the VCC to a 3.3V regulator and the audio out to the audio amplifier.<br />
**<br />Writing the Code<br />**
Reading the encoder and writing to the display are included functions that come with the RadioLab code. I added a library “PU2CLR SI4735 Library for Arduino” by Ricardo Lima Caratti which allows setup of the module and changing frequency. There are many functions available but I wanted to keep it simple.
The code is simple to use. The main loop checks if the encoder has changed and if so it changes the frequency in 100KHz steps depending on how many encoder steps were changed. It also reads three buttons that have pre programmed frequencies for my favourite stations.
**<br />Performance<br />**
The overall performance is similar to other FM radios that I have. Using a 1 meter wire antenna I could receive stations but overall reception was not great. This was expected as I am in a poor FM signal area. However when I used a 40 meter dipole antenna that is  in the attic all that changed and reception was great. I can get stations from all over the country and they are loud and clear.
Finally, using the RadioLab to test the Si4730 module can be both educational and fun. Radio experimentation is a great way to learn about electronics, radio theory, and signal processing. By experimenting with different components and configurations, you'll gain a deeper understanding of how radios work and how to optimise their performance. And, of course, experimenting with radios can be a fun and rewarding hobby.
For more info visit www.RadioBuilder.org or search for RadioBuilder.org group on Facebook.




