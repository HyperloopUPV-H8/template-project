#include "ST-LIB.hpp"

//Order packets for VCU
class DataPackets{

enum class valve_state{
 VALVE_OPEN,
VALVE_CLOSED 
};

enum class reed1{
 EXTENDED,
RETRACTED 
};

enum class reed2{
 EXTENDED,
RETRACTED 
};

enum class reed3{
 EXTENDED,
RETRACTED 
};

enum class reed4{
 EXTENDED,
RETRACTED 
};

enum class general_state{
 CONNECTING,
OPERATIONAL,
FAULT 
};

enum class specific_state{
 IDLE,
TAKING OFF,
STABLE LEVITATION,
PROPULSION,
LANDING,
UNLOADING,
LOADING,
TRACTION 
};

enum class voltage_state{
 NOT_HV,
HV 
};

enum class emergency_tape{
 DISABLED,
ENABLED 
};

enum class emergency_tape_value{
 NORMAL,
EMERGENCY 
};

enum class pcu_connection{
 Disconnected,
Connected 
};

enum class obccu_connection{
 Disconnected,
Connected 
};

enum class lcu_connection{
 Disconnected,
Connected 
};

enum class bmsl_connection{
 Disconnected,
Connected 
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
        
        
    DataPackets(&reed1,&acceleration,&valve_state,&high_pressure,&longest_update_ms,&voltage_state,&output_voltage,&low_pressure_1,&obccu_connection,&general_state,&emergency_tape,&lcu_connection,&reed3,&emergency_tape_value,&driving_mosfets,&specific_state,&actual_pressure,&reference_pressure,&direction,&low_pressure_2,&bottle_temp_1,&reed2,&position,&reed4,&speed,&pcu_connection,&waterblock_temperature,&bottle_temp_2,&bmsl_connection,&waterblock_pressure)
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