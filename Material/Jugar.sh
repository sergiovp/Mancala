#!/bin/bash

cd VelaBot
make
cd ..
cp ./VelaBot/VelaBot Bots
echo 'Los bots tienen que estar guardados en la carpeta Bots'
ls Bots
echo 'Introduzca el nombre del Bot 1: '
read bot1
echo 'Introduzca el nombre del Bot 2: '
read bot2
java -jar MancalaNoGUI.jar -p1 ./Bots/$bot1 -p2 ./Bots/$bot2
