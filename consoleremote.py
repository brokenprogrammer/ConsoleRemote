#!/usr/bin/python3

import socketserver
from server.serverhandler import ServerHandler
from util.commandparser import CommandParser


def doit():
    print("live")

if __name__ == '__main__':
    print("test")
    cmds = CommandParser()
    cmds.add_command("start show", doit)
    cmds.add_command("start show", doit)
    cmds.parse_command("start show")
    cmds.parse_command("start live")

    myServer = socketserver.TCPServer(("localhost", 9999), ServerHandler)
    myServer.serve_forever()
