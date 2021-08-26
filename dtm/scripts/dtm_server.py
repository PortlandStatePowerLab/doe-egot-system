import os
import sys
import configparser
from pathlib import Path
import xml.etree.ElementTree as ET
from xml.dom import minidom
from time import sleep
import datetime
from http.server import BaseHTTPRequestHandler, HTTPServer
import ssl

dirname, filename = os.path.split(os.path.abspath(__file__))
posts_received = 0
post_data = ''
log_file = ''

def seedLog(path):
    # create the file structure
    root = minidom.Document()
    xml = root.createElement('TrustLog')
    root.appendChild(xml)
    xml_str = root.toprettyxml(indent ="\t") 
    
    # create a new XML file with the results
    time_stamp = datetime.datetime.now().strftime("%Y_%m_%d-%H_%M_%S")
    log_file = path + "/" + time_stamp + ".xml"
    with open(log_file, "w+") as f:
        f.write(xml_str)

def cta_msg_valid(xml_string):
    valid_parties = ("DCM", "DTM", "GSP", "DER")
    print("checking CTA validity")

    try:
        root = ET.fromstring(xml_string)
    except ET.ParseError:
        print("This message cannot be parsed into XML")
        append_error_log(xml_string, msg_is_xml=False)
        return 'not xml'

    if root.findtext('from') not in valid_parties:  # check contents of from tag
        return 'from field error'
    if root.findtext('to') not in valid_parties:
        return 'to field error'
    elif root.find('content') is None:
        return 'lacks content tag'
    elif root.find('DCM_timestamp') is None:
        return 'lacks timestamp tag'
    return 'valid'


def _pretty_print(current, parent=None, index=-1, depth=0):  # ngl I found this on stackoverflow, thanks @Tatarize
    for i, node in enumerate(current):
        _pretty_print(node, current, i, depth + 1)
    if parent is not None:
        if index == 0:
            parent.text = '\n' + ('\t' * depth)
        else:
            parent[index - 1].tail = '\n' + ('\t' * depth)
        if index == len(parent) - 1:
            current.tail = '\n' + ('\t' * (depth - 1))
    return current


def append_subtree(current):
    tree = ET.parse(log_file)
    root = tree.getroot()
    root.append(current)
    with open (log_file, "wb") as f :
        tree.write(f)

def append_xml_str(xml_str):
    '''tree = ET.parse('TrustLog_testing1.xml')  # create xml tree from file contents
    root = tree.getroot()  # ID root of tree (TrustLog)
    dtm_time = str(datetime.datetime.now())  # get current time
    print("xml_Str: ")
    print(xml_str)'''
    log_entry = ET.Element('dtm_log_entry')
    log_entry.set('logged', str(datetime.datetime.now()))
    #xml_obj = ET.fromstring(xml_str)
    log_entry.set('message', xml_str)
    pretty_xml = _pretty_print(log_entry)
    append_subtree(pretty_xml)


def append_error_log(posted_str, msg_is_xml=True):
    error_note = ET.Element('dtm_log_ERROR')
    error_note.set('logged', str(datetime.datetime.now()))
    err_type = ET.SubElement(error_note, 'error_type')
    contents = ET.SubElement(error_note, 'invalid_msg_contents')

    if msg_is_xml:
        err_type.text = 'INCOMPLETE/INCORRECT XML MSG RECEIVED'
        xml_obj = ET.fromstring(posted_str)
        contents.append(xml_obj)  # put the error tree under contents
        pretty_error = _pretty_print(error_note)
        append_subtree(pretty_error, log_file)
    else:
        err_type.text = 'UN-PARSABLE/NON-XML MSG RECEIVED'
        contents.text = posted_str
        ET.dump(error_note)
        pretty_error = _pretty_print(error_note)
        append_subtree(pretty_error, log_file)

class MyServer(BaseHTTPRequestHandler):
    """server derived from python standard library BASEHTTPRequestHandler object, custom handlers
        for HEAD, GET, POST, and redirect interactions
    """

    def do_HEAD(self):
        """HEAD method type, sends to client
        """
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()  # need to call end_headers() to actually send the headers

    def _redirect(self, path):
        """redirect method type
        """
        self.send_response(303)
        self.send_header('Content-type', 'text/html')
        self.send_header('Location', path)
        self.end_headers()

    def do_GET(self):
        """GET method type, updates the "served" html page that you can access from a browser
            on a local network with [ip address 00.00.00.00 blah]:[port num, 4 digits, matching encoded]
            copy pasted to url in browser
        """
        print("do_GET called")
        self.do_HEAD()  # call the HEAD method, which sends headers to the client

    def do_POST(self):
        """POST method type
            the http.client is running on a DCM on the network, that client
            submits requests with 'POST', which contain xml
            rfile.read().decode() then decodes that msg
            and saves it to a global string var
        """
        global posts_received  # global keyword needed to modify the var, there were errors declaring as
        # class data members
        global post_data
        posts_received += 1  # iterate count of POST requests received
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode("utf-8")  # Get the data
        #self.do_HEAD()

        #append_xml_str(post_data)

"""
this is main, just run the server
"""
if __name__ == '__main__':
    run_path = Path(sys.argv[0])
    bin_path = str(run_path.parent.absolute())
    config_path = bin_path + '/../../config.ini'    
    log_path = bin_path + '/../../logs'    
    seedLog(log_path)
    
    config = configparser.ConfigParser()
    config.read(config_path)
    
    port = config.getint('DTM','port')
    host = 'localhost'
    cert = bin_path + config.get('DTM', 'cert')
    key = bin_path + config.get('DTM', 'key')

    http_server = HTTPServer((host, port), MyServer)
    http_server.socket = ssl.wrap_socket(http_server.socket, keyfile=key, certfile=cert, server_side=True)
    
    print("DISTRIBUTED TRUST MANAGMENT")
    print(">>>\t%s:%s" % (host, port))

    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()