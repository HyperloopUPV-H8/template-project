#include "ST-LIB.hpp"

//Order packets for {{board}}
class OrderPackets{
{% for enum in enums %}
{{enum.enum}}
{% endfor %}

{%for packet in packets%}void {{packet.name}}_callback();
{% endfor %}

    private:
        constexpr static size_t size ={{size}};
        uint32_t id{0};
    public:
        std::array<StackOrder*,size> packets; 
        {%for packet in packets%}StackOrder* {{packet.name}};
        {% endfor %}
        
    OrderPackets({{data}})
{

{% for packet in packets %}{{packet.name}} = new StackOrder({{packet.id}},{{packet.name}}_callback{% if packet.data%},{{packet.data}}{% endif%});
packets[id] = {{packet.name}};
id++;
{% endfor %}

}
};