#!/usr/bin/python3

import socketserver
import logging
from server.serverhandler import ServerHandler
from server.actions import *
# from util.medialib import MediaLib
from util.commandparser import CommandParser

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    logger = logging.getLogger(__name__)

    # mlib = MediaLib()
    cmds = CommandParser(logger)

    cmds.add_command("start movie", start_movie)
    # cmds.add_command("start show", doit)
    cmds.parse_command("start movie")
    # cmds.parse_command("start live")
    myList = cmds.get_commands()
    print(myList)

    myServer = socketserver.TCPServer(("localhost", 9999), ServerHandler)
    myServer.serve_forever()
