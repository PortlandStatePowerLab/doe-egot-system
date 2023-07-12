import sys
import os
from http.server import BaseHTTPRequestHandler, HTTPServer
import ssl
from datetime import datetime

HOST_NAME = "0.0.0.0"
# PORT = 8090
ROOT = os.path.dirname(__file__)
LOG = ROOT

if len(sys.argv) > 1:
    # Access the first argument (sys.argv[1])
    PORT = int(sys.argv[1])
    print("The argument provided is:", PORT)
else:
    print("No command-line argument provided.")
def logPost(data):
    with open(LOG, 'a') as file:
        file.write(data)

class Handler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path != '/na':
            self.send_response(404)
            self.end_headers()
        else:
            self.send_response(201)
            self.end_headers()

            content_length = int(self.headers['Content-Length'])
            data = self.rfile.read(content_length).decode("utf-8")
            print(data)
            logPost(data)

if __name__ == "__main__":
    print(ROOT)
    print(f"DTMC started on https://{HOST_NAME}:{PORT}")

    LOG = ROOT + datetime.now().strftime('/log_%H_%M_%d_%m_%Y.log')
    print(f"message log found at {LOG}")

    server = HTTPServer((HOST_NAME, PORT), Handler)
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