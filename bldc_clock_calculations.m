clear;
% STM32F4 Clock Tree
f_HSE = 8e6; % HSE clock frequency
STM32_PLLM_VALUE = 4;
STM32_PLLN_VALUE = 144;
STM32_PLLP_VALUE = 2;
f_STM32_SYSCLK = f_HSE / STM32_PLLM_VALUE * STM32_PLLN_VALUE / STM32_PLLP_VALUE
STM32_PPRE1 = 4; % APB1 prescaler
STM32_PPRE2 = 2; % APB2 prescaler

% ADC configuration
ADC_CCR_ADCPRE_DIV2 = 0;
ADC_CCR_ADCPRE_DIV4 = 1;
ADC_CCR_ADCPRE_DIV6 = 2;
ADC_CCR_ADCPRE_DIV8 = 3;
STM32_ADC_ADCPRE = ADC_CCR_ADCPRE_DIV2; % defined in mcuconf.h

STM32_ADC_ADCPRESCALER = 2 + (2 * STM32_ADC_ADCPRE);
Ks_ADC_samplehold = 3; % ADC sampling (hold) cycles (see ADC_SMPRx registers)
Ks_ADC_conversion = 12;% ADC resolution / ADCCLK cycles for conversion
Ks_ADC = Ks_ADC_samplehold + Ks_ADC_conversion
disp('ADC clock frequency (check against max value in datasheet!)')
f_ADCCLK = f_STM32_SYSCLK / STM32_PPRE2 / STM32_ADC_ADCPRESCALER
f_ADC = f_ADCCLK / Ks_ADC;
ADC_COMMUTATE_FREQUENCY = f_ADC

Ts_ADC1 = 1 / f_ADC; % Sample time of ADC [s]


% PWM configuration
ADC_PWM_DIVIDER = Ks_ADC * STM32_ADC_ADCPRESCALER % When f_TIM1 == f_TIM2 (*STM32_PPRE2 for f_TIM1 = f_SYSCLK)


disp('Schaltzeiten')
PWM_CLOCK_FREQUENCY = f_STM32_SYSCLK / 2;

ADC_NUM_CHANNELS = 1;               % Number of channels per ADC for (6-step mode)
ADC_FRT_DEFAULT_PERIOD_CYCLES = 100; % Fastest FRT cycle period in ADC cycles
PWM_ADC_DEFAULT_PERIOD_CYCLES = 20;  % Choose a default number of ADC samples in a PWM period
PWM_ADC_MAXIMUM_PERIOD_CYCLES = 200; % Choose a maximum number of ADC samples in a PWM period (determines maximum PWM period)
ADC_COMMUTATE_BUF_DEPTH = ADC_NUM_CHANNELS * PWM_ADC_MAXIMUM_PERIOD_CYCLES * 2 % TODO Check if this is sufficient!
PWM_FRT_DEFAULT_PERIOD_CYCLES = ADC_PWM_DIVIDER * ADC_FRT_DEFAULT_PERIOD_CYCLES;
PWM_DEFAULT_PERIOD_CYCLES = ADC_NUM_CHANNELS * ADC_PWM_DIVIDER * PWM_ADC_DEFAULT_PERIOD_CYCLES;
PWM_MAXIMUM_PERIOD_CYCLES = ADC_NUM_CHANNELS * ADC_PWM_DIVIDER * PWM_ADC_MAXIMUM_PERIOD_CYCLES;

FRT_DEFAULT_FREQUENCY = PWM_CLOCK_FREQUENCY / PWM_FRT_DEFAULT_PERIOD_CYCLES
PWM_DEFAULT_FREQUENCY = PWM_CLOCK_FREQUENCY / PWM_DEFAULT_PERIOD_CYCLES % [40e3, 50e3, 62500, 100e3]	choose one of these base frequencies [Hz]
PWM_MINIMUM_FREQUENCY = PWM_CLOCK_FREQUENCY / PWM_MAXIMUM_PERIOD_CYCLES

%ADC_COMMUTATE_FREQUENCY	= 1e6;%		// [Hz]
% ADC_PWM_DIVIDER = (PWM_CLOCK_FREQUENCY / ADC_COMMUTATE_FREQUENCY)
% ADC_PWM_PERIOD = (ADC_COMMUTATE_FREQUENCY / PWM_DEFAULT_FREQUENCY) % In ADC-ticks
% PWM_MAXIMUM_PERIOD = (ADC_PWM_DIVIDER * ADC_COMMUTATE_FREQUENCY / PWM_MINIMUM_FREQUENCY);


% Calculate the PWM-period with respect to the duty cycle
d_percent = (1:49) + 49;
pwm_period = fix( ((PWM_ADC_DEFAULT_PERIOD_CYCLES * 2500) ./ ((100 .- d_percent) .* d_percent))) .* (ADC_NUM_CHANNELS * ADC_PWM_DIVIDER);

pwm_frequency = PWM_CLOCK_FREQUENCY ./ pwm_period;

for i=1:length(pwm_period)
  if pwm_period(i) > PWM_MAXIMUM_PERIOD_CYCLES
    pwm_period(i) = PWM_MAXIMUM_PERIOD_CYCLES;
  endif
  frt_period(i) = pwm_period(i); % TODO: Normiere auf ADC
  if frt_period(i) < PWM_FRT_DEFAULT_PERIOD_CYCLES
    frt_period(i) = ( fix(PWM_FRT_DEFAULT_PERIOD_CYCLES / pwm_period(i)) + 1 ) * pwm_period(i);
  endif
endfor

t_on = d_percent ./ 100 .* pwm_period;
t_off = pwm_period - t_on;
plot(d_percent, frt_period, d_percent, pwm_period, d_percent, t_off)
xlabel('Duty cycle, d [%]');
legend('FRT-Period', 'PWM-Period', 't_{off}');

figure;
plot(d_percent, frt_period ./ ADC_PWM_DIVIDER .* 2)
% plot(d_percent, t_off)
% Check max samples for linear fit;
