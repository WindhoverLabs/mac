/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#include "mac_app_test.hpp"
#include "mac_app.hpp"
#include "mac_test_utils.hpp"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_sb_hooks.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"


int32 hookCalledCount = 0;

/**************************************************************************
 * Tests for MAC_InitEvent()
 **************************************************************************/

/**
 * Test MAC_InitEvent() with failed CFE_EVS_Register
 */
void Test_MAC_InitEvent_Fail_Register(void)
{
    /* Set a fail result for EVS */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EVENTS_SERVICE | CFE_EVS_NOT_IMPLEMENTED;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitEvent();

    /* Verify results */
    UtAssert_True (result == expected, "InitEvent, failed EVS Register");
}


/**************************************************************************
 * Tests for MAC_InitPipe()
 **************************************************************************/
/**
 * Test MAC_InitPipe(), fail SCH CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateSCHPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create SCH pipe");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_SubscribeEx for wakeup
 */
void Test_MAC_InitPipe_Fail_SubscribeWakeup(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for wakeup");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_SubscribeEx for sendhk
 */
void Test_MAC_InitPipe_Fail_SubscribeSendHK(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBEEX_INDEX, expected, 2);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_SubscribeEx for sendhk");
}


/**
 * Test MAC_InitPipe(), fail CMD CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateCMDPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 2);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create CMD pipe");
}


/**
 * Test MAC_InitPipe(), fail CFE_SB_Subscribe for CMD msg
 */
void Test_MAC_InitPipe_Fail_SubscribeCMD(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_SUBSCRIBE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail CFE_SB_Subscribe for CMD");
}


/**
 * Test MAC_InitPipe(), fail DATA CFE_SB_CreatePipe
 */
void Test_MAC_InitPipe_Fail_CreateDATAPipe(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_SOFTWARE_BUS_SERVICE | CFE_SB_NOT_IMPLEMENTED;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 3);

    /* Execute the function being tested */
    result = oMAC.InitPipe();

    /* Verify results */
    UtAssert_True (result == expected, "InitPipe, fail SB create DATA pipe");
}


/**************************************************************************
 * Tests for MAC_InitData()
 **************************************************************************/
/**
 * Test MAC_InitData()
 */
void Test_MAC_InitData(void)
{
    /* Set a fail result */
    int32 result = -1;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = oMAC.InitData();

    /* Verify results */
    UtAssert_True (result == expected, "InitData");
}


/**************************************************************************
 * Tests for MAC_InitApp()
 **************************************************************************/
/**
 * Test MAC_InitApp(), fail init event
 */
void Test_MAC_InitApp_Fail_InitEvent(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_EVS_APP_NOT_REGISTERED;

    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init event");
}


/**
 * Test MAC_InitApp(), fail init pipe
 */
void Test_MAC_InitApp_Fail_InitPipe(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SB_BAD_ARGUMENT;

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_CREATEPIPE_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init pipe");
}


/**
 * Test MAC_InitApp(), fail init data.
 * NOTE: no current way to fail MAC_InitData() in default
 */
void Test_MAC_InitApp_Fail_InitData(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = oMAC.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init data");
}


/**
 * Test MAC_InitApp(), fail init config table
 */
void Test_MAC_InitApp_Fail_InitConfigTbl(void)
{
    int32 result = CFE_SUCCESS;
    int32 expected = CFE_TBL_ERR_INVALID_NAME;

    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_REGISTER_INDEX, expected, 1);

    /* Execute the function being tested */
    result = oMAC.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, fail init config table");
}


/**
 * Test MAC_InitApp(), Nominal
 */
void Test_MAC_InitApp_Nominal(void)
{
    /* Set a fail result for SB */
    int32 result = (CFE_SEVERITY_BITMASK & CFE_SEVERITY_ERROR)
                   | CFE_EXECUTIVE_SERVICE | CFE_ES_ERR_APP_REGISTER;
    int32 expected = CFE_SUCCESS;

    /* Execute the function being tested */
    result = oMAC.InitApp();

    /* Verify results */
    UtAssert_True (result == expected, "InitApp, nominal");
}

/**************************************************************************
 * Tests for MAC_AppMain()
 **************************************************************************/
/**
 * Test MAC_AppMain(), Fail RegisterApp
 */
void Test_MAC_AppMain_Fail_RegisterApp(void)
{
    /* fail the register app */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERAPP_INDEX, CFE_ES_ERR_APP_REGISTER, 1);

    /* Execute the function being tested */
    oMAC.AppMain();
}


/**
 * Test MAC_AppMain(), Fail InitApp
 */
void Test_MAC_AppMain_Fail_InitApp(void)
{
    /* fail the register app */
    Ut_CFE_EVS_SetReturnCode(UT_CFE_EVS_REGISTER_INDEX, CFE_EVS_APP_NOT_REGISTERED, 1);

    /* Execute the function being tested */
    oMAC.AppMain();
}


/**
 * Test MAC_AppMain(), Fail AcquireConfigPtrs
 */
void Test_MAC_AppMain_Fail_AcquireConfigPtrs(void)
{
    /* fail the register app */
    Ut_CFE_TBL_SetReturnCode(UT_CFE_TBL_GETADDRESS_INDEX, CFE_TBL_ERR_INVALID_HANDLE, 2);

    /* Execute the function being tested */
    oMAC.AppMain();
}


/**
 * Test MAC_AppMain(), Invalid Schedule Message
 */
void Test_MAC_AppMain_InvalidSchMessage(void)
{
    /* The following will emulate behavior of receiving a SCH message to send HK */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, 0, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    oMAC.AppMain();

}


/**
 * Hook to support: MAC_AppMain(), Nominal - SendHK
 */
int32 Test_MAC_AppMain_Nominal_SendHK_SendMsgHook(CFE_SB_Msg_t *MsgPtr)
{
    /* TODO:  Test the contents of your HK message here. */

    hookCalledCount++;

    return CFE_SUCCESS;
}

/**
 * Test MAC_AppMain(), Nominal - SendHK
 */
void Test_MAC_AppMain_Nominal_SendHK(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_SEND_HK_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Used to verify HK was transmitted correctly. */
    hookCalledCount = 0;
    Ut_CFE_ES_SetFunctionHook(UT_CFE_SB_SENDMSG_INDEX, (void*)&Test_MAC_AppMain_Nominal_SendHK_SendMsgHook);

    /* Execute the function being tested */
    oMAC.AppMain();

    /* Verify results */
    UtAssert_True (hookCalledCount == 1, "AppMain_Nominal_SendHK");

}


/**
 * Test MAC_AppMain(), Nominal - Wakeup
 */
void Test_MAC_AppMain_Nominal_Wakeup(void)
{
    /* The following will emulate behavior of receiving a SCH message to WAKEUP */
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_RUN_CONTROLLER_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    oMAC.AppMain();

}


/**
 * Test MAC_AppMain(), ProcessNewData - InvalidMsgID
 */
void Test_MAC_AppMain_ProcessNewData_InvalidMsgID(void)
{
    MAC_InData_t  InMsg;
    int32 DataPipe;

    /* The following will emulate behavior of receiving a SCH message to WAKEUP,
       and gives it data to process. */
    DataPipe = Ut_CFE_SB_CreatePipe("MAC_DATA_PIPE");
    CFE_SB_InitMsg (&InMsg, 0x0000, sizeof(MAC_InData_t), TRUE);
    Ut_CFE_SB_AddMsgToPipe(&InMsg, DataPipe);

    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_RCVMSG_INDEX, CFE_SUCCESS, 1);
    Ut_CFE_SB_SetReturnCode(UT_CFE_SB_GETMSGID_INDEX, MAC_RUN_CONTROLLER_MID, 1);

    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_RUNLOOP_INDEX, FALSE, 2);

    /* Execute the function being tested */
    oMAC.AppMain();

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    //UtAssert_EventSent(MAC_MSGID_ERR_EID, CFE_EVS_ERROR, "", "Error Event Sent");
}



void Test_MAC_RunController(void)
{

}



void Test_MAC_ControlAttitude(void)
{
	/* Set inputs */
	/*
	INFO  [mc_att_control] dt = 0.004976
	INFO  [mc_att_control] _v_att_sp.thrust = 0.557261
	INFO  [mc_att_control] _v_att_sp.q_d[0] = 0.709146
	INFO  [mc_att_control] _v_att_sp.q_d[1] = 0.006867
	INFO  [mc_att_control] _v_att_sp.q_d[2] = -0.015907
	INFO  [mc_att_control] _v_att_sp.q_d[3] = 0.704849
	INFO  [mc_att_control] _ctrl_state.q_d[0] = 0.708758
	INFO  [mc_att_control] _ctrl_state.q_d[1] = 0.007156
	INFO  [mc_att_control] _ctrl_state.q_d[2] = -0.013554
	INFO  [mc_att_control] _ctrl_state.q_d[3] = 0.705285
	INFO  [mc_att_control] _params.att_p[0] = 6.000000
	INFO  [mc_att_control] _params.att_p[1] = 6.000000
	INFO  [mc_att_control] _params.att_p[2] = 2.800000
	INFO  [mc_att_control] _v_control_mode.flag_control_velocity_enabled = 1
	INFO  [mc_att_control] _v_control_mode.flag_control_auto_enabled = 1
	INFO  [mc_att_control] _v_control_mode.flag_control_manual_enabled = 0
	INFO  [mc_att_control] _v_att_sp.yaw_sp_move_rate = 0.000000
	INFO  [mc_att_control] _params.yaw_ff = 0.500000
	INFO  [mc_att_control] _v_att_sp.disable_mc_yaw_control = 0
	INFO  [mc_att_control] _params.auto_rate_max(0) = 3.839725
	INFO  [mc_att_control] _params.auto_rate_max(1) = 3.839725
	INFO  [mc_att_control] _params.auto_rate_max(2) = 0.785398
	INFO  [mc_att_control] _params.vtol_wv_yaw_rate_scale = 0.150000
	INFO  [mc_att_control] _rates_sp(2) = -0.003174
	INFO  [mc_att_control] _params.mc_rate_max(0) = 3.839725
	INFO  [mc_att_control] _params.mc_rate_max(1) = 3.839725
	INFO  [mc_att_control] _params.mc_rate_max(2) = 3.490659
	INFO  [mc_att_control] _rates_int(2) = 0.000017
	INFO  [mc_att_control]
	*/
    oMAC.CVT.VAttSp.Thrust = 0.547918f;
    oMAC.CVT.VAttSp.Q_D[0] = 0.704050f;
    oMAC.CVT.VAttSp.Q_D[1] = 0.002164f;
    oMAC.CVT.VAttSp.Q_D[2] = -0.012259f;
    oMAC.CVT.VAttSp.Q_D[3] = 0.710041f;
    oMAC.CVT.ControlState.Q[0] = 0.704148f;
    oMAC.CVT.ControlState.Q[1] = 0.000206f;
    oMAC.CVT.ControlState.Q[2] = -0.011443f;
    oMAC.CVT.ControlState.Q[3] = 0.709961f;
    oMAC.m_Params.att_p[0] = 6.000000f;
    oMAC.m_Params.att_p[1] = 6.000000f;
    oMAC.m_Params.att_p[2] = 2.800000f;
    oMAC.CVT.VControlMode.ControlVelocityEnabled = TRUE;
    oMAC.CVT.VControlMode.ControlAutoEnabled = TRUE;
    oMAC.CVT.VControlMode.ControlManualEnabled = FALSE;
    oMAC.CVT.VAttSp.YawSpMoveRate = 0.000000f;
    oMAC.m_Params.yaw_ff = 0.500000f;
    oMAC.CVT.VAttSp.DisableMcYawControl = FALSE;
    oMAC.m_Params.auto_rate_max[0] = 3.839725f;
    oMAC.m_Params.auto_rate_max[1] = 3.839725f;
    oMAC.m_Params.auto_rate_max[2] = 0.785398f;
    oMAC.m_Params.vtol_wv_yaw_rate_scale = 0.150000f;
    oMAC.m_AngularRatesSetpoint[2] = 0.000594f;
    oMAC.m_Params.mc_rate_max[0] = 3.839725f;
    oMAC.m_Params.mc_rate_max[1] = 3.839725f;
    oMAC.m_Params.mc_rate_max[2] = 3.490659f;
    oMAC.m_AngularRatesIntegralError[2] = 0.000206f;

    /* Run the function */
    oMAC.ControlAttitude(0.005003f);

	/* Check outputs */
    /*
	INFO  [mc_att_control] _v_att_sp.disable_mc_yaw_control = 0.000000
	INFO  [mc_att_control] _thrust_sp = 0.557261
	INFO  [mc_att_control] _rates_sp(0) = -0.022480
	INFO  [mc_att_control] _rates_sp(1) = -0.017538
	INFO  [mc_att_control] _rates_sp(2) = -0.003145
	INFO  [mc_att_control] _rates_int(2) = 0.000017
     */
    printf("oMAC.CVT.VAttSp.DisableMcYawControl = %u\n", oMAC.CVT.VAttSp.DisableMcYawControl);
    printf("oMAC.m_ThrustSp = %f\n", oMAC.m_ThrustSp);
    printf("oMAC.m_AngularRatesSetpoint[0] = %f\n", oMAC.m_AngularRatesSetpoint[0]);
    printf("oMAC.m_AngularRatesSetpoint[1] = %f\n", oMAC.m_AngularRatesSetpoint[1]);
    printf("oMAC.m_AngularRatesSetpoint[2] = %f\n", oMAC.m_AngularRatesSetpoint[2]);
    printf("oMAC.m_AngularRatesIntegralError[2] = %f\n", oMAC.m_AngularRatesIntegralError[2]);
}


void Test_MAC_ControlAttitudeRates(void)
{

}



void Test_MAC_PidAttenuations(void)
{

}



void Test_MAC_UpdateParams(void)
{

}



/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void MAC_App_Test_AddTestCases(void)
{
    UtTest_Add(Test_MAC_InitEvent_Fail_Register, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitEvent_Fail_Register");

    UtTest_Add(Test_MAC_InitPipe_Fail_CreateSCHPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateSCHPipe");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeWakeup, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeWakeup");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeSendHK, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeSendHK");
    UtTest_Add(Test_MAC_InitPipe_Fail_CreateCMDPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateCMDPipe");
    UtTest_Add(Test_MAC_InitPipe_Fail_SubscribeCMD, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_SubscribeCMD");
    UtTest_Add(Test_MAC_InitPipe_Fail_CreateDATAPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitPipe_Fail_CreateDATAPipe");

    UtTest_Add(Test_MAC_InitData, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitData");

    UtTest_Add(Test_MAC_InitApp_Fail_InitEvent, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitEvent");
    UtTest_Add(Test_MAC_InitApp_Fail_InitPipe, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitPipe");
    UtTest_Add(Test_MAC_InitApp_Fail_InitData, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitData");
    UtTest_Add(Test_MAC_InitApp_Fail_InitConfigTbl, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Fail_InitConfigTbl");
    UtTest_Add(Test_MAC_InitApp_Nominal, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_InitApp_Nominal");

    UtTest_Add(Test_MAC_AppMain_Fail_RegisterApp, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_RegisterApp");
    UtTest_Add(Test_MAC_AppMain_Fail_InitApp, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_InitApp");
    UtTest_Add(Test_MAC_AppMain_Fail_AcquireConfigPtrs, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Fail_AcquireConfigPtrs");
    UtTest_Add(Test_MAC_AppMain_InvalidSchMessage, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_InvalidSchMessage");
    UtTest_Add(Test_MAC_AppMain_Nominal_SendHK, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Nominal_SendHK");
    UtTest_Add(Test_MAC_AppMain_Nominal_Wakeup, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_Nominal_Wakeup");
    UtTest_Add(Test_MAC_AppMain_ProcessNewData_InvalidMsgID, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_AppMain_ProcessNewData_InvalidMsgID");

    UtTest_Add(Test_MAC_RunController, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_RunController");

    UtTest_Add(Test_MAC_ControlAttitude, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_ControlAttitude");

    UtTest_Add(Test_MAC_ControlAttitudeRates, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_ControlAttitudeRates");

    UtTest_Add(Test_MAC_PidAttenuations, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_PidAttenuations");

    UtTest_Add(Test_MAC_UpdateParams, MAC_Test_Setup, MAC_Test_TearDown,
               "Test_MAC_UpdateParams");


}


