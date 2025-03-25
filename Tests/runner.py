import subprocess
from argparse import ArgumentParser
import time
import sys
import os
from datetime import datetime
import traceback

import logging
import threading

pathlogs = 'testsLog'

def LOG(*args, mode= 'INFO'):
    print(args)
    if(mode == 'INFO'):
        logging.info(args)
    elif(mode == 'ERR'):
        logging.error(args)
    elif(mode=='ELF'):
        logging.info(f'<CPP>{args}')



class DuplicatedTestError(Exception):
    def __init__(self, name):
        self._name = name

    def __str__(self):
        return f"Test {self._name} is duplicated"


class UnitUnderTest:
    def __init__(self, executable):
        self._executable = executable
    
    def __enter__(self):
        self._executable = f"stdbuf -oL {self._executable}"
        self._process = subprocess.Popen(
            self._executable,
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1,
        )

        self._stdout_thread = threading.Thread(target=self.stream_output)
        self._stdout_thread.daemon = True
        self._stdout_thread.start()

    def stream_output(self):
        while True:
            line = self._process.stdout.readline()
            if not line: break
            
            LOG(line, mode = 'ELF')

    def __exit__(self, *args):
        try:
            out, err = self._process.communicate(timeout=1)
        except Exception:
            self._process.kill()
            try:
                out, err = self._process.communicate(timeout=1)
            except Exception:
                out = "Error recovering stdout"
                err = "Error recovering stderr"
        
        self._stdout_thread.join(timeout=1)
        
        if out:
            LOG(f"  * UUT stdout:\n{out}")
        if err:
            LOG(f"  * UUT stderr:\n{err}")


class Test:
    def __init__(self, func):
        self._func = func
        self._prepare = None
        self._cleanup = None

    def __call__(self, *args, **kwargs):
        return self._func(*args, **kwargs)
    
    def prepare(self):
        def decorator(prepare_func):
            nonlocal self
            self._prepare = prepare_func
            return prepare_func

        return decorator
    
    def cleanup(self):
        def decorator(cleanup_func):
            nonlocal self
            self._cleanup = cleanup_func
            return cleanup_func

        return decorator

    def run_prepare(self):
        if self._prepare is not None:
            self._prepare()
    
    def run_cleanup(self):
        if self._cleanup is not None:
            self._cleanup()

class TestRunner:

    def __init__(self, uut_executable):
        self._prepare = {}
        self._tests = {}
        self._cleanup = {}
        self._uut = UnitUnderTest(uut_executable)

    # Registers a new test in the runner, name is infered from the function name
    def test(self):
        def decorator(test_func):
            nonlocal self

            if test_func.__name__ in self._tests:
                raise DuplicatedTestError(test_func.__name__)
            
            self._tests[test_func.__name__] = Test(test_func)

            return self._tests[test_func.__name__]
        
        return decorator
    
    
    # Runs all the registered tests, cleaning up after each test
    def run(self):

        failed_tests = 0

        if not os.path.exists(f'./{pathlogs}'):
            os.makedirs(f'./{pathlogs}')
        date  = datetime.now()
        logging.basicConfig(level=logging.INFO, filename=f'{pathlogs}/{date}log.log', filemode='w', format="%(levelname)s - %(message)s")

        for name, test in self._tests.items():
            try:
                test.run_prepare()

                with self._uut:
                    time.sleep(0.1)
                    try:
                        LOG(f"[{name}] Running...")
                        result = test()
                        LOG(f"[{name}] Succesfull!")
                        if result is not None:
                            LOG(f"  * Result: {result}")
                    except Exception as reason:
                        tb = traceback.extract_tb(reason.__traceback__)
                        failed_tests += 1

                        # Obtener la última llamada (donde ocurrió el error)
                        file1, line1, _, _ = tb[-2]
                        file2, line2, _, _ = tb[-1]
                        LOG(f"[{name}] Failed!", mode= 'ERR')
                        LOG(f'file: {file1} line: {line1}, file: {file2} line: {line2}', mode = 'ERR')
                        LOG(f"  * Reason: {reason}", mode = 'ERR')

                test.run_cleanup()
            except KeyboardInterrupt:
                LOG(f"[{name}] Keyboard Interrupt. Aborted.")
                import sys
                sys.exit(130)
               
        if failed_tests>0:
            import sys
            LOG(f"[{failed_tests}] Tests Failed!", mode= 'ERR')
            sys.exit(1)

                

parser = ArgumentParser(
    prog="test",
    description="run multiple simulator tests on a target executable"
)

parser.add_argument(
    "-uut",
    "--executable",
    required=True,
    help="full path to the target executable"
)

args = parser.parse_args()

runner = TestRunner(args.executable)
