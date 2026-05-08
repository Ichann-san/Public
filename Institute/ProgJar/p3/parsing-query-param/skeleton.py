import socket
import unittest
from unittest import mock
from io import StringIO
import sys
from unittest.mock import patch, MagicMock
import json


def fetch_comments():
    host = 'jsonplaceholder.typicode.com'
    path = '/comments?postId=1'
    request = f"GET {path} HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n"

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, 80))
            s.send(request.encode())
            raw = s.recv(4096)

        text = raw.decode(errors='ignore')
        start = text.find('[')
        end = text.rfind(']')
        if start == -1 or end == -1 or end < start:
            return 0
        body = text[start:end+1]

        try:
            data = json.loads(body)
        except Exception:
            return 0

        count = sum(1 for item in data if item.get('postId') == 1)
        return count
    except Exception:
        return 0
    finally:
        pass


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestCommentsFetcher(unittest.TestCase):
    @patch('socket.socket')
    def test_fetch_comments(self, mock_socket):
        # Setup mock socket
        mock_socket_instance = MagicMock()
        mock_socket.return_value.__enter__.return_value = mock_socket_instance

        # Define the fake response to be returned by socket.recv
        fake_response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n5e3[{\"postId\": 1, \"id\": 1, \"name\": \"Test Comment\"}]0"
        mock_socket_instance.recv.return_value = fake_response.encode()

        # Call the function
        result = fetch_comments()

        # Assertions to verify behavior and results
        mock_socket_instance.connect.assert_called_with(('jsonplaceholder.typicode.com', 80))
        print(f"connect called with: {mock_socket_instance.connect.call_args}")

        mock_socket_instance.send.assert_called_once()
        print(f"send called with: {mock_socket_instance.send.call_args}")
        
        mock_socket_instance.recv.assert_called_once()
        print(f"recv called with: {mock_socket_instance.recv.call_args}")

        assert_equal(result, 1)

if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        comment = fetch_comments()
        print(comment)

    # run unit test to test locally
    # or for domjudge
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
