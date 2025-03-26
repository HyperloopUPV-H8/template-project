import json 
import sys
from Packet_generation.Packet_generation import *
from State_machine_generation.State_machine_generation import *

if len(sys.argv)<2:
    print("Please enter a board name,exiting...")
    sys.exit()
    
JSONpath = "Core/Inc/Code_generation/JSON_ADE"
boards = Generate_PacketDescription(JSONpath)
aux = sys.argv[1]
filtered = ""
for c in aux:
    if c.isalpha():
        filtered += c
    else:
        break
board = filtered
if board not in boards:
    sys.exit()

Generate_DataPackets_hpp(board)
Generate_OrderPackets_hpp(board)
Generate_Protections_hpp(board)
if __name__ == "__main__":
    with open("state_machine.json", "r") as file:
        data = json.load(file)
    sm = parse_state_machine(data)
    generate_code(sm)








        