#!/usr/bin/python3

import socketserver
from server.server import MyTCPHandler

if __name__ == '__main__':
    print("test")
    myServer = socketserver.TCPServer(("localhost", 9999), MyTCPHandler)
    myServer.serve_forever()
