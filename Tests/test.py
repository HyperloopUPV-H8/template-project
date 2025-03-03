import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

import vmcu.assertions as assertions
import vmcu.pin.pinout as Pinout
import vmcu.services.digital_in as DigitalInService
import vmcu.shared_memory as SharedMemory
from runner import runner

@runner.test()
def led_toggle():
   shm = SharedMemory("gpio_SHM_tests","state_machine_SHM_tests")
   led = DigitalInService(shm, Pinout.PA1)

   led.turn_on()

   assertions.completes(assertions.wait_until_true(shm.get_sm(1)==1), before=assertions.seconds(1), msg="The state machine did not transition")
runner.run() # Runs the tests, do not delete!
