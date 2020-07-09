<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# ATMEGA4809 Noise Countermeasures for ADC Applications

This is an example for noise countermeasures for ADC applications on the ATMEGA4809, this is a general example which is applicable to the whole megaAVR 0-series. The example code is based on the application note [AN2551](#Related-Documentation)

## Related Documentation

- [AN2551 -  Noise Countermeasures for ADC Applications ](https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en600674)
- [ATmega4809 Device Page](https://www.microchip.com/wwwproducts/en/ATMEGA4809)

## Software Used

- [MPLAB X IDE v5.40 or later](https://www.microchip.com/mplab/mplab-x-ide)
- [Data Visualizer](https://www.microchip.com/mplab/avr-support/data-visualizer)
- ATmega_DFP 1.4.351 or later

## Hardware Used

- [ATmega4809 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/ATMEGA4809-XPRO)

## Setup

* Connect the ATmega4809 Xplained Pro to your computer with a micro usb cable.
* The ADC input is mapped to `PD5` and will change the ADC values being sent over UART depending on the voltage applied.

## Operation

1. Open `NoiseCountermeasuresforADCApplicationswithmegaAVR0-series.X` in MPLAB
2. Connect the ATmega4809 Xplained Pro to your computer with a micro usb cable.
3. Make sure the kit is selected as the tool to be programmed under project settings
4. Press the make and program button to program the device.
5. Open data visualizer to interact with the virtual comport over UART on the devkit. The baud rate is `19200`
6. Follow Appendix A in [AN2551](#Related-Documentation) for step by step instructions on how to graph the samples

Filtered ADC values will be passed over the UART port, these can be parsed or graphed for a visual understanding of ADC value.

## Conclusion

We have here shown how to get started with the [AN2551](#Related-Documentation) appnote. For more details about the code and theory of operation please inspect the appnote itself.