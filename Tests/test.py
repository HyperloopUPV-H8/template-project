import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

import vmcu.assertions as assertions
from vmcu.pin.pinout import Pinout
from vmcu.services.digital_in import DigitalInService
from vmcu.shared_memory import SharedMemory
from runner import runner

@runner.test()
def StateMachine_test():
   #-----------Create shared memory and inscrbe pin--------------#
   shm = SharedMemory("gpio_stmtests","state_machine_stmtests")
   led = DigitalInService(shm, Pinout.PB2)

   #-----------Test the state machine transition--------------#
   led.turn_on()

   def check_transition():
      return shm.get_state_machine_state(1)==1
   
   assertions.completes(assertions.wait_until_true(check_transition), before=assertions.seconds(1), msg="The state machine did not transition")
runner.run() # Runs the tests, do not delete!
