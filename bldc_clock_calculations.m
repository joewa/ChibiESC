% STM32F4 Clock Tree
f_HSE = 8e6; % HSE clock frequency
STM32_PLLM_VALUE = 6;
STM32_PLLN_VALUE = 216;
STM32_PLLP_VALUE = 2;
f_STM32_SYSCLK = f_HSE / STM32_PLLM_VALUE * STM32_PLLN_VALUE / STM32_PLLP_VALUE
STM32_PPRE1 = 4; % APB1 prescaler
STM32_PPRE2 = 2; % APB2 prescaler

% ADC configuration
STM32_ADC_ADCPRE = 2;
Ks_ADC_samplehold = 3; % ADC sampling (hold) cycles (see ADC_SMPRx registers)
Ks_ADC_conversion = 12;% ADC resolution / ADCCLK cycles for conversion
Ks_ADC = Ks_ADC_samplehold + Ks_ADC_conversion
disp('ADC clock frequency (check against max value in datasheet!)')
f_ADCCLK = f_STM32_SYSCLK / STM32_PPRE2 / STM32_ADC_ADCPRE
f_ADC = f_ADCCLK / Ks_ADC
ADC_COMMUTATE_FREQUENCY = f_ADC;

Ts_ADC1 = 1 / f_ADC; % Sample time of ADC [s]
ADC_COMMUTATE_NUM_CHANNELS = 1;
ADC_COMMUTATE_BUF_DEPTH = 50;
f_ADC_single = 1 / (Ts_ADC1 * ADC_COMMUTATE_NUM_CHANNELS) % Sample frequency of each channel
T_cb_ADC1 = Ts_ADC1 * ADC_COMMUTATE_NUM_CHANNELS * ADC_COMMUTATE_BUF_DEPTH / 2 % Period of ADC1 streaming callback
f_cb_ADC1 = 1 / T_cb_ADC1

% PWM configuration
ADC_PWM_DIVIDER = Ks_ADC * STM32_ADC_ADCPRE % When f_TIM1 = f_TIM2 (*STM32_PPRE2 for f_TIM1 = f_SYSCLK)
% PWM clock ticks per ADC samples

f_PWM = 20e3;
duty_cycle = 0.6;
t_on = duty_cycle * 1/f_PWM
samples_when_on = t_on * f_single

disp('Schaltzeiten')
PWM_CLOCK_FREQUENCY = f_STM32_SYSCLK / 2;

PWM_DEFAULT_PERIOD_CYCLES = ADC_PWM_DIVIDER * 20; % Choose a number of ADC samples in a PWM period

PWM_DEFAULT_FREQUENCY = PWM_CLOCK_FREQUENCY / PWM_DEFAULT_PERIOD_CYCLES % [40e3, 50e3, 62500, 100e3]	choose one of these base frequencies [Hz]
PWM_MINIMUM_FREQUENCY = 40000;

%ADC_COMMUTATE_FREQUENCY	= 1e6;%		// [Hz]
ADC_PWM_DIVIDER = (PWM_CLOCK_FREQUENCY / ADC_COMMUTATE_FREQUENCY)
ADC_PWM_PERIOD = (ADC_COMMUTATE_FREQUENCY / PWM_DEFAULT_FREQUENCY); % In ticks
PWM_MAXIMUM_PERIOD = (ADC_PWM_DIVIDER * ADC_COMMUTATE_FREQUENCY / PWM_MINIMUM_FREQUENCY);

d_percent = (1:49) + 49;
pwm_period = fix( ((ADC_PWM_PERIOD * 2500) ./ ((100 .- d_percent) .* d_percent))) .* ADC_PWM_DIVIDER;

pwm_frequency = PWM_CLOCK_FREQUENCY ./ pwm_period

for i=1:length(pwm_period)
  if pwm_period(i) > PWM_MAXIMUM_PERIOD
    pwm_period(i) = PWM_MAXIMUM_PERIOD;
  endif
endfor

t_on = d_percent ./ 100 .* pwm_period;
t_off = pwm_period - t_on;
plot(d_percent, pwm_period, d_percent, t_off)
% plot(d_percent, t_off)
% Check max samples for linear fit;
