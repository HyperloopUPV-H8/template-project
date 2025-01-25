import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "VirtualMCU", "src"))

from runner import runner
import Communications.SPI.TestSPI
    
runner.run() # Runs the tests, do not delete!
