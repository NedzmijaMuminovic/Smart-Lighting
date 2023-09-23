# Smart Lighting Control

## Overview

This project aims to simplify the control of various types of lighting through a smart lighting control system. It utilizes a web application that enables remote management of smart lighting via the internet.

The project consists of three main components:

1. **Control Side**: This is a web application built using HTML and JavaScript.

2. **Execution Side**: The execution side involves a NodeMCU ESP12f equipped with a light-dependent resistor (light sensor) and an LED lamp. The LED lamp serves as a representation of the lighting.

3. **Real-time Database**: The project utilizes Google's Firebase service to create a real-time database that facilitates communication between the control and execution sides.

## Functionality

The system offers the following functionalities:

### Automatic Lighting Control

- Users can set the desired level of room illumination using a slider on the web application.
- The web application communicates the selected illumination level to the real-time database.
- The execution side regularly checks this value and automatically turns the lighting on or off based on the user's threshold.

### Manual Lighting Control

- Users have the option to manually control the lighting.
- The web application provides buttons to enable or disable automatic lighting control.
- When automatic control is disabled, the slider for setting the illumination threshold in automatic mode is deactivated, and a manual slider for adjusting the illumination level is activated. Users can use this slider to increase or decrease the current light level.

### Sensor Data Display

- The web application displays real-time sensor data, showing the current value of the light sensor measuring the room's illumination.
- These sensor values are refreshed every 5 seconds.

## Usage

To use this project, follow these steps:

1. Clone the repository to your local machine.
2. Set up the NodeMCU ESP12f with the necessary components (light-dependent resistor and LED lamp).
3. Configure the Firebase real-time database with your project settings.
4. Deploy the web application to a hosting service or run it locally.

**Note**: Please ensure that you have the required hardware components and understand how to set up and configure the NodeMCU ESP12f and Firebase before using this project.
