#!/usr/bin/python3

import socketserver
import logging
from server.serverhandler import ServerHandler
from server.actions import *
from util.processhandler import ProcessHandler
from util.commandparser import CommandParser

if __name__ == '__main__':
    # logging.basicConfig(level=logging.INFO)
    # logger = logging.getLogger(__name__)

    # plib = ProcessHandler()
    # cmds = CommandParser(logger)

    # plib.register_process("VLC", "/Applications/VLC.app/Contents/MacOS/VLC")

    # cmds.add_command("start movie", start_movie)
    # cmds.parse_command("start movie", plib)

    myServer = socketserver.TCPServer(("localhost", 9999), ServerHandler)
    myServer.serve_forever()
