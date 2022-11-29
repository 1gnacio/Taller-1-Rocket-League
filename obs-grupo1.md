cppcheck muestra muchisimos errores. Haber codeado el TP sin la ayuda de
cppcheck y valgrind fue un error grave.
Las herramientas estan para ayudarlos.

El servidor no se cierra al presionar `q`. Parece colgarse.

El cliente 99.99% del tiempo crashea al empezar (luego del join).

Este es el traceback obtenido con GDB:

```
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=140308987408640) at ./nptl/pthread_kill.c:44
#1  __pthread_kill_internal (signo=6, threadid=140308987408640) at ./nptl/pthread_kill.c:78
#2  __GI___pthread_kill (threadid=140308987408640, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
#3  0x00007f9c3ea83476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#4  0x00007f9c3ea697f3 in __GI_abort () at ./stdlib/abort.c:79
#5  0x00007f9c3ed2bbbe in ?? () from /lib/x86_64-linux-gnu/libstdc++.so.6
#6  0x00007f9c3ed3724c in ?? () from /lib/x86_64-linux-gnu/libstdc++.so.6
#7  0x00007f9c3ed372b7 in std::terminate() () from /lib/x86_64-linux-gnu/libstdc++.so.6
#8  0x000055d4c8e9eded in std::thread::~thread() ()
#9  0x000055d4c8e9ec26 in Client::run() ()
#10 0x000055d4c8e99a33 in lobby::on_pushButton_join_clicked() ()
#14 0x00007f9c3fd54116 in QAbstractButton::clicked(bool) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#15 0x00007f9c3fd5439e in ?? () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#16 0x00007f9c3fd55fc4 in ?? () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#17 0x00007f9c3fd561e7 in QAbstractButton::mouseReleaseEvent(QMouseEvent*) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#18 0x00007f9c3fca14ee in QWidget::event(QEvent*) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#19 0x00007f9c3fc5e713 in QApplicationPrivate::notify_helper(QObject*, QEvent*) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#20 0x00007f9c3fc66364 in QApplication::notify(QObject*, QEvent*) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#21 0x00007f9c3f16ee3a in QCoreApplication::notifyInternal2(QObject*, QEvent*) () from /lib/x86_64-linux-gnu/libQt5Core.so.5
#22 0x00007f9c3fc64e47 in QApplicationPrivate::sendMouseEvent(QWidget*, QMouseEvent*, QWidget*, QWidget*, QWidget**, QPointer<QWidget>&, bool, bool) ()
   from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#23 0x00007f9c3fcbad40 in ?? () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#24 0x00007f9c3fcbdfd5 in ?? () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#25 0x00007f9c3fc5e713 in QApplicationPrivate::notify_helper(QObject*, QEvent*) () from /lib/x86_64-linux-gnu/libQt5Widgets.so.5
#26 0x00007f9c3f16ee3a in QCoreApplication::notifyInternal2(QObject*, QEvent*) () from /lib/x86_64-linux-gnu/libQt5Core.so.5
#27 0x00007f9c3f555307 in QGuiApplicationPrivate::processMouseEvent(QWindowSystemInterfacePrivate::MouseEvent*) () from /lib/x86_64-linux-gnu/libQt5Gui.so.5
#28 0x00007f9c3f52aa2c in QWindowSystemInterface::sendWindowSystemEvents(QFlags<QEventLoop::ProcessEventsFlag>) () from /lib/x86_64-linux-gnu/libQt5Gui.so.5
#29 0x00007f9c3b487d6e in ?? () from /lib/x86_64-linux-gnu/libQt5XcbQpa.so.5
#30 0x00007f9c3da4cd1b in g_main_context_dispatch () from /lib/x86_64-linux-gnu/libglib-2.0.so.0
#31 0x00007f9c3daa16f8 in ?? () from /lib/x86_64-linux-gnu/libglib-2.0.so.0
#32 0x00007f9c3da4a3c3 in g_main_context_iteration () from /lib/x86_64-linux-gnu/libglib-2.0.so.0
#33 0x00007f9c3f1c80b8 in QEventDispatcherGlib::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) () from /lib/x86_64-linux-gnu/libQt5Core.so.5
#34 0x00007f9c3f16d75b in QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) () from /lib/x86_64-linux-gnu/libQt5Core.so.5
#35 0x00007f9c3f175cf4 in QCoreApplication::exec() () from /lib/x86_64-linux-gnu/libQt5Core.so.5
#36 0x000055d4c8e990ed in main ()
```


El server por su parte muere horriblemente con varias corrupciones de memoria:

```
llega un comando de TURBO_RELEASE
llega un comando de
llega un comando de TURBO_RELEASE
==89== Thread 5:
==89== Invalid read of size 4
==89==    at 0x13C76C: void std::__invoke_impl<void, void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> >(std::__invoke_memfun_deref, void (ConnectionHelper::*&&)(Socket&, int), ConnectionHelper*&&, std::reference_wrapper<Socket>&&, std::reference_wrapper<int>&&) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x13C57F: std::__invoke_result<void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> >::type std::__invoke<void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> >(void (ConnectionHelper::*&&)(Socket&, int), ConnectionHelper*&&, std::reference_wrapper<Socket>&&, std::reference_wrapper<int>&&) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x13C3F0: void std::thread::_Invoker<std::tuple<void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> > >::_M_invoke<0ul, 1ul, 2ul, 3ul>(std::_Index_tuple<0ul, 1ul, 2ul, 3ul>) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x13C34D: std::thread::_Invoker<std::tuple<void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> > >::operator()() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x13C309: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (ConnectionHelper::*)(Socket&, int), ConnectionHelper*, std::reference_wrapper<Socket>, std::reference_wrapper<int> > > >::_M_run() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==89==    by 0x4C33B42: start_thread (pthread_create.c:442)
==89==    by 0x4CC4BB3: clone (clone.S:100)
==89==  Address 0x61ccbac is on thread 3's stack
==89==  212 bytes below stack pointer
==89==
llega un comando de TURBO_RELEASE
llega un comando de
==89== Thread 2:
==89== Invalid read of size 1
==89==    at 0x11CE2C: ResponseHandler::isFinished() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F9F3: ClientConnection::push(Response&) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12CFEA: ServerEndpoint::sendResponsesHandler() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F85D: void std::__invoke_impl<void, void (ServerEndpoint::*)(), ServerEndpoint*>(std::__invoke_memfun_deref, void (ServerEndpoint::*&&)(), ServerEndpoint*&&) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F7B0: std::__invoke_result<void (ServerEndpoint::*)(), ServerEndpoint*>::type std::__invoke<void (ServerEndpoint::*)(), ServerEndpoint*>(void (ServerEndpoint::*&&)(), ServerEndpoint*&&) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F710: void std::thread::_Invoker<std::tuple<void (ServerEndpoint::*)(), ServerEndpoint*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F6C5: std::thread::_Invoker<std::tuple<void (ServerEndpoint::*)(), ServerEndpoint*> >::operator()() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x12F6A5: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (ServerEndpoint::*)(), ServerEndpoint*> > >::_M_run() (in /home/user/mnt/Taller-1-Rocket-League/build/game_server)
==89==    by 0x494A2B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==89==    by 0x4C33B42: start_thread (pthread_create.c:442)
==89==    by 0x4CC4BB3: clone (clone.S:100)
==89==  Address 0x68 is not stack'd, malloc'd or (recently) free'd
```

No hay mucho mas para decir. Al crashear casi inmediatamente el cliente
y al poco tiempo el servidor no pude ni crear una partida ni jugar
(ni siquiera pude mover el auto).

