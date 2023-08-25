# AUTONOMOUS_EMBEDDED_CONTROL
Send frame to car using UART containes of 8-bits:
First 3-bits  --> Speed of DC Motor [0 --> 100]
Bit_4         --> Direction of DC Motor [F or f or B or b]
Bit_5 & Bit_6 --> Angle of Stepper Motor [0 --> 45]
Bit_7         --> Direction of Stepper Motor [R or r or L or l]
Bit_8         --> End of frame [E or e]
Then display Data on the Dash Board 
