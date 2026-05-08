import json
import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch




def post_json() -> str:
    body = json.dumps({"username": "alice", "score": 95})
    body_bytes = body.encode("utf-8")
    request = ( 
        "POST /post HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Content-Type: application/json\r\n"
        f"Content-Length: {len(body_bytes)}\r\n"
        "Connection: close\r\n"
        "\r\n"
    ).encode("utf-8") + body_bytes

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(("httpbin.org", 80))
        sock.send(request)
        response = sock.recv(4096)

    response_text = response.decode("utf-8", errors="replace")
    if "\r\n\r\n" in response_text:
        return response_text.split("\r\n\r\n", 1)[1]
    return ""

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestPostJsonSocket(unittest.TestCase):
    @patch('socket.socket')
    def test_post_json(self, mock_socket):
        print('Testing post_json ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value.__enter__.return_value = mock_sock_instance
        mock_sock_instance.recv.return_value = b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\nmock response body'

        result = post_json()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called_once()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 'mock response body')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        body = post_json()
        print(body)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
