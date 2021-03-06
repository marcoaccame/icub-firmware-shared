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

// - include guard ----------------------------------------------------------------------------------------------------
#ifndef _EOVMUTEX_H_
#define _EOVMUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @file       EOVmutex.h
    @brief      This header file implements public interface to a mutex object.
    @author     marco.accame@iit.it
    @date       08/03/2011
**/

/** @defgroup eov_mutex Object EOVmutex
    The EOVmutex is an abstract object used to derive a mutex object for the singletask or multitask execution environments.
    The EOVmutex exposes only pure virtual methods which have to be defined inside the derived object.
    The user shall create a derived object (e.g., EOMmutex *mm) and then she/he can use it in the normal way with the 
    methods of the derived objects (e.g., eom_mutex_Take(mm, ...)) or also with the methods of the abstract object
    EOVmutex (e.g., eov_mutex_Take(mm, ...)).
    
    An advanced user who wants to derive an object from EOVmutex shall include its hidden interfaces and provide
    function pointers to fill the hidden vtable.  As a reference, see the implementations of EOMmutex and of EOSmutex.
    
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "EoCommon.h"



// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
  

// - declaration of public user-defined types ------------------------------------------------------------------------- 
 

/** @typedef    typedef struct EOVmutex_hid EOVmutex
    @brief      EOVmutex is an opaque struct. It is used to implement data abstraction for the mutex 
                object so that the user cannot see its private fields and he/she is forced to manipulate the
                object only with the proper public functions. 
 **/  
typedef struct EOVmutex_hid EOVmutex;


/** @typedef    typedef void EOVmutexDerived
    @brief      EOVmutexDerived is used to implement polymorphism in the objects derived from EoMutex
 **/
typedef void EOVmutexDerived;


/** @typedef    typedef EOVmutexDerived* (*eov_mutex_fn_mutexderived_new)(void)
    @brief      eov_mutexderived_fn_new is used to represent a pointer to a function which allocates a derived mutex.
 **/
typedef EOVmutexDerived* (*eov_mutex_fn_mutexderived_new)(void);

/** @typedef    typedef void (*eov_mutex_fn_mutexderived_delete)(EOVmutexDerived* m)
    @brief      eov_mutexderived_fn_delete is used to represent a pointer to a function which deallocates a derived mutex.
 **/
typedef void (*eov_mutex_fn_mutexderived_delete)(EOVmutexDerived* m);
    
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------
// empty-section


// - declaration of extern public functions ---------------------------------------------------------------------------
 

/** @fn         extern eOpurevirtual eOresult_t eov_mutex_Take(EOVmutexDerived *d, eOreltime_t tout)
    @brief      Waits until the mutex is either taken or the timeout has expired
    @param      d               Pointer to the mutex-derived object
    @param      tout           Timeout in micro-seconds. for no-wait or infinite wait use proper values.
    @return     eores_OK in case of success. eores_NOK_timeout upon failure to take the mutex, or 
                or eores_NOK_nullpointer if mutex is NULL.
    @warning    This function cannot be used with a EOVmutex object but only with one object derived
                from it.
 **/
extern eOpurevirtual eOresult_t eov_mutex_Take(EOVmutexDerived *d, eOreltime_t tout);


/** @fn         extern eOpurevirtual eOresult_t eov_mutex_Release(EOVmutexDerived *mutex)
    @brief      Releases the mutex. 
    @param      d               Pointer to the mutex-derived object
    @return     eores_OK in case of success. osal_res_NOK_generic upon failure to release the mutex, or 
                or eores_NOK_nullpointer if mutex is NULL.
    @warning    This function cannot be used with a EOVmutex object but only with one object derived
                from it.
 **/
extern eOpurevirtual eOresult_t eov_mutex_Release(EOVmutexDerived *d);


/** @fn         extern eOpurevirtual void eov_mutex_Delete(EOVmutexDerived *d)
    @brief      Deletes the mutex. 
    @param      d               Pointer to the mutex-derived object
    @warning    This function cannot be used with a EOVmutex object but only with one object derived
                from it.
 **/
extern eOpurevirtual void eov_mutex_Delete(EOVmutexDerived *d);



/** @}            
    end of group eov_mutex  
 **/

#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



