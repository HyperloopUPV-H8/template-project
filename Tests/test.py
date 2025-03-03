import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
import vmcu.assertions as assertions
from vmcu.services.communications.FDCAN import FDCAN
from vmcu.pin.pinout import Pinout
from vmcu.shared_memory import SharedMemory


@runner.test()
def FDCAN_tests():
    ip = "127.0.0.1" 
    port = 7070
    sendport = 6969
    shm = SharedMemory("gpio_FDCAN_TEST","state_machine_FDCAN_TEST")
    fdcan = FDCAN(Pinout.PD1,Pinout.PD0, shm)
    fdcan.start(ip, port,sendport)
    assertions.completes(fdcan.transmit(2,b"Hello1",FDCAN.DLC.BYTES_6), before=assertions.seconds(1), msg="FDCAN did not transmit")
    class InvalidPacketError(assertions.TestException):
        def __init__(self, message):
            super().__init__("InvalidPacketError", message)
    def PacketReceived():
        packet = fdcan.read()
        if packet.rx_data == b"Hello2" and packet.identifier == 1 and packet.data_length == FDCAN.DLC.BYTES_6:
            return True
        raise InvalidPacketError("Invalid packet received")
    
    assertions.completes(assertions.wait_until_true(PacketReceived), before=assertions.seconds(1), msg="FDCAN did not receive the expected packet")

runner.run() # Runs the tests, do not delete!
