#ifndef __BSP_H
#define __BSP_H

#include <os_cpu.h>
#include <os_cfg.h>
#include <app_cfg.h>
#include <ucos_ii.h>


// Add interfaces to the specific hardware for use by application code
#include "discoveryboard.h"
#include "hw_init.h"
#include "bspLed.h"
#include "bspUart.h"

#endif /* __BSP_H */