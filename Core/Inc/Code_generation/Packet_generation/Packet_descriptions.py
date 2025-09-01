import re 
import json

class BoardDescription:
    def __init__(self,name:str,board:dict,JSONpath:str):
        self.name = name
        self.id = board["board_id"]
        self.ip = board["board_ip"]
        self.data_size =0
        self.order_size =0
        self.measurements_files = board["measurements"]
        self.packet_files = board["packets"]
        self.measurement_lists = []
        self.packets = {}
        for measurement in board["measurements"]:
            with open(JSONpath+"/boards/" + name + "/" + measurement) as f:
                m = json.load(f)
                self.measurement_lists.append(m)
        for packets in board["packets"]:
            packets_name = re.split(r'_|\.', packets)[0]
            self.packets[packets_name] = []
            with open(JSONpath+"/boards/" + name+"/" + packets) as f:
                p= json.load(f)
            i=0
            for packet in p:
                self.packets[packets_name].append(PacketDescription(packet,self.measurement_lists))
                if self.packets[packets_name][i].type != "order":
                    self.data_size += 1
                else:
                    self.order_size += 1
                i += 1
class PacketDescription:
    def __init__(self, packet:dict,measurements:list):
        self.id =packet["id"]
        self.name = packet["name"].replace(" ", "_").replace("-", "_")
        self.type = packet["type"]
        self.variables = []
        self.measurements = []
        if "variables" not in packet:
            return
        for variable in packet["variables"]:
            self.variables.append(variable)
            self.measurements.append(MeasurmentsDescription(measurements,variable))

class MeasurmentsDescription:
    def __init__(self,measurements:list, variable:str):
        self.id = variable
        if not hasattr(self.__class__, 'viewed_measurements'):
            self.__class__.viewed_measurements = {}
        measurement = self._MeasurementSearch(measurements,variable)
        
        if measurement is None:
            print(variable)
            raise Exception("Measurement not found")
        
        self.name = measurement["name"]
        self.type = (self._unsigned_int_correction(measurement["type"]).replace(" ", "_").replace("-", "_"))
        if self.type == "enum":
            values = []
            for value in measurement["enumValues"]:
                values.append(str(value))
            self.enum ={"name": (measurement["id"].replace(" ", "_").replace("-", "_")), "values": self._Enum_values_correction(values)}
            self.type = (measurement["id"].replace(" ", "_").replace("-", "_"))

    @staticmethod
    def _Enum_values_correction(values:list):
        for i in range(len(values)):
            values[i] = values[i].replace(" ", "_").replace("-", "_")
        return values
                
                
    @staticmethod
    def _MeasurementSearch(measurements:list, variable:str):
        if variable in MeasurmentsDescription.viewed_measurements:
            return MeasurmentsDescription.viewed_measurements[variable]
        for measurement_list in measurements:
            for measurment in measurement_list:
                if measurment["id"] == variable:
                    MeasurmentsDescription.viewed_measurements[variable] = measurment
                    return measurment
        return None
    
    
    @staticmethod
    def _unsigned_int_correction(type:str):
        aux_type = type[:4]
        if aux_type == "uint":
            type += "_t"
        return type