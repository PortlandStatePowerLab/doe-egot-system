#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

# We need to know how many DERs are going to be configured 
# before we can start generating them
def ValidateArgs(argv):
    if (len(sys.argv) < 2):
        print('please input number of DER to configure.')
        print('\tExample: python3 config_generator.py 10')
        sys.exit()

def LoadTopology():
    tree = ET.parse("grid_topology.xml")
    return tree.getroot()

def PrintTopology():
    root = LoadTopology()
    for group in root.findall('group'):
        print('group :', group.get('name'))
        bus_list = group.findall('bus')
        print('\tbus :',bus_list[1].text)

def main (argv):
    ValidateArgs(argv)
    PrintTopology()

if __name__ == "__main__":
    main(sys.argv)