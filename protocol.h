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
#define SC "USER"
#define PW "PASS"
#define SD  "QUIT"
#define ECHO "ECHO"


// RESPUESTAS A COMANDOS DE APLICACION
#define OK  "OK"
#define ER  "ER"

//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_INIT 0
#define S_USER 1
#define S_PASS 2
#define S_DATA 3
#define S_QUIT 4


//PUERTO DEL SERVICIO
#define TCP_SERVICE_PORT	60000

// NOMBRE Y CLAVE AUTORIZADOS
// Nota: esto no se debe hacer nunca, es solamente para simplificar el funcionamiento del
// servidor, el cual debería almacenar estos datos en una base de datos de forma segura.
#define USER		"user" 
#define PASSWORD	"1234"