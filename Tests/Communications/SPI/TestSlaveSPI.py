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
    master2 = SPIMaster("localhost", 50006, shm)
    slave2 = SPIMaster.MCUSlave("localhost", 50003, Pinout.PD6)

    msg = b"Hello world"

    def slave_selected_transmission_reception():
        nonlocal slave_selected, msg
        slave_selected.transmit(msg)
        msg_received = slave_selected.receive()
        return msg_received == msg

    def slave_not_selected_transmission_reception():
        nonlocal slave_not_selected, msg
        try:
            slave_not_selected.transmit(msg)
            return False
        except:
            try:
                slave_not_selected.receive()
                return False
            except:
                return True

    def master_transmission_reception():
        nonlocal master1, slave1, msg
        master1.transmit(msg, slave1)
        msg_received = master1.receive()
        return msg_received == msg

    def master_transmission_reception_slave_deselected():
        nonlocal master2, slave2, msg
        master2.transmit(msg, slave2)
        master2.chip_select_off(slave2)
        try:
            completes(master2.receive, before=seconds(1))
            return False
        except TooLateError:
            return True

    check(slave_selected_transmission_reception)
    check(slave_not_selected_transmission_reception)
    check(master_transmission_reception)
    check(master_transmission_reception_slave_deselected)
