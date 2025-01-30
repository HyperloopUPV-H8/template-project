#include "ST-LIB.hpp"

//Order packets for VCU
class OrderPacket{
    
enum class test_speed_control_direction{ 
 FORWARD,
BACKWARD 
};

    private:
        constexpr static size_t size =35;
        uint32_t id{0};
    public:
        std::array<StackPacket*,size> packets; 
        StackPacket* propagate_fault;
        StackPacket* start_charging_(obccu);
        StackPacket* stop_charging_(obccu);
        StackPacket* open_contactors_(obccu);
        StackPacket* close_contactors_(obccu);
        StackPacket* brake;
        StackPacket* unbrake;
        StackPacket* set_regulator_pressure;
        StackPacket* disable_emergency_tape;
        StackPacket* enable_emergency_tape;
        StackPacket* reset_vcu;
        StackPacket* test_pwm;
        StackPacket* test_current_control;
        StackPacket* set_reset_on;
        StackPacket* set_reset_off;
        StackPacket* start_levitation_control;
        StackPacket* start_vertical_levitation;
        StackPacket* stop_levitation;
        StackPacket* stick_down;
        StackPacket* landing;
        StackPacket* start_horizontal_levitation;
        StackPacket* enter_testing_mode;
        StackPacket* exit_testing_mode;
        StackPacket* manual_zeroing;
        StackPacket* set_stable_levitation_on;
        StackPacket* set_stable_levitation_off;
        StackPacket* set_rgb_color;
        StackPacket* turn_on_party;
        StackPacket* turn_off_party;
        StackPacket* turn_on_pump;
        StackPacket* turn_off_pump;
        StackPacket* discharge_dclink;
        StackPacket* change_position_references;
        StackPacket* start_vf_control;
        StackPacket* CRUISING_DEMONSTRATION;

        
    OrderPacket(uint16_t &idpacket902,uint16_t &idpacket210,float32 &new_reference_pressure,uint16_t &idpacket625,uint16_t &idpacket354,uint16_t &ldu_buffer_id,uint16_t &idpacket646,float32 &target_test_speed_control_kmh,test_speed_control_direction &test_speed_control_direction,float64 &lower_position_limit,float64 &upper_position_limit,uint16_t &idpacket356,float32 &lcu_desired_distance,uint16_t &idpacket216,uint16_t &idpacket290,uint16_t &idpacket362,uint16_t &idpacket223,uint16_t &idpacket293,uint16_t &idpacket359,uint16_t &idpacket901,uint16_t &idpacket291,uint16_t &idpacket611,uint16_t &idpacket217,uint16_t &idpacket353,uint16_t &ldu_buffer_id,uint16_t &idpacket215,uint16_t &idpacket218,uint16_t &idpacket363,uint16_t &idpacket0,uint16_t &idpacket352,uint16_t &ldu_id,float32 &lcu_desired_current,uint16_t &idpacket903,uint16_t &idpacket292,uint16_t &idpacket350,uint16_t &ldu_id,float32 &pwm_duty_cycle,uint16_t &idpacket364,uint16_t &idpacket355,float32 &lcu_desired_distance,uint16_t &idpacket357,uint16_t &idpacket358,uint16_t &idpacket360,uint16_t &idpacket361,uint16_t &idpacket294,uint16_t &idpacket645,float64 &lower_position_limit,float64 &upper_position_limit,uint16_t &idpacket368,uint16_t &idpacket900)
{

   propagate_fault = new StackPacket(idpacket0);
   packets[id] = propagate_fault;
   id++;
   start_charging_(obccu) = new StackPacket(idpacket900);
   packets[id] = start_charging_(obccu);
   id++;
   stop_charging_(obccu) = new StackPacket(idpacket901);
   packets[id] = stop_charging_(obccu);
   id++;
   open_contactors_(obccu) = new StackPacket(idpacket902);
   packets[id] = open_contactors_(obccu);
   id++;
   close_contactors_(obccu) = new StackPacket(idpacket903);
   packets[id] = close_contactors_(obccu);
   id++;
   brake = new StackPacket(idpacket215);
   packets[id] = brake;
   id++;
   unbrake = new StackPacket(idpacket216);
   packets[id] = unbrake;
   id++;
   set_regulator_pressure = new StackPacket(idpacket210,new_reference_pressure);
   packets[id] = set_regulator_pressure;
   id++;
   disable_emergency_tape = new StackPacket(idpacket217);
   packets[id] = disable_emergency_tape;
   id++;
   enable_emergency_tape = new StackPacket(idpacket218);
   packets[id] = enable_emergency_tape;
   id++;
   reset_vcu = new StackPacket(idpacket223);
   packets[id] = reset_vcu;
   id++;
   test_pwm = new StackPacket(idpacket350,ldu_id,pwm_duty_cycle);
   packets[id] = test_pwm;
   id++;
   test_current_control = new StackPacket(idpacket352,ldu_id,lcu_desired_current);
   packets[id] = test_current_control;
   id++;
   set_reset_on = new StackPacket(idpacket353,ldu_buffer_id);
   packets[id] = set_reset_on;
   id++;
   set_reset_off = new StackPacket(idpacket354,ldu_buffer_id);
   packets[id] = set_reset_off;
   id++;
   start_levitation_control = new StackPacket(idpacket355,lcu_desired_distance);
   packets[id] = start_levitation_control;
   id++;
   start_vertical_levitation = new StackPacket(idpacket356,lcu_desired_distance);
   packets[id] = start_vertical_levitation;
   id++;
   stop_levitation = new StackPacket(idpacket357);
   packets[id] = stop_levitation;
   id++;
   stick_down = new StackPacket(idpacket358);
   packets[id] = stick_down;
   id++;
   landing = new StackPacket(idpacket359);
   packets[id] = landing;
   id++;
   start_horizontal_levitation = new StackPacket(idpacket360);
   packets[id] = start_horizontal_levitation;
   id++;
   enter_testing_mode = new StackPacket(idpacket361);
   packets[id] = enter_testing_mode;
   id++;
   exit_testing_mode = new StackPacket(idpacket362);
   packets[id] = exit_testing_mode;
   id++;
   manual_zeroing = new StackPacket(idpacket611);
   packets[id] = manual_zeroing;
   id++;
   set_stable_levitation_on = new StackPacket(idpacket363);
   packets[id] = set_stable_levitation_on;
   id++;
   set_stable_levitation_off = new StackPacket(idpacket364);
   packets[id] = set_stable_levitation_off;
   id++;
   set_rgb_color = new StackPacket(idpacket290);
   packets[id] = set_rgb_color;
   id++;
   turn_on_party = new StackPacket(idpacket291);
   packets[id] = turn_on_party;
   id++;
   turn_off_party = new StackPacket(idpacket292);
   packets[id] = turn_off_party;
   id++;
   turn_on_pump = new StackPacket(idpacket293);
   packets[id] = turn_on_pump;
   id++;
   turn_off_pump = new StackPacket(idpacket294);
   packets[id] = turn_off_pump;
   id++;
   discharge_dclink = new StackPacket(idpacket368);
   packets[id] = discharge_dclink;
   id++;
   change_position_references = new StackPacket(idpacket645,lower_position_limit,upper_position_limit);
   packets[id] = change_position_references;
   id++;
   start_vf_control = new StackPacket(idpacket625);
   packets[id] = start_vf_control;
   id++;
   CRUISING_DEMONSTRATION = new StackPacket(idpacket646,target_test_speed_control_kmh,test_speed_control_direction,lower_position_limit,upper_position_limit);
   packets[id] = CRUISING_DEMONSTRATION;
   id++;

}
};