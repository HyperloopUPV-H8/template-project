#include "ST-LIB.hpp"

//Order packets for {{board}}
class DataPackets{
{% for enum in enums %}
{{enum.enum}}
{% endfor %}

    private:
        constexpr static size_t size ={{size}};
        uint32_t id{0};
    public:
        std::array<StackPacket*,size> packets; 
        {%for packet in packets%}StackPacket* {{packet.name}};
        {% endfor %}
        
    DataPackets({{data}})
{

{% for packet in packets %}{{packet.name}} = new StackPacket({{packet.id}}{% if packet.data%},{{packet.data}}{% endif%});
packets[id] = {{packet.name}};
id++;
{% endfor %}

}
};