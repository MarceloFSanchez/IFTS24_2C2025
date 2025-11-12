void inicioRtc(){
    rtc.begin();
    
    /*Definimos variables para el inicio de HH:MM:SS */
    const byte seconds = 0;
    const byte minutes = 0;
    const byte hours = 0;

    /*Definimos variables para el inicio de DD:MM:AA */
    const byte day = 1;
    const byte month = 6;
    const byte year = 22;

    rtc.setTime(hours, minutes, seconds);
    rtc.setDate(day, month, year);
}
