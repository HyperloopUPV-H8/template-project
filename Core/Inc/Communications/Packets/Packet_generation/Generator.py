import json 
import Packet_descriptions as Pd
import os
import jinja2


def Generate_PacketDescription():
    with open("Core/Inc/Communications/JSON_ADE/boards.json") as f:
        boards = json.load(f)
    boards_name = []
    for board in boards["boards"]:
        with open("Core/Inc/Communications/JSON_ADE/" + (boards["boards"][board])) as f:
            b = json.load(f)
        board_instance = Pd.BoardDescription(board, b)
        boards_name.append(board_instance.name)
        globals()[board] = board_instance
    
    return boards_name
        

#DataPackets generation:

def Get_data_context(board:Pd.BoardDescription):
    def GenerateDataEnum(board:Pd.BoardDescription):
        Enums = []
        for packet in board.packets:
            if packet != "orders":
                for packet_instance in board.packets[packet]:
                    for measurement in packet_instance.measurements:
                        if hasattr(measurement, "enum"):
                            Enums.append({"enum":measurement.enum})
        return Enums

    
    def GenerateDataPackets(board:Pd.BoardDescription):
        Packets =[]
        totaldata = set()
        for packet in board.packets:
            if packet != "orders":
                for packet_instance in board.packets[packet]:
                    tempdata = ""
                    for variable in packet_instance.variables:
                        tempdata +=(str(variable) +",")
                    if tempdata.endswith(","):
                        tempdata = tempdata[:-1]  
                    aux_packet = {"name": packet_instance.name, "data":tempdata , "id": packet_instance.id}
                    Packets.append(aux_packet)
                    for measurement in packet_instance.measurements:
                        auxdata = ("&"+str(measurement.type)+" "+str(measurement.id) +",")
                        totaldata.add(auxdata)
        totaldata = list(totaldata)
        totaldata = "".join(totaldata)
        if totaldata.endswith(","):
            totaldata = totaldata[:-1]
        
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
    
    if board_instance.order_size == 0:
        if os.path.exists("Core/Inc/Communications/Packets/OrderPackets.hpp"):
            os.remove("Core/Inc/Communications/Packets/OrderPackets.hpp")
        return    
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Communications/Packets/Packet_generation"))
    template = env.get_template("DataTemplate.hpp")
    context = Get_data_context(board_instance)

    
    with open("Core/Inc/Communications/Packets/DataPackets.hpp","w") as Output:
        Output.write(template.render(context))
            
#OrderPackets generation:

def Get_order_context(board:Pd.BoardDescription):
    def GenerateOrderEnum(board:Pd.BoardDescription):
        Enums = []
        for packet in board.packets:
            if packet == "orders":
                for packet_instance in board.packets[packet]:
                    for measurement in packet_instance.measurements:
                        if hasattr(measurement, "enum"):
                            Enums.append({"enum":measurement.enum})
        return Enums
    
    
    def GenerateOrderPackets(board:Pd.BoardDescription):
        Packets =[]
        totaldata = set()
        for packet in board.packets:
            if packet == "orders":
                for packet_instance in board.packets[packet]:
                    tempdata = ""
                    for variable in packet_instance.variables:
                        tempdata +=(str(variable) +",")
                    if tempdata.endswith(","):
                        tempdata = tempdata[:-1]  
                    aux_packet = {"name": packet_instance.name, "data":tempdata , "id": packet_instance.id}
                    Packets.append(aux_packet)
                    for measurement in packet_instance.measurements:
                        auxdata = ("&"+str(measurement.type)+" "+str(measurement.id) +",")
                        totaldata.add(auxdata)
        totaldata = list(totaldata)
        totaldata = "".join(totaldata)
        if totaldata.endswith(","):
            totaldata = totaldata[:-1]
        
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
  
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Communications/Packets/Packet_generation"))
    template = env.get_template("OrderTemplate.hpp")
    context = Get_order_context(board_instance)

    
    with open("Core/Inc/Communications/Packets/OrderPackets.hpp","w") as Output:
        Output.write(template.render(context))


#Protections generation:

def Generate_Protections_context(board:Pd.BoardDescription):
    def Get_Bondaries(measurement:Pd.MeasurmentsDescription):
        Boundaries = []
        for i in {0,1}:
            for j in {0,1}:
                if measurement.protections.protections[i].Protectionvalue[j] is None:
                    continue
                temp_boundary= {"type": measurement.type, "Above_or_Below":measurement.protections.protections[i].ProtectionType, "value": measurement.protections.protections[i].Protectionvalue[j],"coma":"," }
                Boundaries.append(temp_boundary)
        
        Boundaries[-1]["coma"] = ""
        return Boundaries
            

    def Get_protection_packets(board:Pd.BoardDescription):
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
    data =""
    for measurement in protection_packets:
        Boundaries = Get_Bondaries(measurement)
        aux_protection = {"packet": measurement.id, "Boundaries": Boundaries}
        if aux_protection in protections:
            continue
        protections.append(aux_protection)
        data += aux_protection["packet"]+","
    data = data[:-1]
    
    context ={
        "board": board.name,
        "data": data,
        "protections": protections 
    }
    return context

def Generate_Protections_hpp(board_input:str):
    board_instance = globals()[board_input]
    env= jinja2.Environment(loader=jinja2.FileSystemLoader("Core/Inc/Communications/Packets/Packet_generation"))
    template = env.get_template("ProtectionsTemplate.hpp")
    context = Generate_Protections_context(board_instance)
    if context == False:
        if os.path.exists("Core/Inc/Communications/Packets/Protections.hpp"):
            os.remove("Core/Inc/Communications/Packets/Protections.hpp")
            return
    with open("Core/Inc/Communications/Packets/Protections.hpp","w") as Output:
        Output.write(template.render(context))


#Main function:

boards = Generate_PacketDescription()
board = input("Enter board name: ")
while board not in boards: 
    print("Board not found, select an available board")
    board = input("Enter board name: ")
Generate_DataPackets_hpp(board)
Generate_OrderPackets_hpp(board)
Generate_Protections_hpp(board)







        