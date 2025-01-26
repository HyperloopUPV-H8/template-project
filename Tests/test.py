import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
from vmcu.shared_memory import SharedMemory
from vmcu.services.communications.DatagramSocket import DatagramSocket
from vmcu.services.communications.Packets import Packets
from vmcu.assertions import *
from random import *
import time
import struct
from typing import Optional

@runner.test()

#values 
def datagramsocket_test():
    ALLOWED_SLACK = 1
    shm = SharedMemory("gpio_ethernet_test", "state_machine_ethernet_test")
    datagramsocket = DatagramSocket("127.0.0.1",9015,"127.0.0.1",9006)
    packets = {
        0:["enum(OFF,ON)"],
        1: ["uint16","int32","enum(OFF,ON)","float32"]
    }
    packet = Packets(packets)

    def check_datagram_socket_running()->bool:
        return datagramsocket.is_running()
    
    def check_received_packet()->bool:
        raw_data = datagramsocket.get_packet()
        if raw_data is None: 
            return False
        if(len(raw_data) == 13):
            id,uint16,uint32,sensor,float32 = struct.unpack("<HHiBf",raw_data)
            if sensor == 0:
                string_ = "OFF"
            else:
                string_ = "ON"
            print(f"paquete recibido id = {id}, paquete numero: {uint16}, valores : {uint32}, {float32}, el sensor esta {string_}")
        return True
    
    print("Conectar el datagramSocket")
    datagramsocket.connect()
    completes(
        wait_until_true(check_datagram_socket_running),
        before=ALLOWED_SLACK,
        msg="Connection Completed"
    )
    print("conexion establecida")
    
    print("Comenzar a enviar paquetes id = 0, y recibir paquetes id = 1")
    for i in range(100):
        raw_data = packet.serialize_packet(0,"ON") 
        datagramsocket.transmit(raw_data)
        completes(
            wait_until_true(check_received_packet),
            before=ALLOWED_SLACK,
            msg="Received echo"
        )
        time.sleep(0.5)
  

runner.run() # Runs the tests, do not delete!