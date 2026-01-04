from . import LLMZip
import sys
import os
from typing import List, Tuple

def unzip():
    files = get_files()
    params, flags = get_flags()
    
    assert len(files) == 1, "Error: you should provide only one file to unzip"
    assert files[0].endswith('.llmzip'), "Error: you can only uncompress files with .llmzip extension"
   
    # handle flags and params 
    output_name = get_default_unzip_name()
    for flag in flags:
        raise Exception(f"Error: unknown flag: {flag}")
    
    for param in params:
        if param[0] == "-output":
            output_name = param[1]
        else:
            raise Exception(f"Error: unknown parameater: {param[0]}={param[1]}")

def zip():
    params, flags = get_flags()
    files = get_files()
    
    # handle flags and params
    output_name = get_default_zip_name()
    recursive = False
    model = "0"
    
    for flag in flags:
        if flag == '-r':
            recursive = True
        else:
            raise Exception(f"Error: unknown flag: {flag}")
        
    for param in params: 
        if param[0] == "-model":
            model = param[1]
        elif param[0] == '-output':
            output_name = param[1]
        else: 
            raise Exception(f"Error: unknown parameater: {param[0]}={param[1]}")

# smaller utils
def get_flags() -> Tuple[List[Tuple[str, str]], List[str]]:
    args = sys.argv[1:]
    flags = [arg for arg in args if arg.startswith("-")]
    
    parsed_params: List[Tuple[str, str]] = []  
    parsed_flags: List[str] = []
    
    for i in range(len(flags)):
        flag = flags[i].split("=")
        assert len(flag) > 2, f"Error: unknown flag: {flags[i]}"
        
        if len(flag) == 1:
            parsed_flags.append(flag[0])
        else:  
            parsed_params.append((flag[0], flag[1]))
        
    return parsed_params, parsed_flags
         

def get_files() -> List[str]:
    args = sys.argv[1:]
    return [arg for arg in args if not arg.startswith("-")]

def get_default_zip_name() -> str:
    if not os.path.exists("compressed.llmzip"):
        return "compressed.llmzip"
    
    idx = 1 
    while os.path.exists(f"compressed{idx}.llmzip"):
        idx += 1 
        
    return f"compressed{idx}.llmzip"

def get_default_unzip_name() -> str:
    if not os.path.exists("uncompressed"):
        return "uncompressed"
    
    idx = 1 
    while os.path.exists(f"uncompressed{idx}"):
        idx += 1 
        
    return f"uncompressed{idx}"
        
        