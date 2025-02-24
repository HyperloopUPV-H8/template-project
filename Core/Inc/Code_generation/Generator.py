import json 
from Packet_descriptions import *
import os
import jinja2


def Generate_PacketDescription():
    with open("Core/Inc/Communications/JSON_ADE/boards.json") as f:
        boards = json.load(f)
    boards_name = []
    for board in boards["boards"]:
        with open("Core/Inc/Communications/JSON_ADE/" + (boards["boards"][board])) as f:
            b = json.load(f)
        board_instance = BoardDescription(board, b)
        boards_name.append(board_instance.name)
        globals()[board] = board_instance
    
    return boards_name
        

#--------------DataPackets.hpp generation---------------#

def Get_data_context(board:BoardDescription):
    def GenerateDataEnum(board:BoardDescription):
        Enums = []
        for packet in board.packets:
            for packet_instance in board.packets[packet]:
                if packet_instance.type != "order":
                    for measurement in packet_instance.measurements:
                        if hasattr(measurement, "enum"):
                            Enums.append(measurement.enum)
        return Enums
    
    
    def GenerateDataPackets(board:BoardDescription):
        Packets =[]
        totaldata = []
        for packet in board.packets:
            for packet_instance in board.packets[packet]:
                if packet_instance.type != "order":
                    tempdata = ""
                    for variable in packet_instance.variables:
                        tempdata +=(str(variable) +",")
                    if tempdata.endswith(","):
                        tempdata = tempdata[:-1]  
                    aux_packet = {"name": packet_instance.name, "data":tempdata , "id": packet_instance.id}
                    Packets.append(aux_packet)
                    for measurement in packet_instance.measurements:
                        aux_data = {"type": measurement.type, "name": measurement.id}
                        totaldata.append(aux_data)
        
        return Packets,totaldata
    
    packets,data = GenerateDataPackets(board)
    context = {
        "board": board.name,
        "enums": GenerateDataEnum(board),
        "packets" : packets,
        "data": data,
        "size": board.order_size,
    }
    return context

def Generate_DataPackets_hpp(board_input:str):
    board_instance = globals()[board_input]
    if board_instance.data_size == 0:
        if os.path.exists("Core/Inc/Communications/Packets/DataPackets.hpp"):
            os.remove("Core/Inc/Communications/Packets/DataPackets.hpp")
        return    
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Code_generation"))
    template = env.get_template("DataTemplate.hpp")
    context = Get_data_context(board_instance)

    
    with open("Core/Inc/Communications/Packets/DataPackets.hpp","w") as Output:
        Output.write(template.render(context))
            
#--------------OrderPackets.hpp generation---------------#

def Get_order_context(board:BoardDescription):
    def GenerateOrderEnum(board:BoardDescription):
        Enums = []
        for packet in board.packets:
            for packet_instance in board.packets[packet]:
                if packet_instance.type == "order":
                    for measurement in packet_instance.measurements:
                        if hasattr(measurement, "enum"):
                            Enums.append(measurement.enum)
        return Enums
    
    
    def GenerateOrderPackets(board:BoardDescription):
        Packets =[]
        totaldata = []
        for packet in board.packets:
            for packet_instance in board.packets[packet]:
                if packet_instance.type == "order":
                    tempdata = ""
                    for variable in packet_instance.variables:
                        tempdata +=(str(variable) +",")
                    if tempdata.endswith(","):
                        tempdata = tempdata[:-1]  
                    aux_packet = {"name": packet_instance.name, "data":tempdata , "id": packet_instance.id}
                    Packets.append(aux_packet)
                    for measurement in packet_instance.measurements:
                        aux_data = {"type": measurement.type, "name": measurement.id}
                        totaldata.append(aux_data)
        
        return Packets,totaldata
    
    
    packets,data = GenerateOrderPackets(board)
    context = {
        "board": board.name,
        "enums": GenerateOrderEnum(board),
        "packets" : packets,
        "data": data,
        "size": board.order_size,
    }
    return context

def Generate_OrderPackets_hpp(board_input:str):
    board_instance = globals()[board_input]
    if board_instance.order_size == 0:
        if os.path.exists("Core/Inc/Communications/Packets/OrderPackets.hpp"):
            os.remove("Core/Inc/Communications/Packets/OrderPackets.hpp")
        return    
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Code_generation"))
    template = env.get_template("OrderTemplate.hpp")
    context = Get_order_context(board_instance)

    
    with open("Core/Inc/Communications/Packets/OrderPackets.hpp","w") as Output:
        Output.write(template.render(context))


#--------------Protections.hpp generation---------------#

def Generate_Protections_context(board:BoardDescription):
    def Get_Bondaries(measurement:MeasurmentsDescription):
        Boundaries = []
        for i in {0,1}:
            for j in {0,1}:
                if measurement.protections.protections[i].Protectionvalue[j] is None:
                    continue
                temp_boundary= {"type": measurement.type, "Above_or_Below":measurement.protections.protections[i].ProtectionType, "value": measurement.protections.protections[i].Protectionvalue[j],"coma":"," }
                Boundaries.append(temp_boundary)
        
        Boundaries[-1]["coma"] = ""
        return Boundaries
            

    def Get_protection_packets(board:BoardDescription):
        protections = []
        for packet in board.packets:
            for packet_instance in board.packets[packet]:
                for measurement in packet_instance.measurements:
                    if hasattr(measurement, "protections"):
                        protections.append(measurement)
        if len(protections) == 0:
            return False
        return protections
    
    
    protection_packets = Get_protection_packets(board)
    if protection_packets == False:
        return False
    protections=[]
    data =[]
    for measurement in protection_packets:
        Boundaries = Get_Bondaries(measurement)
        aux_protection = {"packet": measurement.id, "Boundaries": Boundaries}
        aux_data = {"type": measurement.type, "name": measurement.id}
        if aux_data not in data:
            data.append(aux_data)
        if aux_protection in protections:
            continue
        protections.append(aux_protection)
    
    context ={
        "board": board.name,
        "data": data,
        "protections": protections 
    }
    return context

def Generate_Protections_hpp(board_input:str):
    board_instance = globals()[board_input]
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Code_generation"))
    template = env.get_template("ProtectionsTemplate.hpp")
    context = Generate_Protections_context(board_instance)
    if context == False:
        if os.path.exists("Core/Inc/Communications/Packets/Protections.hpp"):
            os.remove("Core/Inc/Communications/Packets/Protections.hpp")
            return
    with open("Core/Inc/Communications/Packets/Protections.hpp","w") as Output:
        Output.write(template.render(context))

#--------------state_machine.hpp generation---------------#
def instance_object_name(name):
    return f"{name}_State_Machine"

def generate_code(state_machine):
    content = []
    
    content.extend([
        "#pragma once",
        '#include "ST-LIB.hpp"',
        "using namespace std::chrono_literals;",
        "",
        "// AUTOGENERATED CODE, DO NOT EDIT MANUALLY",
        "",
        f"class {state_machine.name}{{",
        "",
        "    public:",
        ""
    ])

    for t in state_machine.transitions:
        content.append(f"    static bool {t.name}();")
    for action in state_machine.actions:
        for sa in action.state_actions:
            content.append(f"    static void {sa.name}();")
    content.append("")
    
    main_instance = instance_object_name(state_machine.name)
    content.append(f"    StateMachine {main_instance};")
    for nested_sm in state_machine.nested_state_machines:
        nested_instance = instance_object_name(nested_sm.name)
        content.append(f"    StateMachine {nested_instance};")
    content.append("")
    
    content.append(f"    enum {state_machine.name}States {{")
    for state in state_machine.states:
        if isinstance(state, State):
            content.append(f"        {state.name.upper()},")
    content.append("    };")
    content.append("")
    
    for nested_sm in state_machine.nested_state_machines:
        content.append(f"    enum {nested_sm.name}{{")
        for state in nested_sm.states:
            content.append(f"        {state.name.upper()},")
        content.append("    };")
        content.append("")
    
    content.append(f"    {state_machine.name}(){{")
    content.append("")
    
    if state_machine.states:
        first_state = state_machine.states[0]
        content.append(f"        {main_instance} = StateMachine({state_machine.name}States::{first_state.name.upper()});")
        content.append("")
    
    for nested_sm in state_machine.nested_state_machines:
        nested_instance = instance_object_name(nested_sm.name)
        if nested_sm.states:
            first_nested = nested_sm.states[0]
            content.extend([
                f"        {nested_instance} = StateMachine({nested_sm.name}::{first_nested.name.upper()});",
                f"        {main_instance}.add_state_machine({nested_instance}, {get_state_reference(nested_sm.nested_to, state_machine.name)});"
            ])
            for state in nested_sm.states[1:]:
                content.append(f"        {nested_instance}.add_state({nested_sm.name}::{state.name.upper()});")
        content.append("")
    
    for state in state_machine.states[1:]:
        if isinstance(state, State):
            content.append(f"        {main_instance}.add_state({state_machine.name}States::{state.name.upper()});")
    content.append("")
    
    for t in state_machine.transitions:
        if t.comment:
            content.append(f"        // {t.comment}")
        from_state = get_state_reference(t.from_state, state_machine.name)
        to_state = get_state_reference(t.to_state, state_machine.name)
        content.append(f"        {main_instance}.add_transition({from_state}, {to_state}, {t.name});")
    content.append("")
    
    for action in state_machine.actions:
        for sa in action.state_actions:
            if sa.description:
                content.append(f"        // {sa.description}")
            state_ref = get_state_reference(action.state, state_machine.name)
            if action.type == "enter":
                content.append(f"        {main_instance}.add_enter_action({sa.name}, {state_ref});")
            elif action.type == "exit":
                content.append(f"        {main_instance}.add_exit_action({sa.name}, {state_ref});")
            elif action.type.startswith("cyclic"):
                precision = action.type.split("_")[1]
                content.append(f"        {main_instance}.add_{precision}_precision_cyclic_action({sa.name}, {sa.period}, {state_ref});")
    content.append("")
    
    content.extend([
        "    }",
        "",
        "};"
    ])
    
    with open("Core/Inc/state_machine.hpp", "w") as f:
        f.write("\n".join(content))


#Main function

boards = Generate_PacketDescription()
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








        