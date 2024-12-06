
# 1. Leerse JSON_ADE/boards.json
# 2. Leerse archivo correspondiente a la placa
# 3. Genera el hpp

# Do this in another file
"""
class DataPackets {
   private:
    constexpr static size_t N_PACKETS{%N_PACKETS%};

   public:
    %PACKET_DEFINITION%

    static std::array<Packet *, N_PACKETS> packets;

    DataPackets(%CONSTRUCTOR_ARGS%) {
        %PACKET_INITIALIZATION%

        %PACKET_ARRAY%
    }
};
""".replace("%N_PACKETS%", "5")