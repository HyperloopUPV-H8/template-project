//Data protections for {{ board }}
class DataProtections{
    public:
    DataProtections({{ data }}){

{% for protection in protections %}ProtectionManager::_add_protection({{ protection.packet }},{% for Boundary in protection.Boundaries %}Boundary<{{Boundary.type}},{{Boundary.Above_or_Below}}>({{ Boundary.value }}){{ Boundary.coma }}{% endfor %}}).set_name("{{ protection.packet }}");
{% endfor %}
}
};