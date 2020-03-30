/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"

//TODO
void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void* a_enviar = malloc (bytes + sizeof(int));
	int offset=0;

	memcpy(a_enviar+offset,&(paquete->codigo_operacion),sizeof(int));
	offset+=sizeof(int);
    memcpy(a_enviar+offset,&(paquete->buffer->size),sizeof(int));
    offset+=sizeof(int);
    memcpy(a_enviar+offset,paquete->buffer->stream,paquete->buffer->size);

    return a_enviar;
}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODO
void enviar_mensaje(char* mensaje, int socket_cliente)
{
	int long_mensaje=strlen(mensaje)+1;
	t_buffer* buffer = malloc(sizeof(t_buffer));
	t_paquete* paquete = malloc(sizeof(t_paquete));
	buffer->stream = malloc(long_mensaje);


    buffer->size=long_mensaje;
    memcpy(buffer->stream,mensaje,long_mensaje);
    paquete->buffer=buffer;
    paquete->codigo_operacion=MENSAJE;
    send(socket_cliente,serializar_paquete(paquete,buffer->size),buffer->size+sizeof(int)*2,0);
    free(buffer->stream);
    free(paquete);
    free(buffer);
}

//TODO
char* recibir_mensaje(int socket_cliente)
{
	int codigoOP;
	int size;
	void * stream;

    recv(socket_cliente, &codigoOP, sizeof(int), MSG_WAITALL);
	recv(socket_cliente, &size, sizeof(int), MSG_WAITALL);
	stream = malloc(size);
 	recv(socket_cliente, stream, size, MSG_WAITALL);

	return (char *)stream;

}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
