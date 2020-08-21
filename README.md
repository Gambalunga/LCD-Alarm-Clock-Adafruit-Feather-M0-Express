## LCD-Alarm-Clock-Adafruit-Feather-M0-Express
An LCD Alarm Clock using the Adafruit Feather M0 Express. Automatic correction for Daylight Saving Time and plays a short WAV file for the alarm.

<p align="center">
  <img src="https://raw.githubusercontent.com/Gambalunga/LCD-Alarm-Clock-Adafruit-Feather-M0-Express/master/Images/TickTock.jpg">
</p>
<p align="center"><em>The fascia and box covering is yet to be added</em></p>

The automatic correction for daylight savings time uses Western European rules but US rules are also available.
The SPI Flash storage was used for a 2 minute section of music that was extracted from an MP3 and saved as an 8bit 16000Hz WAV file (Alarm.wav) using Audacity. This file is played via the DAC of the ATSAMD21 processor. 

It should be noted that the PAM8302 Audio Amplifier overpowers the 4 Ohm speakers at full volume and the volume trim pot needs to be adjusted down until you get clear sound.

Items used were:
* an [Adafruit Feather M0 Express](https://www.adafruit.com/product/3403) (I recommend stacking headers for the eventual attachment of wires)
* [DS3231 Precision RTC FeatherWing](https://www.adafruit.com/product/3028) (with stacking headers)
* [4-Digit 7-Segment Display FeatherWing](https://www.adafruit.com/product/3106)
* [Mono 2.5W Class D Audio Amplifier - PAM8302](https://www.adafruit.com/product/2130)
* [Mono Enclosed Speaker - 3W 4 Ohm](https://www.adafruit.com/product/4445)
* 2 small pushbuttons (7 mm threaded with nuts for mounting in the case)
* 1 larger latching pushbutton (12mm - I found one with a blue 5V blue LED which works fine with 3V)
* a 1000 mAh Lithium battery to keep the clock running for a period in case of a power outage (if it loses power the alarm time would reset to the default time). See note below.
* Various jumper wires mainly female female which were cut in half to solder to the pushbuttons.

![image](https://raw.githubusercontent.com/Gambalunga/LCD-Alarm-Clock-Adafruit-Feather-M0-Express/master/Images/TickTock%20LCD.jpg)

Assembly was done in such a way that the switches and the amp were connected so that all components could be removed.

The assembly was pretty straight forward. I soldered a strip of 4 female headers to the underside of the 3V row on the prototyping section of the Feather (though in the end I only used one to provide power for the LED in the alarm control button) and a row of 4 pins to the GND section to provide GND attachments for the push buttons.

I soldered a length of 5 stacking header to the underside of the  Audio Amplifier and then snipped off the protruding pins on the top side for  A+, A-, and Vin This left the pins for Gnd and SD protruding from the top of the amp board.  The terminal block was soldered in place. The two pins protruding from the bottom of the stacking headers on the Feather M0 Express for RST and ARf were then snipped off so as not to form a contact with the Gnd and SD on the amp. In this way the amp can piggyback on the underside of the feather with the A+ to the A0 pin on the Feather, A- the the GND, and the Vin to the 3V pin.

The Gnd pin on the amp could probably be jumpered to the A- but I connected it to one of the GND pins on the Feather. The SD (Shut Down) pin on the amp was connected to pin 12 on the Feather.

The 3 pushbuttons were connected to GND and one of the small pushbuttons connected to pin 9 and the other to pin 10. The Gnd wire on the latching pushbutton was bridged to one of the LED pins and the other LED pin was connected to 3V on the Feather. The other side of the latching pushbutton was connected to pin 11 on the Feather.

When everything is functioning the unused pins on the underside of the Feather can be snipped off to clean things up a bit.

Regarding the Lithium battery. I do not know if the output of the battery that I have used is insufficient or if the alarm, or perhaps better to say the amplifier, simply draws too much power. The 1000 mAh battery will keep the clock running and the display functioning for several hours but if the alarm starts whilst there is only battery power the moment the amp is switched on the Feather either re-sets or goes into a sort of "brown-out". In either case the clock may still show the correct time, and the alarm may be re-set to the default time, but the alarm will not function and the USB serial communications with a PC, if connected, will show an unknown USB device. The only way to recover from this is to do a hard reset using the button on the feather, or to disconnect the battery and power from the Feather and then reconnect. A battery than can tolerate a higher current flow may not have this problem.

For the sketch I modified and worked on existing example sketches and libraries. For the alarm WAV playing through the DAB I modified and updated the SamdAudio library (which I have called Audio_FeatherM0). I also modified the DST_RTC library for European DST and it has no been updated on GitHub.

If the Alarm button is released (up) the alarm time shows for a few seconds and the alarm time can be adjusted forwards or backwards using the advance and retard buttons. After holding an advance or retard button down for 15 seconds the change in time speeds up. If the Alarm button is down (Alarm off) the time can be adjusted but this should be largely unnecessary. The exact time and date should be set with one of the RTC example sketches.

As it is in my sketch the Alarm.wav only plays once but it could be set to repeat several times or until the Alarm button is depressed. If repeated the delay of 3 minutes to turn off the amp should be lengthened.
