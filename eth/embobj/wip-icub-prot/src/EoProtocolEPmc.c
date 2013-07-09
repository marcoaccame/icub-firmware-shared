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

/* @file       EoProtocolEPmc.c
    @brief      This file keeps ...
    @author     marco.accame@iit.it
    @date       06/05/2013
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"

#include "EoProtocolEPmc_rom.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EoProtocolEPmc.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------

#if !defined(EOCFG_EPS_BOARDS_MAXNUMBER)
    #define EOCFG_EPS_BOARDS_MAXNUMBER 10
#endif


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------

// - guard on max number of entities
EO_VERIFYproposition(eoprot_ep_mc_dew4, eoprot_ep_mc_entities_numberof <= eoprot_entities_maxnumberof);

// - guard on tags ...
EO_VERIFYproposition(eoprot_ep_mc_tagsnum_jo, eoprot_ep_mc_tags_joint_numberof == eoprot_ep_mc_rwmodes_joint_numberof);
EO_VERIFYproposition(eoprot_ep_mc_tagsmax_jo, eoprot_ep_mc_tags_joint_numberof <= eoprot_tags_maxnumberof);

EO_VERIFYproposition(eoprot_ep_mc_tagsnum_mo, eoprot_ep_mc_tags_motor_numberof == eoprot_ep_mc_rwmodes_motor_numberof);
EO_VERIFYproposition(eoprot_ep_mc_tagsmax_mo, eoprot_ep_mc_tags_motor_numberof <= eoprot_tags_maxnumberof);

EO_VERIFYproposition(eoprot_ep_mc_tagsnum_co, eoprot_ep_mc_tags_controller_numberof == eoprot_ep_mc_rwmodes_controller_numberof);
EO_VERIFYproposition(eoprot_ep_mc_tagsmax_co, eoprot_ep_mc_tags_controller_numberof <= eoprot_tags_maxnumberof);
  

// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

static uint16_t s_eoprot_ep_mc_brdentity2ramoffset(eOprotBRD_t brd, eOprotEntity_t entity);
static uint16_t s_eoprot_ep_mc_brdid2ramoffset(eOprotBRD_t brd, eOprotID32_t id);

static eObool_t s_eoprot_ep_mc_tag_joint_is_valid(eOprotTag_t tag);
static eObool_t s_eoprot_ep_mc_tag_motor_is_valid(eOprotTag_t tag);
static eObool_t s_eoprot_ep_mc_tag_controller_is_valid(eOprotTag_t tag);


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

#if 0   // dynamic mode
static const uint8_t** s_eoprot_ep_mc_board_numberofeachentity = NULL; // s_eoprot_ep_mc_board_numberofeachentity[brd][entype] tells how many entities of kind entype are in brd
static uint16_t s_eoprot_ep_mc_board_numberofthem = 0;
#endif
static const uint8_t* s_eoprot_ep_mc_board_numberofeachentity[EOCFG_EPS_BOARDS_MAXNUMBER] = { NULL };
static const uint16_t s_eoprot_ep_mc_board_numberofthem = EOCFG_EPS_BOARDS_MAXNUMBER;


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

#if 0   // dynamic mode
extern eOresult_t eoprot_ep_mc_number_of_boards_Load(uint16_t numofboards)
{
    if((0 != s_eoprot_ep_mc_board_numberofthem) || (NULL != s_eoprot_ep_mc_board_numberofeachentity))
    {
        return(eores_NOK_generic);
    }
    
    s_eoprot_ep_mc_board_numberofthem = numofboards;
    s_eoprot_ep_mc_board_numberofeachentity = (const uint8_t**) calloc(numofboards, sizeof(uint8_t*));
    
    return(eores_OK);   
}
#endif

extern eOresult_t eoprot_ep_mc_number_of_entities_Load(eOprotBRD_t brd, const uint8_t* numberofeachentity)
{
    if(NULL == s_eoprot_ep_mc_board_numberofeachentity)
    {
        return(eores_NOK_generic);
    }
    
    if(brd > s_eoprot_ep_mc_board_numberofthem)
    {
        return(eores_NOK_generic);
    }
        
    s_eoprot_ep_mc_board_numberofeachentity[brd] = numberofeachentity;
    
    return(eores_OK);       
}

extern eObool_t eoprot_ep_mc_variables_id_isvalid(eOprotBRD_t brd, eOprotID32_t id)
{
    eObool_t ret = eobool_false;    
    
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(eobool_false);
    }    
    
    eOprotEntity_t ent = eoprot_ep_variable_ID2entity(id);
    eOprotIndex_t  ind = eoprot_ep_variable_ID2index(id);
    eOprotTag_t    tag = eoprot_ep_variable_ID2tag(id);
    
    switch(ent)
    {
        case eomc_entity_joint:
        {   
            if(ind < s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint])
            {
                ret = s_eoprot_ep_mc_tag_joint_is_valid(tag);
            }            
        } break;
        
        case eomc_entity_motor:
        {
            if(ind < s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor]) 
            {
                ret = s_eoprot_ep_mc_tag_motor_is_valid(tag);
            }            
        } break;        
 
        case eomc_entity_controller:
        {
            if(ind < s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_controller]) 
            {
                ret = s_eoprot_ep_mc_tag_controller_is_valid(tag);
            }            
        } break; 
        
        default:
        {           
        } break;        
    }
    
    return(ret);     
}


extern uint16_t eoprot_ep_mc_variables_numberof_Get(eOprotBRD_t brd)
{
    uint16_t num = 0;
    
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(0);
    }
    
    num = eoprot_ep_mc_tags_joint_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint] +
          eoprot_ep_mc_tags_motor_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor] +
          eoprot_ep_mc_tags_controller_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_controller];
          
    return(num);
}

extern eOprotID32_t eoprot_ep_mc_variable_idfromprognumber_Get(eOprotBRD_t brd, eOprotPROGnum_t prog)
{
    eOprotTag_t tag = 0xff;
    eOprotIndex_t index = 0xff;
    eOprotEntity_t entity = 0xff;
    
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(EOK_uint32dummy);
    }
    
    eOprotPROGnum_t progsinjoints = eoprot_ep_mc_tags_joint_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint];
    eOprotPROGnum_t progsinmotors = eoprot_ep_mc_tags_motor_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor];
    eOprotPROGnum_t progsincontrollers = eoprot_ep_mc_tags_controller_numberof * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_controller];
    
    if((0 != progsinjoints) && (prog < (progsinjoints)))
    {   // entity is eomc_entity_joint 
        entity  = eomc_entity_joint;
        index   = prog / eoprot_ep_mc_tags_joint_numberof;       // eoprot_ep_mc_tags_joint_numberof cannot be zero if progsinjoints is non-zero
        tag     = prog % eoprot_ep_mc_tags_joint_numberof;        
    }
    else if((0 != progsinmotors) && (prog < (progsinjoints + progsinmotors)))
    {   // entity is eomc_entity_motor 
        prog -= (progsinjoints);
        entity  = eomc_entity_motor;
        index   = prog / eoprot_ep_mc_tags_motor_numberof;       // eoprot_ep_mc_tags_motor_numberof cannot be zero if progsinmotors is non-zero
        tag     = prog % eoprot_ep_mc_tags_motor_numberof;                      
    }
    else if((0 != progsincontrollers) && (prog < (progsinjoints + progsinmotors + progsincontrollers)))
    {   // entity is eomc_entity_controller 
        prog -= (progsinjoints+progsinmotors);
        entity  = eomc_entity_controller;
        index   = prog / eoprot_ep_mc_tags_controller_numberof;       // eoprot_ep_mc_tags_controller_numberof cannot be zero if progsincontrollers is non-zero
        tag     = prog % eoprot_ep_mc_tags_controller_numberof;                      
    }    
    else
    {
        return(EOK_uint32dummy);
    }
    
    return(eoprot_ep_variable_ID_get(eoprot_endpoint_motioncontrol, entity, index, tag));
    
}


extern eOprotPROGnum_t eoprot_ep_mc_variable_progressivenumber_Get(eOprotBRD_t brd, eOprotID32_t id)
{
    eOprotPROGnum_t prog = EOK_uint32dummy;
    
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(EOK_uint32dummy);
    }
    
    eOprotEntity_t entity = eoprot_ep_variable_ID2entity(id);
    eOprotIndex_t index = eoprot_ep_variable_ID2index(id);
    switch(entity)
    {
        case eomc_entity_joint: 
        {
            prog = index*eoprot_ep_mc_tags_joint_numberof + eoprot_ep_mc_rom_get_prognum(id);
        } break;
        
        case eomc_entity_motor: 
        {
            prog = s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint]*eoprot_ep_mc_tags_joint_numberof +
                   index*eoprot_ep_mc_tags_motor_numberof + eoprot_ep_mc_rom_get_prognum(id);
        } break; 
        
        case eomc_entity_controller: 
        {
            prog = s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint]*eoprot_ep_mc_tags_joint_numberof +
                   s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor]*eoprot_ep_mc_tags_motor_numberof +
                   index*eoprot_ep_mc_tags_controller_numberof + eoprot_ep_mc_rom_get_prognum(id);
        } break;   
        
        default:
        {   
            prog = EOK_uint32dummy;
        } break;    
    }
    
    return(prog);
}

extern uint16_t eoprot_ep_mc_joints_numberof_Get(eOprotBRD_t brd)
{
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(0);
    }
    
    return(s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint]);
}

extern uint16_t eoprot_ep_mc_motors_numberof_Get(eOprotBRD_t brd)
{
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(0);
    }
    
    return(s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor]);
}

extern uint16_t eoprot_ep_mc_controllers_numberof_Get(eOprotBRD_t brd)
{
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(0);
    }
    
    return(s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_controller]);
}

extern uint16_t eoprot_ep_mc_ram_sizeof_Get(eOprotBRD_t brd)
{
    uint16_t size = 0;
    
    if((NULL == s_eoprot_ep_mc_board_numberofeachentity) || (NULL == s_eoprot_ep_mc_board_numberofeachentity[brd]))
    {
        return(0);
    }
    
    //#warning --> it is valid only if organisation of memory is jo[n], mo[m], c[l]
    size = sizeof(eOmc_joint_t) *      s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_joint] +
           sizeof(eOmc_motor_t) *      s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_motor] +
           sizeof(eOmc_controller_t) * s_eoprot_ep_mc_board_numberofeachentity[brd][eomc_entity_controller];
    
    return(size);
}

extern uint16_t eoprot_ep_mc_variable_ram_sizeof_Get(eOprotID32_t id)
{
    return(eoprot_ep_mc_rom_get_sizeofvar(id));
}


extern void* eoprot_ep_mc_entity_ram_Extract(eOprotBRD_t brd, eOprotEntity_t ent, void* epram)
{
    uint8_t* startofdata = epram;
    uint16_t offset = s_eoprot_ep_mc_brdentity2ramoffset(brd, ent);
    
    if(EOK_uint16dummy == offset)
    {
        return(NULL);
    }   

    return(&startofdata[offset]);
} 

extern void* eoprot_ep_mc_variable_ram_Extract(eOprotBRD_t brd, eOprotID32_t id, void* epram)
{
    uint8_t* startofdata = epram;
    uint16_t offset = s_eoprot_ep_mc_brdid2ramoffset(brd, id);
    
    if(EOK_uint16dummy == offset)
    {
        return(NULL);
    }   

    return(&startofdata[offset]);
}    
    

extern void* eoprot_ep_mc_variable_rom_Get(eOprotID32_t id)
{
    return(eoprot_ep_mc_rom_get_nvrom(id));
}

extern const eOmc_joint_t* eoprot_ep_mc_joint_default_Get(void)
{
    return(&eoprot_ep_mc_rom_joint_defaultvalue);
}

extern const eOmc_motor_t* eoprot_ep_mc_motor_default_Get(void)
{
    return(&eoprot_ep_mc_rom_motor_defaultvalue);
}

extern const eOmc_controller_t* eoprot_ep_mc_controller_default_Get(void)
{
    return(&eoprot_ep_mc_rom_controller_defaultvalue);
}


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section

// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------

static uint16_t s_eoprot_ep_mc_brdentity2ramoffset(eOprotBRD_t brd, eOprotEntity_t entity)
{
    uint16_t offset = 0;

    switch(entity)
    {
        case eomc_entity_joint:
        {   // the joints are all displaced at the beginning of the data in every mc endpoint
            offset = 0; 
        } break;
        
        case eomc_entity_motor:
        {   // the motors are placed after all the joints. 
            uint16_t numberofjoints = eoprot_ep_mc_joints_numberof_Get(brd);
            offset = numberofjoints*sizeof(eOmc_joint_t);  
        } break;      
 
        case eomc_entity_controller:
        {   // the controller is placed after all joints and motors. their index depends on the board
            uint16_t numberofjoints = eoprot_ep_mc_joints_numberof_Get(brd);
            uint16_t numberofmotors = eoprot_ep_mc_motors_numberof_Get(brd);
            offset = numberofjoints*sizeof(eOmc_joint_t) + numberofmotors*sizeof(eOmc_motor_t);
        } break; 
                
        default:
        {   // error
            offset = EOK_uint16dummy;
        } break;    
    }
    
    return(offset);  
}


static uint16_t s_eoprot_ep_mc_brdid2ramoffset(eOprotBRD_t brd, eOprotID32_t id)
{
    uint16_t offset = 0;
    eOprotTag_t tag = eoprot_ep_variable_ID2tag(id);
    
    if(EOK_uint08dummy == tag)
    {
        return(EOK_uint16dummy);
    }
    
    //#warning --> it is valid only if organisation of memory is jo[n], mo[m], c[l]
    
    eOprotEntity_t entity = eoprot_ep_variable_ID2entity(id);
    uint16_t index = eoprot_ep_variable_ID2index(id);
    
    switch(entity)
    {
        case eomc_entity_joint:
        {   // the joints are all displaced at the beginning of the data in every mc endpoint
            offset = index*sizeof(eOmc_joint_t) + eoprot_ep_mc_rom_joint_get_offset(tag); 
        } break;
        
        case eomc_entity_motor:
        {   // the motors are placed after all the joints. the index of the joints depends on the board
            uint16_t numberofjoints = eoprot_ep_mc_joints_numberof_Get(brd);
            offset = numberofjoints*sizeof(eOmc_joint_t) + index*sizeof(eOmc_motor_t) + eoprot_ep_mc_rom_motor_get_offset(tag);  
        } break;      

        case eomc_entity_controller:
        {   // the controller is placed after all joints and motors. their index depends on the board
            uint16_t numberofjoints = eoprot_ep_mc_joints_numberof_Get(brd);
            uint16_t numberofmotors = eoprot_ep_mc_motors_numberof_Get(brd);
            offset = numberofjoints*sizeof(eOmc_joint_t) + numberofmotors*sizeof(eOmc_motor_t) + index*sizeof(eOmc_controller_t) + eoprot_ep_mc_rom_controller_get_offset(tag);
        } break; 
        
        default:
        {   // error
            offset = EOK_uint16dummy;
        } break;
    
    }
    
    return(offset);  
}


static eObool_t s_eoprot_ep_mc_tag_joint_is_valid(eOprotTag_t tag)
{   // in case of holes in tags ... change the code
    return((tag < eoprot_ep_mc_tags_joint_numberof)?(eobool_true):(eobool_false));
}

static eObool_t s_eoprot_ep_mc_tag_motor_is_valid(eOprotTag_t tag)
{   // in case of holes in tags ... change the code  
    return((tag < eoprot_ep_mc_tags_motor_numberof)?(eobool_true):(eobool_false));
}

static eObool_t s_eoprot_ep_mc_tag_controller_is_valid(eOprotTag_t tag)
{   // in case of holes in tags ... change the code 
    return((tag < eoprot_ep_mc_tags_controller_numberof)?(eobool_true):(eobool_false));
}

// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



