from tqdm.auto import tqdm
import time
import subprocess
import random

class Test():
    NODES = 4
    CONNECTIONS = 10
    
    def __init__(self):
        self.n = self.NODES
        self.generate_test()
        
    def generate_test(self):
        with open("test.in", 'w') as test:
            test.write(f"{self.CONNECTIONS}\n")
            
            con = {}
            self.G = [[] for i in range(self.n + 1)]
            
            for _ in range(self.CONNECTIONS):
                a = random.randint(0, self.n - 1)
                b = random.randint(0, self.n - 1)
                while b == a:
                    b = random.randint(0, self.n - 1)
                
                no_conn = con.get((a, b), 0)
                self.G[a].append([b, no_conn])
                
                test.write(f"{a} {no_conn} {b}\n")
                con[(a, b)] = no_conn + 1
        
    def check_solutions(self, a_out, b_out):
        # a: brut, b: better_solution
        with open(a_out, 'r') as a_out, open(b_out, 'r') as b_out:
            if a_out.readline().strip() != b_out.readline().strip():
                print('solutions are different')
                exit(3)

# convention a: brut, b: better_solutoin
class Referee():
    def __init__(self, program_a: str, program_b: str, max_time):
        # program a = sth.cpp (give full name with .cpp)
        
        self.program_a = program_a
        self.program_b = program_b
        self.max_time = max_time
        
        # compile programs 
        self.exe_a = compile(program_a)
        self.exe_b = compile(program_b)
        
    def compile(self, program):
        exe_name = program.split('0')[0]
        compile_command = ['g++', program, '-o', exe_name]
        subprocess.run(compile_command, check=True)
        return exe_name
    
    def do_tests(self):
        self.times = []
        for _ in tqdm(1000):
            # create test
            self.test = Test()
            
            # test program_a
            start_time_a = time.time()
            with open("test.in", "r") as test_input, open(f"{self.exe_a}.out", "w") as output_a:
                try:
                    subprocess.run(f"./{self.exe_a}", stdin=test_input, stdout=output_a, stderr=subprocess.DEVNULL, timeout=self.max_time * 2, check=True)
                except subprocess.TimeoutExpired:
                    print(f"{self.exe_a} exceeded time limit")
                    exit(1)
                except subprocess.CalledProcessError:
                    print(f"{self.exe_a} ended with an error")
                    exit(2)
            end_time_a = time.time()
            
            # test program_b
            start_time_b = time.time()
            with open("test.in", "r") as test_input, open(f"{self.exe_b}.out", "w") as output_b:
                try:
                    subprocess.run(f"./{self.exe_a}", stdin=test_input, stdout=output_b, stderr=subprocess.DEVNULL, timeout=self.max_time * 2, check=True)
                except subprocess.TimeoutExpired:
                    print(f"{self.exe_b} exceeded time limit")
                    exit(1)
                except subprocess.CalledProcessError:
                    print(f"{self.exe_b} ended with an error")
                    exit(2)
            end_time_b = time.time()
            
            
            # check solution
            self.test.check_solutions()
            
            # solutions are ok
            self.times.append([end_time_a - start_time_a, end_time_b - start_time_b])
        
        print("everything ok 🚀") 