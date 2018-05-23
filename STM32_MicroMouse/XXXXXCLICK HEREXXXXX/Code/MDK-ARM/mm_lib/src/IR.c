#include "IR.h"
// variables to keep track of IR readings
//      correspond to L, LF1, LF2, RF1, RF2, R sensors
//      LF = RF = diagonal sensors
__IO uint16_t IR_values[6] = {0, 0, 0, 0, 0, 0};

// init pins to a "garbage" value of 0, they will be reassigned in the tester
GPIO L_emitter, R_emitter, LF_emitter, RF_emitter;
int L_receiver, R_receiver, LF0_receiver, LF1_receiver, RF0_receiver, RF1_receiver = 0;
uint8_t cc1Flag = 0;


extern __IO uint16_t CCR1_Val;
void initIR(void) {
		L_emitter = initIO(PC2, OUTPUT);
    R_emitter = initIO(PC9, OUTPUT);
    LF_emitter = initIO(PB5, OUTPUT);
    RF_emitter = initIO(PA12, OUTPUT);
	
    L_receiver = addADC(PC3, ADC_Channel_13);
    R_receiver = addADC(PB1, ADC_Channel_9);
		
    LF0_receiver = addADC(PC1, ADC_Channel_10);
    LF1_receiver = addADC(PC0, ADC_Channel_11);
    RF1_receiver = addADC(PB0, ADC_Channel_8);
    RF0_receiver = addADC(PC5, ADC_Channel_15);
	
		initADC(ADC1);
    CCR1_Val = usToCCR(10);
    TIM3_initIT();  
}
/**
 * Paramerter pin: is the pin which we wish to send an IR pulse for.
 * This is called by the interrupt handler.``
 */
void IR_pulse(GPIO EM) { 
    if (cc1Flag == 0) {
        digitalWrite(EM, HIGH);
				CCR1_Val = usToCCR(Impulse_period);
        cc1Flag = 1;
    } else {
        digitalWrite(EM, LOW);
				CCR1_Val = usToCCR(4 * Impulse_period);
        cc1Flag = 0;
    }
}
void IR_Tester(void) {
		initIR();
    while(1) {
			printf("\r%d %d %d %d %d %d\r\n", IR_values[0], IR_values[1], IR_values[2], IR_values[3], IR_values[4], IR_values[5]);
			delay(1);
		}
}

/**
* Helper method to average readings over a sample.
*/
uint16_t parse_ADC_Sample(uint16_t Sarr[], uint32_t n) {
    int sum = 0;

    for (int i = 0 ; i < n; i++) {
        sum += *(Sarr+i);
    }
    return sum / n;
}

/**
 * This method is an interupt handler for. 
 * We want to take readings from the 4 IR sensors.
 *
 * Naming convention for IRs:
 *      Front facing IRS: L, R
 *      Diagonal facing IRS: LF, RF
 */

// this corresponds to the length of the instruction cycle. 
// Ie. if we model the IR-system as a FSM with states corresponding to interrupts,
// this keeps track of current state.

int instr = 0;     
uint16_t reading_arr[num_samples_IR];

void TIM3_itTask_cc1(void) {
    // idea:
    // first interrupt, set p1 to high
    // second interrupt, read pin and then set to low
    // repeat. To read use ADC_sampling method.
    switch(instr) {
        // left pairs
        case 0:
            IR_pulse(L_emitter);
						break;

        case 1:
            // read the pin
						IR_values[0] = analogRead(L_receiver);
            // set the pin to low
            IR_pulse(L_emitter);
						break;

            // left-front pairs
        case 2:
            IR_pulse(LF_emitter);
            break;

        case 3:
            // read both front left receivers						
						IR_values[1] = analogRead(LF0_receiver);	
						IR_values[2] = analogRead(LF1_receiver);
            // set the pin to low
            IR_pulse(LF_emitter);
            break;

            // right-front pairs
        case 4:
            IR_pulse(RF_emitter);
            break;

        case 5:
            // read both front right receivers
						IR_values[3] = analogRead(RF1_receiver);
						IR_values[4] = analogRead(RF0_receiver);
            // set the pin to low
            IR_pulse(RF_emitter);
            break;

            // right pair
        case 6:
            IR_pulse(R_emitter);
            break;

        case 7:
            // read the right pair
						IR_values[5] = analogRead(R_receiver);
            IR_pulse(R_emitter);
            break;

        default:
            // this should never be reached
            break;
    }
		
    instr++;
    if (instr >= 8) instr = 0; // reset using "modular" arithmetic simulation.
}

