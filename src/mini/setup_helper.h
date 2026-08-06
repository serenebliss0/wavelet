#include "mini/qr_setup.h"
#include "lvgl.h"

String color = "pink"; //change this color var
String model = "mini";

String getSetupPayload(){
    return buildQRPayload(model, color);
}
