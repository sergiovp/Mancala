#!/bin/bash

cd VelaBot
make
cd ..
java -jar MancalaNoGUI.jar -p1 ./VelaBot/VelaBot -p2 ./GreedyBot/GreedyBot
