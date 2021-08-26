import os
import sys
import random
import xml.etree.ElementTree as ET
from xml.dom import minidom
from time import sleep
import datetime
from http.server import BaseHTTPRequestHandler, HTTPServer, ThreadingHTTPServer
import ssl

dirname, filename = os.path.split(os.path.abspath(__file__))
host_name = 'localhost'  # DTM Rpi address
host_port = 4430
posts_received = 0
post_data = ''
host_port = 4430
host_name = 'localhost'  # DTM Rpi address
rel_path_raspi_workaround = '../build/bin'
key_path = rel_path_raspi_workaround + '/certs/private/server.key'
cert_path = rel_path_raspi_workaround + '/certs/server.crt'
LOG_FILE = 'Trustlog_testing1.xml'


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


def append_subtree(current, log_file):
	tree = ET.ElementTree(file=log_file)
	root = tree.getroot()
	root.append(current)
	tree.write(log_file, xml_declaration=True)
	print("subtree has been appended to log")


def append_xml_str(xml_str):
	'''tree = ET.parse('TrustLog_testing1.xml')  # create xml tree from file contents
    root = tree.getroot()  # ID root of tree (TrustLog)
    dtm_time = str(datetime.datetime.now())  # get current time
    print("xml_Str: ")
    print(xml_str)'''
	log_entry = ET.Element('dtm_log_entry')
	log_entry.set('logged', str(datetime.datetime.now()))
	xml_obj = ET.fromstring(xml_str)
	log_entry.append(xml_obj)
	pretty_xml = _pretty_print(log_entry)
	append_subtree(pretty_xml, LOG_FILE)


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
		append_subtree(pretty_error, LOG_FILE)
	else:
		err_type.text = 'UN-PARSABLE/NON-XML MSG RECEIVED'
		contents.text = posted_str
		ET.dump(error_note)
		pretty_error = _pretty_print(error_note)
		append_subtree(pretty_error, LOG_FILE)


def makeHtmlLine(str_in):
	"""add formatting for a "paragraph" in html to a string
    """
	str_in = '<p style="text-indent: 40px">' + str_in + '</p>'
	return str_in


def makeHtmlText(str_in):
	"""add formatting for an html textarea to a string
    """
	str_in = '<textarea rows="2" cols="100" style="border:double 2px blue;">' + str_in + '</textarea>'
	return str_in


class MyServer(BaseHTTPRequestHandler):
	"""server derived from python standard library BASEHTTPRequestHandler object, custom handlers
        for HEAD, GET, POST, and redirect interactions
    """

	def do_HEAD(self):
		"""HEAD method type, sends to client
        """
		print("do head")
		self.send_response(200)
		self.send_header('Content-type', 'text/html')
		self.end_headers()  # need to call end_headers() to actually send the headers
		print("head over")

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
		if posts_received == 0:  # if the DCM has not made contact via POST request
			print("NO POST REQUESTS")
			# the below is the html string which is the webpage visible in browser
			html = '''
                <html>
                <head>
                    <title>DTM Server (Stable Page)</title>
                </head>
                <body style="width:960px; margin: 20px auto;">
                    <h1 style="text-indent: 40px">Welcome to the DTM loopback http.server v2.0</h1>
                    <p style="text-indent: 40px">Running on your computer</p>
                    <p style="text-indent: 40px">Client has not made contact</p>
                    <hr><br><br>
                </body>
                </html>
            '''
			self.do_HEAD()
			self.wfile.write(html.encode("utf-8"))
			print("do_GET with no posts received is complete")

		if posts_received > 0:  # if the DCM has made contact via POST request
			print("POST REQUEST: UPDATE HTML PAGE")
			html = '''
                <html>
                <head>
                    <title>DTM Server Display </title>
                </head>
                <body style="width:960px; margin: 20px auto;">
                    <h1 style="text-indent: 40px">Welcome to the DTM loopback http.server v2.0</h1>
                    <p style="text-indent: 40px">Running on your computer</p>
                    <hr><br><br>
            '''
			end_html = '''</body>
                             </html>'''

			global post_data
			timestamp = '<b>Updated: ' + str(datetime.datetime.now()) + '</b>'  # html bold formatting for posting
			xmlTitle = '<i>Data parsed from the following (DCM generated) XML:</i>'  # html italicized formatting
			raw_xml = str(post_data)  # generate string from xml data sent from dcm client in last POST request
			connections = 'From DCM Update #: ' + str(
				posts_received) + ' since DTM Server epoch'  # update connection num
			# the below line just concantenates strings for the wfile.write()
			# function, the xml has to go in an html textarea, otherwise it won't be displayed
			html = html + makeHtmlLine(timestamp) + makeHtmlLine(xmlTitle) + makeHtmlText(raw_xml) + makeHtmlLine(
				connections) + end_html
			self.do_HEAD()  # call the HEAD method, which sends headers to the client
			self.wfile.write(html.encode(
				"utf-8"))  # write the formatted (to add temp data from dtm and dcm) html string (encoded) to client

		print("do_GET over")

	# write the formatted (to add temp data from dtm and dcm) html string (encoded) to client

	def do_POST(self):
		"""POST method type
            the http.client is running on a DCM on the network, that client
            submits requests with 'POST', which contain xml. Then
            rfile.read().decode()  decodes that msg
            and saves it to a global string var
        """
		global posts_received  # global keyword needed to modify the var, there were errors declaring as
		# class data members
		global post_data
		posts_received += 1  # iterate count of POST requests received
		content_length = int(self.headers['Content-Length'])
		post_data = self.rfile.read(content_length).decode("utf-8")  # Get the data
		print(" POST REQUEST RECEIVED. raw:")
		print(post_data)
		print(posts_received)

		post_validity = cta_msg_valid(post_data)  # validate POST contents

		if post_validity == 'valid':  # verify completeness of incoming xml
			print("Message is complete")
			append_xml_str(post_data)  # append the message to the log
		elif post_validity != 'not xml':  # only if post is xml, but contains wrong data
			print("ERROR, this XML message is not valid")
			append_error_log(post_data, msg_is_xml=True)
		print("do_POST complete")


"""
this is main, just run the server
"""
if __name__ == '__main__':

	http_server = ThreadingHTTPServer((host_name, host_port), MyServer)
	http_server.socket = ssl.wrap_socket(http_server.socket, keyfile=key_path, certfile=cert_path, server_side=True)

	print("Server Starts - %s:%s" % (host_name, host_port))

	try:
		http_server.serve_forever()
	except KeyboardInterrupt:
		http_server.server_close()
