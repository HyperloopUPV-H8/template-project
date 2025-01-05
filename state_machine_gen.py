import json

########################################################
#                  OPEN THE JSON FILE
########################################################

with open("state_machine.json","r") as file:
    data=json.load(file)

########################################################
#           ENUM + STATE MACHINE + STATES
########################################################

states=data["states"]

enum_code = "enum GeneralStates {\n"
for state in states:
    if isinstance(state,str):
        enum_code += f"        {state.upper()},\n"
enum_code +="    };\n\n"

state_machine_code ="    GeneratedStateMachine(){\n"
state_machine_code += f"\n        StateMachine general_state_machine = StateMachine(GeneralStates::{states[0].upper()});\n"

for i in range (1,len(states)):
    if isinstance(states[i],str):
        state_machine_code += f"        general_state_machine.add_state(GeneralStates::{states[i].upper()});\n"
    elif isinstance(states[i], dict):
        nested_sm_name=states[i]["name"]
        nested_sm_states=states[i]["sub-states"]

        enum_code += f"    enum {nested_sm_name}"
        enum_code += "{\n"
        for state in nested_sm_states:
            enum_code += f"        {state.upper()},\n"
        
        enum_code +="    };\n\n"

        state_machine_code += f"\n        StateMachine {nested_sm_name} = StateMachine({nested_sm_states[0].upper()});\n"
        state_machine_code += f"        general_state_machine.add_state_machine({nested_sm_name},{nested_sm_states[0].upper()});\n"
        for j in range (1,len(nested_sm_states)):
            state_machine_code += f"        {nested_sm_name}.add_state({nested_sm_states[j].upper()});\n"


########################################################
#                     TRANSITIONS
########################################################

transitions=data["transitions"]

function_header_code="\n"
transitions_code="\n"
for transition in transitions:
    old_state=transition["old_state"]
    new_state=transition["new_state"]
    transition_name=transition["transition_name"]
    description=transition.get("description")
    
    if(isinstance(old_state,dict)):
        if description:
            transitions_code+=f"        // {description}\n"
        transitions_code+=f"        general_state_machine.add_transition({old_state["name"]}::{old_state["sub-state"].upper()},GeneralStates::{new_state.upper()},{transition_name});\n"
        function_header_code+=f"    static bool {transition_name}();\n"
    elif(isinstance(new_state,dict)):
        if description:
            transitions_code+=f"        // {description}\n"
            transitions_code+=f"    general_state_machine.add_transition(GeneralStates::{old_state.upper()},{new_state["name"]}::{new_state["sub-state"].upper()},{transition_name});\n"
        function_header_code+=f"    static bool {transition_name}();\n"
    elif(isinstance(old_state,dict) and isinstance(new_state,dict)):
        if description:
            transitions_code+=f"        // {description}\n"
        transitions_code+=f"        general_state_machine.add_transition({old_state["name"]}::{old_state["sub-state"].upper()},GeneralStates::{new_state.upper()},{transition_name});\n"
        function_header_code+=f"    static bool {transition_name}();\n"
    else:
        if description:
            transitions_code+=f"        // {description}\n"
        transitions_code+=f"        general_state_machine.add_transition(GeneralStates::{old_state.upper()},GeneralStates::{new_state.upper()},{transition_name});\n"
        function_header_code+=f"    static bool {transition_name}();\n"
    


########################################################
#                       ACTIONS
########################################################

actions=data["actions"]

enter_actions=actions["enter"]
low_precision_cyclic_actions=actions["cyclic"]["low_precision"]
mid_precision_cyclic_actions=actions["cyclic"]["mid_precision"]
high_precision_cyclic_actions=actions["cyclic"]["high_precision"]
exit_actions=actions["exit"]

actions_code="\n"
function_header_code+="\n"

# ENTER ACTIONS

for enter_action in enter_actions:
    state=enter_action["state"]
    state_actions=enter_action["state_actions"]

    if(isinstance(state,dict)):
        for state_action in state_actions:
            if(isinstance(state_action,dict)):
                actions_code+=f"        // {state_action[description]}\n"
                actions_code+=f"        general_state_machine.add_enter_action({state_action["name"]},{state["name"]}::{state["sub-state"].upper()});\n"
                function_header_code+=f"    static void {state_action["name"]}();\n"
            else:
                actions_code+=f"        general_state_machine.add_enter_action({state_action},{state["name"]}::{state["sub-state"].upper()});\n"
                function_header_code+=f"    static void {state_action}();\n"
    else:
        for state_action in state_actions:
            if(isinstance(state_action,dict)):
                actions_code+=f"        // {state_action["description"]}\n"
                actions_code+=f"        general_state_machine.add_enter_action({state_action["name"]},GeneralStates::{state.upper()});\n"
                function_header_code+=f"    static void {state_action["name"]}();\n"
            else:
                actions_code+=f"        general_state_machine.add_enter_action({state_action},GeneralStates::{state.upper()});\n"
                function_header_code+=f"    static void {state_action}();\n"

actions_code+="\n"
function_header_code+="\n"

# LOW PRECISION CYCLIC ACTIONS

for low_precision_cyclic_action in low_precision_cyclic_actions :
    states=low_precision_cyclic_action["states"]
    state_actions=low_precision_cyclic_action["state_actions"]
    description=low_precision_cyclic_action.get("description")


    for state in states:
        if(isinstance(state,dict)):
            for state_action in state_actions:
                description=state_action.get("description")
                if(description):
                    actions_code+=f"        // {description}\n"
                    actions_code+=f"        general_state_machine.add_low_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code+=f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code+=f"        general_state_machine.add_low_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code+=f"    static void {state_action["action_name"]}();\n"
        else:
            for state_action in state_actions :
                description=state_action.get("description")
                if(description):
                    actions_code+=f"        // {description}\n"
                    actions_code+=f"        general_state_machine.add_low_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code+=f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code+=f"        general_state_machine.add_low_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code+=f"    static void {state_action["action_name"]}();\n"

actions_code+="\n"
function_header_code+="\n"

# MID PRECISION CYCLIC ACTIONS

for mid_precision_cyclic_action in mid_precision_cyclic_actions:
    states = mid_precision_cyclic_action["states"]
    state_actions = mid_precision_cyclic_action["state_actions"]
    description = mid_precision_cyclic_action.get("description")

    for state in states:
        if(isinstance(state,dict)):
            for state_action in state_actions:
                description = state_action.get("description")
                if(description):
                    actions_code += f"        // {description}\n"
                    actions_code += f"        general_state_machine.add_mid_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code += f"        general_state_machine.add_mid_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
        else:
            for state_action in state_actions:
                description = state_action.get("description")
                if(description):
                    actions_code += f"        // {description}\n"
                    actions_code += f"        general_state_machine.add_mid_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code += f"        general_state_machine.add_mid_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"

actions_code += "\n"
function_header_code += "\n"

# HIGH PRECISION CYCLIC ACTIONS

for high_precision_cyclic_action in high_precision_cyclic_actions:
    states = high_precision_cyclic_action["states"]
    state_actions = high_precision_cyclic_action["state_actions"]
    description = high_precision_cyclic_action.get("description")

    for state in states:
        if(isinstance(state,dict)):
            for state_action in state_actions:
                description = state_action.get("description")
                if(description):
                    actions_code += f"        // {description}\n"
                    actions_code += f"        general_state_machine.add_high_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code += f"        general_state_machine.add_high_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},{state["name"]}::{state["sub-state"].upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
        else:
            for state_action in state_actions:
                description = state_action.get("description")
                if(description):
                    actions_code += f"        // {description}\n"
                    actions_code += f"        general_state_machine.add_high_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"
                else:
                    actions_code += f"        general_state_machine.add_high_precision_cyclic_action({state_action["action_name"]},{state_action["action_period"]},GeneralStates::{state.upper()});\n"
                    function_header_code += f"    static void {state_action["action_name"]}();\n"

actions_code += "\n"
function_header_code += "\n"

# EXIT ACTIONS
for exit_action in exit_actions:
    state = exit_action["state"] 
    state_actions = exit_action["state_actions"]

    if(isinstance(state, dict)):
        for state_action in state_actions:
            if(isinstance(state_action, dict)):
                actions_code += f"        // {state_action['description']}\n"
                actions_code += f"        general_state_machine.add_exit_action({state_action['name']},{state['name']}::{state['sub-state'].upper()});\n"
                function_header_code += f"    static void {state_action['name']}();\n"
            else:
                actions_code += f"        general_state_machine.add_exit_action({state_action},{state['name']}::{state['sub-state'].upper()});\n"
                function_header_code += f"    static void {state_action}();\n"
    else:
        for state_action in state_actions:
            if(isinstance(state_action, dict)):
                actions_code += f"        // {state_action['description']}\n"
                actions_code += f"        general_state_machine.add_exit_action({state_action['name']},GeneralStates::{state.upper()});\n"
                function_header_code += f"    static void {state_action['name']}();\n"
            else:
                actions_code += f"        general_state_machine.add_exit_action({state_action},GeneralStates::{state.upper()});\n"
                function_header_code += f"    static void {state_action}();\n"

actions_code += "\n"
function_header_code += "\n"

actions_code += "\n    }\n"
function_header_code+="\n"


########################################################
#                  REPLACE THE TEMPLATE
########################################################

with open('Core/Inc/template_state_machine.hpp', "r") as template:
    template_content = template.read()

final_content=template_content.replace("%STATE_DEFINITION%", enum_code + state_machine_code)
final_content=final_content.replace("%TRANSITION_DEFINITION%",transitions_code)
final_content=final_content.replace("%ACTION_DEFINITION%",actions_code)
final_content=final_content.replace("%FUNCTION_HEADERS%",function_header_code)

########################################################
#                 REWRITE THE .HPP FILE
########################################################

with open('Core/Inc/state_machine.hpp', "w") as destination:
    destination.write(final_content)