#!/bin/bash

cd  VelaBot
make
cd ..
java -jar MancalaNoGUI.jar -p1 ./GreedyBot/GreedyBot -p2 ./VelaBot/VelaBot
