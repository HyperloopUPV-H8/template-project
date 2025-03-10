from Packet_generation.Packet_descriptions import *
import json
import os
import jinja2

templates_path = "Core/Inc/Code_generation/Packet_generation"

def Generate_PacketDescription(JSONpath:str):    
    with open(JSONpath+"/boards.json") as f:
        boards = json.load(f)
    boards_name = []
    for board in boards["boards"]:
        
        with open(JSONpath+"/" + (boards["boards"][board])) as f:
            b = json.load(f)
        board_instance = BoardDescription(board, b,JSONpath)
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
    data_packets_path = "Core/Inc/Communications/Packets/DataPackets.hpp"
    board_instance = globals()[board_input]
    if board_instance.data_size == 0:
        if os.path.exists(data_packets_path):
            os.remove(data_packets_path)
        return    
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader(templates_path))
    template = env.get_template("DataTemplate.hpp")
    context = Get_data_context(board_instance)

    
    with open(data_packets_path,"w") as Output:
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
    order_packets_path = "Core/Inc/Communications/Packets/OrderPackets.hpp"
    board_instance = globals()[board_input]
    if board_instance.order_size == 0:
        if os.path.exists(order_packets_path):
            os.remove(order_packets_path)
        return    
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader(templates_path))
    template = env.get_template("OrderTemplate.hpp")
    context = Get_order_context(board_instance)

    
    with open(order_packets_path,"w") as Output:
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
    protections_path = "Core/Inc/Communications/Packets/Protections.hpp"
    board_instance = globals()[board_input]
    env= jinja2.Environment(loader=jinja2.FileSystemLoader(templates_path))
    template = env.get_template("ProtectionsTemplate.hpp")
    context = Generate_Protections_context(board_instance)
    if context == False:
        if os.path.exists(protections_path):
            os.remove(protections_path)
        return
    with open(protections_path,"w") as Output:
        Output.write(template.render(context))