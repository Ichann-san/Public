import socket
import sys
import unittest
from io import StringIO
from unittest.mock import MagicMock, patch




def build_request(method: str, path: str, host: str, headers: dict, body: str = '') -> bytes:
    lines = [f"{method} {path} HTTP/1.1", f"Host: {host}"]
    for key, value in headers.items():
        lines.append(f"{key}: {value}")

    request_text = "\r\n".join(lines) + "\r\n\r\n" + body
    return request_text.encode("utf-8")

def send_request() -> str:
    request = build_request(
        "GET",
        "/get",
        "httpbin.org",
        {"Accept": "application/json", "Connection": "close"},
    )

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(("httpbin.org", 80))
        sock.send(request)
        response = sock.recv(4096)

    response_text = response.decode("utf-8", errors="replace")
    parts = response_text.split("\r\n\r\n", 1)
    return parts[1] if len(parts) == 2 else ""

class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestBuildRequest(unittest.TestCase):
    def test_build_request(self):
        print('Testing build_request ...')
        result = build_request('GET', '/test', 'example.com', {'Accept': 'text/html'})
        expected = b'GET /test HTTP/1.1\r\nHost: example.com\r\nAccept: text/html\r\n\r\n'
        assert_equal(result, expected)

    @patch('socket.socket')
    def test_send_request(self, mock_socket):
        print('Testing send_request ...')
        mock_sock_instance = MagicMock()
        mock_socket.return_value.__enter__.return_value = mock_sock_instance
        mock_sock_instance.recv.return_value = b'HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\nmock response body'

        result = send_request()

        mock_sock_instance.connect.assert_called_with(('httpbin.org', 80))
        print(f"connect called with: {mock_sock_instance.connect.call_args}")

        mock_sock_instance.send.assert_called_once()
        print(f"send called with: {mock_sock_instance.send.call_args}")

        mock_sock_instance.recv.assert_called_once()
        print(f"recv called with: {mock_sock_instance.recv.call_args}")

        assert_equal(result, 'mock response body')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        body = send_request()
        print(body)

    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
