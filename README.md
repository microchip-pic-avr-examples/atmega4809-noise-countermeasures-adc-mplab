<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# ATMEGA4809 Noise Countermeasures for ADC Applications

This is an example for noise countermeasures for ADC applications on the ATmega4809, this is a general example which is applicable to the whole megaAVR® 0-series. In the ADCs implemented in megaAVR® 0-series, the input signal is fed through a Sample-and-Hold circuit which ensures that the input voltage to the ADC is held at a constant level during sampling.

The example code is based on the application note [AN2551](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en600674).

## Related Documentation

- [AN2551 -  Noise Countermeasures for ADC Applications ](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en600674)
- [ATmega4809 Device Page](https://www.microchip.com/wwwproducts/en/ATMEGA4809)

## Software Used

- [MPLAB X IDE v5.40 or later](https://www.microchip.com/mplab/mplab-x-ide)
- Data Visualizer
    - [MPLAB Data Visualizer](https://gallery.microchip.com/packages/MPLAB-Data-Visualizer-Standalone(Windows)/)
    - [Studio Data visualizer](https://www.microchip.com/mplab/avr-support/data-visualizer)
- ATmega_DFP 2.2.108 or later
- [XC8 (v2.20)](https://www.microchip.com/mplab/compilers) alternatively [AVR/GNU C Compiler 5.4.0](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers) can be used

## Hardware Used

- [ATmega4809 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/ATMEGA4809-XPRO)

## Setup

* The ADC input is mapped to `PD5` and will change the ADC values being sent over UART depending on the voltage applied

## Operation

1. Download the zip file or clone the example to get the source code.
2. Open `atmega4809-noise-countermeasures-adc-mplab.X` in MPLAB
3. Connect the ATmega4809 Xplained Pro to your computer with a micro usb cable.
4. Use these defines to plot a graph without noise
    ```c
    #define HARMONIC_NOISE 0
    #define ADC_64X_ACCUMULATOR_ENABLE 0
    #define SAMPLING_DELAY 0
    #define ENABLE_ASDV 0 
    ```
5. Make sure the kit is selected as the tool to be programmed under project settings.
6. Press the make and program button to program the device.
7. Open data visualizer to interact with the virtual comport over UART on the devkit. The baud rate is `19200`.
8. Follow Appendix A in [AN2551](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en600674) for step by step instructions on how to graph the samples.
    * Alternatively, the MPLAB Data Visualizer can be used. To start plotting data, click load workspace and choose the provided config file `MPLAB_Data_Visualizer_Config_Noise_Countermesure.json`. Make sure the correct COM port is selected when it is opened. Documentation for the MPLAB Data Visualizer can be opened inside the visualizer by clicking the ‘?’ symbol or by pressing F1 

Filtered ADC values will be passed over the UART port, these can be parsed or graphed for a visual understanding of ADC value.

## Conclusion

We have here shown how to get started with the [AN2551](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en600674) appnote. For more details about the code and theory of operation please inspect the appnote itself.