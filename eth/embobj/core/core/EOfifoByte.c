/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
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

// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h"
#include "EoCommon.h"
#include "string.h"
#include "EOtheMemoryPool.h"
#include "EOtheErrorManager.h"

#include "EOfifo_hid.h"



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EOfifoByte.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------

#include "EOfifoByte_hid.h" 


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

static const char s_eobj_ownname[] = "EOfifoByte";


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------


extern EOfifoByte* eo_fifobyte_New(eOsizecntnr_t capacity, EOVmutexDerived *mutex) 
{
    EOfifoByte *retptr = NULL; 
    
    // i get memory for a fifobyte. it can never be NULL 
    retptr = (EOfifoByte*) eo_mempool_GetMemory(eo_mempool_GetHandle(), eo_mempool_align_32bit, sizeof(EOfifoByte), 1);

    eo_errman_Assert(eo_errman_GetHandle(), (0 != capacity), "eo_fifobyte_New(): 0 capacity", s_eobj_ownname, &eo_errman_DescrWrongParamLocal);

    // now i create a fifo made of bytes (no ctor or dtor!) and i fill it into the fifo of 
    // the fifobyte. it can never be NULL 
    retptr->fifo = eo_fifo_New(1, capacity, NULL, 0, NULL, NULL, mutex);

    // ok, done
    return(retptr);
}


extern void eo_fifobyte_Delete(EOfifoByte *fifobyte) 
{
    if(NULL == fifobyte)
    {
        return;
    }

    if(NULL == fifobyte->fifo)
    {
        return;
    }

    eo_fifobyte_Clear(fifobyte, eok_reltimeINFINITE);
    
    eo_fifo_Delete(fifobyte->fifo);
    
    memset(fifobyte, 0, sizeof(EOfifoByte));    
    eo_mempool_Delete(eo_mempool_GetHandle(), fifobyte);
    return;  
}


extern eOresult_t eo_fifobyte_Capacity(EOfifoByte *fifobyte, eOsizecntnr_t *capacity, eOreltime_t tout) 
{
    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }
    return(eo_fifo_Capacity(fifobyte->fifo, capacity, tout));
}


extern eOresult_t eo_fifobyte_Size(EOfifoByte *fifobyte, eOsizecntnr_t *size, eOreltime_t tout) 
{
    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }
    return(eo_fifo_Size(fifobyte->fifo, size, tout));
}


extern eOresult_t eo_fifobyte_Put(EOfifoByte *fifobyte, uint8_t item, eOreltime_t tout) 
{
    // marco.accame: i dont like using the address of a function parameter which is stored in a register.
    // even if it is perfectly safe to do so, i prefer using the address of a variable on the stack.
    uint8_t myitem = item;
    
    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }
    return(eo_fifo_Put(fifobyte->fifo, &myitem, tout));
}

extern eOresult_t eo_fifobyte_Get(EOfifoByte *fifobyte, uint8_t *item, eOreltime_t tout) 
{
    const void *fitem = NULL;
    eOresult_t res = eores_NOK_generic;

    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }

    res = eo_fifo_Get(fifobyte->fifo, &fitem, tout);

    if(fitem != NULL) 
    {
        *item = *((uint8_t *)fitem); 
    }
    
    return(res);    
}


extern eOresult_t eo_fifobyte_Rem(EOfifoByte *fifobyte, eOreltime_t tout) 
{
    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }

    return(eo_fifo_Rem(fifobyte->fifo, tout));
}


extern eOresult_t eo_fifobyte_Clear(EOfifoByte *fifobyte, eOreltime_t tout) 
{
    if(NULL == fifobyte)
    {
        return(eores_NOK_nullpointer);
    }

    return(eo_fifo_Clear(fifobyte->fifo, tout));
}

// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section




// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------




