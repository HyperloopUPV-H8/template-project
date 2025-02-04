#include "ST-LIB.hpp"

//Order packets for VCU
class DataPackets{

enum class valve_state : uint8_t {
VALVE_OPEN=0,
VALVE_CLOSED=1 
};

enum class reed1 : uint8_t {
EXTENDED=0,
RETRACTED=1 
};

enum class reed2 : uint8_t {
EXTENDED=0,
RETRACTED=1 
};

enum class reed3 : uint8_t {
EXTENDED=0,
RETRACTED=1 
};

enum class reed4 : uint8_t {
EXTENDED=0,
RETRACTED=1 
};

enum class general_state : uint8_t {
CONNECTING=0,
OPERATIONAL=1,
FAULT=2 
};

enum class specific_state : uint8_t {
IDLE=0,
TAKING OFF=1,
STABLE LEVITATION=2,
PROPULSION=3,
LANDING=4,
UNLOADING=5,
LOADING=6,
TRACTION=7 
};

enum class voltage_state : uint8_t {
NOT_HV=0,
HV=1 
};

enum class emergency_tape : uint8_t {
DISABLED=0,
ENABLED=1 
};

enum class emergency_tape_value : uint8_t {
NORMAL=0,
EMERGENCY=1 
};

enum class pcu_connection : uint8_t {
Disconnected=0,
Connected=1 
};

enum class obccu_connection : uint8_t {
Disconnected=0,
Connected=1 
};

enum class lcu_connection : uint8_t {
Disconnected=0,
Connected=1 
};

enum class bmsl_connection : uint8_t {
Disconnected=0,
Connected=1 
};


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
        
        
    DataPackets(&actual_pressure,&obccu_connection,&reed4,&general_state,&bottle_temp_1,&reed2,&reference_pressure,&low_pressure_1,&valve_state,&bottle_temp_2,&acceleration,&waterblock_temperature,&pcu_connection,&output_voltage,&reed3,&specific_state,&longest_update_ms,&driving_mosfets,&voltage_state,&emergency_tape_value,&speed,&waterblock_pressure,&reed1,&direction,&low_pressure_2,&lcu_connection,&position,&emergency_tape,&bmsl_connection,&high_pressure)
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