#!/bin/bash

# ==================================== Description du script ==================
# Ce script met à jour Raspbian, et il installe et configure les logiciels et
# et services utile pour la sonde de l'hydradrone.
# Avec ce script, la Raspberry pourra émettre un hotspot wifi,
# un partage réseau pour récuperer facilement les données de la sonde stockées localement,
# installe les bibliothèque utile pour faire tourner le programme python de la sonde,
# Et préconfigure le fichier de service pour le programme python de la sonde.

# Coté développeur, ce script ajoute 2 commandes supplémentaire :
# hotspot-disable et hotspot-enable qui permettent d'activer et désactiver la fonction hotspot
# de la Raspberry
#=============================================================================

if [ $USER = "root" ]
then

echo "Démarrage du script, ne vous inquiétez pas, tout va bien, ça prend du temps ... ;)"
#mise a jour de la raspberry sur la version actuel (pas d'upgrade)
sudo apt update -yqq
sudo apt upgrade -yqq

#installation de paquet et logiciel nécessaire ou utile à la maintenance de la carte
sudo apt install samba samba-common-bin -yqq

#installation des services permettant de faire un hotspot wifi (hostapd) et le service dns et dhcp associé (dnsmasq) :
sudo apt install hostapd dnsmasq -yqq

#configuration du service samba :

#sauvegarde du fichier initial :
sudo mv /etc/samba/smb.conf /etc/samba/smb.conf.orig

#création du nouveau fichier de configuration :
sudo cat > /etc/samba/smb.conf <<EOF
[global]

    workgroup = WORKGROUP
    security = user
    passdb backend = tdbsam
    server role = standalone server
    map to guest = bad user
    #min protocol = SMB2

#======================== Share Definitions ====================

[pharoIOT]
    comment = access to pharo vm
    browseable = yes
    path = /opt/pharo-iot
    read only = no
    writable = yes
    create mask = 0777
    directory mask = 0777
    valid users = pi

EOF

#on redemarre le service
sudo /etc/init.d/samba restart

#configuration du hotspot wifi hydradrone

#sauvegarde de fichier de config
sudo cp /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo cp /etc/hostapd/hostapd.conf /etc/hostapd/hostapd.conf.orig
sudo cp /etc/network/interfaces /etc/network/interfaces.orig
sudo cp /etc/default/hostapd /etc/default/hostapd.orig
sudo cp /etc/dhcpcd.conf /etc/dhcpcd.conf.orig

#modification des fichiers de config

sudo cat > /etc/dnsmasq.conf <<EOF
interface=wlan0
dhcp-range=192.168.102.2,192.168.102.6,255.255.255.248,6h
EOF

sudo cat > /etc/hostapd/hostapd.conf <<EOF
interface=wlan0
hw_mode=g
channel=10
auth_algs=1
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_pairwise=CCMP
rsn_pairwise=CCMP
wpa_passphrase=robotrobot59
ssid=ClubRobotique2
ieee80211n=1
wmm_enabled=1
ht_capab=[HT40][SHORT-GI-20][DSSS_CCK-40]
EOF

sudo sed -i -- 's/allow-hotplug wlan0//g' /etc/network/interfaces
sudo sed -i -- 's/iface wlan0 inet manual//g' /etc/network/interfaces
sudo sed -i -- 's/    wpa-conf \/etc\/wpa_supplicant\/wpa_supplicant.conf//g' /etc/network/interfaces
sudo sed -i -- 's/#DAEMON_CONF=""/DAEMON_CONF="\/etc\/hostapd\/hostapd.conf"/g' /etc/default/hostapd

sudo cat >> /etc/network/interfaces <<EOF
# Added by rPi Access Point Setup
allow-hotplug wlan0
iface wlan0 inet static
	address 192.168.102.1
	netmask 255.255.255.248
	network 192.168.102.0
	broadcast 192.168.102.7
EOF

echo "denyinterfaces wlan0" >> /etc/dhcpcd.conf

sudo systemctl enable hostapd
sudo systemctl enable dnsmasq

sudo service hostapd start
sudo service dnsmasq start


#Création du service probe, le programme de la sonde démarre comme un service !

sudo cat >> /etc/systemd/system/pharoIOT.service <<EOF
[Unit]
Description=Pharo IOT
After=autologin@.service

[Service]
Type=simple
ExecStart=/opt/pharo-iot/pharo --nodisplay /home/pi/pharo-iot/Pharo6.1-IoT.image remotePharo --startServerOnPort=40423
Restart=always
RestartSec=0

[Install]
WantedBy=multi-user.target
EOF

#création des commandes linux pour activer ou désactiver le hotspot

#fichier nécessaire
sudo cp /etc/network/interfaces /etc/network/interfaces.hotspot
sudo cp /etc/dhcpcd.conf /etc/dhcpcd.conf.hotspot

#commande hotspot-enable
sudo cat > /opt/hotspot-enable.sh <<EOF
#!/bin/bash
echo
echo "Hotspot-enable"
echo "Cette commande active le hotspot avant de redémarrer la Raspberry"
echo

confirm()
{
    read -r -p "\${1} [y/N] " response

    case "\$response" in
        [yY][eE][sS]|[yY])
            true
            ;;
        *)
            false
            ;;
    esac
}

if confirm "Etes-vous sûr ?"; then
  sudo systemctl stop dhcpcd

  sudo cp /etc/network/interfaces.hotspot /etc/network/interfaces
  sudo cp /etc/dhcpcd.conf.hotspot /etc/dhcpcd.conf

  sudo systemctl start hostapd
  sudo systemctl start dnsmasq
  sudo systemctl enable hostapd
  sudo systemctl enable dnsmasq
  sudo reboot
else
    echo "Command canceled"
fi

EOF

#commande hotspot-disable

sudo cat > /opt/hotspot-disable.sh <<EOF
#!/bin/bash
echo
echo "Hotspot-disable : "
echo "Cette commande va désactiver le hotspot ClubRobotique2 et réactiver le wifi \"classique\" après un redémarrage"

confirm()
{
    read -r -p "\${1} [y/N] " response

    case "\$response" in
        [yY][eE][sS]|[yY])
            true
            ;;
        *)
            false
            ;;
    esac
}

if confirm "Etes-vous sûr ?"; then
  sudo systemctl stop hostapd
  sudo systemctl stop dnsmasq
  sudo systemctl disable hostapd
  sudo systemctl disable dnsmasq

  sudo systemctl stop dhcpcd

  sudo cp /etc/network/interfaces.orig /etc/network/interfaces
  sudo cp /etc/dhcpcd.conf.orig /etc/dhcpcd.conf

  sudo systemctl start dhcpcd
  sudo reboot
else
    echo "Command canceled"
fi

EOF


sed -i -e "s/^##//g" /opt/hotspot-disable.sh



sudo chmod 755 /opt/hotspot-disable.sh
sudo chmod 755 /opt/hotspot-enable.sh

sudo ln -s /opt/hotspot-disable.sh /usr/local/bin/hotspot-disable
sudo ln -s /opt/hotspot-enable.sh /usr/local/bin/hotspot-enable



#le fichier du nouveau service est créé, il faudra après redémarrage et déplacement des fichiers, lancer le service avec la commande suivante :
#sudo systemctl enable probe.service


echo "Le script est terminé, s'il n'y a pas d'erreur. Il reste à :
1. Ajouter un mot de passe pour samba pour l'utilisateur pi : sudo smbpasswd -a pi
2. Activer le démarrage du service de la sonde au démarrage : sudo systemctl enable pharoIOT.service
3. Redémarrer la carte Raspberry pi : sudo reboot"

else
  echo "Vous n'avez pas lancé ce script en tant que \"root\", merci de relancer la commande "
fi
