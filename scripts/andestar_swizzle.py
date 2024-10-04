def sign_extend(value, bits):
    """Sign extend a value to the specified number of bits."""
    sign_bit = 1 << (bits - 1)
    return (value & (sign_bit - 1)) - (value & sign_bit)

def extract_immediate(hex_str):
    # Convert the hex string to a 32-bit integer (little-endian)
    encoding = int(hex_str, 16)

    # Extract the relevant bit fields from the encoding
    imm17    = (encoding >> 31) & 0x1     # 31    -> 17
    imm10_1  = (encoding >> 21) & 0x3FF   # 30:21 -> 10:1
    imm11    = (encoding >> 20) & 0x1     # 20    -> 11
    imm14_12 = (encoding >> 17) & 0x7     # 19:17 -> 14:12
    imm16_15 = (encoding >> 15) & 0x3     # 16:15 -> 16:15
    imm0     = (encoding >> 14) & 0x1     # 14    -> 0

    # Reconstruct the 18-bit immediate value
    immediate = (imm17 << 17) | (imm16_15 << 15) | (imm14_12 << 12) | (imm11 << 11) | (imm10_1 << 1) | imm0

    # 18 is the number of bits, not the bit position
    sign_extended_imm_32b = sign_extend(immediate, 18) & 0xFFFFFFFF
    sign_extended_imm_64b = sign_extend(immediate, 18)  # 64-bit sign-extended

    return immediate, sign_extended_imm_32b, sign_extended_imm_64b

# Test input
input_ = [
  "0xee87930b",
  "0x849f970b",
  "0xf915180b",
  "0xf5151c8b"
]

for hex_str in input_:
    imm_value, sign_extended_imm_32b, sign_extended_imm_64b = extract_immediate(hex_str)

    binary_imm = f"{imm_value:018b}"  # 18-bit immediate in binary form (without sign extension)
    hex_imm = hex(imm_value)          # Hex value of the 18-bit unsigned immediate

    # Print the results
    print(f"input: {hex_str}")
    print(f"18-bit immediate (binary, without sign extension): {binary_imm}")
    print(f"18-bit unsigned immediate (hex): {hex_imm}")
    print(f"32-bit sign-extended immediate (hex): {hex(sign_extended_imm_32b)}")
    
    # Print 64-bit sign-extended immediate in two's complement form
    print(f"64-bit sign-extended immediate (hex): {format(sign_extended_imm_64b & 0xFFFFFFFFFFFFFFFF, '016x')}")
    print("")


#def sign_extend(value, bits):
#    """Sign extend a value to the specified number of bits."""
#    sign_bit = 1 << (bits - 1)
#    return (value & (sign_bit - 1)) - (value & sign_bit)
#
#def extract_immediate(hex_str):
#    # Convert the hex string to a 32-bit integer (little-endian)
#    encoding = int(hex_str, 16)
##   3322222222221111111111----------
##   10987654321098765432109876543210
##
##    print(f"string:   {str(hex_str)}")
##    print(f"encoding: {hex(encoding)}")
#
#    # Extract the relevant bit fields from the encoding
#    imm17    = (encoding >> 31) & 0x1     # 31    -> 17
#    imm10_1  = (encoding >> 21) & 0x3FF   # 30:21 -> 10:1
#    imm11    = (encoding >> 20) & 0x1     # 20    -> 11
#    imm14_12 = (encoding >> 17) & 0x7     # 19:17 -> 14:12
#    imm16_15 = (encoding >> 15) & 0x3     # 16:15 -> 16:15
#    imm0     = (encoding >> 14) & 0x1     # 14    -> 0
#
#
#    immediate = (imm17 << 17) | (imm16_15 << 15) | (imm14_12 << 12) | (imm11 << 11) | (imm10_1 << 1) | imm0;
#
#    #18 is number of bits, not bit position
#    sign_extended_imm_32b = sign_extend(immediate, 18) & 0xFFFFFFFF
#    sign_extended_imm_64b = sign_extend(immediate, 18)  # 64-bit sign-extended
#
#    return immediate, sign_extended_imm_32b, sign_extended_imm_64b
#
## Test input
#input_ = [
#  "0xee87930b",
#  "0x849f970b",
#  "0xf915180b",
#  "0xf5151c8b"
#]
#
#for hex_str in input_:
#  imm_value, sign_extended_imm_32b, sign_extended_imm_64b = extract_immediate(hex_str)
#
#  binary_imm = f"{imm_value:018b}"  # 18-bit immediate in binary form (without sign extension)
#  hex_imm = hex(imm_value)          # Hex value of the 18-bit unsigned immediate
#
#  # Print the results
#  print(f"input: {hex_str}")
#  print(f"18-bit immediate (binary, without sign extension): {binary_imm}")
#  print(f"18-bit unsigned immediate (hex): {hex_imm}")
#  print(f"32-bit sign-extended immediate (hex): {hex(sign_extended_imm_32b)}")
#  print(f"64-bit sign-extended immediate (hex): {hex(sign_extended_imm_64b)}")
#  print("")
