/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;


	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	//loggear "soy un log"
	log_info(logger,"soy un log");


	config = leer_config();
	log_info(logger,config_get_string_value(config,"IP"));
	log_info(logger,config_get_string_value(config,"PUERTO"));
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
    conexion=crear_conexion(config_get_string_value(config,"IP"), config_get_string_value(config,"PUERTO"));


	//enviar mensaje

	enviar_mensaje("PRUEBA FINAL",conexion);


	//recibir mensaje
	log_info(logger, recibir_mensaje(conexion));



	//loguear mensaje recibido
	terminar_programa(conexion, logger, config);

	return 0;
}

//TODO
t_log* iniciar_logger(void)
{
  return log_create("tp0.log", "Game-watch", 1,  LOG_LEVEL_INFO);
}
//TODO
t_config* leer_config(void)
{
  return config_create("/home/utnso/Game-watch-client/tp0.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	close(conexion);
}

