import json 
from Packet_generation.Packet_generation import *
from State_machine_generation.State_machine_generation import *



JSONpath = "Core/Inc/Code_generation/JSON_ADE"
boards = Generate_PacketDescription(JSONpath)
board = input("Enter board name: ")
while board not in boards: 
    print("Board not found, select an available board")
    board = input("Enter board name: ")
Generate_DataPackets_hpp(board)
Generate_OrderPackets_hpp(board)
Generate_Protections_hpp(board)
if __name__ == "__main__":
    with open("state_machine.json", "r") as file:
        data = json.load(file)
    sm = parse_state_machine(data)
    generate_code(sm)








        