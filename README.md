# STM32F446RE Bare-Metal USART2 Transmit & Receive (Echo) Driver

A complete register-level Bare-Metal C implementation for bidirectional asynchronous serial communication (USART2 TX and RX) on the STM32F446RE microcontroller without using HAL libraries.

---

## 📌 Technical Highlights

* *Pure Bare-Metal C:* Direct register manipulation (Memory-Mapped Registers) for peripheral clock, GPIO mode, and baud rate control.
* *Full-Duplex UART Communication:* Configured both Transmitter (TX) and Receiver (RX) channels on USART2.
* *Alternate Function Mapping:* 
  * PA2 configured as USART2_TX (AF7)
  * PA3 configured as USART2_RX (AF7)
* *Baud Rate Calculation:* Dynamic baud rate divider computation configured for 115200 bps at a 16 MHz APB1 peripheral clock.
* *Polling Architecture:* Utilizes status register flags (SR_TXE and SR_RXNE) for synchronous byte transmission and reception.

---

## 🛠️ Pin Configuration & Hardware

* *Microcontroller:* STM32F446RE (ARM Cortex-M4)
* *Peripheral:* USART2, GPIOA, RCC
* *Baud Rate:* 115200 bps
* *Pins Used:*
  * PA2 -> USART2_TX
  * PA3 -> USART2_RX

---

## 📁 Repository Structure

* main.c - Core driver code containing initialization routines (uar2_tx_init, uart_rx_init), baud rate configuration logic, read/write functions, and the main echo loop.
*
