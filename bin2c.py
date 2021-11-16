import sys
from pathlib import Path

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <input file> <output file>")
        exit(1)
    
    with open(sys.argv[1], "rb") as file_in:
        with open(sys.argv[2], "w") as file_out:
            file_out.write(f"static const uint8_t {Path(sys.argv[2]).stem}[]")
            file_out.write(" = {\n")

            b = file_in.read(1)
            col = 0
            while(len(b) > 0):
                if col == 0:
                    file_out.write("    ")
                    col = 4
                col += file_out.write(f"0x{b.hex()},")
                if col >= 75:
                    file_out.write('\n')
                    col = 0
                
                b = file_in.read(1)
            
            file_out.write("\n};")