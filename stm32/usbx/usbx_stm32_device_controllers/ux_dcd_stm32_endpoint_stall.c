/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation 
 * 
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 * 
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** USBX Component                                                        */
/**                                                                       */
/**   STM32 Controller Driver                                             */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE
#define UX_DCD_STM32_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_dcd_stm32.h"
#include "ux_device_stack.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_dcd_stm32_endpoint_stall                        PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will stall a physical endpoint.                       */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    endpoint                              Pointer to endpoint container */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    HAL_PCD_EP_SetStall                   Set STALL condition           */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    STM32 Controller Driver                                             */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*  09-30-2020     Chaoqiong Xiao           Modified comment(s), used ST  */
/*                                            HAL library to drive the    */
/*                                            controller,                 */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT  _ux_dcd_stm32_endpoint_stall(UX_DCD_STM32 *dcd_stm32, UX_SLAVE_ENDPOINT *endpoint)
{

UX_DCD_STM32_ED     *ed;


    /* Get the physical endpoint address in the endpoint container.  */
    ed =  (UX_DCD_STM32_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Set the endpoint to stall.  */
    ed -> ux_dcd_stm32_ed_status |=  UX_DCD_STM32_ED_STATUS_STALLED;

    /* Stall the endpoint.  */
    HAL_PCD_EP_SetStall(dcd_stm32 -> pcd_handle, endpoint->ux_slave_endpoint_descriptor.bEndpointAddress | ed -> ux_dcd_stm32_ed_direction);

    /* This function never fails.  */
    return(UX_SUCCESS);
}

