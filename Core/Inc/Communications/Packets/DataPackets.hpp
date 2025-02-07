#include "ST-LIB.hpp"

//Order packets for VCU
class DataPackets{

{'name': 'valve_state', 'values': ['VALVE_OPEN', 'VALVE_CLOSED']}

{'name': 'reed1', 'values': ['EXTENDED', 'RETRACTED']}

{'name': 'reed2', 'values': ['EXTENDED', 'RETRACTED']}

{'name': 'reed3', 'values': ['EXTENDED', 'RETRACTED']}

{'name': 'reed4', 'values': ['EXTENDED', 'RETRACTED']}

{'name': 'general_state', 'values': ['CONNECTING', 'OPERATIONAL', 'FAULT']}

{'name': 'specific_state', 'values': ['IDLE', 'TAKING OFF', 'STABLE LEVITATION', 'PROPULSION', 'LANDING', 'UNLOADING', 'LOADING', 'TRACTION']}

{'name': 'voltage_state', 'values': ['NOT_HV', 'HV']}

{'name': 'emergency_tape', 'values': ['DISABLED', 'ENABLED']}

{'name': 'emergency_tape_value', 'values': ['NORMAL', 'EMERGENCY']}

{'name': 'pcu_connection', 'values': ['Disconnected', 'Connected']}

{'name': 'obccu_connection', 'values': ['Disconnected', 'Connected']}

{'name': 'lcu_connection', 'values': ['Disconnected', 'Connected']}

{'name': 'bmsl_connection', 'values': ['Disconnected', 'Connected']}


    private:
        constexpr static size_t size =35;
        uint32_t id{0};
    public:
        std::array<StackPacket*,size> packets; 
        StackPacket* vcu_regulator_packet;
        StackPacket* vcu_reed_packet;
        StackPacket* vcu_bottle_temperature_packet;
        StackPacket* vcu_pressure_packet;
        StackPacket* encoder_packet;
        StackPacket* state_machines_packet;
        StackPacket* emergency_tape_state;
        StackPacket* output_vtg;
        StackPacket* Tcp_connections;
        StackPacket* waterblock_data;
        
        
    DataPackets(&obccu_connection obccu_connection,&general_state general_state,&reed1 reed1,&float32 actual_pressure,&lcu_connection lcu_connection,&float64 acceleration,&reed2 reed2,&float32 low_pressure_2,&voltage_state voltage_state,&specific_state specific_state,&float32 low_pressure_1,&uint16_t output_voltage,&pcu_connection pcu_connection,&float32 waterblock_pressure,&reed3 reed3,&valve_state valve_state,&bool driving_mosfets,&float32 high_pressure,&emergency_tape_value emergency_tape_value,&float64 direction,&emergency_tape emergency_tape,&reed4 reed4,&float32 reference_pressure,&float64 position,&float64 bottle_temp_2,&uint32_t longest_update_ms,&float64 bottle_temp_1,&bmsl_connection bmsl_connection,&float32 waterblock_temperature,&float64 speed)
{

vcu_regulator_packet = new StackPacket(211,valve_state,reference_pressure,actual_pressure);
packets[id] = vcu_regulator_packet;
id++;
vcu_reed_packet = new StackPacket(212,reed1,reed2,reed3,reed4);
packets[id] = vcu_reed_packet;
id++;
vcu_bottle_temperature_packet = new StackPacket(213,bottle_temp_1,bottle_temp_2);
packets[id] = vcu_bottle_temperature_packet;
id++;
vcu_pressure_packet = new StackPacket(214,high_pressure,low_pressure_1,low_pressure_2);
packets[id] = vcu_pressure_packet;
id++;
encoder_packet = new StackPacket(219,direction,position,speed,acceleration);
packets[id] = encoder_packet;
id++;
state_machines_packet = new StackPacket(220,longest_update_ms,general_state,specific_state,voltage_state);
packets[id] = state_machines_packet;
id++;
emergency_tape_state = new StackPacket(221,emergency_tape,emergency_tape_value);
packets[id] = emergency_tape_state;
id++;
output_vtg = new StackPacket(981,output_voltage,driving_mosfets);
packets[id] = output_vtg;
id++;
Tcp_connections = new StackPacket(230,pcu_connection,obccu_connection,lcu_connection,bmsl_connection);
packets[id] = Tcp_connections;
id++;
waterblock_data = new StackPacket(231,waterblock_temperature,waterblock_pressure);
packets[id] = waterblock_data;
id++;


}
};