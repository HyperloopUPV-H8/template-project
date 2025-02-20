import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
import vmcu.assertions as assertions
import vmcu.services.communications.FDCAN as FDCAN
import vmcu.pin.pinout as Pinout
import vmcu.shared_memory as SharedMemory


@runner.test()
def led_toggle():
    ip = "127.0.0.1" 
    port = 6969
    sendport = 7070
    print("Starting test")
    shm = SharedMemory("gpio_FDCAN_TEST","state_machine_FDCAN_TEST")
    print("Shared memory created")
    fdcan = FDCAN(Pinout.PD1,Pinout.PD0, shm)
    print("FDCAN created")
    fdcan.start(ip, port,sendport)
    print("FDCAN started")
    assertions.completes(fdcan.transmit(),(1,b"Hello1",FDCAN.DLC.BYTES_6), before=assertions.seconds(1), msg="FDCAN did not transmit")
    class InvalidPacketError(assertions.TestException):
        def __init__(self, message):
            super().__init__("InvalidPacketError", message)
    def PacketReceived():
        packet = fdcan.read()
        if packet.rx_data == b"Hello2" and packet.identifier == 2 and packet.data_length == FDCAN.DLC.BYTES_6:
            return True
        raise InvalidPacketError("Invalid packet received")
    
    assertions.completes(assertions.wait_until_true(PacketReceived), before=assertions.seconds(1), msg="FDCAN did not receive the expected packet")
    

runner.run() # Runs the tests, do not delete!
