/*
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Davide Pollarolo
 * email:   davide.pollarolo@iit.it
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

/* @file        EoMCConfigurations.c
    @brief      This file keeps ...
    @author     davide.pollarolo@iit.it
    @date       29/04/2015
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EoMCConfigurations.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------

// it contains a pair {value, configuration}
typedef struct // 2B+12*4B = 50B
{
    uint16_t                value;
    eOmcconfig_jomo_cfg_t   jomos[eomcconfig_jomo_maxnumberof];
} eomcconfig_codeconfig_t;  EO_VERIFYsizeof(eomcconfig_codeconfig_t, 50);

// it contains a pair {string, value}
typedef struct
{
    const char*             string;
    uint16_t                value;
} eomcconfig_valuestring_t;  EO_VERIFYsizeof(eomcconfig_valuestring_t, 8);


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

static const uint16_t s_eomcconfig_maxvalue_in_type[] =
{
    eOmcconfig_value_2FOC_numberof,
    eOmcconfig_value_MC4CAN_numberof,
    eOmcconfig_value_MC4PLUS_numberof
};  EO_VERIFYsizeof(s_eomcconfig_maxvalue_in_type, eOmcconfig_type_numberof*sizeof(uint16_t)); //check correctness

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------

const eOmcconfig_code_t eOmcconfig_code_dummy = EOMCCONFIG_CODE_DUMMY;
const eOmcconfig_value_t eOmcconfig_value_dummy = EOMCCONFIG_VALUE_DUMMY;

const eOmcconfig_jomo_cfg_t dummy_jomo = {0};
// - begin of: section for configuration 
// - fill the configurations in here for all the known boards 

//use EOINIT here to initialize everything
const eomcconfig_codeconfig_t eomcconfig_codeconfig_2FOC[] =
{
    {EO_INIT(.value) eOmcconfig_value_2FOC_unspecified}
}; EO_VERIFYsizeof(eomcconfig_codeconfig_2FOC, eOmcconfig_value_2FOC_numberof*sizeof(const eomcconfig_codeconfig_t)); 

const eomcconfig_codeconfig_t eomcconfig_codeconfig_MC4CAN[] =
{
    {EO_INIT(.value) eOmcconfig_value_MC4CAN_unspecified}
}; EO_VERIFYsizeof(eomcconfig_codeconfig_MC4CAN, eOmcconfig_value_MC4CAN_numberof*sizeof(const eomcconfig_codeconfig_t)); 

const eomcconfig_codeconfig_t eomcconfig_codeconfig_MC4PLUS[] =
{
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_unspecified},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_experimental, EO_INIT(.jomos[0].actuator.local.type)  1, EO_INIT(.jomos[0].actuator.local.index) 2, EO_INIT(.jomos[0].encoder.etype)  2, EO_INIT(.jomos[0].encoder.index)  2},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b0},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b1},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b7},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b9}
}; EO_VERIFYsizeof(eomcconfig_codeconfig_MC4PLUS, eOmcconfig_value_MC4PLUS_numberof*sizeof(const eomcconfig_codeconfig_t)); 

const eomcconfig_valuestring_t eomcconfig_valuestring_MC4PLUS[] =
{
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_unspecified,  EO_INIT(.string) "Unspecified configuration"},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_experimental, EO_INIT(.string) "MC4Plus_experimental_jig"},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b0,           EO_INIT(.string) "MC4plus_b0"},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b1,           EO_INIT(.string) "MC4plus_b1"},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b7,           EO_INIT(.string) "MC4plus_b7"},
    {EO_INIT(.value) eOmcconfig_value_MC4PLUS_b9,           EO_INIT(.string) "MC4plus_b9"},
};


//const pointer reference to const structures
const eomcconfig_codeconfig_t * const eomcconfig_codeconfigs[] =
{   
    (const eomcconfig_codeconfig_t *)&eomcconfig_codeconfig_2FOC,   
    (const eomcconfig_codeconfig_t *)&eomcconfig_codeconfig_MC4CAN,        
    (const eomcconfig_codeconfig_t *)&eomcconfig_codeconfig_MC4PLUS,
};  EO_VERIFYsizeof(eomcconfig_codeconfigs, eOmcconfig_type_numberof*sizeof(const eomcconfig_codeconfig_t *));  

const eomcconfig_valuestring_t * const eomcconfig_valuestrings[] =
{   
    (const eomcconfig_valuestring_t *)NULL, //not handled   
    (const eomcconfig_valuestring_t *)NULL, //not handled       
    (const eomcconfig_valuestring_t *)&eomcconfig_valuestring_MC4PLUS,
};
 

// - end of: section for configuration 


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

extern eOmcconfig_code_t eOmcconfig_code_get(eOmcconfig_type_t type, eOmcconfig_value_t val)
{
    eOmcconfig_code_t cc = 0;
    
    uint16_t t = (uint16_t)type;
    
    if(t > eOmcconfig_type_numberof)
    {
        return(eOmcconfig_code_dummy);
    }
    
    if(val > s_eomcconfig_maxvalue_in_type[t-1])
    {
        return(eOmcconfig_code_dummy);
    }
     
    cc = EOMCCONFIGCODE(t, val);

    return(cc);
}


extern eOmcconfig_type_t eOmcconfig_code2type(eOmcconfig_code_t code)
{
    uint16_t type = (code & EOMCCONFIG_TYPE_MASK) >> EOMCCONFIG_TYPE_SHIFT;
        
    if(type > eOmcconfig_type_numberof)
    {
        return(eOmcconfig_type_dummy);
    }
    
    return((eOmcconfig_type_t)type);    
}


extern eOmcconfig_value_t eOmcconfig_code2value(eOmcconfig_code_t code)
{  
    eOmcconfig_type_t type = eOmcconfig_code2type(code);
    uint16_t val = code & EOMCCONFIG_VALUE_MASK;
    
    if(eOmcconfig_value_dummy == type)
    {
        return(eOmcconfig_value_dummy);
    }
       
    if(val > s_eomcconfig_maxvalue_in_type[type -1])
    {
        return(eOmcconfig_value_dummy);
    }
        
    return(val);    
}

extern const eOmcconfig_jomo_cfg_t* eOmcconfig_code2config(eOmcconfig_code_t code)
{
    eOmcconfig_type_t type = eOmcconfig_code2type(code);
    eOmcconfig_value_t val = eOmcconfig_code2value(code);
    
    if((eOmcconfig_type_dummy == type) || (eOmcconfig_value_dummy == val))
    {
        return(NULL);
    }
    
    if(NULL == eomcconfig_codeconfigs[type -1])
    {
        return(NULL);
    }

    if(val != eomcconfig_codeconfigs[type -1][val].value)
    {
        return(NULL);
    }
    
    return(eomcconfig_codeconfigs[type -1][val].jomos);
}

extern eOmcconfig_value_t eOmcconfig_string2value(const char * str, eOmcconfig_type_t type)
{
    if((type > eOmcconfig_type_numberof) || (str == NULL))
    {
        return(eOmcconfig_value_dummy);
    }
    //search here the right string for the specified config
    uint8_t i = 0;
    for (;i < eOmcconfig_value_MC4PLUS_numberof; i++)
    {
        if (strcmp(eomcconfig_valuestrings[type-1][i].string, str) == 0)
        {
            return eomcconfig_valuestrings[type-1][i].value;
        }
    }
    
    // string not found
    return eOmcconfig_value_dummy;
}
//deprecated
/*
extern const char* eoerror_code2string(eOerror_code_t code)
{
    static const char interror_codeunrecognised[] = "eoerror_INTERNALERROR__codeunrecognised";
    static const char interror_categoryisempty[] = "eoerror_INTERNALERROR__categoryisempty";
    static const char interror_valueisempty[] = "eoerror_INTERNALERROR__valueisempty";
    static const char interror_stringatwrongplace[] = "eoerror_INTERNALERROR__stringatwrongplace";
       
    eOerror_category_t cat = eoerror_code2category(code);
    eOerror_value_t val = eoerror_code2value(code);
    
    if((eoerror_category_dummy == cat) || (eoerror_value_dummy == val))
    {
        return(interror_codeunrecognised);
    }
    
    if(NULL == eoerror_valuestrings[cat])
    {
        return(interror_categoryisempty);
    }

    if(NULL == eoerror_valuestrings[cat][val].string)
    {
        return(interror_valueisempty);
    }

    if(val != eoerror_valuestrings[cat][val].value)
    {
        return(interror_stringatwrongplace);
    }
    
    return(eoerror_valuestrings[cat][val].string);
}
*/


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


