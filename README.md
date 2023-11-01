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

1. **Firebase Configuration:**
    - Set up a Firebase project at [Firebase Console](https://console.firebase.google.com/).
    - Create a real-time database in Firebase.
    - After setting up Firebase, obtain the following information from your Firebase project:
        - Firebase project API Key
        - RTDB URL (Real-Time Database URL)

    If you prefer, you can use my pre-made Firebase project by clicking [here](https://console.firebase.google.com/u/0/project/iot-seminarski-d5dbe/database/iot-seminarski-d5dbe-default-rtdb/data).

2. **Arduino Project Setup:**
    - Set up the NodeMCU ESP12f with the necessary components (light-dependent resistor and LED lamp).
    - Open the Arduino project located in the `Smart-Lighting/arduino/Pametna rasvjeta` directory.
    - Ensure you have the Arduino IDE installed.
    - Connect your NodeMCU ESP12f to your computer.
    - Before uploading the Arduino sketch (`Pametna rasvjeta.ino`) to the NodeMCU ESP12f, make the following changes in the code:

        ```cpp
        // Insert your network credentials
        #define WIFI_SSID "your_wifi_name"
        #define WIFI_PASSWORD "your_wifi_password"

        // Insert Firebase project API Key
        #define API_KEY "your_firebase_api_key"

        // Insert RTDB URL (define the RTDB URL)
        #define DATABASE_URL "your_firebase_database_url"
        ```

    - Upload the modified Arduino sketch to the NodeMCU ESP12f.

4. **HTML Page:**
    - Open the `Smart-Lighting/index.html` file in your preferred web browser.
    - Update the Firebase configuration in the HTML file by modifying the following section:

        ```javascript
        const firebaseConfig = {
          apiKey: "your_api_key",
          authDomain: "your_auth_domain",
          databaseURL: "your_database_url",
          projectId: "your_project_id",
          storageBucket: "your_storage_bucket",
          messagingSenderId: "your_messaging_sender_id",
          appId: "your_app_id",
        };
        ```

**Note**: Please ensure that you have the required hardware components and understand how to set up and configure the NodeMCU ESP12f and Firebase before using this project.
