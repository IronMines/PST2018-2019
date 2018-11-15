# Installation de la Raspberry

## Lien vers les projets du DIA : Documentation et Ressources

- [Piros : Ubuntu sur Raspberry avec Ros](https://github.com/CARMinesDouai/MultiRobotExplorationPackages/tree/master/inria_demo)
- [Installation de Pharo sur Raspberry : github](https://github.com/pharo-ide/TelePharo)

## Installation de Piros

* En ligne de commande sur linux : `sudo dd bs=4M if=piros.img of=/dev/mmcblk0 conv=fsync`
  * `if=piros.img` : correspond à l'emplacement du fichier `.img` pour installer piros
  * `of=/dev/mmcblk0` : correspond au point de montage de la carte
* On met la carte sd dans la Raspberry ce qui démarre l'installation
* Le clavier par défaut sur la Raspberry est en QWERTY !
  * `sudo loadkeys fr` : pour changer la langue jusqu'au prochain redémarrage
* Il faut changer les paramètres de connexion de la Raspberry :
  * `sudo vi /etc/wpa_supplicant/wpa_supplicant.conf` : on change les paramètres de connexion au wifi
  * `sudo vi /etc/network/interfaces` : on change les paramètres d'adressage IP
  * `sudo vi /etc/apt/apt.conf` : On modifie -ou supprime- les paramètres du proxy
* Faire les mises à jour :
  * `sudo apt-get update`
  * `sudo apt-get upgrade`

## Installation de pharo sur la Raspberry

* En cours ... 
