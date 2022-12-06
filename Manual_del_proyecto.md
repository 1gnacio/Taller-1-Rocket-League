<center>

![](data/FIUBA.png)
<h1>MANUAL DEL PROYECTO </h1>
<h3>TALLER DE PROGRAMACIÓN I</h3>
<h3>2º Cuatrimestre 2022</h3>
</center>

### integrantes:

* **Ignacio Garcia Segovia** - [1gnacio](https://github.com/1gnacio)
* **Nahuel Gomez** - [NahuelNGomez](https://github.com/NahuelNGomez)
* **Iñaki Gonzalez Bigliardi** - [igonzalezb](https://github.com/igonzalezb)


### Indice:
1) **División de tareas.**
2) **Inconvenientes encontrados.**
3) **Puntos pendientes**
4) **Herramientas que se utilizaron.**
5) **Conclusiones y aprendizaje.**

-----------

### División de tareas:

El proyecto se dividió en tres partes completamente diferenciadas:
* Lógica de juego
* Comunicación / protocolo
* Cliente / Interfaz gráfica

El encargado de implementar la lógica de juego fue Nahuel Gomez, quien desarrolló, entre otros features:
 * Partidas multijugador.


 * Lógica de la partida.


 * Integración de la librería Box2D.


 * Golpes especiales; flips.


 * Loop principal del juego.

El encargado de implementar la comunicación fue Ignacio Garcia Segovia. En particular se encargó de desarrollar:
 * El protocolo de comunicación.


 * Perfecta transmisión de datos sobre cliente - servidor.


 * Feature de repetición de partidas.


 * Archivos de configuración YAML.


El encargado de implementar el cliente fue Iñaki González Bigliardi. Se encargó de las siguientes implementaciones:
* Loop principal del cliente.


* Interacción con el usuario.


* Interfaz gráfica completa del juego utilizando la herramienta SDL2.


* Interfaz gráfica del lobby, ayudado con la herramienta QT5.

-----------

### Inconvenientes encontrados:

Se listarán los inconvenientes encontrados durante la realización del proyecto:

1) Uno de los mayores inconvenientes fue la utilización de nuevas herramientas, como box2D y SDL2
dado que ningún integrante sabía manipularlas, en general llevó bastante tiempo familiarizarnos con cada librería.


2) Otro inconveniente fue el pasaje de posiciones de Box2D a SDL para que el juego sea redimensionable, dado que box2D utiliza una escala en metros y
SDL en pixeles,


3) Nos resultó complicado tratar de debuggear el juego durante los últimos momentos ya que todavía no estaban implementados los archivos
YAML para facilitar esta tarea, por ejemplo en el tiempo máximo de juego y tomaba mucho tiempo llegar al bug.


4)  Tuvimos un problema con el consumo de memoria provocado por las colas no bloqueantes.


---------

### Puntos pendientes:

El único feature que no se llegó a concretar fue sobre el andar sobre las paredes.

A continuación, se nombran algunos features sobre el proyecto que son mejorables:

- Un jugador no puede reconectarse a una partida.

---------

### Herramientas que se utilizaron:

Se realiza una lista de las principales herramientas que se utilizaron durante el proyecto:
 * C++: Fue el lenguaje utilizado para implementar todo el proyecto.


 * QT5: Librería utilizada para la interfaz gráfica del lobby.


 * SDL2: Librería utilizada para la interfaz gráfica del juego.


 * Box2D: Librería encargada de manejar las físicas dentro de una partida.


 * yaml-cpp: Librería que parsea archivos en formato YAML.


 * cmake: Herramienta utilizada para la compilación del proyecto.


 * GitHub: Plataforma utilizada para guardar el proyecto de forma remota utilizando el control de versiones de Git.


 * GoogleTest: Framework utilizado en la implementación de los test unitarios.


 * plantUML: Página web utilizada para la creación de diagramas UML.
---------

### Conclusiones y aprendizaje

Como conclusión, podemos sacar que los tres integrantes aprendimos muchísimo sobre programación, aplicando los conocimientos
que brinda la materia, pero también, considerando que es lo más importante, se aprendió bastante en cómo trabajar en grupo y
cómo la comunicación entre los participantes del proyecto debe ser parte fundamental del mismo.
Esta comunicación facilita de manera inmediata la división de tareas y la organización del trabajo.
