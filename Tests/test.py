import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
import Tests.Communications.SPI.TestSlaveSelectedSPI
    
runner.run() # Runs the tests, do not delete!
