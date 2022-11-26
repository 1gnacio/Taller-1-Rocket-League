# Taller-1-Rocket-League

## Grupo 1

* **Ignacio Garcia Segovia** - [1gnacio](https://github.com/1gnacio)
* **Nahuel Gomez** - [NahuelNGomez](https://github.com/NahuelNGomez)
* **Iñaki Gonzalez Bigliardi** - [igonzalezb](https://github.com/igonzalezb)

Corrector: Martin

## Manual de usuario

### Introduccion

El presente trabajo consiste en diseniar e implementar una version simplificada en 2D del juego de celular Rocket League: Sideswipe.
El juego consiste en un partido de fútbol, en donde los jugadores son autos que pueden hacer distintos movimientos para poder empujar una pelota dentro del arco contrario.

### Requerimientos de software

Sistema operativo: Ubuntu --AGREGAR VERSION--  
  
Listado de dependencias del proyecto

- [cmake](https://cmake.org/)
- [yaml](https://yaml.org/)
- [X.Org](https://www.x.org/wiki/)
- [SDL2](https://github.com/libsdl-org/SDL)
- [SDL_image](https://github.com/libsdl-org/SDL_image)
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)
- [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp)
- [QT5](https://wiki.qt.io/Install_Qt_5_on_Ubuntu)

### Dependencies

- [cmake](https://cmake.org/)
- `libyaml-cpp-dev`, `xorg-dev`, `libsdl2-dev`, `libx11-dev`, `libxrandr-dev`, `libxinerama-dev`, `libxcursor-dev`
  - Debian based distros: `sudo apt install libyaml-cpp-dev xorg-dev libsdl2-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev`


## Proceso de instalacion

Clonar el repositorio

```console
https://github.com/1gnacio/Taller-1-Rocket-League.git
```

Correr los siguientes comandos para compilar tanto el cliente como el servidor

```console
    mkdir build
    cd build
    cmake ..
    make -j4
```

Al correr el comando `make` se generan dos ejecutables en el directorio `/build`, el ejecutable `game_server` es el servidor del juego y el ejecutable `game_client` es el cliente 

## Inicializar servidor y cliente  
  
**Correr el servidor**  

```console
./game_server <puerto>
```

Al correr este comando se inicia el servidor, dejando la consola en modo de espera hasta que el usuario ingrese la letra `q` y presione enter para cerrar el servidor. Durante este tiempo el servidor se encuentra esperando conexiones de jugadores  
  
**Correr el cliente**  

```console
./game_client <nombre del servidor> <puerto>`
```

_Para partidas locales recomendamos los puertos `8080` u `8088`_

## Ciclo de juego

Al conectarse al servidor, el jugador vera la siguiente interfaz grafica que representa el lobby del juego, donde se pueden crear, visualizar y unir a partidas

![lobby](https://user-images.githubusercontent.com/23293753/198899200-60d1e4ec-2ea4-4f94-aed7-e51e71dd6912.gif)

### Acciones desde el lobby

* **Crear**: el jugador podra crear una partida nueva escribiendo el nombre y la cantidad maxima permitida de jugadores. El servidor valida que no existan partidas con el mismo nombre ya empezadas. Una vez creada correctamente la partida, el jugador se conectara a la misma y vera en pantalla el campo de juego con su auto asignado.

* **Unirse**: el jugador podra unirse a una partida existente eligiendola desde la lista que se encuentra en la parte inferior de la ventana. Si no encuentra la partida en la interfaz, haciendo click en _Refresh_ se volveran a cargar las partidas disponibles y su estado. Solo podra unirse a aquellas partidas que no se encuentren llenas o terminadas.

* Nota: para la version pre-release se opto por crear una partida default para pruebas de movimiento, a la cual se ingresa apretando el boton _Join_ desde el lobby

Al unirse o crear una partida, el jugador sera llevado al campo de juego, donde podra ver su auto, el marcador de la partida, el tiempo restante y al resto de jugadores. Para mover su auto presione las flechas direccionales, para saltar presione la tecla espacio y para activar turbo presione la letra T.

En todo momento el jugador podra salir de la partida haciendo click en la cruz de la ventana de partida, la cual volvera abrir el lobby para unirse a otra partida o crear una nueva. Al cerrar la ventana de lobby el cliente se desconecta del servidor.

## Testing 
Para correr los test y ver el coverage por archivo  --TODO terminar esta parte--
  
```console
    cmake ..
    make scrub
    make gcov
```

## Juego
![juego](data/firstGame.gif)

## Ejemplo integrador

![Ejemplo](data/cliente_servidor.gif)


## Documentación & Notas

[Link Google Docs](https://docs.google.com/document/d/1HAAGN4PyoHdXEmL62-MtdpeMkoSojueFdWUvSQ4e9Ag/edit?usp=sharing)

[EverNote](https://www.evernote.com/shard/s392/client/snv?noteGuid=1dd9e1ff-3bbe-c34f-33f0-5545271bdf81&noteKey=8f2645c4fdc094c5fc3e4e4d6d404fc8&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs392%2Fsh%2F1dd9e1ff-3bbe-c34f-33f0-5545271bdf81%2F8f2645c4fdc094c5fc3e4e4d6d404fc8&title=TP1%2B-%2BAPUNTES)

![Diagram_2](https://user-images.githubusercontent.com/23293753/197909510-b1a9e6c4-802a-4d81-be34-bb86e7162652.png)

![Diagrama_1](https://user-images.githubusercontent.com/23293753/197909532-d5b5c027-a6e9-4891-ab14-f975289d62f8.png)

