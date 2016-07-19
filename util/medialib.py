#!/usr/bin/python3

import os


class MediaLib():
    """
    The MediaLib class for our server.

    It stores all the library paths and lets us build media paths to wanted
    media like videos.
    """
    libs = []
    logger = None

    def __init__(self, logger=None):
        self.logger = logger

    def add_lib_path(self, path):
        self.libs.append(path)

    def get_lib_paths(self):
        return self.libs

    def get_lib_content(self, lib):
        contentList = os.listdir(self.libs[lib])
        return contentList

    def select_lib_content(self, path, content):
        print()
