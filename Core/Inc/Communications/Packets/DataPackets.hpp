#include "ST-LIB.hpp"

//Data packets for VCU
class DataPacket{
    
enum class valve_state{ 
 VALVE_OPEN,
VALVE_CLOSED 
};
enum class pcu_connection{ 
 Disconnected,
Connected 
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
enum class emergency_tape_value{ 
 NORMAL,
EMERGENCY 
};
enum class obccu_connection{ 
 Disconnected,
Connected 
};
enum class reed2{ 
 EXTENDED,
RETRACTED 
};
enum class voltage_state{ 
 NOT_HV,
HV 
};
enum class reed3{ 
 EXTENDED,
RETRACTED 
};
enum class lcu_connection{ 
 Disconnected,
Connected 
};
enum class reed1{ 
 EXTENDED,
RETRACTED 
};
enum class bmsl_connection{ 
 Disconnected,
Connected 
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
enum class emergency_tape{ 
 DISABLED,
ENABLED 
};

    private:
        constexpr static size_t size =10;
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

        
    DataPacket(uint16_t &idpacket230,pcu_connection &pcu_connection,obccu_connection &obccu_connection,lcu_connection &lcu_connection,bmsl_connection &bmsl_connection,uint16_t &idpacket211,valve_state &valve_state,float32 &reference_pressure,float32 &actual_pressure,uint16_t &idpacket231,float32 &waterblock_temperature,float32 &waterblock_pressure,uint16_t &idpacket220,uint32_t &longest_update_ms,general_state &general_state,specific_state &specific_state,voltage_state &voltage_state,uint16_t &idpacket219,float64 &direction,float64 &position,float64 &speed,float64 &acceleration,uint16_t &idpacket212,reed1 &reed1,reed2 &reed2,reed3 &reed3,reed4 &reed4,uint16_t &idpacket213,float64 &bottle_temp_1,float64 &bottle_temp_2,uint16_t &idpacket221,emergency_tape &emergency_tape,emergency_tape_value &emergency_tape_value,uint16_t &idpacket981,uint16_t &output_voltage,bool &driving_mosfets,uint16_t &idpacket214,float32 &high_pressure,float32 &low_pressure_1,float32 &low_pressure_2)
{

   vcu_regulator_packet = new StackPacket(idpacket211,valve_state,reference_pressure,actual_pressure);
   packets[id] = vcu_regulator_packet;
   id++;
   vcu_reed_packet = new StackPacket(idpacket212,reed1,reed2,reed3,reed4);
   packets[id] = vcu_reed_packet;
   id++;
   vcu_bottle_temperature_packet = new StackPacket(idpacket213,bottle_temp_1,bottle_temp_2);
   packets[id] = vcu_bottle_temperature_packet;
   id++;
   vcu_pressure_packet = new StackPacket(idpacket214,high_pressure,low_pressure_1,low_pressure_2);
   packets[id] = vcu_pressure_packet;
   id++;
   encoder_packet = new StackPacket(idpacket219,direction,position,speed,acceleration);
   packets[id] = encoder_packet;
   id++;
   state_machines_packet = new StackPacket(idpacket220,longest_update_ms,general_state,specific_state,voltage_state);
   packets[id] = state_machines_packet;
   id++;
   emergency_tape_state = new StackPacket(idpacket221,emergency_tape,emergency_tape_value);
   packets[id] = emergency_tape_state;
   id++;
   output_vtg = new StackPacket(idpacket981,output_voltage,driving_mosfets);
   packets[id] = output_vtg;
   id++;
   Tcp_connections = new StackPacket(idpacket230,pcu_connection,obccu_connection,lcu_connection,bmsl_connection);
   packets[id] = Tcp_connections;
   id++;
   waterblock_data = new StackPacket(idpacket231,waterblock_temperature,waterblock_pressure);
   packets[id] = waterblock_data;
   id++;

}
};