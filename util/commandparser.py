#!/usr/bin/python3

import logging


class CommandParseError(Exception):

    def __init__(self, msg):
        self.msg = msg

    def __str__(self):
        return self.msg


class CommandValueError(CommandParseError):
    """
    Raised if an invalid option value is encountered or an command
    already exists.
    """


class CommandParser():
    """
    The CommandParser class for our server.

    It stores all the commands and parses messages comparing commands
    and then execute functions depending on what command was parsed.
    """
    cmds = {}
    helpCmd = ''
    logger = None

    def __init__(self, logger):
        self.logger = logger

    def add_command(self, command, function):
        if command not in self.cmds:
            # Add command to the command dict.
            self.logger.info("Stored new command: %s", command)
            self.cmds[command] = function
        else:
            # Raise error
            # raise CommandValueError(("Error adding command: %s") % (command))
            self.logger.info(
                "Can't add command, it already exists: %s", command)

    def get_commands(self):
        commandList = []
        for key in self.cmds:
            commandList.append(key)
        return commandList

    def parse_command(self, command, processHandler):
        if command in self.cmds:
            self.logger.info("Parsed command: %s", command)
            # Call the function for the specified command.
            self.cmds[command](processHandler)
        else:
            # Raise error
            raise CommandParseError(("Error parsing command: %s") % (command))

    def set_help_command(self, command):
        if type(command) is str:
            self.logger.info("Set new command as the help command: %s",
                             command)
            self.helpCmd = command
        else:
            raise TypeError("Setting help command only accepts strings.")

    def get_help_command(self, command):
        return self.helpCmd
