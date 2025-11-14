bool nextState(const uint8_t mask[], enum estados stateMatch, enum estados stateOther){
// Esta función recibe una máscara "mask" para comparar con el registro devuelto
// al consultar el registro de estados del chip RN2903.
// Luego cambia el estado state = stateMatch si coincide
// ó state = sateOther si no coincide.
// devuelve un booleno true si coincidió
  
  bool match = true; // si fuera vector nulo matchea siempre
  int i = 0;
    
  lora.statusView(false);
  lora.getStatusVector(statusEESAMR34); 
    
  for( i = 0; i < STATUS_EESAMR34_LEN; i++){ 
    if(mask[i]){ // compara solo si la máscara es distanta de '0'
      if(statusEESAMR34[i] & mask[i]){
        state = stateMatch;
        match = true;
      }
      else{
        state = stateOther;
        match = false;
        break;     
      }
    }
  }

  return match;

}
