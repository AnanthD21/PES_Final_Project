# Digital Angle Gauge

As proposed in the PDR, digital Angle gauge has been implemented adhering to PDR. The tilt angle has been measured using on chip sensor MMA8451.
In order to accomplish this task a state machine has been implemented as shown below.

![stateMachine drawio](https://user-images.githubusercontent.com/89766346/145932161-b80dcb32-2518-40d5-aba2-82e2af1b1768.png)

Also, serial terminal has been utilised to interact with user. The serial terminal settings are shown in the below screenshot.

![Com_settings](https://user-images.githubusercontent.com/89766346/145932368-ab277a27-fed7-4704-bc5e-6a2be7e0e1a7.PNG)

NOTE: The tilt angle displayed is the relative angle with respect to that of angle measured at the time of calibration. Thus if angle at calibration is 30 degrees, then if the tilt angle displayed is 20 degrees, then this implies that, board is at 50 degrees with respect to ground.

For further information please refer to testDocs_PDR_ComSnapshot_DemoVideo folder, this contains PDR, state machine diagram document, Manual test document, Demo video and PortD pin3 GPIO pin screenshot.
