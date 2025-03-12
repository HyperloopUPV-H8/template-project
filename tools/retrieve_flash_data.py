import subprocess
import argparse
from datetime import datetime
import os
def main():
    parser = argparse.ArgumentParser(description="Retrieve the binary metadata from flash given an address")
    parser.add_argument(
        "--address",             # Argument name
        type=str,                  # Argument type (string)
        default="0x080DFD00",   # Default value if no argument is provided
        help="The memory address to retrieve from, if unsure leave empty"  # Help text
    )
    args = parser.parse_args()
    try:
        result = subprocess.run(["STM32_Programmer_CLI", "-c", "port=swd", "mode=ur", "Freq=4000", "-u", args.address, "0xFF", "dump.bin"])
        if result.returncode != 0:
            #if we tried to read and it failed, remove the 
            # existing file to avoid confussion
            os.remove("dump.bin")
            raise Exception()
    except Exception:
        print("Error when running STM32_Programmer_CLI, make sure the board is powered and the cable connected,\nalso make sure STLINK is not in use by the debugger or STM32CubeProgrammer")
        exit(-1)

    binary_raw = None

    with open("dump.bin","r") as binary:
        binary_raw = binary.read()

    #DEFINITIONS FOR LOCATIONS
    checksum_length = 16
    iso_time_offset = checksum_length
    iso_time_length = 15
    padding_length = 1
    stlib_commit_offset = iso_time_offset + iso_time_length + padding_length
    stlib_commit_length = 8

    adj_commit_offset = stlib_commit_offset + stlib_commit_length
    adj_commit_length = 8

    board_commit_offset = adj_commit_offset + adj_commit_length
    board_commit_legnth = 8 

    custom_variables_offset = board_commit_offset + board_commit_legnth

    def __validate_retrieved_binary():
        for i in range(0,checksum_length):
            if binary_raw[i] != '*':
                raise Exception("Retrieved binary did not pass checksum test\n Maybe the metadata is not at that address? ADDRESS: {}".format(args.address))
        return True
    if __validate_retrieved_binary() == True:
        print("Found binary metadata!")

    iso_time = binary_raw[iso_time_offset:iso_time_offset + iso_time_length]
    stlib_commit = binary_raw[stlib_commit_offset:stlib_commit_offset + stlib_commit_length]
    adj_commit = binary_raw[adj_commit_offset:adj_commit_offset + adj_commit_length]
    board_commit = binary_raw[board_commit_offset:board_commit_offset + board_commit_legnth]


    dt = datetime.strptime(iso_time, "%Y%m%dT%H%M%S")
    # Format to a readable format (e.g., "March 2, 2025, 1:12:41 PM")
    readable_time = dt.strftime("%d %B %Y, %H:%M:%S")  # 24-hour format (%H)


    print("Code was compiled at: {}".format(readable_time))
    print("STLIB commit {}".format(stlib_commit))
    print("ADJ commit {}".format(adj_commit))
    print("Board commit {}".format(board_commit))


    for i in range(custom_variables_offset, 255):
        if binary_raw[i].isdigit() == True and binary_raw[i+1].isdigit() == False:
            print(binary_raw[i],end="\n")
        else:
            print(binary_raw[i],end="")
if __name__ == "__main__":
    main()