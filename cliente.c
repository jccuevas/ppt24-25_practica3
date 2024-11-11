/*******************************************************
 * Protocolos de Transporte
 * Grado en Ingeniería Telemática
 * Dpto. de Ingeníería de Telecomunicación
 * Universidad de Jaén
 *
 *******************************************************
 * Práctica 1
 * Fichero: cliente.c
 * Versión: 3.1
 * Curso: 2024/2025
 * Descripción: Cliente SMTP TCP para IPv4 e IPv6
 * Autor: Juan Carlos Cuevas Martínez
 *
 ******************************************************
 * Alumno 1:
 * Alumno 2:
 *
 ******************************************************/
#include <stdio.h>		// Biblioteca estándar de entrada y salida
#include <ws2tcpip.h>	// Necesaria para las funciones IPv6
#include <conio.h>		// Biblioteca de entrada salida básica
#include <locale.h>		// Para establecer el idioma de la codificación de texto, números, etc.
#include "protocol.h"	// Declarar constantes y funciones de la práctica

#pragma comment(lib, "Ws2_32.lib")//Inserta en la vinculación (linking) la biblioteca Ws2_32.lib


int main(int* argc, char* argv[])
{
	SOCKET sockfd;
	struct sockaddr* server_in = NULL;
	struct sockaddr_in server_in4;
	struct sockaddr_in6 server_in6;
	int address_size = sizeof(server_in4);
	char buffer_in[1024], buffer_out[1024], input[1024];
	int recibidos = 0, enviados = 0;
	int estado;
	char option;
	int ipversion = AF_INET;//IPv4 por defecto
	char ipdest[256];
	//char default_ip4[16] = "127.0.0.1"; //CASA
	char default_ip4[16] = "150.214.179.118"; //CLASE
	char default_ip6[64] = "::1";
	int recipientOk = 0;
	int msgOn = 0;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	//Inicialización de idioma
	setlocale(LC_ALL, "es-ES");


	//Inicialización Windows sockets - SOLO WINDOWS
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		return(0);
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return(0);
	}
	//Fin: Inicialización Windows sockets

	printf("**************\r\nCLIENTE TCP SENCILLO SOBRE IPv4 o IPv6\r\n*************\r\n");

	do {
		printf("CLIENTE> ¿Qué versión de IP desea usar? 6 para IPv6, 4 para IPv4 [por defecto] ");
		gets_s(ipdest, sizeof(ipdest));

		if (strcmp(ipdest, "6") == 0) {
			//Si se introduce 6 se empleará IPv6
			ipversion = AF_INET6;

		}
		else { //Distinto de 6 se elige la versión IPv4
			ipversion = AF_INET;
		}

		sockfd = socket(ipversion, SOCK_STREAM, 0);
		if (sockfd == INVALID_SOCKET) {
			printf("CLIENTE> ERROR\r\n");
			exit(-1);
		}
		else {
			printf("CLIENTE> Introduzca la IP destino (pulsar enter para IP por defecto): ");
			gets_s(ipdest, sizeof(ipdest));

			//Dirección por defecto según la familia
			if (strcmp(ipdest, "") == 0 && ipversion == AF_INET)
				strcpy_s(ipdest, sizeof(ipdest), default_ip4);

			if (strcmp(ipdest, "") == 0 && ipversion == AF_INET6)
				strcpy_s(ipdest, sizeof(ipdest), default_ip6);

			if (ipversion == AF_INET) {
				server_in4.sin_family = AF_INET;
				server_in4.sin_port = htons(TCP_SERVICE_PORT);
				inet_pton(ipversion, ipdest, &server_in4.sin_addr.s_addr);
				server_in = (struct sockaddr*) & server_in4;
				address_size = sizeof(server_in4);
			}

			if (ipversion == AF_INET6) {
				memset(&server_in6, 0, sizeof(server_in6));
				server_in6.sin6_family = AF_INET6;
				server_in6.sin6_port = htons(TCP_SERVICE_PORT);
				inet_pton(ipversion, ipdest, &server_in6.sin6_addr);
				server_in = (struct sockaddr*) & server_in6;
				address_size = sizeof(server_in6);
			}

			//Cada nueva conexión establece el estado incial en
			estado = S_INIT;

			if (connect(sockfd, server_in, address_size) == 0) {
				printf("CLIENTE> CONEXION ESTABLECIDA CON %s:%d\r\n", ipdest, TCP_SERVICE_PORT);

				//Inicio de la máquina de estados
				do {
					switch (estado) {
					case S_INIT:
						// Se recibe el mensaje de bienvenida
						break;
					case S_HELO:
						// establece la conexion de aplicacion 
						printf("CLIENTE> Introduzca el dominio local (enter para salir): ");
						gets_s(input, sizeof(input));
						if (strlen(input) == 0) {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", QUIT, CRLF);
							estado = S_QUIT;
						}
						else {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s %s%s", HELO, input, CRLF);
						}
						break;
					case S_MAIL:
						recipientOk = 0;//Para asegurar que al menos se ha introducido un destinario válido
						printf("CLIENTE> Introduzca el remitente (enter para salir): ");
						gets_s(input, sizeof(input));
						if (strlen(input) == 0) {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", QUIT, CRLF);
							estado = S_QUIT;
						}
						else {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s %s%s", MAIL, input, CRLF);
						}

						break;
					case S_RCPT:
						printf("CLIENTE> Introduzca el destinatario (enter para salir): ");
						gets_s(input, sizeof(input));
						if (strlen(input) == 0) {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", QUIT, CRLF);
							estado = S_QUIT;
						}
						else {
							sprintf_s(buffer_out, sizeof(buffer_out), "%s %s%s", RCPT, input, CRLF);
						}
						break;
					case S_DATA:
						sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", DATA, CRLF);
						break;
					
					case S_MSG:
						//sprintf_s(buffer_out, sizeof(buffer_out), "subject:Práctica 3\r\n\r\nEstoy con la práctica 3\r\n.\r\n");

						switch (statusMail) {
						case 1:
							pritnf("Asunto del correo: ");
							gets_s(input, sizeof(input));//Cadena a enviar
							if (strcmp(input, ".") == 0) {
								msgOn = 0;
							}
							sprintf_s(buffer_out, sizeof(buffer_out), "%s%s%s",SUBJECT,input, CRLF);
							statusMail++;
							break;

						case 4:
							printf("Escriba una nueva línea de correo o un punto para finalizar");
							gets_s(input, sizeof(input));//Cadena a enviar
							if (strcmp(input, ".") == 0) {
								msgOn = 0;
							}
							sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", input, CRLF);

						}
						break;
					}

					if (estado != S_INIT) {
						enviados = send(sockfd, buffer_out, (int)strlen(buffer_out), 0);
						if (enviados == SOCKET_ERROR) {
							estado = S_QUIT;
							continue;// La sentencia continue hace que la ejecución dentro de un
									 // bucle salte hasta la comprobación del mismo.
						}
					}
					if (msgOn==0) {
						recibidos = recv(sockfd, buffer_in, 512, 0);
						if (recibidos <= 0) {
							DWORD error = GetLastError();
							if (recibidos < 0) {
								printf("CLIENTE> Error %d en la recepción de datos\r\n", error);
								estado = S_QUIT;
							}
							else {
								printf("CLIENTE> Conexión con el servidor cerrada\r\n");
								estado = S_QUIT;
							}
						}
						else {
							char statusCode[1024] = "";

							buffer_in[recibidos] = 0x00;
							printf("RECIBIDO %d bytes> %s", recibidos, buffer_in);

							//Robustez -> comprobar que la longitud de buffer_in es almenos 3
							strncpy_s(statusCode, sizeof(statusCode), buffer_in, 3);
							statusCode[3] = 0;

							switch (estado) {
							case S_INIT:
								if (strcmp(statusCode, SC220) == 0) {
									estado = S_HELO;
								}
								else {
									estado = S_QUIT;
									continue;
								}

								break;

							case S_HELO:
								if (strcmp(statusCode, SC250) == 0) {
									estado = S_MAIL;//Transición al estado MAIL
								}
								else {//Error al iniciar la sesión de SMTP
									printf("Error al enviar el comando HELO");
									estado = S_QUIT;
									continue;
								}
								break;

							case S_MAIL:
								if (strcmp(statusCode, SC250) == 0) {
									estado = S_RCPT;//Transición al estado RCPT
								}
								else {//Error al enviar el remitente
									printf("Error al enviar el comando MAIL");
									estado = S_QUIT;
									continue;
								}
								break;
							case S_RCPT:
								if (strcmp(statusCode, SC250) == 0) {
									recipientOk = 1;
									//añadir variable que indique que ya hemos enviado AL MENOS UN destino correcto
									//pregunto si quiere otro
										//no hago nada
									//else (no quiere otro)
									estado = S_DATA;//Transición al estado RCPT
								}
								else if (strcmp(statusCode, SC550) == 0) {
									//pregunto si quiere otro
										//no hago nada
									//else (no quiere otro)
										// Si ya hay uno correcto
									estado = S_DATA;//Transición al estado RCPT
									// si no hay correcto
									 //seguimos en el mismo estado.
								}
								else {//Error al enviar el remitente
									printf("Error al enviar el comando RCPT");
									estado = S_QUIT;
									continue;
								}
								break;
							case S_DATA:
								if (strcmp(statusCode, SC354) == 0) {
									estado = S_MSG;//Transición al estado de preparación del cuerpo del mensaje
									msgOn = 1; 
								}
								else {//Error al enviar el remitente
									printf("Error al enviar el comando DATA");
									estado = S_QUIT;
									continue;
								}
								break;
							case S_MSG:
								if (strcmp(statusCode, SC250) == 0) {
									estado = S_MAIL;//Transición al estado MAIL
								}
								else {//Error al enviar el remitente
									printf("Error al enviar el cuerpo del correo");
									estado = S_QUIT;
									continue;
								}
								break;

							}//switch

						}//recv correcto
					}
				} while (estado != S_QUIT);
			}
			else {
				int error_code = GetLastError();
				printf("CLIENTE> ERROR AL CONECTAR CON %s:%d\r\n", ipdest, TCP_SERVICE_PORT);
			}
			closesocket(sockfd);

		}
		printf("-----------------------\r\n\r\nCLIENTE> Volver a conectar (S/N)\r\n");
		option = _getche();

	} while (option != 'n' && option != 'N');

	return(0);
}
