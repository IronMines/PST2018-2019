#!/bin/bash
# Script to download the folder with all files to run PharoThings on Raspbian
# To use: wget -O - http://pharo.allexoliveira.com.br/hackaton/install.sh | bash

wget http://pharo.allexoliveira.com.br/hackaton/pharo-iot.zip

unzip pharo-iot.zip

#rm -rf pharo-iot.zip
cd pharo-iot

chmod +x pharo-ui.sh
chmod +x pharo-line.sh
chmod +x pharo-enable-all.sh
chmod +x pharo-enable-i2c.sh
chmod +x pharo-enable-ssh.sh
chmod +x pharo-enable-pharo-autoinit.sh
chmod +x pharo
chmod +x lib/pharo/5.0-201804182009/pharo

exit