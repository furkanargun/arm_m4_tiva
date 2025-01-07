# arm_m4_tiva
This repository contains projects developed for the TM4C123GH6PM microcontroller, showcasing various embedded systems applications.

The projects include:

- Project 1: LCD Display - Displaying Character
    This project involves configuring an LCD display to show the character 'A'. It uses the TM4C123GH6PM microcontroller and various libraries to initialize the system and control the LCD.

Key Features:

    Initializes the microcontroller clock.
    Configures the LCD for displaying characters.
    Displays the character 'A' on the first row, seventh column of the LCD.

The main function calls the initialization functions for the system and LCD, then writes the character 'A' to the display.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Project 2: Digital Clock - Hour, Minute, and Second Display
    This project uses the TM4C123GH6PM microcontroller to implement a simple digital clock. The clock displays the current time in hours, minutes, and seconds on an LCD display, updating every second.

Key Features:

    Configures the microcontroller clock and sets up a timer for 1-second intervals.
    Uses an interrupt service routine to increment seconds, minutes, and hours.
    Displays the current time in the format hh:mm:ss on the second row of the LCD.

The timer interrupt function is responsible for updating the clock every second. The current time is shown on the LCD in the 2nd row, starting from the 8th column.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Project 3: UART Communication with LCD - Time Parsing and Display
    This project uses UART communication to send and receive time data to and from a microcontroller. It displays the received time on an LCD and also periodically sends the current time via UART. The main components include:

    UART Communication: The microcontroller receives time data in the format hh:mm:ss from an external device and sends time updates.
    LCD Display: The LCD shows the received or current time in the format hh:mm:ss on the second row.
    Timer Interrupt: A timer interrupt is used to increment seconds, minutes, and hours and periodically update the displayed time on the LCD and send the time via UART.

Key Features:

    UART Reception:
        The microcontroller receives time data in the format hh:mm:ss (sent with $ markers).
        The data is parsed and the time is updated.
    LCD Display:
        Displays time on the LCD in hh:mm:ss format, updating each second.
        Shows data received from the UART interface if the data is formatted correctly.
    Periodic UART Transmission:
        The current time is periodically sent over UART.
        Time is also displayed on the LCD with each update.

Main Functions:

    uart_ayari(): Configures UART for communication.
    serikesme(): UART interrupt service routine to read incoming data.
    parseData(): Parses the received data to update the clock or display messages.
    saatiGonder(): Periodically sends the current time via UART.
    timerkesmefonksiyonu(): Timer interrupt function to update the time every second.
    SetInitSettings(): Initializes the timer and other peripherals.

The program reads incoming time in the format hh:mm:ss from UART, updates the internal time and LCD display, and sends periodic updates of the current time back via UART.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Project 4: UART Communication and ADC with LCD Display
    This project involves configuring the TM4C123GH6PM microcontroller to communicate via UART, handle ADC conversions, and display the results on an LCD screen. It also handles timekeeping and displays the time on the LCD.

Key Features:

    Configures the microcontroller's system clock, UART communication, and ADC for reading analog values.
    Uses an interrupt service routine to handle UART data reception and process incoming commands.
    Displays incoming data on the LCD, including text and time information.
    Periodically updates the time (hour, minute, second) and displays it on the LCD.
    Reads an analog input (connected to port E3) using the ADC and sends the value over UART.
    Implements a timer-based system for triggering ADC conversions every second.
    Handles the received UART data, parses it, and updates the LCD or internal settings accordingly.

The main function initializes the system and peripherals, including UART, ADC, and the LCD. It then enters a continuous loop, waiting for UART data or other events. The program processes incoming data, updates the LCD with relevant information, and manages the timekeeping mechanism.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Project 5: Hibernation Mode Implementation for Low Power Consumption
    This project demonstrates how to implement hibernation mode on the TM4C123GH6PM microcontroller to achieve low power consumption. Hibernation mode allows the system to enter a deep sleep state where most of the system's peripherals are powered off, with the exception of the RTC (Real-Time Clock) and the wake-up sources, such as GPIO or RTC.

Key Features:

    Configures the system clock for efficient power usage.
    Enables the Hibernate module and configures the RTC (Real-Time Clock) to wake the system after a set time period (10 seconds in this case).
    Sets up GPIO and RTC as wake-up sources for the system.
    The microcontroller enters hibernation mode with minimal power consumption while maintaining the ability to wake up based on configured events.

The main function initializes the system and peripherals, then requests the microcontroller to enter hibernation mode. The program remains in the hibernation state until the configured wake-up conditions are met.
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- Project 6: Floating Point Operations for Advanced Mathematical Computations
    This project demonstrates how to use the Floating Point Unit (FPU) of the TM4C123GH6PM microcontroller to perform advanced mathematical computations. The FPU allows for efficient and precise floating-point calculations, making it suitable for applications that require operations like addition, subtraction, multiplication, division, and square root calculations.

Key Features:

    Configures the system clock for optimized performance.
    Enables and configures the Floating Point Unit (FPU) to handle floating-point operations.
    Performs basic mathematical operations such as addition, subtraction, multiplication, division, and square root calculation.
    Implements floating-point computations with improved precision, thanks to the FPU, which supports operations on floating-point numbers.

The ConfigureFPU function enables the FPU and configures it to handle advanced mathematical computations, including rounding modes and support for subnormal numbers. The PerformMathOperations function performs a series of floating-point calculations with two sample numbers, num1 and num2.

The calculations include:

    Addition: Adds two floating-point numbers.
    Subtraction: Subtracts two floating-point numbers.
    Multiplication: Multiplies two floating-point numbers.
    Division: Divides two floating-point numbers.
    Square Root: Computes the square root of a floating-point number.

This project demonstrates the use of the FPU to efficiently perform mathematical operations on floating-point values in embedded systems.

All files are organized under the 'Projeler' directory with appropriate project subfolders.
