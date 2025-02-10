#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" // Biblioteca para controle do hardware PWM

#define PWM_MOTOR 22 // Pino GPIO utilizado para o sinal PWM do servo motor

// Configurações do PWM
const float PWM_DIVISER = 100.0;    // Divisor de clock para ajustar a frequência do PWM
const uint16_t WRAP_PERIOD = 25000; // Valor máximo do contador PWM (determina a frequência do sinal)

// Definição dos níveis de PWM para diferentes ângulos do servo motor
const uint16_t MOTOR_STEP = 5;         // Incremento/decremento do duty cycle
const uint16_t motor_level_180 = 3000; // PWM correspondente a 180°
const uint16_t motor_level_90 = 1837;  // PWM correspondente a 90°
const uint16_t motor_level_0 = 625;    // PWM correspondente a 0°
uint16_t motor_level = motor_level_0;  // Nível PWM inicial do servo motor

// Função para configurar o módulo PWM no pino especificado
void pwm_setup()
{
  gpio_set_function(PWM_MOTOR, GPIO_FUNC_PWM); // Configura o pino como saída PWM
  uint slice = pwm_gpio_to_slice_num(PWM_MOTOR); // Obtém o número do slice PWM correspondente ao pino

  // Configura a frequência do PWM para aproximadamente 50Hz (período de 20ms)
  pwm_set_clkdiv(slice, PWM_DIVISER); // Define o divisor de clock do PWM
  pwm_set_wrap(slice, WRAP_PERIOD);   // Define o valor máximo do contador PWM

  // Configura o duty cycle inicial e habilita o PWM
  pwm_set_gpio_level(PWM_MOTOR, motor_level); // Define o nível inicial do PWM
  pwm_set_enabled(slice, true);               // Habilita o módulo PWM
}

int main()
{
  stdio_init_all(); // Inicializa a entrada e saída padrão (para comunicação via terminal)
  pwm_setup();      // Configuração inicial do PWM

  printf("SERVO INICIADO\n");

  // Testa diferentes posições do servo motor
  printf("180 GRAUS\n");
  pwm_set_gpio_level(PWM_MOTOR, motor_level_180);
  sleep_ms(5000);

  printf("90 GRAUS\n");
  pwm_set_gpio_level(PWM_MOTOR, motor_level_90);
  sleep_ms(5000);

  printf("0 GRAUS\n");
  pwm_set_gpio_level(PWM_MOTOR, motor_level_0);
  sleep_ms(5000);

  uint motor_State = 1; // Define o estado inicial do motor (1 = aumentando, 0 = diminuindo)

  while (true)
  {
    pwm_set_gpio_level(PWM_MOTOR, motor_level); // Atualiza o duty cycle do PWM

    // Alterna entre aumentar e diminuir o ângulo do servo motor
    if (motor_State)
    {
      motor_level += MOTOR_STEP; // Incrementa o nível PWM
      if (motor_level >= motor_level_180)
      {
        motor_State = 0; // Inverte a direção ao atingir o limite superior
        printf("Mudança de direção: diminuindo\n");
      }
    }
    else
    {
      motor_level -= MOTOR_STEP; // Decrementa o nível PWM
      if (motor_level <= motor_level_0)
      {
        motor_State = 1; // Inverte a direção ao atingir o limite inferior
        printf("Mudança de direção: aumentando\n");
      }
    }

    sleep_ms(10); // Pequeno atraso para suavizar a movimentação do servo
  }
}
