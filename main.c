#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#if 0
typedef struct {
    uint8_t avg_samples; //Average Number of Samples to get one value
    uint8_t time_capt_sample; //Time for capture one sample. The avg number (seconds)
    uint8_t time_loop_capt; 
    uint8_t PWM_pin; //
    uint8_t capt_sensor_pin; // Pin of measure sensor to get values
    uint8_t heat_sensor_pin; // Pin of measure sensor to heat the sensor
    uint16_t resist_measure; // Value measure of the internal variable resistance
    uint16_t resist_install; // Value of installed resistance
    uint8_t HT_sensor; // Humidity and Temperature sensor
    uint8_t voltage; // Voltage value used
    //ptr inicializate ADC_PWM
    //ptr tratamiento captura fichero
    uint8_t file_desc_save; // Descriptor file to save information
    uint8_t save_path[100]; // Path to save the capture data
} Elect_Nose;
#endif

typedef struct {
    FileReader fr;
    Experiment_Config exp;
    HW_Config hw;
}Elect_Nose;

#define exp_str(x)  (x->exp)
#define hw_str(x)   (x->hw)

int8_t create_saves_file(Elect_Nose* en)
{
    struct sb sb;
    if((stat(path(exp_str(en)), &sb) != 0))// ||
      /* (S_ISDIR(sb.st_mode))) */{
        if(mkdir(path(exp_str(en)), 0755))
            return -1;
    }

    char name[100];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    uint8_t aux = strcpy(&name[0], path(exp_str(en)));
    sprintf(&name[aux], "_%d-%d-%d--%d-%d-%d%c", (tm->tm_year+1900), (tm->tm_mon+1), 
        tm->mday, tm->hour, tm->min, tm->sec, 0);
    
    save_file(exp_str(en)) = open((char *)name, O_CREAT, (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
    if(save_file(exp_str(en)) == -1)
        return -1;

    return;
}

int capt_sample(Elec_Nose* en, bool init_sample)
{
    time_t t_ini = time(NULL);
    uint16_t sample = 0;
    
    for(uint8_t i = 0; i < en->avg_samples; i++) {
        sample+=en->read_sample();
        sleep(en->time_capt_sample); //Ver si poner en milisegundos
    }

    sample/=en->avg_samples;
    en->resist_measure = (((en->voltage * en->resist_install) / (sample / 1000.0)) - en->resist_install);
    //en->adapt_PWM_sensor_heat();
    save_data_file(sample, en->resist_measure);
    sleep(en->time_loop_capt - (time(NULL) - t_ini));

    return 1;
}

int capt_odor(Elect_Nose* en)
{
    create_saves_file(en);
    en->iniciate_IO_pins(); //Ptr function

    //Capture the x initial samples
    for(uint8_t i = 0; i < en->init_sampls; i++)
        capt_sample(en, false);

    //Capture the x seconds of samples wanted
    for(uint8_t i = 0; i < en->init_sampls; i++)
        capt_sample(en, true);

    close(en->file_desc_save);
    en->close_IO_pins();
    return 1;
}


