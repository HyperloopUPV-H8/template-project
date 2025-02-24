from enum import Enum
from vmcu.shared_memory import SharedMemory
from vmcu.services.communications.Socket import Socket
from vmcu.services.communications.spi import SPISlave

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
    def connect_control_station(gui_connection, lip, lport, rip, rport)->Socket:
        '''
        Function that simulates a connection to the control station
        -----------------------------------------------------------------------------------------------
        Args:
            gui_connection (None): Instance of the Socket that is initially initialized to None
            lip (str): Local IP
            lport (str):  Local port
            rip (str): Remote IP
            rport (str): Remote port
        '''
        if(gui_connection is None):
            gui_connection=Socket(lip, lport, rip, rport)
            gui_connection.connect()
            return gui_connection
        else:
            print("GUI connection already established!")
    
    @staticmethod
    def disconnect_control_station(gui_connection: Socket):
        '''
        Function that disconnects the simulated connection to the control station
        -----------------------------------------------------------------------------------------------
        Args:
            gui_connection (Socket): Instance of the Socket that is already initialized as a Socket
        '''
        if(gui_connection is not None):
            gui_connection.stop()
            gui_connection=None
            return gui_connection

    @staticmethod
    def check_control_station_connection(gui_connection: Socket)->bool:
        '''
        Function that checks if the simulated connection to the control station is still active
        -----------------------------------------------------------------------------------------------
        Args:
            gui_connection (Socket): Instance of the Socket that is already initialized as a Socket
        '''
        return gui_connection.is_running()