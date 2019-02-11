# __Installation de Raspbian Stretch PhaROS__


## Présentation :

[Téléchargement de Raspbian sur le site offficiel de Raspberry Pi ](https://downloads.raspberrypi.org/raspbian_lite_latest)


## Image toute faite du système :

1. Téléchargement de l'image [Raspbian + Pharo things + ROS kinetic]()
  - Sha256sum Raspbian_pharoIOT_ROS.gz : 252c9e6012a4c4beb50354b6fcdca461f9aa6b546e96ef0fd5b097c221f194fe
2. Décompression et installation sur une carte_sd l'image :
  ```
  gzip -cd Raspbian_pharoIOT_ROS.gz | dd of=/dev/mmcblk0 status=progress
  ```
3. Ajuster la taille de la partition ext4 sur l'ensemble de l'espace libre de la carte SD
4. Mettre la carte SD dans la Raspberry, l'installation est fini.

## Information diverse

1. Commande pour activer le hotspot WiFi :
  ```
  # La raspberry redémarre automatiquement après
  $ sudo hotspot-enable
  ```

  Information sur le hotspot WiFi :
    - SSID : ClubRobot
    - PWD : robotrobot59

2. Commande pour désactiver le hotspot -et activer le WiFi- :
  ```
  # La raspberry redémarre automatiquement après
  $ sudo hotspot-disable
  ```
3. Le processus lié à l'image Pharo IOT
  ```
  # Démarrer l'image
  $ sudo sytemctl start pharoIOT

  # Arreter l'image
  $ sudo sytemctl start pharoIOT

  # Lancer l'image à chaque démarrage
  $ sudo sytemctl enable pharoIOT

  # Arréter l'image à chaque démarrage
  $ sudo sytemctl disable pharoIOT

  # Le status de l'image Raspbian_pharoIOT
  $ systemctl status pharoIOT

  ```

## Installation sur une carte SD : Toutes les étapes que j'ai réalisé pour arriver à l'image ci-dessus

1. En ligne de commande :

  - En remplacant l'image de Raspbian par le bon nom de fichier et le chemin
  - Idem pour la carte SD -souvent /dev/mmcblk0
  - status=progress permet d'afficher l'état de chargement de l'image sur la carte SD

  `$ sudo dd bs=4M if=image_de_raspbian.img of=carte_sd conv=fsync status=progress`

2. Graphiquement sous linux :

  - On utilise gnome disk utility (Par défaut sous Ubuntu 16.04 et ultérieur)

3. Sous Windows :

  - Etcher
  - Rufus

## On configure les réseaux WiFi que l'on souhaite utiliser :

Pour ajouter les réseaux sur lesquelles on veut que la Raspberry Pi puisse se connecter, on édite le fichier : `$ vi /etc/wpa_supplicant/wpa_supplicant.conf`

```
network={
    ssid="testing"
    psk="testingPassword"
}
```
__Remarque :__ On peut définir les réseaux WiFi sur lesquelles on veut se connecter avant de mettre la carte SD dans la Raspberry Pi. Par exemple, on peut utiliser son PC portable comme routeur : faire un partage de connexion.

1. On édite le fichier dans `etc/wpa_supplicant/wpa_supplicant.conf` qui se trouve sur la seconde partition de la carte SD : `rootfs`

2. On ajoute un fichier via la commande`$ touch ssh` dans la partitiion : `boot` pour activer le service SSH et ne pas avoir à utiliser de clavier / écran dès le premier démarrage de la Raspberry Pi.

3. On veut connaître l'adresse IP prise par la Raspberry Pi sur notre point d'accès. Pour cela il nous faut connaître la plage d'adresse IP possible :
  - `$ ip addr show` ou `$ ip a` ou `ifconfig`
  - Une fois qu'on connaît l'adresse IP de notre machine : par exemple 10.42.0.1/24 (par défaut sous Ubuntu)
  - `$ nmap -sP IP_connu/Masque` donc avec l'exemple : `$ nmap -sP 10.42.0.1/24` va nous donner l'ensemble des adresses IP utilisé sur le réseau, ce qui va nous permettre de savoir l'adresse IP de la Raspberry Pi.

4. Une fois l'adresse IP de la Raspberry Pi connu, on se connecte en ssh :
  - Login : pi
  - Mot de passe par défaut : raspberry

## Configuration pour utiliser dérière un proxy :

On ajout du proxy dans : `$ sudo vi /etc/environnement`
```
export http_proxy=http://'addr':'port'
export https_proxy=http://'addr':'port'
```

On ajout du proxy dans : `$ sudo vi /etc/apt/apt.conf.d/proxyIMT.conf`
```
Acquire::http::proxy "http://'addr':'port'";
Acquire::https::proxy "http://'addr':'port'";
```

On modifie les paramètres du proxy dans : `$ sudo vi /etc/wgetrc`
```
http_proxy = http://'addr':'port'/
https_proxy = http://'addr':'port'/
ftp_proxy = http://'addr':'port'/

use_proxy = on
```

## Configuration d'une connexion filaire avec IP fixe

Par défaut tout est en DHCP, si on veut une IP fixe :
Modification du fichier de configuration : `$ sudo vi /etc/network/interfaces`

```
# eth0 pour l'éthernet ou wlan0 pour le WiFi

auto eth0
#iface eth0 inet dhcp

iface eth0 inet static
    address 'IP'
    netmask 'Masque'
    gateway 'adresse de la passerelle'
```

## Installation de Pharo IOT dessus :

```
# On télécharge le script d'installation de Allex Oliveira et on l'installe
$ wget -O - http://pharo.allexoliveira.com.br/hackaton/install.sh | bash

# On installe Wiring Pi
$ sudo apt install wiringpi

# On modifie le fichier pharo-line.sh

# On exécute ./pharo-line.sh // modification à faire
```

## Création d'un fichier Systemd pour lancer l'image pharo en tant que service

// à rédiger

## Installation d'un hotspot + samba pour accéder facilement au contenu de la raspi

- On déplace le fichier hotspotWiFi.sh vers la Raspberry Pi
- `$ sudo chmod +x hotspotWiFi.sh`
- `$ sudo ./hotspotWiFi.sh`


## Installation de ROS on Raspbian Stretch

[Documentation en ligne ](http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Kinetic%20on%20the%20Raspberry%20Pi)

### Les prérequis :

1. Setup ROS Repositories :
  ```
  $ sudo apt-get install dirmngr
  $ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

  # Si on est dérière un proxy : en remplacant par l'adresse du proxy et son port !  
  $ sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --keyserver-options http-proxy=http://AddrProxy:Port --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

  # Sinon :
  sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
  ```

2. Install Bootstrap Dependencies

  ```
  $ sudo apt-get install -y python-rosdep python-rosinstall-generator python-wstool python-rosinstall build-essential cmake
  ```
3. Initializing rosdep

  ```
  $ sudo rosdep init
  $ rosdep update
  ```

### Installation

1. Create a catkin Workspace
  ```
  $ mkdir -p ~/ros_catkin_ws
  $ cd ~/ros_catkin_ws
  ```
2. ROS-Comm: (recommended)
  ```
  $ rosinstall_generator ros_comm --rosdistro kinetic --deps --wet-only --tar > kinetic-ros_comm-wet.rosinstall
  $ wstool init src kinetic-ros_comm-wet.rosinstall
  ```

  __Remarque :__ If wstool init fails or is interrupted, you can resume the download by running:
  ```
  $ wstool update -j4 -t src
  ```
3. Resolve Dependencies
  ```
  $ mkdir -p ~/ros_catkin_ws/external_src
  $ cd ~/ros_catkin_ws/external_src
  $ wget http://sourceforge.net/projects/assimp/files/assimp-3.1/assimp-3.1.1_no_test_models.zip/download -O assimp-3.1.1_no_test_models.zip
  $ unzip assimp-3.1.1_no_test_models.zip
  $ cd assimp-3.1.1
  $ cmake .
  $ make
  $ sudo make install
  ```
  __Remarque :__ If you have problems, you can skip collada_urdf using the following generator:
  ```
  $ rosinstall_generator desktop --rosdistro kinetic --deps --wet-only --exclude collada_parser collada_urdf --tar > kinetic-desktop-wet.rosinstall
  ```
4. Resolving Dependencies with rosdep
  ```
  $ cd ~/ros_catkin_ws
  $ rosdep install -y --from-paths src --ignore-src --rosdistro kinetic -r --os=debian:stretch
  ```
5. Building the catkin Workspace

  ```
  $ sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/kinetic -j2

  $ source /opt/ros/kinetic/setup.bash

  $ echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
  ```

### Maintaining a Source Checkout

[Go to the web site part 4.](http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Kinetic%20on%20the%20Raspberry%20Pi)

Pour installer d'autre outils ou module ROS

## Export de l'image de la carte_sd vers un fichier compressé :

```
$ sudo dd if=/dev/mmcblk0 status=progress | gzip -c > Raspbian_pharoIOT_ROS.gz
```
