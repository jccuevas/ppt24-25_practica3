/*******************************************************
 * Protocolos de Transporte
 * Grado en Ingeniería Telemática
 * Dpto. de Ingeníería de Telecomunicación
 * Universidad de Jaén
 *
 *******************************************************
 * Práctica 1
 * Fichero: protocol.c
 * Versión: 4.0
 * Curso: 2024/2025
 * Descripción: Fichero de encabezado para práctica 1
 * Autor: Juan Carlos Cuevas Martínez
 *
 ******************************************************
 * Alumno 1:
 * Alumno 2:
 *
 ******************************************************/
#ifndef protocolostpte_practicas_headerfile
#define protocolostpte_practicas_headerfile
#endif

// COMANDOS DE APLICACION
#define QUIT "QUIT"
#define HELO "HELO"
#define EHLO "EHLO"

#define MAIL "MAIL FROM:"// Comando para enviar el remitente
#define RCPT "RCPT TO:"// Comando para enviar el destinatario
#define DATA "DATA"

// RESPUESTAS A COMANDOS DE APLICACION
#define SC220   "220" //Saludo
#define SC221   "221" //QUIT
#define SC250	"250" //Respuesta afirmativa a comandos HELO, MAIL y RCPT
#define SC354	"354" //Respuesta afirmativa a comando DATA

//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_INIT 0
#define S_HELO 1
#define S_MAIL 2
#define S_RCPT 3
#define S_DATA 4
#define S_MSG  5
#define S_QUIT 6


//PUERTO DEL SERVICIO
#define TCP_SERVICE_PORT	25

