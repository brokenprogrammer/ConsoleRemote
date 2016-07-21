#!/usr/bin/python3

import os


class ProcessHandler():
    """
    The ProcessHandler class for our server.

    It stores all the processes in a dictionary and limits it to one
    process per application.
    """
    processes = {}
    processPaths = {}
    logger = None

    def __init__(self, logger=None):
        self.logger = logger

    def register_process(self, pname, path):
        self.processPaths[pname] = path
