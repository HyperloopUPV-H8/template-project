from jinja2 import Environment, FileSystemLoader
from datetime import datetime
from git import Repo
import os

def __get_git_root__():
    try:
        repo = Repo(os.getcwd(), search_parent_directories=True)
        return repo.git.rev_parse("--show-toplevel")
    except Exception:
        return None  # Not in a Git repo
def __get_current_commit__(path):
    try:
        repo = Repo(path, search_parent_directories=True)
        return repo.head.commit.hexsha[:8]  # Get the current commit hash
    except Exception:
        return "--------"  # not using that repo, return placeholder for commit
    
class Variable:
    def __init__(self,name,value):
        self.name = name
        self.value = value
variables = []

def parse_file(file_path):
    with open(file_path, 'r') as file:
        for line in file:
            # Look for the expression in the line
            if "ADD_TO_FLASH_INFO" in line:
                # Remove the 'ADD_TO_FLASH_INFO(' and ')'
                line = line.strip()[len("ADD_TO_FLASH_INFO("):-1]
                # Split the string by commas
                parts = line.split(',')
                # Ensure that we have exactly three parts (TYPE, VAR_NAME, VALUE)
                if len(parts) == 3:
                    var_name = parts[1].strip()  # Extract VAR_NAME
                    value = parts[2].strip()     # Extract VALUE
                    if var_name == 'VAR_NAME' and value == 'VALUE)': #make sure to not add the MACRO definition 
                        #in case it was present in that file
                        pass
                    else:
                        variables.append(Variable(var_name, value))
print("Starting binary metadata generation")

def search_in_subfolder(root_folder):
    for folder_name, subfolders, filenames in os.walk(root_folder):
        for filename in filenames:
            if filename.endswith('.h') or filename.endswith('.hpp'):  
                file_path = os.path.join(folder_name, filename)
                parse_file(file_path)

repo_root = __get_git_root__()
search_in_subfolder(os.path.join(repo_root,"Core/Inc"))

environment = Environment(loader=FileSystemLoader(os.path.join(repo_root,'tools')))
template = environment.get_template(os.path.join('binary_metadata_template.cpp'))

iso_time = datetime.now().strftime("%Y%m%dT%H%M%S")
repo_root = __get_git_root__()
stlib_commit    =   __get_current_commit__(os.path.join(repo_root,"deps/ST-LIB"))
adj_commit      =   __get_current_commit__(os.path.join(repo_root,"deps/adj"))  ## keep an eye on this  
board_commit    =   __get_current_commit__(repo_root)


output_file = os.path.join(repo_root,"Core/Src/Runes/generated_metadata.cpp")
content = template.render(
    DateTimeISO8601=iso_time,
    STLIB_COMMIT = stlib_commit,
    ADJ_COMMIT = adj_commit,
    BOARD_COMMIT = board_commit,
    variables=variables)
with open(output_file, mode="w", encoding="utf-8") as message:
    message.write(content)

print("Generation completed")