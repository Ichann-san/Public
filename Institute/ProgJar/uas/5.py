import xmlrpc
import xmlrpc.client
import unittest
import sys
from base64 import b64decode
from xmlrpc.server import SimpleXMLRPCServer, SimpleXMLRPCRequestHandler
from unittest.mock import patch, MagicMock
from io import StringIO


class SecureXMLRPCServer(SimpleXMLRPCServer):

    def __init__(self, host, port, username, password, *args, **kargs):
        # store credentials
        self.username = username
        self.password = password

        class VerifyingRequestHandler(SimpleXMLRPCRequestHandler):
            def parse_request(request):
                if SimpleXMLRPCRequestHandler.parse_request(request):
                    # authenticate the incoming request
                    if self.authenticate(request.headers):
                        return True
                    else:
                        # return HTTP 401 on failure
                        request.send_error(401, 'Authentication failed')
                return False

        # initialize the parent SimpleXMLRPCServer with the custom handler
        SimpleXMLRPCServer.__init__(self, (host, port), VerifyingRequestHandler, *args, **kargs)

    def authenticate(self, headers):
        # split the Authorization header into scheme and encoded credentials
        headers = headers.get('Authorization').split()
        basic, encoded = headers[0], headers[1]
        if basic != 'Basic':
            print('Only basic authentication supported')
            return False
        # decode the base64 credentials and split on ':'
        secret = b64decode(encoded).decode('utf-8')
        username, password = secret.split(':', 1)[0], secret.split(':', 1)[1]
        return True if (username == self.username and password == self.password) else False


def run_server(host, port, username, password):
    # create the secure server
    server = SecureXMLRPCServer(host, port, username, password)

    def echo(msg):
        """Reply client in upper case"""
        reply = msg.upper()
        print("Client said: %s. So we echo that in uppercase: %s" % (msg, reply))
        return reply

    # register the echo function
    server.register_function(echo, 'echo')
    print("Running a HTTP auth enabled XMLRPC server on %s:%s..." % (host, port))
    # start serving
    server.serve_forever()


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestSecureXMLRPCServer(unittest.TestCase):

    @patch('__main__.SimpleXMLRPCServer.__init__', return_value=None)
    def test_authenticate_invalid(self, mock_init):
        # Build a server instance without binding a real socket
        server = SecureXMLRPCServer('localhost', 8000, 'user', 'pass')

        # Mock headers with wrong password (base64 of 'user:wrong')
        mock_headers = MagicMock()
        mock_headers.get.return_value = 'Basic dXNlcjp3cm9uZw=='

        result = server.authenticate(mock_headers)
        assert_equal(result, False)

    @patch('__main__.SimpleXMLRPCServer.__init__', return_value=None)
    def test_authenticate_valid(self, mock_init):
        # Build a server instance without binding a real socket
        server = SecureXMLRPCServer('localhost', 8000, 'user', 'pass')

        # Mock headers with correct credentials (base64 of 'user:pass')
        mock_headers = MagicMock()
        mock_headers.get.return_value = 'Basic dXNlcjpwYXNz'

        result = server.authenticate(mock_headers)
        assert_equal(result, True)

    @patch('__main__.SecureXMLRPCServer')
    def test_run_server(self, mock_server_cls):
        mock_server = MagicMock()
        mock_server_cls.return_value = mock_server

        run_server('localhost', 8000, 'user', 'pass')

        # Verify SecureXMLRPCServer was created with the correct parameters
        mock_server_cls.assert_called_with('localhost', 8000, 'user', 'pass')
        print(f"mock_server_cls.call_args: {mock_server_cls.call_args}")

        # Verify register_function was called and the registered name is 'echo'
        mock_server.register_function.assert_called_once()
        args, kwargs = mock_server.register_function.call_args
        print(f"registered function name: {args[1]}")

        # Verify serve_forever was called
        mock_server.serve_forever.assert_called_once()


if __name__ == '__main__':
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
