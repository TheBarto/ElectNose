#ifndef EN_STRUCT_H
#define EN_STRUCT_H

#define PWM_PORT_TYPE   ((uint8_t) 0)
#define ADC_PORT_TYPE   ((uint8_t) 1)
#define GPIO_PORT_TYPE  ((uint8_t) 2)

typedef int8_t (* ptr_func_initialize_pwm)(int);
typedef int8_t (* ptr_func_initialize_adc)(int);
typedef int8_t (* ptr_func_initialize_gpio)(int);

typedef struct{
    uint8_t capt_modul; //Modulation algoritm to use
    uint8_t init_samples; //Initial samples to capture
    uint8_t capt_samples; //Number of samples to capture
    //succion motor
    uint8_t file_desc_save; // Descriptor file to save information
    uint8_t save_path[100]; //Save path of the capture data
    uint16_t resist_measure; // Value measure of the internal variable resistance
    //ptr inicializate ADC, PWM, GPIOs
    ptr_func_initialize_pwm init_pwm;
    ptr_func_initialize_adc init_adc;
    ptr_func_initialize_gpio init_gpio;
    //ptr free ADC, PWM, GPIOs
    //ptr tratamiento captura datos 
    //ptr get sample from adc, gpio, pwm
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
    uint16_t resist_install; // Value of installed resistance
}HW_Config;

#define time_capt_sample(x) (x->time_capt_sample)
#define heat_pin(x)         (x->heat_sensor_pin)
#define read_pin(x)         (x->read_sensor_pin)
#define avg_samples(x)      (x->avg_samples)

typedef struct {
    FileReader fr;
    Experiment_Config exp;
    HW_Config hw;
}Elect_Nose;

#define exp_str(x)  (x->exp)
#define hw_str(x)   (x->hw)

#endif //EN_STRUCT_H
