#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_MOTOR 22 // Pino GPIO para PWM do servo motor

// Configurações do PWM
const float PWM_DIVISER = 100.0; // Divisor de clock para ajustar a frequência do PWM
const uint16_t WRAP_PERIOD = 25000; // Valor máximo do contador PWM, determina a frequência
const uint16_t MOTOR_STEP = 5; // Incremento/decremento do duty cycle

// Níveis PWM correspondentes aos ângulos do servo
const uint16_t MOTOR_LEVEL_180 = 3000; // PWM para 180°
const uint16_t MOTOR_LEVEL_90 = 1837;  // PWM para 90°
const uint16_t MOTOR_LEVEL_0 = 625;    // PWM para 0°
uint16_t motor_level = MOTOR_LEVEL_0;  // Nível PWM inicial do servo motor

// Função para configurar o módulo PWM no pino especificado
void pwm_setup() {
    gpio_set_function(PWM_MOTOR, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(PWM_MOTOR); // Obtém o número do slice PWM correspondente ao pino
    pwm_set_clkdiv(slice, PWM_DIVISER); // Define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD);   // Define o valor máximo do contador PWM
    pwm_set_gpio_level(PWM_MOTOR, motor_level); // Define o nível inicial do PWM
    pwm_set_enabled(slice, true); // Habilita o módulo PWM
}

// Função para definir a posição do servo motor
void set_motor_position(uint16_t level, const char *position) {
    printf("Posição: %s\n", position); // Exibe a posição do servo no console
    pwm_set_gpio_level(PWM_MOTOR, level); // Atualiza o nível PWM
    sleep_ms(5000); // Aguarda 5 segundos para a estabilização da posição
}

// Função para varrer continuamente os ângulos do servo motor
void motor_sweep() {
    uint8_t increasing = 1; // Variável para controlar a direção do movimento
    while (true) {
        pwm_set_gpio_level(PWM_MOTOR, motor_level); // Aplica o duty cycle atual

        // Alterna entre aumentar e diminuir o ângulo do servo motor
        if (increasing) {
            motor_level += MOTOR_STEP; // Incrementa o nível PWM
            if (motor_level >= MOTOR_LEVEL_180) {
                increasing = 0; // Inverte a direção ao atingir o limite superior
                printf("Mudança de direção: diminuindo\n");
            }
        } else {
            motor_level -= MOTOR_STEP; // Decrementa o nível PWM
            if (motor_level <= MOTOR_LEVEL_0) {
                increasing = 1; // Inverte a direção ao atingir o limite inferior
                printf("Mudança de direção: aumentando\n");
            }
        }
        sleep_ms(10); // Pequeno atraso para suavizar a movimentação do servo
    }
}

int main() {
    stdio_init_all(); // Inicializa a entrada e saída padrão
    pwm_setup(); // Configuração inicial do PWM
    printf("SERVO INICIADO\n");

    // Testa diferentes posições do servo motor
    set_motor_position(MOTOR_LEVEL_180, "180 GRAUS");
    set_motor_position(MOTOR_LEVEL_90, "90 GRAUS");
    set_motor_position(MOTOR_LEVEL_0, "0 GRAUS");

    motor_sweep(); // Inicia a varredura contínua do servo
    return 0;
}
