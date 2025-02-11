# Controle de Servo Motor com Raspberry Pi Pico 🚀
Link vídeo: https://youtu.be/fI2V2_3sOXI

Este projeto implementa o controle de um servo motor utilizando um sinal PWM gerado pelo microcontrolador **Raspberry Pi Pico**. O código é escrito em **C** e faz uso da biblioteca **Pico SDK** para configurar e operar o PWM.

## 📌 Funcionalidades

- Geração de sinal **PWM** para controle de servo motor.
- Movimento automático do servo entre **0°**, **90°** e **180°**.
- Alternância suave entre os ângulos com incremento/decremento progressivo.
- Comunicação serial para depuração e acompanhamento do funcionamento.

## 🛠️ Configuração do Hardware

- **Microcontrolador**: Raspberry Pi Pico
- **Servo Motor**: Qualquer servo compatível com controle PWM (ex: SG90, MG995)
- **Conexões**:
  - Sinal PWM: GPIO **22** do Pico
  - Alimentação: **5V** (Vbus) ou **3.3V** dependendo do servo
  - GND: GND do Pico

## 📝 Dependências

- **Raspberry Pi Pico SDK**
- **Compilador ARM GCC**
- **CMake**

## 🚀 Como Compilar e Executar

1. Clone este repositório:
   ```bash
   git clone https: https://github.com/Gabriellacerdaaa/ATIVIDADE_PWM.git
   cd seu-repositorio
   ```

2. Configure o ambiente **Pico SDK**:
   ```bash
   export PICO_SDK_PATH=/caminho/para/pico-sdk
   ```

3. Compile o projeto:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. Carregue o firmware no Raspberry Pi Pico:
   - Conecte o **Pico** ao PC enquanto pressiona o botão **BOOTSEL**.
   - Copie o arquivo `.uf2` gerado para o dispositivo montado.


## 📜 Licença

Este projeto é distribuído sob a licença **MIT**. 

---
AUTOR: Gabriel Santos Lacerda

