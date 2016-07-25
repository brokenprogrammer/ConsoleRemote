#!/usr/bin/python3

import socketserver
from server.serverhandler import ServerHandler
from server.actions import *

if __name__ == '__main__':
    myServer = socketserver.TCPServer(("localhost", 9999), ServerHandler)
    myServer.serve_forever()
