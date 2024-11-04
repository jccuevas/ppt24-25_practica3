# ClienteSMTP

Práctica 3. Implementación de un cliente socket TCP basado en un estándar en C
TITULACIÓN: Grado en Ingeniería telemática (14512011)
TITULACIÓN: Doble Grado Ing. de tecnologías de la telecomunicación e Ing. telemática (15212023)
CENTRO: ESCUELA POLITÉCNICA SUPERIOR (LINARES)
CURSO ACADÉMICO: 2024-2025

Descripción
Realizar un cliente SMTP [1] en lenguaje C empleando las primitivas Sockets [2]. El cliente se implementará como una aplicación de consola guiada a través de la entrada estándar (teclado) y deberá seguir la RFC 5321 [1] y la RFC 5322 [3]. La aplicación desarrollada permitirá el envío de correos electrónicos a cualquier servidor SMTP de Internet que admita el comando HELO. Téngase en cuenta que la especificación del protocolo sigue la nomenclatura ABNF [3]. La presente práctica deberá cumplir los siguientes requisitos:
1. Se deberá dar soporte a los comandos HELO, MAIL, RCPT, DATA, QUIT y RSET.
2. Se deberá tener al usuario informado del estado o fase en la que se encuentre el cliente en todo momento.
3. El interfaz de usuario de la aplicación deberá ocultar al usuario los comandos del protocolo necesarios para la operación.
4. Se deberá poder añadir más de un destinatario al correo.
5. Redacción de correos en formato ASCII.
6. Los correos deberán tener un número ilimitado de líneas.
7. Se deberá preservar la longitud máxima de línea especificada para SMTP.
8. Se deberá poder enviar más de un correo en la misma sesión.

En este repositorio se subirán los resultados de las explicaciones de clase.
