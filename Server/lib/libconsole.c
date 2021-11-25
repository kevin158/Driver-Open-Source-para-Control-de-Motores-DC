#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

char *portname = "/dev/ttyUSB0";
int fd;
int wlen;

int setAttributes(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int initComm(){
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    setAttributes(fd, B9600);
    return 0;
}

int sendCommand(const char* str, int size){
    wlen = write(fd, str, size);
    if (wlen != size) {
        printf("Error from write: %d, %d\n", wlen, errno);
        return -1;
    }
    tcdrain(fd);
    return 0;
}

int waitAnswer(){
    do {
        unsigned char buf[80];
        int rdlen;

        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            buf[rdlen] = 0;
            printf("|%s|\n", buf);
            if( strncmp(buf, "Done", 4) == 0){
                usleep (500000);
                return 0;
            }
        }
    } while (1);
}

int getSize(char *msg){
    int size = 0;
    while(msg[size]!='\n')size++;
    return size+1;
}

void moveRight(){
    int  commandLen = 32;
    char command[commandLen];

    sprintf(command, "right");
    sendCommand(command,getSize(command));
    waitAnswer();
}

void moveLeft(){
    int  commandLen = 32;
    char command[commandLen];

    sprintf(command, "left");
    sendCommand(command,getSize(command));
    waitAnswer();
}

void moveUp(){
    int  commandLen = 32;
    char command[commandLen];

    sprintf(command, "up");
    sendCommand(command,getSize(command));
    waitAnswer();
}

void moveDown(){
    int  commandLen = 32;
    char command[commandLen];

    sprintf(command, "down");
    sendCommand(command,getSize(command));
    waitAnswer();
}

void verifyDevice(){
    int  commandLen = 32;
    char command[commandLen];

    sprintf(command, "check");
    sendCommand(command,getSize(command));
    waitAnswer();
}