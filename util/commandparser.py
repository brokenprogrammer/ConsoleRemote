#!/usr/bin/python3

import logging


class CommandParseError(Exception):
    """
    Raised if an invalid option value is encountered or an command
    already exists
    """

    def __init__(self, msg):
        self.msg = msg

    def __str__(self):
        return self.msg


class CommandParser():
    """
    The CommandParser class for our server.

    It stores all the commands and parses messages comparing commands
    and then execute functions depending on what command was parsed.
    """
    cmds = {}
    helpCmd = ""
    logger = None

    def __init__(self, logger):
        self.logger = logger

    def add_command(self, command, function):
        """
        Add a command for the command parser to recognise.

        Args:
            command: The string to be used as the command.
            function: The function to be attatched with the command.
        """
        if command not in self.cmds:
            # Add command to the command dict.
            self.logger.info("Stored new command: %s", command)
            self.cmds[command] = function
        else:
            # Command already exists so it wont be added.
            self.logger.info(
                "Can't add command, it already exists: %s", command)

    def get_commands(self):
        commandList = []
        for key in self.cmds:
            commandList.append(key)
        return commandList

    def parse_command(self, command, option, processHandler):
        """
        Parse target command and run function attatched to
        command.

        Args:
            command: The command to be parsed and checked.
            processHandler: Sending the processHandler to the function
                incase it needs to start a new process or kill a process.
        """
        print("Its an option:  " + option)
        if command in self.cmds:
            self.logger.info("Parsed command: %s", command)
            # Call the function for the specified command.
            self.cmds[command](processHandler, option)
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
