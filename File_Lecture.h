#ifndef FILE_LECTURE
#define FILE_LECTURE

#include "EN_struct.h"
#include <stdint.h>

//Ptr a funcion que segun el hardware analiza si los puertos introducidos son correctos
typedef int8_t (* ptr_func_anal_ports)(uint8_t id_port, uint8_t type_port);

//Ptr a funcion que analiza los parametros extras de los diferentes algoritmos de captura
typedef int8_t (* ptr_func_modul_exp)(uint32_t* read_vals, Experiment_Config* exp_config);

int8_t check_experiment_config_values(uint32_t* read_vals, Experiment_Config* exp_config);
int8_t check_HW_config_values(uint32_t* read_vals, HW_Config* hw);
void read_experiment_line(FileReader* fr, Capt_Spec* exp, HW_Config* hw);

static ptr_func_anal_ports* ptr_func_hw_ports;
static ptr_func_modul_exp* ptr_func_exp_capture;

//static array of functions to analyze the ports of the hardware
static ptr_func_anal_ports arr_funcs_ports_hw[1];
static potr_func_modul_exp arr_funcs_exp_modul[1];

#endif /* FILE_LECTURE */
