# Le code pharo du robot

## Installation de l'image Remote (sur le PC) :

```smalltalk
"Installation"

Metacello new
  baseline: 'PharoThings';
  repository: 'github://pharo-iot/PharoThings/src';
  load: #(RemoteDevServer Raspberry).

ClySystemEnvironmentPlugin disableSlowPlugins.

Metacello new
  baseline: 'TelePharo';
  repository: 'github://dionisiydk/TelePharo';
  load: 'Server'.

TlpRemoteUIManager registerOnPort: 40423.
TlpRemoteUIManager unregister.

Metacello new
  baseline: 'PharoThings';
  repository: 'github://pharo-iot/PharoThings/src';
  load: 'RemoteDev'.

Metacello new
  baseline: 'TelePharo';
  repository: 'github://dionisiydk/TelePharo';
  load: 'Client'.
```

## Connexion à la carte distant et accès aux outils de developpement :

```smalltalk
remotePharo := TlpRemoteIDE connectTo: (TCPAddress ip: #[192 168 102 1] port: 40423).

"Control du GPIO"
remoteBoard := remotePharo evaluate: [ RpiBoard3B current].
remoteBoard inspect.

"Ouvrir les outils de développement distant : "
remotePharo openBrowser.
remotePharo openTranscript.
remotePharo openPlayground.

"Sauvegarder l'image distant"
remotePharo saveImage.

"Faire une copie en local des changements fait sur la Raspberry :"
remotePharo applyChangesToClient.

"Arrêter le serveur"
remotePharo applyChangesToClient
```

## Exemple de code pour communiquer avec les ports GPIO

Allumer et éteindre un pin GPIO
```smalltalk
rpi := RpiBoard3B current.

led := PotPwmGPIOPin id:18.
led board: rpi.
led beDigitalOutput.
led number: 1.
led position: 2@6.
led value: 1.

led value: 0.

led writePWMValue: 100.

[100 timesRepeat: [
	led value:0.
	(Delay forMilliseconds: 100 )wait.
	led value: 1.
	(Delay forMilliseconds: 100 )wait. ]]fork.
```
Envoyer un caractère via i2c

```smalltalk
board := RpiBoard3B current.
i2cConnection := board connectToI2CDevice: 16r12.

test := test := 'MVTN', ';' ,10 asString.
test2 := test asByteArray.
i2cConnection writeData: test2 size.
test2 do: [ :each | i2cConnection writeData: each ].
```


Pour la lecture tester :
```
read8BitsArray: blockSize startingAt: reg

board := RpiBoard3B current.
i2cConnection := board connectToI2CDevice: 16r12.
i2cCapteur := board connectToI2CDevice: 16r8.
test := i2cCapteur read8BitsAt:200.


test2 := test asByteArray.
test2
```


Récupérer les données des capteurs :
```
board := RpiBoard3B current.
i2cCapteur := board connectToI2CDevice: 16r8.
envoi := 'UAvDr' asByteArray.
"envoi := 'UAvGa' asByteArray."
i2cCapteur writeData: envoi size.
envoi do: [ :each | i2cCapteur writeData: each] .
test := i2cCapteur read8BitsAt:1.
test asByteArray.
test2 := i2cCapteur read16BitsAt:1.
test2 asByteArray.
res := (test asByteArray at:1) + (test asByteArray at:2) + 1.
```
