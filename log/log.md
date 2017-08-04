# Activities Logging

### Friday 4th August 

#### Hardware

Raspi -> Arduino -> H Bridge -> 1 Motor

#### Software 

First time that we trigger a command from the keyboard on the mac received by the raspi by ssh and transmitted by
Serial connection to arduino board which in turn switched rotation of the motor.

This was enabled after installing the arduino IDE on the raspi with 
 
```shell
sudo apt-­get install arduino
```

and the python serial library to send data from a python script on the raspi.

```shell
sudo apt-get install python-serial
```

