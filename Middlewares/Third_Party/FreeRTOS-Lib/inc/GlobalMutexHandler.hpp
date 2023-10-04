/**
 * @file GlobalMutexHandler.hpp
 * @author gonzalo
 * @brief GlobalMutex handler by Hyperloop UPV team
 * @version 0.1
 * @date 2023-10-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "defs.hpp"
#include "global_mutex.hpp"
#include <free-rtos/include/semphr.h>
#include <free-rtos/include/FreeRTOS.h>

#include "ErrorHandler/ErrorHandler.hpp"
#include <unordered_map>
#include <array>
#include <type_traits>

namespace rtos
{
    /**
     * @class GlobalMutexHandler
     * @brief Global class that handles several global mutexes
*/
template<typename T>
class GlobalMutexHandler;

template<>
class GlobalMutexHandler<mutex_type>{
    using mutex = GlobalMutexHandler;
public:
    static std::array<StaticSemaphore_t,mutex_type::mutex_type_MAX> semaphore_buffer;
    static std::array<global_mutex*,mutex_type::mutex_type_MAX> mutexes;
    constexpr GlobalMutexHandler()
    {
       for(uint32_t i = 0; i < mutex_type::mutex_type_MAX;i++){
           GlobalMutexHandler<mutex_type>::mutexes[i] = new global_mutex(&GlobalMutexHandler<mutex_type>::semaphore_buffer[i]);
       }
    }
        /**
     * @brief tries to acquire a mutex
     *
     * @tparam mutex_type that want to be acquired
     * @return mutex_state
     * */
    template<mutex_type::types T>
    [[nodiscard]] mutex_state acquire(float ms = 1000)
    {
    	if(ms < 0){
    		ErrorHandler("INVALID PERIOD, please enter a period greater than 0");
    	}

    	//f constexpr( T == mutex_type::types::DMA){std::cout<<"\nAcquired DMA mutex\n";}
    	//if constexpr( T == mutex_type::types::TCP){std::cout<<"\nAcquired TCP mutex\n";}
    	//if constexpr( T == mutex_type::types::ZZZ){std::cout<<"\nAcquired ZZZ mutex\n";}
      return GlobalMutexHandler<mutex_type>::mutexes[static_cast<int>(T)]->acquire(ms);
    }


    /**
     * @brief releases the mutex specified as the template argument
     *
     * @tparam mutex_type that wants to be released
     * @return true if the mutex could be released
     * @return false if the mutex could not be released
     */
    template<mutex_type::types T>
    bool release()
    {
       return GlobalMutexHandler<mutex_type>::mutexes[static_cast<int>(T)]->release();
    }
};




}//rtos
