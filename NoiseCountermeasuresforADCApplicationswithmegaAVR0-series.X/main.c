/***********************************************************************************************************************************************************
This application demonstrates the noise countermeasures for ADC applications.
Application is 'Periodic noise generation and noise filtering with sample accumulation, sampling delay, automatic
sampling delay'.

In this application, PWM noise is generated using timer TCA. This PWM signal is added as a noise to the 'signal to be
measured'. A DC signal from potentiometer is used as 'signal to be measured'. This mixed signal ( signal + noise signal)
is given as input signal to ADC. It will be sampled and the ADC result value is sent through USART to the serial
terminal of Data Visualizer and graph of ADC samples is plotted in the Data Visualizer. Different graphs with different
noise filtering configurations such as sample accumulation for 1 or 64 samples, sampling delay, automatic sampling delay
are plotted.

For more details and HW connection please refer Application note: Noise countermeasures for ADC applications.
Refer figure 'Adding noise to the signal circuit' from application note for signal mixing.
*************************************************************************************************************************************************************/

#include <atmel_start.h>

#define HARMONIC_NOISE                                                                                                 \
	1 /*  1: Generate PWM signal as a periodic noise.                                                                  \
	      0: Do not generate PWM signal.                                                                 */

#define PWM_FRQ                                                                                                        \
	62000 /*  Harmonic noise frequency in Hz.																   */

#define ADC_64X_ACCUMULATOR_ENABLE                                                                                     \
	0 /*  Configuration of consecutive sample accumulation                                                             \
	      1: 64 consecutive sample accumulation                                                                        \
	      0: No multiple sample accumulation (only 1 ADC sample accumulation)                                          \
	      Please note this example shows result graph with ADC sample accumulation of 1 sample or 64 samples only .    \
	      tinyAVR 1-series supports sample accumulation of 1,2,4,8,16,32,64. For sample accumulation other than 1 or   \
	     64, code needs to be changed accordingly (register ADC0.CTRLB and variable result_shift_cnt needs to be                   \
	     changed accordingly) */

#define SAMPLING_DELAY                                                                                                 \
	0 /*  0       : No sampling delay between consecutive samples in one single burst.                                 \
	      1 to 15 : Configures the sampling delay between consecutive samples in one single burst. The                 \
	                delay is expressed as CLK_ADC cycles. 1 being delay of 1 cycle.                      */

#define ENABLE_ASDV                                                                                                    \
	0 /*  1: Enable the automatic sampling delay between consecutive samples in one single burst.                      \
	      0: Do not enable automatic sampling delay variation                                            */

#define ADC_CHANNEL                                                                                                    \
	5 /*   read ADC CHANNEL 5   : pin PD5                                                                 */

uint16_t adc_result;
uint8_t  result_shift_cnt;

/**********************************************************************************************************************************************************
ADC result has been read and it has been sent through USART.
For Data Streamer protocol, START byte is 0x03 and END byte is 0xFC;
Data streamer protocol has been used to send ADC result to serial terminal so that one 16 bit value will be used to plot
the graph in Data Visualizer. For more details on Data Streamer and Graph, refer section: "Appendix A: Plotting graph in
Data Visualizer" from application note:Noise countermeasures for ADC applications. or
  http://content.alexandria.atmel.com/webhelp/GUID-F897CF19-8EAC-457A-BE11-86BDAC9B59CF-en-US-3/index.html?GUID-A6CB54F0-041D-4B12-A3E1-97602C36ED7B
***********************************************************************************************************************************************************/

void Transmit_Samples()
{
	adc_result = ADC_0_get_conversion_result();
	adc_result = adc_result >> result_shift_cnt;

	USART_0_write(0x03);                       /* Data Streamer protocol START */
	USART_0_write((uint8_t)adc_result);        /* ADC sample LSB */
	USART_0_write((uint8_t)(adc_result >> 8)); /* ADC sample MSB */
	USART_0_write(0xFC);                       /* Data Streamer protocol END */
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/*  Harmonic noise is enabled so generate PWM using TCA at pin PB0*/
#if HARMONIC_NOISE
	PWM_TCA_init();
	PWM_TCA_load_top((F_CPU / PWM_FRQ) - 1);
	PWM_TCA_load_duty_cycle_ch0(((F_CPU / PWM_FRQ) - 1) / 2); /*  50 % duty cycle */
#endif

	ADC0.CTRLD |= SAMPLING_DELAY;

#if ENABLE_ASDV
	ADC0.CTRLD |= 1 << ADC_ASDV_bp;
#endif

#if ADC_64X_ACCUMULATOR_ENABLE
	ADC0.CTRLB       = ADC_SAMPNUM_ACC64_gc;
	result_shift_cnt = 6;
#else
	ADC0.CTRLB       = ADC_SAMPNUM_ACC1_gc;
	result_shift_cnt = 0;
#endif

	ADC_0_start_conversion(ADC_CHANNEL);

	while (1) {

		if (ADC_0_is_conversion_done()) {
			Transmit_Samples();
		}
	}
}
