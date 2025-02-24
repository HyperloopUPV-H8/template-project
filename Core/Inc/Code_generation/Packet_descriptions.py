import re
import json

#--------------PacketDescription------------------------#

class BoardDescription:    
    def __init__(self,name:str,board:dict):
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
            with open("Core/Inc/Communications/JSON_ADE/boards/" + name+"/" + board["packets"][i]) as f:
                p= json.load(f)
            with open("Core/Inc/Communications/JSON_ADE/boards/" + name + "/" + measurement) as f:
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
            
#--------------StateMachine------------------------#
            
class State:
    def __init__(self, name:str):
        self.name=name

class Transition:
    def __init__(self, name:str,from_state:str,to_state:str,description:str=None):
        self.name=name
        self.from_state=from_state
        self.to_state=to_state
        self.comment=description

class Enter:
    def __init__(self, state: str, state_actions: list):
        self.state = state
        self.state_actions = state_actions

class CyclicLowPrecision:
    def __init__(self, states: list, state_actions: list):
        self.states = states
        self.state_actions = state_actions

class CyclicMidPrecision:
    def __init__(self, states: list, state_actions: list):
        self.states = states
        self.state_actions = state_actions

class CyclicHighPrecision:
    def __init__(self, states: list, state_actions: list):
        self.states = states
        self.state_actions = state_actions

class Exit:
    def __init__(self, state: str, state_actions: list):
        self.state = state
        self.state_actions = state_actions

class StateReference:
    def __init__(self, state_data):
        if isinstance(state_data, str):
            self.state_name = state_data
            self.nested_machine = None
            self.sub_state = None
        else:
            self.state_name = None
            self.nested_machine = state_data["name"]
            self.sub_state = state_data["sub-state"]

    def __str__(self):
        if self.nested_machine:
            return f"{self.nested_machine}.{self.sub_state}"
        return self.state_name

class ActionDefinition:
    def __init__(self, action_data):
        if isinstance(action_data, str):
            self.name = action_data
            self.description = None
            self.period = None
        else:
            self.name = action_data.get("name") or action_data.get("action_name")
            self.description = action_data.get("description")
            self.period = action_data.get("action_period")

class Action:
    def __init__(self):
        self.type = None
        self.state = None
        self.state_actions = []

    @classmethod
    def create_enter_exit(cls, action_type, state_data, actions_data):
        action = cls()
        action.type = action_type
        action.state = StateReference(state_data)
        action.state_actions = [ActionDefinition(a) for a in actions_data]
        return action

    @classmethod
    def create_cyclic(cls, precision, states_data, actions_data):
        actions = []
        for state in states_data:
            for action_data in actions_data:
                action = cls()
                action.type = f"cyclic_{precision}"
                action.state = StateReference(state)
                action.state_actions = [ActionDefinition(action_data)]
                actions.append(action)
        return actions

    def describe(self):
        states_str = ", ".join(str(s) for s in self.states)
        actions_str = ", ".join(
            f"{a.name}" + (f"({a.period})" if a.period else "") + 
            (f" - {a.description}" if a.description else "")
            for a in self.actions
        )
        return f"{self.type} action on {states_str}: {actions_str}"

class StateMachine:
    def __init__(self,name:str):
        self.name=name
        self.states=[]
        self.transitions=[]
        self.actions=[]
        self.nested_state_machines=[]
    
    def add_state(self,state:State):
        self.states.append(state)

    def add_transition(self,transition:Transition):
        self.transitions.append(transition)

    def add_action(self, action:Action):
        self.actions.append(action)
    
    def add_nested_state_machine(self, state_machine:'StateMachine'):
        self.nested_state_machines.append(state_machine)


def parse_state(data):
    if isinstance(data, str):
        return State(data)
    elif isinstance(data, dict):
        nested_sm = StateMachine(data["name"])
        for sub_state in data["sub-states"]:
            nested_sm.add_state(State(sub_state))
        return nested_sm

def parse_transition(data):
    name = data["transition_name"]
    description = data.get("description")

    from_state = StateReference(data["from_state"])
    to_state = StateReference(data["to_state"]) 
    
    return Transition(name, from_state, to_state, description)

def parse_actions(data):
    actions_list = []
    
    actions_data = data.get("actions", {})
    
    for enter_data in actions_data.get("enter", []):
        action = Action.create_enter_exit(
            "enter",
            enter_data["state"],
            enter_data["state_actions"]
        )
        actions_list.append(action)

    cyclic_data = actions_data.get("cyclic", {})
    for precision in ["low_precision", "mid_precision", "high_precision"]:
        for cyclic_item in cyclic_data.get(precision, []):
            actions = Action.create_cyclic(
                precision,
                cyclic_item["states"],
                cyclic_item["state_actions"]
            )
            actions_list.extend(actions)

    for exit_data in actions_data.get("exit", []):
        action = Action.create_enter_exit(
            "exit",
            exit_data["state"],
            exit_data["state_actions"]
        )
        actions_list.append(action)

    return actions_list

def parse_state_machine(data):
    sm = StateMachine(data["name"])

    for st_data in data["states"]:
        parsed = parse_state(st_data)
        if isinstance(parsed, State):
            sm.add_state(parsed)
        else:
            sm.add_nested_state_machine(parsed)

    for tr_data in data["transitions"]:
        tr = parse_transition(tr_data)
        sm.add_transition(tr)

    parsed_actions = parse_actions(data)
    sm.actions = parsed_actions

    return sm

def get_state_reference(state_ref, state_machine_name):
    if isinstance(state_ref, str):
        return f"{state_machine_name}States::{state_ref.upper()}"
    
    if state_ref.nested_machine:
        return f"{state_ref.nested_machine}::{state_ref.sub_state.upper()}"
    return f"{state_machine_name}States::{state_ref.state_name.upper()}"