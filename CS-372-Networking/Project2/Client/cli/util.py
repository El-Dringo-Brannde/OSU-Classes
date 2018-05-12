import sys


class util:
    connecting_port, file_opt, recv_port, host, name = None, None, None, None, None

    def __init__(self):
        self.cli_check()

    def cli_check(self):
        self.check_cli_length()
        self.get_host()
        self.check_connecting_port_num()
        self.check_file_option()
        self.file_or_directory_name()
        self.check_recv_port_num()

    def check_cli_length(self):
        if len(sys.argv) <= 4:
            raise Exception(
                'Please use in format of: python index.py {connecting_port} {option} {filename} {receiving_port}')

    def check_connecting_port_num(self):
        if int(sys.argv[2]) > 65535 or int(sys.argv[2]) < 1024:
            raise Exception('You tried to use a bad port number, you fail.')
        else:
            self.connecting_port = sys.argv[2]

    def check_file_option(self):
        if sys.argv[3] != '-l' and sys.argv[3] != '-g':
            raise Exception('Illegal file option, try again')
        else:
            self.file_opt = sys.argv[3]

    def check_recv_port_num(self):
        if len(sys.argv) == 5:
            if int(sys.argv[4]) > 65535 or int(sys.argv[4]) < 1024 or int(sys.argv[2]) == int(sys.argv[4]):
                raise Exception('Stop trying to do funky stuff in the CLI')
            else:
                self.recv_port = sys.argv[4]
        elif len(sys.argv) == 6:
            if int(sys.argv[5]) > 65535 or int(sys.argv[5]) < 1024 or int(sys.argv[2]) == int(sys.argv[5]):
                raise Exception('Stop trying to do funky stuff in the CLI')
            else:
                self.recv_port = sys.argv[5]

    def get_host(self):
        self.host = sys.argv[1]

    def file_or_directory_name(self):
        self.name = sys.argv[4]
