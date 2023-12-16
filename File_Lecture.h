#ifndef FILE_LECTURE
#define FILE_LECTURE

#define PWM_PORT_TYPE   ((uint8_t) 0)
#define ADC_PORT_TYPE   ((uint8_t) 1)
#define GPIO_PORT_TYPE  ((uint8_t) 2)

typedef struct{
    uint8_t capt_modul; //Modulation algoritm to use
    uint8_t init_samples; //Initial samples to capture
    uint8_t capt_samples; //Number of samples to capture
    //succion motor
    uint8_t file_desc_save; // Descriptor file to save information
    uint8_t save_path[100]; //Save path of the capture data
    //ptr inicializate ADC_PWM
    //ptr tratamiento captura fichero   
}Experiment_Config;

#define init_samples(x) (x->init_samples)
#define capt_samples(x) (x->capt_samples)
#define save_file(x)    (x->file_desc_save)
#define path(x)         (x->save_path)

typedef struct{
    //succion motor pin
    uint8_t heat_sensor_pin; // Heat sensor pin id
    uint8_t read_sensor_pin; // Read sensor pin id
    uint8_t TH_read_sensor_pin; //Temp & Humidity sensor read pin
    uint8_t TH_sensor_type; //Temperature&Humidity sensor type
    uint8_t avg_samples; //Average Number of Samples to get one value
    uint8_t time_capt_sample; //Time for capture one sample. The avg number (seconds)
    uint8_t time_loop_capt; //Total time (in seconds) to the hole one sample capture  
    uint8_t voltage; // Voltage value used
    uint16_t resist_measure; // Value measure of the internal variable resistance
    uint16_t resist_install; // Value of installed resistance
}HW_Config;

#define heat_pin(x)     (x->heat_sensor_pin)
#define read_pin(x)     (x->read_sensor_pin)
#define avg_samples(x)  (x->avg_samples)

int8_t check_experiment_config_values(uint32_t* read_vals, Experiment_Config* exp_config);
int8_t check_HW_config_values(uint32_t* read_vals, HW_Config* hw);
void read_experiment_line(FileReader* fr, Capt_Spec* exp, HW_Config* hw);

int8_t (* ptr_func_anal_ports)(uint8_t id_port, uint8_t type_port);
int8_t (* ptr_func_modul_exp)(uint32_t* read_vals, Experiment_Config* exp_config);

static ptr_func_anal_ports ptr_func_hw_ports;
static ptr_func_modul_exp ptr_func_exp_capture;

//static array of functions to analyze the ports of the hardware
static ptr_func_anal_ports arr_funcs_ports_hw[1];
static potr_func_modul_exp arr_funcs_exp_modul[1];

#endif /* FILE_LECTURE */
