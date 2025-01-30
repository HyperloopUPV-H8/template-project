//Data protections for VCU
class DataProtections{
    public:
    DataProtections(new_reference_pressure,ldu_id,ldu_id,lcu_desired_current,ldu_buffer_id,ldu_buffer_id,lcu_desired_distance,lcu_desired_distance,lower_position_limit,upper_position_limit,lower_position_limit,upper_position_limit,reference_pressure,actual_pressure,high_pressure,position,speed,acceleration,output_voltage)
{

ProtectionManager::_add_protection(new_reference_pressure,Boundary<float32,Below>(0),Boundary<float32,Below>(0),Boundary<float32,Above>(10),Boundary<float32,Above>(10)}).set_name("new_reference_pressure");
ProtectionManager::_add_protection(ldu_id,Boundary<uint16_t,Below>(1),Boundary<uint16_t,Below>(1),Boundary<uint16_t,Above>(10),Boundary<uint16_t,Above>(10)}).set_name("ldu_id");
ProtectionManager::_add_protection(ldu_id,Boundary<uint16_t,Below>(1),Boundary<uint16_t,Below>(1),Boundary<uint16_t,Above>(10),Boundary<uint16_t,Above>(10)}).set_name("ldu_id");
ProtectionManager::_add_protection(lcu_desired_current,Boundary<float32,Below>(-50),Boundary<float32,Below>(-70),Boundary<float32,Above>(50),Boundary<float32,Above>(70)}).set_name("lcu_desired_current");
ProtectionManager::_add_protection(ldu_buffer_id,Boundary<uint16_t,Below>(1),Boundary<uint16_t,Below>(1),Boundary<uint16_t,Above>(5),Boundary<uint16_t,Above>(5)}).set_name("ldu_buffer_id");
ProtectionManager::_add_protection(ldu_buffer_id,Boundary<uint16_t,Below>(1),Boundary<uint16_t,Below>(1),Boundary<uint16_t,Above>(5),Boundary<uint16_t,Above>(5)}).set_name("ldu_buffer_id");
ProtectionManager::_add_protection(lcu_desired_distance,Boundary<float32,Below>(0.0001),Boundary<float32,Below>(0.01),Boundary<float32,Above>(0.03),Boundary<float32,Above>(0.03)}).set_name("lcu_desired_distance");
ProtectionManager::_add_protection(lcu_desired_distance,Boundary<float32,Below>(0.0001),Boundary<float32,Below>(0.01),Boundary<float32,Above>(0.03),Boundary<float32,Above>(0.03)}).set_name("lcu_desired_distance");
ProtectionManager::_add_protection(lower_position_limit,Boundary<float64,Below>(-2),Boundary<float64,Above>(0)}).set_name("lower_position_limit");
ProtectionManager::_add_protection(upper_position_limit,Boundary<float64,Below>(1),Boundary<float64,Above>(36)}).set_name("upper_position_limit");
ProtectionManager::_add_protection(lower_position_limit,Boundary<float64,Below>(-2),Boundary<float64,Above>(0)}).set_name("lower_position_limit");
ProtectionManager::_add_protection(upper_position_limit,Boundary<float64,Below>(1),Boundary<float64,Above>(36)}).set_name("upper_position_limit");
ProtectionManager::_add_protection(reference_pressure,Boundary<float32,Below>(0),Boundary<float32,Below>(0),Boundary<float32,Above>(10),Boundary<float32,Above>(10)}).set_name("reference_pressure");
ProtectionManager::_add_protection(actual_pressure,Boundary<float32,Below>(0),Boundary<float32,Below>(0),Boundary<float32,Above>(10),Boundary<float32,Above>(10)}).set_name("actual_pressure");
ProtectionManager::_add_protection(high_pressure,Boundary<float32,Below>(40),Boundary<float32,Below>(0),Boundary<float32,Above>(200),Boundary<float32,Above>(200)}).set_name("high_pressure");
ProtectionManager::_add_protection(position,Boundary<float64,Below>(0),Boundary<float64,Below>(0),Boundary<float64,Above>(40),Boundary<float64,Above>(50)}).set_name("position");
ProtectionManager::_add_protection(speed,Boundary<float64,Below>(0),Boundary<float64,Below>(0),Boundary<float64,Above>(8.33),Boundary<float64,Above>(13.88)}).set_name("speed");
ProtectionManager::_add_protection(acceleration,Boundary<float64,Below>(0),Boundary<float64,Below>(0),Boundary<float64,Above>(9.8),Boundary<float64,Above>(19.6)}).set_name("acceleration");
ProtectionManager::_add_protection(output_voltage,Boundary<uint16_t,Below>(192),Boundary<uint16_t,Below>(0),Boundary<uint16_t,Above>(252),Boundary<uint16_t,Above>(252)}).set_name("output_voltage");

}
};