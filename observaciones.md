# Documentación

La documentación tiene muchos errores ortográficos: falta de acentos y
falta de ñ.

La descripción del Protocolo es genérica y se ajusta a casi cualquier
protocolo existente y no describe el suyo.

Cito:

 > "El envio de informacion se realiza en dos pasos, el primero envia el
 > tamanio de la respuesta y el segundo envia los bytes de la respusta"

No hay ninguna descripción de cuantos bytes hay, su endianness, signo ni
como son los mensajes.

En general es un manual técnico bastante pobre.


# Valgrind

Aunque en una corrida normal no parecen haber errores, cuando cierro el
cliente en el medio del juego el servidor emite muchos errores.

Dejo aca uno:

```
==2643== Conditional jump or move depends on uninitialised value(s)
==2643==    at 0x12637E: Serializer::serializeBool(bool) (serializer.cpp:18)
==2643==    by 0x12BF18: BallResponse::serialize() (ball_response.cpp:9)
==2643==    by 0x128F4F: MatchResponse::serialize() (match_response.cpp:11)
==2643==    by 0x12379E: Response::serialize() (response.cpp:45)
==2643==    by 0x11EF5E: Protocolo::sendResponse(Socket&, Response&) (protocolo.cpp:93)
==2643==    by 0x11C226: ResponseHandler::handleSend() (response_handler.cpp:43)
==2643==    by 0x11C967: void std::__invoke_impl<void, void (ResponseHandler::*)(), ResponseHandler*>(std::__invoke_memfun_deref, void (ResponseHandler::*&&)(), ResponseHandler*&&) (invoke.h:74)
==2643==    by 0x11C8BA: std::__invoke_result<void (ResponseHandler::*)(), ResponseHandler*>::type std::__invoke<void (ResponseHandler::*)(), ResponseHandler*>(void (ResponseHandler::*&&)(), 
ResponseHandler*&&) (invoke.h:96)
==2643==    by 0x11C81A: void std::thread::_Invoker<std::tuple<void (ResponseHandler::*)(), ResponseHandler*> >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) (std_thread.h:253)
==2643==    by 0x11C7CF: std::thread::_Invoker<std::tuple<void (ResponseHandler::*)(), ResponseHandler*> >::operator()() (std_thread.h:260)
==2643==    by 0x11C7AF: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (ResponseHandler::*)(), ResponseHandler*> > >::_M_run() (std_thread.h:211)
==2643==    by 0x49892B2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
```

# cppcheck

cppcheck marca algunos warnings y errores de estilo. Podrian haberse
arreglado.


