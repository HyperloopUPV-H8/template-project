import re
import json

class BoardDescription:    
    def __init__(self,name:str,board:dict,JSONpath:str):
        self.name = name
        self.id = board["board_id"]
        self.ip = board["board_ip"]
        self.data_size =0
        self.order_size =0
        i = 0
        self.packets = {}
        for packets in board["packets"]:
            packets_name = re.split(r'_|\.', packets)[0]
            self.packets[packets_name] = []
            measurement = self._MeasurementFileSearch(packets,board["measurements"])
            with open(JSONpath+"/boards/" + name+"/" + board["packets"][i]) as f:
                p= json.load(f)
            with open(JSONpath+"/boards/" + name + "/" + measurement) as f:
                m = json.load(f)
            i += 1
            for packet in p["packets"]:
                j=0
                self.packets[packets_name].append(PacketDescription(packet,m))
                if self.packets[packets_name][j].type != "order":
                    self.data_size += 1
                else:
                    self.order_size += 1
                j += 1
    @staticmethod            
    def _MeasurementFileSearch(packet:str,measurements:dict):
        packet_name = packet.split('_')[0]
        for measurement in measurements:
            measurement_name = measurement.split('_')[0]
            if packet_name[0] == measurement_name[0]:
                return measurement
        else:
            return measurements[0]
class PacketDescription:
    def __init__(self, packet:dict,measurements:dict):
        self.id =packet["id"]
        self.name = (packet["name"].replace(" ", "_").replace("(", "").replace(")", ""))
        self.type = packet["type"]
        self.variables = []
        self.measurements = []
        for variable in packet["variables"]:
            self.variables.append(variable["name"])
            self.measurements.append(MeasurmentsDescription(measurements,variable["name"]))


class MeasurmentsDescription:
    def __init__(self,measurements:dict, variable:str):
        self.id = variable
        measurement = self._MeasurementSearch(measurements,variable)
        if measurement is None:
            raise Exception("Measurement not found")
        else:
            self.name = measurement["name"]
            self.type = self._unsigned_int_correction(measurement["type"])
            if self.type == "enum":
                values = []
                for value in measurement["enumValues"]:
                    values.append(str(value))
                self.enum ={"name": measurement["id"], "values": self._Enum_values_correction(values)}
                self.type = measurement["id"]
            protections = self._protection_search(measurement)
            if protections is not None:
                self.protections = self.Protections(protections)
                
    @staticmethod
    def _Enum_values_correction(values:list):
        for i in range(len(values)):
            values[i] = values[i].replace(" ", "_")
        return values
                
                
    @staticmethod
    def _MeasurementSearch(measurements:dict, variable:str):
        for measurment in measurements["measurements"]:
            if measurment["id"] == variable:
                return measurment
        return None
    
    
    @staticmethod
    def _unsigned_int_correction(type:str):
        aux_type = type[:4]
        if aux_type == "uint":
            type += "_t"
        return type
    
    @staticmethod
    def _protection_search(measurement:dict):
        warningRange = measurement.get("warningRange")
        safeRange = measurement.get("safeRange")
        if warningRange is None and safeRange is None:
            return None
    
        protections = [[None, None], [None, None]]
        
        if safeRange is not None:
            for i in range(len(safeRange)):
                protections[0][i] = safeRange[i]
        
        if warningRange is not None:
            for i in range(len(warningRange)):
                protections[1][i] = warningRange[i]
            
        return protections
    
    class Protections:
        class Below:
            def __init__(self, protections:list):
                self.Protectionvalue = [None, None]
                self.ProtectionType = "Below"
                if protections[0] is not None and protections[0][0] is not None:
                    self.Protectionvalue[0] = protections[0][0]
                if protections[1] is not None and protections[1][0] is not None:
                    self.Protectionvalue[1] = protections[1][0]

        class Above:
            def __init__(self, protections:list):
                self.Protectionvalue = [None, None]
                self.ProtectionType = "Above"
                if protections[0] is not None and protections[0][1] is not None:
                    self.Protectionvalue[0] = protections[0][1]
                if protections[1] is not None and protections[1][1] is not None:
                    self.Protectionvalue[1] = protections[1][1]
                        
        def __init__(self, protections:list):
            self.protections = [None, None]
            self.protections[0] = self.Below(protections)
            self.protections[1] = self.Above(protections)
            
