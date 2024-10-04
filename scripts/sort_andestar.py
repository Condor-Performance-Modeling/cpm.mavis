import pandas as pd

# Given hex values
hex_values = [
    "0x813fab2b", "0x817fa72b", "0x8305128b", "0x8417948b", "0x849f938b", 
    "0x849f970b", "0x851f950b", "0x8645128b", "0x983fa0ab", "0x987fa7ab", 
    "0x98bfa6ab", "0x991f9f8b", "0x9997938b", "0x999f9a0b", "0x9d1f958b", 
    "0xd9c8ffff", "0xdf30ffff", "0xdf4cffff", "0xdf9cffff", "0xe0f4ffff", 
    "0xe324ffff", "0xe334ffff", "0xe354ffff", "0xe378ffff", "0xe3acffff", 
    "0xe3b8ffff", "0xe828ffff", "0xe840ffff", "0xe850ffff", "0xe880ffff", 
    "0xe884ffff", "0xeb80ffff", "0xeb84ffff", "0xeb9cffff", "0xebc0ffff", 
    "0xed18ffff", "0xee87930b", "0xef18ffff", "0xef40ffff", "0xef6cffff", 
    "0xef7cffff", "0xef88ffff", "0xf03cffff", "0xf158ffff", "0xf164ffff", 
    "0xf1f8ffff", "0xf4557bab", "0xf4757bab", "0xf4857bab", "0xf4a549ab", 
    "0xf4f57bab", "0xf515138b", "0xf515180b", "0xf515198b", "0xf5151a0b", 
    "0xf5151a8b", "0xf5151c8b", "0xf5157bab", "0xf524ffff", "0xf52cffff", 
    "0xf5457bab", "0xf5557bab", "0xf8057bab", "0xf915130b", "0xf915170b", 
    "0xf915180b", "0xf915188b", "0xf915198b", "0xf9151b0b", "0xf9151e0b", 
    "0xf9151e8b", "0xf9151f8b"
]

# Functions to check conditions
def check_condition_1(value):
    # Check if lowest 6 bits are 0x0B
    return value & 0x3F == 0x0B

def check_condition_2(value):
    # Check if lowest 6 bits are 0x2B and field 14:12 is 0b100
    lowest_6_bits = value & 0x3F
    field_14_12 = (value >> 12) & 0b111
    return lowest_6_bits == 0x2B and field_14_12 == 0b100

def check_condition_3(value):
    # Check if lowest 6 bits are 0x2B and field 14:12 is 0b010
    lowest_6_bits = value & 0x3F
    field_14_12 = (value >> 12) & 0b111
    return lowest_6_bits == 0x2B and field_14_12 == 0b010

def check_condition_4(value):
    # Check if lowest 6 bits are 0x2B and field 14:12 is 0b111
    lowest_6_bits = value & 0x3F
    field_14_12 = (value >> 12) & 0b111
    return lowest_6_bits == 0x2B and field_14_12 == 0b111

# Convert hex values to integers
hex_int_values = [int(h, 16) for h in hex_values]

# Sort values into lists
list_1 = [hex(v) for v in hex_int_values if check_condition_1(v)]  # Lowest 6 bits = 0x0B
list_2 = [hex(v) for v in hex_int_values if check_condition_2(v)]  # Lowest 6 bits = 0x2B and field 14:12 = 0b100
list_3 = [hex(v) for v in hex_int_values if check_condition_3(v)]  # Lowest 6 bits = 0x2B and field 14:12 = 0b010
list_4 = [hex(v) for v in hex_int_values if check_condition_4(v)]  # Lowest 6 bits = 0x2B and field 14:12 = 0b111
list_5 = [hex(v) for v in hex_int_values if v not in [int(x, 16) for x in list_1 + list_2 + list_3 + list_4]]

# Creating a dataframe for display
sorted_hex_df_final = pd.DataFrame({
    "List 1": pd.Series(list_1),
    "List 2": pd.Series(list_2),
    "List 3": pd.Series(list_3),
    "List 4": pd.Series(list_4),
    "List 5": pd.Series(list_5)
})

# Displaying the dataframe
import ace_tools as tools; tools.display_dataframe_to_user(name="Sorted Hex Values (5 Lists)", dataframe=sorted_hex_df_final)

