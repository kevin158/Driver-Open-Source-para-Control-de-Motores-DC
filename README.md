# Driver Open Source para Control de Motores DC

## Driver

### Compilar

$ cd Driver

$ sudo ./compile.sh

### Verificación

$ lsmod | grep usb

## Servidor/Biblioteca

### Compilación

$ cd Server

$ make

### Ejecución

$ cd build

$ ./server

## Interfaz grafica

### Instalar Nodejs y ReactJS

https://tecadmin.net/how-to-install-reactjs-on-ubuntu-20-04/

### Instalar dependencias

$ cd UI

$ sudo npm install

### Ejecutar aplicación

$ cd UI

$ npm start