# AUTONOMOUS_EMBEDDED_CONTROL
<br> Send frame to car using UART containes of 8-bits:
<br> First 3-bits  --> Speed of DC Motor [0 --> 100]
<br> Bit_4         --> Direction of DC Motor [F or f or B or b]
<br> Bit_5 & Bit_6 --> Angle of Stepper Motor [0 --> 45]
<br> Bit_7         --> Direction of Stepper Motor [R or r or L or l]
<br> Bit_8         --> End of frame [E or e]
<br> Then display Data on the Dash Board 
