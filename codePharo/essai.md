# Essai de code :

## Allumer ou éteindre un GPIO :

```
rpi := RpiBoard3B current.

led := PotPwmGPIOPin id:18.
led board: rpi.
led beDigitalOutput.
led number: 1.
led position: 2@6.
led value: 1.

```
