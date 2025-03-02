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
print("Starting binary metadata generation")

repo_root = __get_git_root__()
environment = Environment(loader=FileSystemLoader(os.path.join(repo_root,'tools')))
template = environment.get_template(os.path.join('binary_metadata_template.txt'))

iso_time = datetime.now().strftime("%Y%m%dT%H%M%S")
repo_root = __get_git_root__()
stlib_commit    =   __get_current_commit__(os.path.join(repo_root,"deps/ST-LIB"))
adj_commit      =   __get_current_commit__(os.path.join(repo_root,"deps/adj"))    
board_commit    =   __get_current_commit__(repo_root)

output_file = os.path.join(repo_root,"Core/Src/Runes/generated_metadata.cpp")

content = template.render(
    DateTimeISO8601=iso_time,
    STLIB_COMMIT = stlib_commit,
    ADJ_COMMIT = adj_commit,
    BOARD_COMMIT = board_commit)
with open(output_file, mode="w", encoding="utf-8") as message:
    message.write(content)

print("Generation completed")