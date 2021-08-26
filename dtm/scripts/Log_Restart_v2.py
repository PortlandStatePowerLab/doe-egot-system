
import os
import sys
import xml.etree.ElementTree as ET
from time import sleep
import datetime

temp = str(00.0)

print("CREATING TrustLogv2test XML FILE")
ct = datetime.datetime.now()
tStamp = str(ct)

data = ET.Element('TrustLog')
el1 = ET.SubElement(data, 'DCMContact')
el1.set('timestamp', tStamp)
el1.set('temp', temp)
el1.text = 'CONNECTION SUCCESSFUL'

obj_xml = ET.tostring(data)
with open("TrustLogv2test.xml", "wb") as f:
    f.write(obj_xml)