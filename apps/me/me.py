#!/usr/bin/python3
# https://flaviocopes.com/python-http-server/
# https://pythonsansar.com/creating-simple-http-server-python/
import os
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer
import ssl
from urllib.parse import urlparse
from urllib.parse import parse_qs

HOST_NAME = "localhost"
PORT = 8000
ROOT = os.path.dirname(__file__)
LOG = ROOT


def read_services():
    try:
        with open('./Outputs To DERMS/OutputtoGSP.xml') as f:
            file = f.read()
    except Exception as e:
        file = e
    return file


class handler(BaseHTTPRequestHandler):
    def do_GET(self):
        if (self.path == '/services'):
            self.send_response(200)
            self.send_header('Content-type', 'application/xml')
            self.end_headers()
            with open('./Outputs To DERMS/OutputtoGSP.xml', 'r') as file:
                self.wfile.write(bytes(file.read(), "utf-8"))
        else:
            self.send_response(404)
            self.end_headers()

    def do_POST(self):
        parsed_url = urlparse(self.path)
        parsed_qs = parse_qs(parsed_url.query)
        lfdi = parsed_qs['lfdi'][0]
        print(self.path, lfdi)
        if (not lfdi or parsed_url.path != '/der'):
            self.send_response(404)
            self.end_headers()
        else:
            self.send_response(201)
            self.end_headers()

            with open(f'{ROOT}/data/{lfdi}.csv', 'w') as file:
                content_length = int(self.headers['Content-Length'])
                file.write(self.rfile.read(content_length).decode("utf-8"))


if __name__ == "__main__":
    print(ROOT)
    print(f"DTMC started on https://{HOST_NAME}:{PORT}")

    server = HTTPServer((HOST_NAME, PORT), handler)
    server.socket = ssl.wrap_socket(
        server.socket,
        server_side=True,
        certfile=ROOT + '/root-ca/server.crt',
        keyfile=ROOT + '/root-ca/private/server.key',
        ca_certs=ROOT + '/root-ca/cert_chain.crt')

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.server_close()
        print("Server stopped successfully")
        sys.exit(0)
