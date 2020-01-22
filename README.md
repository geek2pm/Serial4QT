# Serial4QT

a simpleSerial tools base on Qt Serial Port 

## install qt5

```
sudo apt-get install build-essential qtcreator qt5-default qttools5-dev-tools qttools5-dev qtbase5-private-dev
```

## install  qtserialport

clone qtserialport

```
git clone git://code.qt.io/qt/qtserialport.git
cd qtserialport
```

get qt5 version

```
qmake -v
```

return like this:

```
QMake version 3.1 Using Qt version 5.9.5 in /usr/lib/x86_64-linux-gnu
```

so the version is 5.9.5

check out for this version

```
git checkout v5.9.5
```

make && make install

```
mkdir qtserialport-build
cd qtserialport-build
qmake ../qtserialport.pro
make
sudo make install
```

### clone and run

```
git clone https://github.com/geek2pm/Serial4QT.git
cd Serial4QT
sudo ./Serial4QT
```


