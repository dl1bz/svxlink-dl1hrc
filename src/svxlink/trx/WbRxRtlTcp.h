/**
@file	 WbRxRtlTcp.h
@brief   A_brief_description_for_this_file
@author  Tobias Blomberg / SM0SVX
@date	 2014-07-16

A_detailed_description_for_this_file

\verbatim
SvxLink - A Multi Purpose Voice Services System for Ham Radio Use
Copyright (C) 2003-2014 Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/

#ifndef WBRX_RTL_TCP_INCLUDED
#define WBRX_RTL_TCP_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <sigc++/sigc++.h>
#include <complex>
#include <string>
#include <vector>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <AsyncTcpClient.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

//namespace MyNameSpace
//{


/****************************************************************************
 *
 * Forward declarations of classes inside of the declared namespace
 *
 ****************************************************************************/

  

/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
@brief	A_brief_class_description
@author Tobias Blomberg / SM0SVX
@date   2014-07-16

A_detailed_class_description
*/
class WbRxRtlTcp : public sigc::trackable
{
  public:
    typedef std::complex<float> Sample;
    
    static const int GAIN_UNSET = -1000;

    /**
     * @brief 	Default constructor
     */
    WbRxRtlTcp(const std::string &remote_host="localhost",
           uint16_t remote_port=1234);
  
    /**
     * @brief 	Destructor
     */
    ~WbRxRtlTcp(void) {}
  
    /**
     * @brief 	A_brief_member_function_description
     * @param 	param1 Description_of_param1
     * @return	Return_value_of_this_member_function
     */
    void setCenterFq(uint32_t fq);

    void setSampleRate(uint32_t rate);

    void setGainMode(uint32_t mode);

    void setGain(uint32_t gain);

    void setFqCorr(uint32_t corr);

    void setTunerIfGain(uint16_t stage, int16_t gain);

    void enableTestMode(bool enable);

    void enableDigitalAgc(bool enable);

    /* Missing commands:
     *   9 - set direct sampling
     *   a - set offset tuning
     *   b - set rtl xtal
     *   c - set tuner xtal
     *   d - set tuner gain by index
     */

    sigc::signal<void, std::vector<Sample> > iqReceived;
    
  protected:
    
  private:
    static const int BLOCK_SIZE = 8 * 2 * 960;
    static const unsigned MAX_IF_GAIN_STAGES = 10;

    Async::TcpClient con;
    uint32_t  tuner_type;
    uint32_t  tuner_gain_count;
    bool      center_fq_set;
    uint32_t  center_fq;
    bool      samp_rate_set;
    uint32_t  samp_rate;
    int32_t   gain_mode;
    uint32_t  gain;
    bool      fq_corr_set;
    uint32_t  fq_corr;
    int       tuner_if_gain[MAX_IF_GAIN_STAGES];
    bool      test_mode_set;
    bool      test_mode;
    bool      use_digital_agc_set;
    bool      use_digital_agc;

    WbRxRtlTcp(const WbRxRtlTcp&);
    WbRxRtlTcp& operator=(const WbRxRtlTcp&);
    void sendCommand(char cmd, uint32_t param);
    void connected(void);
    void disconnected(Async::TcpConnection *c,
                      Async::TcpConnection::DisconnectReason reason);
    void updateSettings(void);
    int dataReceived(Async::TcpConnection *con, void *buf, int count);
    
};  /* class WbRxRtlTcp */



//} /* namespace */

#endif /* WBRX_RTL_TCP_INCLUDED */


/*
 * This file has not been truncated
 */
