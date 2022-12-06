<center>

![](data/FIUBA.png)
<h1>DOCUMENTACIÓN TÉCNICA </h1>
<h3>TALLER DE PROGRAMACIÓN I</h3>
<h3>2º Cuatrimestre 2022</h3>
</center>

### integrantes:

* **Ignacio Garcia Segovia** - [1gnacio](https://github.com/1gnacio)
* **Nahuel Gomez** - [NahuelNGomez](https://github.com/NahuelNGomez)
* **Iñaki Gonzalez Bigliardi** - [igonzalezb](https://github.com/igonzalezb)

### Indice:

1) **Composición del protocolo.**
2) **Archivos.**
3) **Diagramas.**
4) **Test unitarios.**
-----------


### Composición del protocolo:

El protocolo esta compuesto por la clase `Protocolo` que se encarga del envio y recepcion de respuestas y comandos. Para ello utiliza las clases `Command` y `Response` las cuales son serializadas durante el envio como un vector de bytes, y son deserializadas durante la recepcion para volver a armar el objeto original.

El envio de informacion se realiza en dos pasos, el primero envia el tamanio de la respuesta y el segundo envia los bytes de la respusta. En caso de desconexion del cliente o del servidor, el `Protocolo` lanza una excepcion de tipo `SocketClosedException`, que es resuelta por los manejadores de clientes y servidor para cerrar la conexion de forma amable.

-----------

### Archivos:


#### <u>Server</u>

**<u>Descrición general:</u>**

Esta entidad se encarga de:
* Recibir a nuevos clientes.


* Distribuir a los clientes en la partida correspondiente.


* Resolver la lógica del juego (de todas las partidas en simultáneo).


* Posee la información de las salas.


* Envía a los clientes las respuestas correspondientes con los datos de su partida.

*Clases sobre el juego:*
1) **GameModel:** Se encarga de la distribución de cada jugador a una partida. Le irán llegando
comandos y, dependiendo el tipo de comando, lo trabajará o derivará a la cola de comandos
de la partida correspondiente.


2) **CompleteGame:** Posee el loop principal del juego, a la vez que contiene la información de la
sala (está empezada, qué jugadores la integran, etc.).


3) **GameLogic:** Le llegan comandos sobre los movimientos que se han realizado durante el juego y
se encarga de manipularlos a partir de la clase BoxLogic.


4) **BoxLogic:** Es un objeto que se encarga de manipular la física de cada partida a partir de la
librería box2D. En ella se encuentran los objetos del propio juego, como por ejemplo los autos;
el propio mundo; la pelota; entre otros.


5) **Game:** Tiene la información de la partida y sabe si una partida terminó. Tiene atributos como
goalsLocal / goalsVisitor (cuántos goles hay en la partida) o el tiempo de la partida.


6) **ContactListenerHits:** Es una clase que hereda de b2ContactListener(propia de la librería box2D)
que se encarga de informar las interacciones entre la pelota y el auto. A su vez, tiene la
capacidad de comunicarle a la pelota con qué golpe ha sido golpeada.


7) **ReplayLogic:** Es capaz de almacenar respuestas para que, una vez que haya existido un gol, se
envíen sus respuestas en lugar de las del propio juego.


8) **Car:** Es un objeto que simula al auto en el juego. Este tiene la capacidad de saber cuándo hacer
un flip, saber si está en el suelo; su estado en el tanque de turbo, entre otras cosas.


9) **Ball:** Clase que se encarga de simular a la pelota dentro de la partida. Tiene la capacidad de
saber si ha sido golpeada con algún movimiento especial y de ser cierto, se aplica una fuerza
extra.

#### <u>Cliente</u>
Esta entidad se encarga de:

* La interacción con el usuario a través del teclado y el mouse.

*  Mostrar en pantalla la interfaz gráfica del lobby y el juego principal.

* Conexión con el servidor y recibe las respuestas.

*Clases sobre el juego:*

1) **Client:** esta clase es el loop principal por el cual a partir de una respuesta del servidor de una cola no bloqueante, actualiza los modelos y luego renderiza la pantalla. 

2) **lobby:** clase de qT que muestra una ventana del lobby por el cual los usuarios crean partidas o se unen a alguna ya creada previamente.

3) **sdl_main:** esta clase es la principal de SDL. Posee el resto de los objetos de SDl y la misma tiene dos funciones principales. Una actualiza los datos de todos los modelos de SDl y la otra renderiza los objetos.

4) **unit_conversion:** se encarga de la conversión de unidades entre Box2D y SDl. Ya sea convertir de metros a pixeles o radianes a grados.

5) **sdl_animation:** esta clase genera animaciones a partir de imágenes estáticas al ir cambiando de frames.

6) **sdl_music:** clase que maneja los sonidos del juego.

7) **sld_{objeto}:** cada objeto de SDL tiene su clase, ya sea los *autos*, *arena*, *scoreboard*, etc. Tienen dos funciones principales: *update* y *render*.


#### <u>Protocolo y conexiones</u>

1) **ServerEndpoint**: Clase que maneja la conexion de los clientes y el servidor. Tiene un vector de *ClientConnection* que representa cada conexion. Recibe las respuestas del servidor y las envia a los clientes, y recibe los comandos de los clientes y los agrega a una cola de comandos que es usada por el servidor para aplicar la logica del comando a la partida correspondiente.

2) **ClientConnection**: Clase que maneja la conexion del servidor con el cliente. `ServerEndpoint` le pasa las respuestas del servidor que deben ser enviadas a cada cliente, 

2) **ServerConnection**: Clase que maneja la conexion del cliente con el servidor. Recibe las respuestas del servidor y las agrega a una cola de respuestas, y agrega los comandos del cliente a una cola de comandos que son enviados al servidor.


3) **ResponseHandler**: Clase que maneja el envio o recepcion de Respuestas. El modo `SENDER` se utiliza por el servidor para enviar las respuestas a un cliente, el modo `RECEIVER` se usa por el cliente para recibir las respuestas del servidor


4) **IdService**: Clase que se encarga de enviar o recibir el id del cliente. El cliente recibe su id cuando se conecta al servidor, mientras que el servidor envia un id nuevo cuando se conecta un cliente.


5) **CommandHandler**: Clase que maneja el envio o recepcion de comandos. El modo `SENDER` se usa por el cliente para enviar comandos al servidor, el modo `RECEIVER` se usa por el servidor para recibir comandos de un cliente.


---------

### Diagramas:

<u>***Flujo principal del juego en una partida comenzada***</u>

A continuación, mostramos un diagrama de secuencia donde se aprecia el flujo estándar del juego:

![flujoJuego.png](data/diagramas/flujoJuego.png)

<u>***Flujo del envio de respuestas del servidor a cada cliente***</u>

Cada respuesta generada por el servidor representa el estado de una partida o el resultado de aplicar una accion en la misma. 

![POv12W8n34NtFKMMkl02BcHW45ph2ORsonJgJqapdj-AA4Wt8P3t7fcQB-RReuGRx0cJmqa-svcfQgRBKUhMrjqLhIeRzg6eLhchOOchH2KHFIl3l_SkpIM3Fl-GiJKGtVfUBmjJWOqIcCBKHt_x1G00](https://user-images.githubusercontent.com/38591482/206005902-10f37404-446c-48d1-9778-9583cd56af63.png)

La respuesta es agregada a una cola bloqueante de respuestas que luego son enviadas al cliente a traves del protocolo por otro hilo

![SoWkIImgAStDuGfABIx8pojEzKZCIyb9BLBGjLE02Jdbv2TdP-Qb1vQcbgOgM2aKb1PdQC0aDRcmAWFf3qxDIu59XcGKfIQcW3Jd5o3fnLG2qXXGb5-IdvoVamzKNuoa0acZ0r0Ow6m0](https://user-images.githubusercontent.com/38591482/206007067-c6d99a26-26c1-4336-9fb6-04376f43eb54.png)

-----------

### Test unitarios:

Para correr los tests unitarios usar los siguientes comandos (desde la carpeta donde se hizo la build)

```console
make scrub
make gcov
```

Es importante correr `make scrub` ya que `gcov` genera archivos de cobertura que deben ser regenerados cada vez que se quiera calcular la cobertura del codigo testeado.

![WhatsApp Image 2022-12-06 at 4 01 37 PM (1)](https://user-images.githubusercontent.com/38591482/206001021-857334cf-6ece-42a0-bfb2-243acd4cb6ee.jpeg)

La primera parte valida que pasen todos los test creados en `google_tests/`, que estan divididos en cuatro archivos

**fisicas.cpp**: Tests de la logica de fisicas con box2d

**logica.cpp**: Tests de la logica de partidas del servidor

**protocolo.cpp**: Tests del envio y recepcion de respuestas y comandos

**serializacion.cpp**: Tests de serializacion y deserializacion de comandos y respuestas


![WhatsApp Image 2022-12-06 at 4 01 37 PM](https://user-images.githubusercontent.com/38591482/206000836-cc805cce-fa8a-418e-b3af-15b02d4f15c3.jpeg)


La segunda parte valida la cobertura de los archivos utilizados en los tests unitarios, donde al finalizar imprime el porcentaje de cobertura total de los cuatro archivos. Una mejora para estos tests es que se pueda calcular para cada archivo por separado.



-----------
