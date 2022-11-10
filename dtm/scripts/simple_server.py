#!/usr/bin/python3
# https://flaviocopes.com/python-http-server/
# https://pythonsansar.com/creating-simple-http-server-python/
from pathlib import Path
import sys, os
from http.server import BaseHTTPRequestHandler, HTTPServer
import ssl
from datetime import datetime

HOST_NAME = "0.0.0.0"
PORT = 8090
ROOT = sys.argv[0]
LOG = ROOT

def logPost (data):
    with open(LOG,'a') as file:
        file.write(data)

class handler(BaseHTTPRequestHandler):
    def do_POST(self):
        if (self.path != '/na'):
            self.send_response(404)
            self.end_headers()
        else:
            self.send_response(201)
            self.end_headers()

            content_length = int(self.headers['Content-Length'])
            data = self.rfile.read(content_length).decode("utf-8")
            logPost(data)

#class a():
  #message_content = BeautifulSoup((message_content, 'r'), "html.parser")
  #import classifier

if __name__ == "__main__":
    LOG = ROOT + datetime.now().strftime('/log_%H_%M_%d_%m_%Y.log')

    server = HTTPServer((HOST_NAME, PORT), handler)
    server.socket = ssl.wrap_socket(
        server.socket,
        server_side=True,
        certfile=ROOT + '/root-ca/server.crt', 
        keyfile=ROOT + '/root-ca/private/server.key',
        ca_certs=ROOT + '/root-ca/cert_chain.crt')

    print(f"DTMC started on https://{HOST_NAME}:{PORT}")
    print(f"message log found at {LOG}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.server_close()
        print("Server stopped successfully")
        sys.exit(0)