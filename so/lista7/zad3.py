import os 
import re

def sum_mem(pat: re.Pattern): 
    total = 0
    
    pids = [pid for pid in os.listdir('/proc') if pid.isdigit()]
    for pid in pids:
        path = os.path.join('/proc', pid, 'status') 
        
        if not os.path.exists(path):
            continue 
        
        with open(path, 'r') as file:
            content = file.read() 
        
        size = pat.search(content)
        if size: 
            total += int(size.group(1))
            
    return total
            

 
if __name__ == "__main__":
    vmsize_pat = re.compile(r'^VmSize:\s+(\d+)\s+kB', re.MULTILINE)
    vmrss_pat = re.compile(r'^VmRSS:\s+(\d+)\s+kB', re.MULTILINE)
    
    print("VmSize: ", sum_mem(vmsize_pat), 'K')
    print("VmRSS: ", sum_mem(vmrss_pat), 'K')