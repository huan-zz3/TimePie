#include "serialib.h"
#define SERIAL_PORT "/dev/ttyS3"
int main(/*int argc, char *argv[]*/)
{
    // Serial object
    serialib serial;

    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT, 115200);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1)
        return errorOpening;
    printf("Successful connection to %s\n", SERIAL_PORT);

    // Create the string
    char buffer[15] = "hello\n";

    // Write the string on the serial device
    serial.writeString(buffer);
    printf("String sent: %s", buffer);

    // Read the string
    serial.readString(buffer, '\n', 14, 2000);
    printf("String read: %s\n", buffer);

    // Close the serial device
    serial.closeDevice();

    return 0;
}