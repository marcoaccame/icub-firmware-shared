/*
 * Copyright (C) 2019 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Luca Tricerri
 * email:   luca.tricerri@iit.it
 * website: https://github.com/icub-tech-iit
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
#ifndef _EOMDIGNOSTICROPMSG_H_
#define _EOMDIGNOSTICROPMSG_H_

#include "EoCommon.h"
#include "MsgDescription.h"

#include <array>
#include <sstream>
#include <iostream>
#include <iterator>
#include <cstring>
#include <iomanip>

/** 
  @file       EOMDiagnosticRopMsg.h
	@brief      This header file implements public interface to the EMS diagnostic message.
 	@author     luca.tricerri@iit.it
	@date       09/2019
 **/

class EOMDiagnosticRopMsg
{
public:
    struct Info
    {
        std::array<uint16_t,8> param_{(uint16_t)DiagnosticRopCode::empty,(uint16_t)DiagnosticRopSeverity::empty,0,0,0,0,0,0};
        uint64_t time_{0};
    };
    EO_VERIFYsizeof(Info, 24)

    constexpr static uint16_t getSize()
    {
        return sizeof(Info);
    }

    EOMDiagnosticRopMsg(void *data, uint8_t size);
    EOMDiagnosticRopMsg(const std::array<uint8_t, sizeof(Info)> &data);
    EOMDiagnosticRopMsg(const Info &data) : data_(data){};
    EOMDiagnosticRopMsg(){};

    uint8_t *data() const;
    void rawdump() const;
    void dump(const std::map<DiagnosticRopSeverity,std::string>* ,
              const std::map<DiagnosticRopCode,std::string>* ,
              const std::map<DiagnosticRopString,std::string>*, 
              std::ostream& stream) const;
    void reset();
    DiagnosticRopCode getCode();
    DiagnosticRopSeverity getSeverity();
    bool isEmptyRop() const;

    Info data_;
};

inline void EOMDiagnosticRopMsg::reset()
{
    data_ = (const struct Info){0};
}

inline DiagnosticRopCode EOMDiagnosticRopMsg::getCode()
{
    return (DiagnosticRopCode)(data_.param_[0]);
}

inline DiagnosticRopSeverity EOMDiagnosticRopMsg::getSeverity()
{
    return static_cast<DiagnosticRopSeverity>(data_.param_[1]);
}

inline EOMDiagnosticRopMsg::EOMDiagnosticRopMsg(void *data, uint8_t size)
{
    if (size > sizeof(Info))
    {
        //TODO
        return;
    }

    std::memcpy(&data_, data, sizeof(Info));
}

inline EOMDiagnosticRopMsg::EOMDiagnosticRopMsg(const std::array<uint8_t, sizeof(Info)> &data)
{
    std::memcpy(&data_, data.data(), sizeof(Info));
}

inline uint8_t *EOMDiagnosticRopMsg::data() const
{
    return (uint8_t *)(&data_);
}

inline void EOMDiagnosticRopMsg::rawdump() const
{
    std::stringstream ss;
    std::array<uint8_t, getSize()> *tmp;
    tmp = (std::array<uint8_t, getSize()> *)&data_;

    std::copy(tmp->begin(), tmp->end(), std::ostream_iterator<int>(ss, " "));
    std::cout << std::hex << ss.str() << std::endl;
}

inline void EOMDiagnosticRopMsg::dump(const std::map<DiagnosticRopSeverity,std::string>* ropSeverity,
                                      const std::map<DiagnosticRopCode,std::string>* ropCode,
                                      const std::map<DiagnosticRopString,std::string>* ropString,
                                      std::ostream& stream) const
{
    std::string codeStr{"unknown"};
    if(ropCode)
    {
        if(ropCode->find((DiagnosticRopCode)data_.param_[0])!=ropCode->end())
            codeStr=ropCode->at((DiagnosticRopCode)data_.param_[0]);
    }      
    std::string severityStr{"unknown"};
    if(ropSeverity)
    {
        if(ropSeverity->find((DiagnosticRopSeverity)data_.param_[1])!=ropSeverity->end())
            severityStr=ropSeverity->at((DiagnosticRopSeverity)data_.param_[1]);    
    }
        
    std::string stringStr{"unknown"};
    if(ropString)
    {
        if(ropString->find((DiagnosticRopString)data_.param_[2])!=ropString->end())
            stringStr=ropString->at((DiagnosticRopString)data_.param_[2]);        
    }

    if((DiagnosticRopCode)data_.param_[0]==DiagnosticRopCode::empty)
        return;

    stream << "------ROP";
    stream << "code:" <<std::left <<std::setw (15)<<codeStr << " ";
    stream << "severity:" <<std::left<<std::setw (15)<<severityStr << " ";
    stream << "param2:" <<std::left<<std::setw (15)<<stringStr << " ";
    stream << "param3:" << data_.param_[3] << " ";
    stream << "param4:" << data_.param_[4] << " ";
    stream << "param5:" << data_.param_[5] << " ";
    stream << "param6:" << data_.param_[6] << " ";
    stream << "param7:" << data_.param_[7] << " ";
    stream << "time:" << data_.time_ << " ";
    stream << std::endl;    
};

inline bool EOMDiagnosticRopMsg::isEmptyRop() const
{
    int tot=0;
    for(uint16_t current:data_.param_)
    {
        tot+=current;
    }
    tot=+data_.time_;

    return !(bool)tot;
}

#endif // include-guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
