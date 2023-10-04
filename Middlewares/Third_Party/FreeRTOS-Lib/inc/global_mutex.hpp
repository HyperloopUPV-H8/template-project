/**
 * @file GlobalMutex.hpp
 * @author gonzalo
 * @brief global_mutex, templated on a mutex type
 * @version 0.1
 * @date 2023-10-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "defs.hpp"
#include <iostream>

#include <free-rtos/include/FreeRTOS.h>
#include <free-rtos/include/semphr.h>

namespace rtos
{

/**
 * @class global_mutex
 * @brief creates a mutex in the global namespace
 * @tparam mutex_type from the mutex_type enum
 */

class global_mutex{
public:
/**
 * @brief Construct a new global mutex object in the global namespace
 *
 */

    global_mutex(StaticSemaphore_t* buffer)
    {
        handle = xSemaphoreCreateMutexStatic(buffer);
    }
    /**
     * @brief tries to acquire the mutex based on the type it is templated on
     *
     * @return mutex_state::ACQUIRED if the mutex could be acquired, otherwise mutex_state::NOT_ACQUIRED
     */
    mutex_state acquire(float ms = 100){

    	if(xSemaphoreTake(handle,(ms*configTICK_RATE_HZ)/1'000) == pdTRUE){
    		return mutex_state::ACQUIRED;
    	}else{
    		return mutex_state::NOT_ACQUIRED;
    	}
    }
    /**
     * @brief tries to release the mutex
     *
     * @return true if it could be released
     * @return false if it could not be released
     */
    bool release()
    {
    	return xSemaphoreGive(handle);
    }
    /**
     * @brief Get the Handle object
     *
     * @return SemaphoreHandle_t
     */
    SemaphoreHandle_t getHandle(){
        return handle;
    }
protected:
    SemaphoreHandle_t handle;
};


}//rtos
