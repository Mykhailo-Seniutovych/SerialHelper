# SerialHelper
This is a small program that automate some tasks for reading/writing serial data in Linux.
It can be useful for microcontrollers programming, when you want to automate some tasks of sending and receiving UART data
from you microcontroller that you connect to your PC through UART to USB adapter. 

Things it can do:
- Continuously send the data to a serial port (most other terminal emulators, so you need to manually click send every time you want to send some data)
- You can set the bytes you want to send in HEX format, each byte, or series of bytes can have a label. 
This might be useful, when you have some protocol of communication with your MCU so each byte represents something.
Having a labeling mechanism can help you to comprehend the message you're sending and receiving more easily
