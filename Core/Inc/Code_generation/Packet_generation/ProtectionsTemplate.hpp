#pragma once
#include "ST-LIB.hpp"

//Data protections for {{ board }} -AUTOGENERATED CODE, DO NOT MODIFY-
class DataProtections{
    public:
    DataProtections({%for value in data %}{{value.type}} &{{value.name}}{%if not loop.last%},{%endif%}{%endfor%}){

    {% for protection in protections %}ProtectionManager::_add_protection({{ protection.packet }},{% for Boundary in protection.Boundaries %}Boundary<{{Boundary.type}},{{Boundary.Above_or_Below}}>({{ Boundary.value }}){{ Boundary.coma }}{% endfor %}}).set_name("{{ protection.packet }}");
    {% endfor %}
}
};