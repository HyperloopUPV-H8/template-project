from State_machine_generation.State_machine_description import *
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

