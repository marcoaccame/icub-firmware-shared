/*
 * Copyright (C) 2013 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EOPROTOCOLEPAS_ROM_H_
#define _EOPROTOCOLEPAS_ROM_H_




/** @file       EoProtocolEPas_rom.h
	@brief      This header file gives the constant configuration for the NVs in mc endpoints
	@author     marco.accame@iit.it
	@date       05/29/2013
**/

/** @defgroup eo_asfdgr23433 Configuration of the NVs ..
    Tcecece 
    
    @{		
 **/



// - external dependencies --------------------------------------------------------------------------------------------

#include "EoProtocolCommon.h"
#include "EoProtocolEPas.h"
#include "EoAnalogSensors.h"

 

// - public #define  --------------------------------------------------------------------------------------------------
// empty-section



// - declaration of public user-defined types ------------------------------------------------------------------------- 


    
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------

extern const eOas_strain_t eoprot_ep_as_rom_strain_defaultvalue;
extern const eOas_mais_t eoprot_ep_as_rom_mais_defaultvalue;


// - declaration of extern public functions ---------------------------------------------------------------------------

extern uint16_t eoprot_ep_as_rom_epid2progressivenumber(eOprotEP_t ep, eOprotID_t id);
extern uint16_t eoprot_ep_as_rom_epid2sizeofvar(eOprotEP_t ep, eOprotID_t id);
extern void* eoprot_ep_as_rom_dataepid2nvram(void* data, eOprotEP_t ep, eOprotID_t id);
extern void* eoprot_ep_as_rom_epid2nvrom(eOprotEP_t ep, eOprotID_t id);


/** @}            
    end of group eo_asfdgr23433  
 **/

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------









