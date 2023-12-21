#include "File_Lecture.h"

static ptr_func_anal_ports arr_funcs_ports_hw[1] = {analyze_BB_Black_ports};
static ptr_func_modul_exp arr_funcs_exp_modul[0] = {};


//Comprobar mejor los puertos segun su uso.
static int8_t analyze_BB_Black_ports(uint8_t port_id, uint8_t port_type)
{

    if(port_type == PWM_PORT_TYPE)
        if(port_id > 29)
            return -1;
    else
        if(port_id > 96)
            return -1;

    return 0;
}

void read_experiment_line(FileReader* fr, Capt_Spec* exp, HW_Config* hw) {
    
    //Poner bien. Generico static? QUITAR MAGIC NUMBER.
    uint32_t dst_array[20];
    int32_t tot_rd = 0;
    if(!hw) {
        tot_rd = read_line(fr, '-', dst_array);
        if(tot_rd < 0)
            return;
        check_HW_config_values(dst_array, hw);
    }
    
    tot_rd = read_line(fr, ':', dst_array);
    check_exp_config_values(dst_array, exp);
    
    return;
}

int8_t check_HW_config_values(uint32_t* read_vals, HW_Config* hw)
{
    ptr_func_hw_ports = arr_funcs_ports_hw[arr[0]];
    
    if(read_vals[1] > 30) //No more than 30 avg samples to calculate the read value
        return -1;
    hw->avg_samples = read_vals[1];

    if(read_vals[2] > 10) //No more than 10 secons of wait for sample
        return -1;
    hw->time_capt_sample = read_vals[2];

    if(read_vals[3] > 10) //No more than 10 seconds of wait for sample
        return -1;
    hw->time_capt_sample = read_vals[3];

    if(read_vals[4] > 1000) //No more than milliseconds of wait for
        return -1;
    hw->time_loop_capt = (read_vals[4]/hw->avg_samples);

    hw->voltage = read_vals[5];
    hw->resist_install = read_vals[6];
    
    if(ptr_func_hw_ports(&read_vals[7], PWM_PORT_TYPE))
        return -1;
    hw->heat_sensor_pin = read_vals[7];
    
    if(ptr_func_hw_ports(&read_vals[8], ADC_PORT_TYPE))
        return -1;
    hw->read_sensor_pin = read_vals[8];

    if(ptr_func_hw_ports(&read_vals[9], ADC_PORT_TYPE))
        return -1;
    hw->TH_read_sensor_pin = read_vals[9];

    /*if(ptr_func_hw_ports(&read_vals[10], ??))
        return -1;*/
    hw->TH_sensor_type = read_vals[10];

    return 0;
}

int8_t check_experiment_config_values(uint32_t* read_vals, Experiment_Config* exp_config)
{
    
    if(read_vals[0] != 1)
        return -1;
    exp_config->capt_modul = read_vals[0];
    ptr_func_exp_capture = arr_funcs_exp_modul[read_vals[0]];

    if(read_vals[1] != 1)
        return -1;
    exp_config->init_samples = read_vals[1];
    
    if(read_vals[2] != 1)
        return -1;
    exp_config->capt_samples = read_vals[2];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t); //Usar string static en el sprintf
    sprintf(&hw->save_path[0],"capture_values/%s/%d_%d_%d",
            modulations_types[read_vals[0]], (tm->tm_year+1900), (tm->tm_mon+1), tm->mday);

    ptr_func_exp_capture(&read_vals[3], exp_config);
    return 0;
}

