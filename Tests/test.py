import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
from vmcu.shared_memory import SharedMemory
from vmcu.services.communications.ServerSocket import Server
from vmcu.services.communications.Packets import Packets
from vmcu.services.communications.Socket import Socket
from vmcu.assertions import *
from random import *
import time
import struct
from typing import Optional

@runner.test()

#values 
def socket_and_server_socket_test():
    ALLOWED_SLACK = 2
    shm = SharedMemory("gpio_ethernet_test", "state_machine_ethernet_test")
    socket = Socket("127.0.0.1",8102,"127.0.0.1",8202)
    server = Server("127.0.0.1",10012)
    packets = {
        0:[],
        1: ["int32"]
    }
    packet = Packets(packets)
    values = 0
    client = None
    def check_connected_socket() -> bool:
        return socket.connect()
    
    def check_client_connected()->bool:
       nonlocal client
       client = server.get_connected_clients()
       return len(client) != 0
    
    def check_received_packet(i)->bool:
        raw_data = socket.get_packet()
        if raw_data is None: 
            return False
        id,value = struct.unpack("<Hi",raw_data)
        return id == 1 and value == i + 5

    def check_received_order()->bool:
        return bool(server.get_packet(client[0]) is not None)
    
    print("Checkear que el socket de la placa sea ha conectado al servidor del simulador")
    completes(
        wait_until_true(check_client_connected),
        before=ALLOWED_SLACK,
        msg="Connection Completed"
    )
    print(f"conexion establecida con {client}")
    
    
    print("conectar el socket del simulador al servidor de la placa")
    completes(
        wait_until_true(check_connected_socket),
        before=ALLOWED_SLACK,
        msg="Connection Completed"
    )
    
    print("comenzar a enviar mensajes al serverSocket de la placa, esperar echo, y comprobar que los valores son los correctos")
    for i in range(100):
        value = i
        raw_data = packet.serialize_packet(1,value) 
        socket.transmit(raw_data)
        completes(
            wait_until_true(lambda: check_received_packet(i)),
            before=ALLOWED_SLACK,
            msg="Received echo"
        )
        time.sleep(0.5)
    print("Comenzar a enviar ordenes al socket de la placa")
    
    for i in range(100):
        value = i
        raw_data = packet.serialize_packet(0) 
        server.transmit(raw_data,client[0])
        completes(
            wait_until_true(check_received_order),
            before=ALLOWED_SLACK,
            msg="Received echo"
        )
        time.sleep(0.5) 

runner.run() # Runs the tests, do not delete!
