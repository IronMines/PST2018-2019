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
    * mettre en commentaire toutes les lignes lié à configuration static de la carte wifi
    * `iface wlan0 inet dhcp` : ligne a mettre pour la configuration wifi dynamique
  * `sudo vi /etc/apt/apt.conf` : On modifie -ou supprime- les paramètres du proxy
    * On met en commentaire les deux lignes du proxy si on sur un réseau sans proxy
  * `sudo vi /etc/environment`: idem on modifie -ou supprime- les paramètre du proxy
    * On met en commentaire les deux lignes du proxy si on sur un réseau sans proxy
* Faire les mises à jour :
  * `sudo apt-get update`
  * `sudo apt-get upgrade`

## Installation de pharo sur la Raspberry

### Repository Git à utiliser :
- [TelePharo ](https://github.com/pharo-ide/TelePharo)
- [PharoThings ](https://github.com/pharo-iot/PharoThings)

### Etape d'installation

1. [Téléchargement de pharo ici ]( http://files.pharo.org/vm/pharo-spur32/linux/armv6/latest.zip )
2. Ajout d'une image pharo 6.1 stable 32 bits que l'on prépare avec pharo-laucher
3. on suit les étapes sur la vidéo youtube [Vidéo d'installation pharo + télépharo sur Raspberry](https://www.youtube.com/watch?v=Yys1M0hZIWY) pour préparer l'image pharo en mode serveur.
4. On lance l'image avec la commande : `/opt/pharo/pharo --headless /opt/pharo-vm/CoupeDeFranceRobotiqueRaspberry/ remotePharo --startServerOnPort=40423 --disableSlowPlugins`
5. On fait une nouvelle image pharo avec le laucher __avec la même version !__
6. On suit toujours les étapes de la [Vidéo ](https://www.youtube.com/watch?v=Yys1M0hZIWY)
7. Bug avec wiring Pi : (http://wiringpi.com/download-and-install/)
  * attention au droit linux pour téléchargé le répository


### actuellement

- installation de l'image et de la vm
- il manque la librairie c !
