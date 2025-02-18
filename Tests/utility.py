from enum import Enum
from vmcu.shared_memory import SharedMemory

class Utility:
    
    @staticmethod
    def check_number_of_active_state_machines(shm:SharedMemory,num: int) -> bool:
        '''
        Function that checks if the number of active state machines is equal to the number you provide
        -----------------------------------------------------------------------------------------------
        Args:
            shm (SharedMemory): Instance of the SharedMemory
            num (int): Number of expected active state machines

        '''
        return (num == shm.get_state_machine_count())

    @staticmethod
    def check_state(shm:SharedMemory, state:Enum) -> bool:
        '''
        Function that checks if the current StateMachine state is the one that we expect
        -----------------------------------------------------------------------------------------------
        Args:
            shm (SharedMemory): Instance of the SharedMemory
            state (Enum): Expected state

        '''
        return (state.value == shm.get_state_machine_state(1))

    @staticmethod
    def check_nested_state(shm:SharedMemory, state:Enum) -> bool:
        '''
        Function that checks if the current nested StateMachine state is the one that we expect
        -----------------------------------------------------------------------------------------------
        Args:
            shm (SharedMemory): Instance of the SharedMemory
            state (Enum): Expected state

        '''
        return (state.value == shm.get_state_machine_state(2))
    
    @staticmethod
    def connect_gui_connection():
        pass
    