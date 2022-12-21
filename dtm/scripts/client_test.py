import http.client
import urllib.request
import urllib.parse
import os
import sys
import random
import xml.etree.ElementTree as ET
from time import sleep
import datetime

host_name = '192.168.0.178'  # loopback DTM server address
host_port = 8889
host_address = '192.168.0.178:8889'

def makeCTACommandMsg(type):
    msg = ET.Element('message')  # creating an xml element structure
    frm_tag = ET.SubElement(msg, 'from')  # subelement
    frm_tag.text = 'DCM'
    to_tag = ET.SubElement(msg, 'to')  # subelement
    to_tag.text = 'DER'
    content_tag = ET.SubElement(msg, 'content')  # subelement
    cmd_tag = ET.SubElement(content_tag, 'command')  # subelement
    type_tag = ET.SubElement(cmd_tag, 'type')
    type_tag.text = str(type)
    start_tag = ET.SubElement(cmd_tag, 'start')
    start_tag.text = 'This afternoon'
    duration_tag = ET.SubElement(cmd_tag, 'duration')
    duration_tag.text = 'like half an hour?'
    expect_resp = ET.SubElement(cmd_tag, 'expect_response')
    expect_resp.text = 'vibes'
    logged = ET.SubElement(msg, 'DCM_timestamp')
    ct = datetime.datetime.now()
    logged.text = str(ct)
    print(ET.tostring(msg))
    return ET.tostring(msg)

def isMsgComplete(xml_string):
    tag1 = 'loopback_random_data'
    tag2 = 'timestamp'
    return ( tag1 in xml_string and tag2 in xml_string)

def isBitMsgComplete(xml_bitstring):
    xml_string = xml_bitstring.decode('ascii')
    tag1 = 'loopback_random_data'
    tag2 = 'timestamp'
    return ( tag1 in xml_string and tag2 in xml_string)

def getTemp():
    """get temp from operating system with an os.popen call
    """
    traw = os.popen("/opt/vc/bin/vcgencmd measure_temp").read()
    traw = traw.replace('temp=', '')
    traw = traw.replace('\n', '')
    traw = traw[:-2]
    temp = str(traw)
    return temp

def randomStr():
    return str(round(random.uniform(0.01, 10.00), 2))

def make_old_temp_msg():
    ct = datetime.datetime.now()
    tStamp = str(ct)
    data = ET.Element('TrustLog') #creating an xml element structure
    el1 = ET.SubElement(data, 'DCMContact') #subelement
    el1.set('timestamp', tStamp) # timestamp is an attribute, attrib
    el1.set('loopback_random_data', randomStr()) #temp is an attribute
    el1.text = 'CONNECTION SUCCESSFUL' #just kinda filler

    obj_xml = ET.tostring(data) #converts xml object into a string
    print(obj_xml.decode('ascii'))
    print(isMsgComplete(obj_xml.decode('ascii')))
    print(isBitMsgComplete(obj_xml))
    return obj_xml

headers = {"Content-type": "text/xml", "Accept": "text/plain"} #headers for the request

while True:

    print("Attempting POST's")
    print(" Enter sc to send complete message, si to send incomplete, f to send fake (non xml), ^ C to quit")

    try:
        choice = str(input())
        if choice == 'sc':
            sendDTM = http.client.HTTPConnection(host_name, host_port)
            sendDTM.request('POST', host_address, makeCTACommandMsg("TEST"), headers)
            sleep(1)
        elif choice == 'si':
            sendDTM = http.client.HTTPConnection(host_name, host_port)
            sendDTM.request('POST', host_address, make_old_temp_msg(), headers)
            sleep(1)
        elif choice == 'f':
            sendDTM = http.client.HTTPConnection(host_name, host_port)
            sendDTM.request('POST', host_address, 'this is a fake non-xml message', headers)

        else:
            print("incorrect choice")

    except KeyboardInterrupt:
        quit()


