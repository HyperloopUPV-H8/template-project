from vmcu.services.communications.spi import SPISlave, SPIMaster
from vmcu.shared_memory import SharedMemory
from vmcu.pin.pinout import Pinout
from runner import runner
from vmcu.assertions import *


@runner.test()
def spi_slave_transmit():

    shm = SharedMemory("gpio_SPI", "state_machine_SPI")
    slave_selected = SPISlave("localhost", 50005, "localhost", 50000, shm, Pinout.PD3)
    slave_not_selected = SPISlave(
        "localhost", 50007, "localhost", 50002, shm, Pinout.PD4
    )
    master1 = SPIMaster("localhost", 50004, shm)
    slave1 = SPIMaster.MCUSlave("localhost", 50001, Pinout.PD5)

    msg1 = b"Hello world1"
    msg2 = b"Hello world2"
    msg3 = b"Hello world3"

    def slave_selected_transmission_reception():
        nonlocal slave_selected, msg1
        slave_selected.transmit(msg1)
        print("Hello1")
        msg_received = slave_selected.receive()
        return msg_received == msg1

    def slave_not_selected_transmission_reception():
        nonlocal slave_not_selected, msg2
        try:
            slave_not_selected.transmit(msg2)
            return False
        except:
            try:
                print("Hello2")
                slave_not_selected.receive()
                return False
            except:
                return True

    def master_transmission_reception():
        nonlocal master1, slave1, msg3
        master1.transmit(msg3, slave1)
        print("Hello3")
        msg_received = master1.receive()
        return msg_received == msg3

    check(slave_selected_transmission_reception, msg="slave_selected_transmission_reception")
    check(slave_not_selected_transmission_reception, msg="slave_not_selected_transmission_reception")
    check(master_transmission_reception, msg="master_transmission_reception")
